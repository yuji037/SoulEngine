#include "DXUT.h"
#include "engine_transform.h"
#include <memory>
#include "engine.h"
#include "engine_layer.h"
#include "engine_rigidbody.h"
#include "engine_collider.h"
#include "../library/lib_camera.h"
#include "../library/lib_time.h"
#include "../library/lib_debug.h"
#include "../library/lib_utility.h"
#include "../support/vec3.h"

GameEngine* GameEngine::instance = nullptr;

GameEngine* GameEngine::GetInstance( ) {
	if (instance)return instance;
	instance = new GameEngine( );
	return instance;
}

GameEngine::GameEngine( ) {
	// メインカメラ
	CameraSP cam = Camera::Create( );
	cam->setScreenRect( );
	cam_list.push_back( cam );

	CollisionLayer::Init();

	sceneSwitchInitialized = false;
	addedObject = false;
}

void GameEngine::AddObject( std::string name, GameObjectSP obj ) {

	GameObjectMap::iterator it = object_map.find( name );

	// 存在しない
	if (it == object_map.end( )) {
		std::list<GameObjectSP> list;
		list.push_back( obj );
		object_map.insert( std::make_pair( name, list ) );
	}
	else {
		it->second.push_back( obj );
	}

	if (name != "RenderOnlyObject") {
		rogic_list.push_back(obj);
	}
	render_list.push_back( obj );

	addedObject = true;

	////ここに入れるとなぜか止まる
	//if (sceneSwitchInitialized) {
	//	RogicSort();
	//	RenderSort();
	//	addedObject = false;
	//}
}

void GameEngine::AddCollider(ColliderSP obj) {

	col_list.push_back(obj);
}

void GameEngine::AddAnimCon(AnimControllerSP obj) {

	anim_list.push_back(obj);
}

void GameEngine::Update( ) {

	// deltaTime の更新
	Time::GetInstance()->Update();
	Debug::GetInstance()->Update();

	int count = 0;

	// シーン初期化後はオブジェクト追加時のみソート
	if (addedObject && sceneSwitchInitialized) {
		RogicSort();
		RenderSort();
		addedObject = false;
	}

	// シーン初期化時のみソート
	if (!sceneSwitchInitialized) {
		RogicSort();
		RenderSort();
		sceneSwitchInitialized = true;
	}

	// ロジックリスト
	GameObjectList::iterator it = rogic_list.begin( );
	while (it != rogic_list.end( )) {

#if !VIEW_MODE
		( *it )->Update( );
#endif

		// 消滅
		if (!( *it )->IsAlive( )) {
			it = rogic_list.erase( it );
			continue;
		}
		it++;
	}

#if !VIEW_MODE
	// 衝突による判定
	Collision();

#endif
	UpdateAnimation();

	CameraList::iterator cam_it = cam_list.begin( );
	while (cam_it != cam_list.end( )) {
		CameraSP cam = *cam_it;
#if !VIEW_MODE
		cam->Update( );
#endif
		// レンダリングリスト
		it = render_list.begin( );
		while (it != render_list.end( )) {
			( *it )->Render( cam );

			// 消滅
			if (!( *it )->IsAlive( )) {
				it = render_list.erase( it );
				continue;
			}
			it++;
		}

		if (!( *cam_it )->isLife( )) {
			cam_it = cam_list.erase( cam_it );
			continue;
		}
		cam_it++;
	}

	// map
	GameObjectMap::iterator it_map = object_map.begin( );
	while (it_map != object_map.end( )) {
		GameObjectList::iterator it_list = it_map->second.begin( );
		while (it_list != it_map->second.end( )) {
			count++;
			if (!( *it_list )->IsAlive( )) {
				it_list = it_map->second.erase( it_list );
				continue;
			}
			it_list++;
		}

		if (it_map->second.empty( )) {
			it_map = object_map.erase( it_map );
			continue;
		}

		it_map++;
	}

#if DEBUG
	Debug::Log("GameObject = %d", count);
	Debug::Log("deltaTime = %f", Time::GetInstance()->deltaTime);
	Debug::GetInstance()->Render();
#endif
}

void GameEngine::Collision() {
	//float push_strength = 100;
	float deltaTime = Time::GetInstance()->deltaTime;
	int count = 0;

	ColliderList::iterator it = col_list.begin();
	while (it != col_list.end()) {
		++count;

		if ((*it)->base.expired()) {
			it = col_list.erase(it);
			continue;
		}
		(*it)->Update();
		// （自身が）衝突によって何も起きないならスルー
		if (!(*it)->baseCollisionMove && !(*it)->isEventOnCollision) {
			it++;
			continue;
		}

		ColliderList::iterator op_it = col_list.begin();
		while (op_it != col_list.end()) {
			
			if ((*op_it)->base.expired()) {
				op_it = col_list.erase(op_it);
				continue;
			}

			t2k::vec3 push(0, 0, 0);

			if ((*it) == (*op_it)) {
				// 自分なので処理なし
			}

			// Layer設定により当たらないならスルー
			else if (!CollisionLayer::IsCanHit((*it)->GetBase()->Layer, (*op_it)->GetBase()->Layer)) {
				// 処理なし
			}
			else if ((*op_it)->GetType() == Collider::Type::RECT) {
				// 矩形同士の当たり判定
				push = Collider::CollisionRectToRect((*it), (*op_it));
			}
			else if ((*op_it)->GetType() == Collider::Type::SLOPE){
				// 矩形と斜面の当たり判定
				push = Collider::CollisionRectToSlopeY((*it), (*op_it));
			}
			else {
				// 矩形とすり抜ける床の当たり判定
				push = Collider::CollisionRectToThroughBridge((*it), (*op_it));
			}
			// 相手がすり抜けないなら押し出す
			if (!(*op_it)->isTrigger && (*it)->baseCollisionMove) {
				(*it)->GetBase()->pos += push;
				(*it)->pos += push;
			}
			op_it++;
		}

		it++;
	}

	Debug::Log("Collider = %d", count);
}

bool GameEngine::CollisionToAllCheck(ColliderSP me) {
	bool hit = false;
	ColliderList::iterator op_it = col_list.begin();
	while (op_it != col_list.end()) {

		if (me == (*op_it)) {
			// 自分なので処理なし
		}
		else if (!(*op_it)->isTrigger && (*op_it)->GetType() == Collider::Type::RECT) {
			// 矩形同士の当たり判定
			if (HitRect(me->pos, (me->width >> 1), (me->height >> 1), (*op_it)->pos, ((*op_it)->width >> 1), ((*op_it)->height >> 1))) {
				hit = true;
				//return hit;
			}
		}
		//else {
		//	// 矩形と斜面の当たり判定
		//	t2k::vec3 push = Collider::CollisionRectToSlopeY(me, (*op_it));
		//	//push = push * push_strength * deltaTime;
		//	me->GetBase()->pos += push;
		//	me->pos += push;
		//}
		op_it++;
	}
	return hit;
}

void GameEngine::UpdateAnimation() {

	AnimControllerList::iterator it = anim_list.begin();

	while (it != anim_list.end()) {
		if ((*it)->base.expired()) {
			it = anim_list.erase(it);
			continue;
		}
		(*it)->Update();
		it++;
	}
}

GameObjectList* GameEngine::getObjects( std::string name ) {

	GameObjectMap::iterator it = object_map.find( name );

	// 指定したリストが存在しない場合
	if (it == object_map.end( ))return nullptr;

	return &( it->second );
}

GameObjectSP GameEngine::getObject( std::string name, int num) {
	
	GameObjectList* obj_list = getObjects( name );

	// まずリストが有効か
	if (!obj_list)return nullptr;

	// 指定番号のオブジェクトが存在するか
	if (num > obj_list->size( ) - 1) return nullptr;

	// 指定番号のオブジェクトを返す
	GameObjectList::iterator it = obj_list->begin( );

	for (int i = 0; i < num; i++) it++;
	return ( *it );
}

CameraSP GameEngine::getCamera( int num ) {
	CameraList::iterator it = cam_list.begin( );

	for (int i = 0; i < num; i++) it++;
	return ( *it );
}

void GameEngine::DeleteBySceneSwitch( ) {
	GameObjectMap::iterator it_map = object_map.begin( );
	while (it_map != object_map.end( )) {
		// CommonObject はシーンをまたいでも消えない
		if (it_map->first == "CommonObject")continue;

		GameObjectList::iterator it_list = it_map->second.begin( );
		while (it_list != it_map->second.end( )) {

			( *it_list )->SetLife( false );
			it_list++;
		}

		if (it_map->second.empty( )) {
			it_map = object_map.erase( it_map );
			continue;
		}

		it_map++;
	}
	sceneSwitchInitialized = false;
}
