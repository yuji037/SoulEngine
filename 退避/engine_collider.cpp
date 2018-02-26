#include "DXUT.h"
#include "engine_collider.h"
#include "engine.h"
#include "engine_rigidbody.h"
#include "engine_gameobject.h"
#include "../library/lib_sprite.h"
#include "../library/lib_utility.h"
#include "../library/lib_time.h"
#include "../library/lib_debug.h"
#include <math.h>

ColliderSP Collider::Create(GameObjectSP _base, Type _type, t2k::vec3 _floorL, t2k::vec3 _floorR) {
	ColliderSP obj = ColliderSP(new Collider());
	obj->base = _base;
	obj->type = _type;
	obj->pos = _base->pos;
	obj->width = 0;
	obj->height = 0;
	obj->floorL = _floorL;
	obj->floorR = _floorR;
	obj->baseCollisionMove = false;
	obj->isTrigger = false;
	obj->isEventOnCollision = false;
	obj->rigidbody = nullptr;

	GameEngine::GetInstance()->AddCollider(obj);

	return obj;
}

void Collider::SetSpriteRect(Sprite* _sprite) {

	width = _sprite->width;
	height = _sprite->height;
	floorL *= width;
	floorR *= height;
}

//enum Collider::OSU {
//	UP,
//	RIGHT,
//	DOWN,
//	LEFT
//};

// 矩形同士の衝突判定

t2k::vec3 Collider::CollisionRectToRect(ColliderSP me, ColliderSP op) {
	t2k::vec3 push(0, 0, 0);
	me->object = nullptr;
	op->object = nullptr;
	// 幅と高さから、当たってるか判定
	if (!HitRect(me->pos, (me->width >> 1), (me->height >> 1), op->pos, (op->width >> 1), (op->height >> 1)))return push;
	// ↑当たってない

	float deltaTime = Time::GetInstance()->deltaTime;

	// ↓当たってる
	if (!me->rigidbody)return push;
	// すり抜ける相手なら衝突イベントのみ
	if (op->isTrigger) {

		//me->object = op->base._Get();
		//op->object = me->base._Get();

		// 衝突イベント
		//me->base._Get()->OnCollision();
		//op->base._Get()->OnCollision();
		return push;
	}
	// me の速度
	t2k::vec3 meV = me->rigidbody->velocity;

	// 調べるべき頂点角の二分線の法線ベクトルの宣言
	t2k::vec3 searchNormalV;
	// 位置関係を調べる
	t2k::vec3 dis = me->pos - op->pos;

	// 上辺に近いなら着地中フラグON
	if (dis.y < (float)(op->height>>1) * -0.9f) {
		me->rigidbody->isOnGround = true;
	}
	// 下辺に近いなら着地中フラグON
	bool ceiling = false;
	if (dis.y > (float)(op->height >> 1) * 0.9f) {
		ceiling = true;
	}

	int osu[4] = { 0 };
	if (dis.x > 0) {
		if (dis.y <= 0) {
			// 位置関係：右上
			// 法線ベクトル向きは右下
			searchNormalV = t2k::vec3(1, 1, 0);
			osu[UP] = osu[RIGHT] = 1;
		}
		else {
			// 位置関係：右下
			// 法線ベクトル向きは左下
			searchNormalV = t2k::vec3(-1, 1, 0);
			osu[RIGHT] = osu[DOWN] = 1;
		}
	}
	else {
		if (dis.y > 0) {
			// 位置関係：左下
			// 法線ベクトル向きは左上
			searchNormalV = t2k::vec3(-1, -1, 0);
			osu[DOWN] = osu[LEFT] = 1;
		}
		else {
			// 位置関係：左上
			// 法線ベクトル向きは右上
			searchNormalV = t2k::vec3(1, -1, 0);
			osu[LEFT] = osu[UP] = 1;
		}
	}
	// 着地中は下方向の速度を受けてることにしないと地面を歩けない
	if (me->rigidbody->isOnGround) {
		meV.y = 500;
	}
	if (ceiling) {
		meV.y = -510;
	}
	// meV との内積を出す
	float dot = t2k::vec3Dot(meV, searchNormalV);

	// 内積が正なら反時計側の面からの押し出しを優先
	if (dis.x > 0) {
		if (dis.y <= 0) {
			// 位置関係：右上
			if (dot > 0) osu[UP]++;
			else osu[RIGHT]++;
		}
		else {
			// 位置関係：右下
			if (dot > 0) osu[RIGHT]++;
			else osu[DOWN]++;
		}
	}
	else {
		if (dis.y > 0) {
			// 位置関係：左下
			if (dot > 0) osu[DOWN]++;
			else osu[LEFT]++;
		}
		else {
			// 位置関係：左上
			if (dot > 0) osu[LEFT]++;
			else osu[UP]++;
		}
	}
	// 仮の押し出し後、他のチップに当たってなければOK
	t2k::vec3 push1;
	t2k::vec3 push2;
	push1 = ResolvePushVec(me, op, osu, 2);
	// 仮押し
	me->pos += push1;
	GameEngine* ge = GameEngine::GetInstance();
	if (ge->CollisionToAllCheck(me)) {
		// まだ当たってるので次候補
		me->pos -= push1;
		push2 = ResolvePushVec(me, op, osu, 1);
		me->pos += push2;
		if (ge->CollisionToAllCheck(me)) {
			me->pos -= push2;
			push = push1 + push2;
			push *= 0.3f;
		}
		else {
			push = push2;
		}
	}
	else {
		push = push1;
	}

	if (push.y < 0) {
		// 上へ押す
		me->rigidbody->isOnGround = true;
		if (me->rigidbody->velocity.y > 0) me->rigidbody->velocity.y = 0;
		
		push.y += 2;
	}
	
	if (push.y > 0){
		// 下へ押す
		//DrawStringEx(100, 340, 0xffffffff, "下へ %d", osu[DOWN]);
		if (me->rigidbody->velocity.y < 0) me->rigidbody->velocity.y = 0;
		push.y -= 2;
	}
	// 左右どちらかに当たってる
	if (push.x < 0) {
		// 左へ押す
		//DrawStringEx(100, 370, 0xffffffff, "左へ %d", osu[LEFT]);
		if(me->rigidbody->velocity.x > 0) me->rigidbody->velocity.x = 0;
		push.x -= 1;
	}
	if (push.x > 0){
		// 右へ押す
		//DrawStringEx(100, 400, 0xffffffff, "右へ %d", osu[RIGHT]);
		if (me->rigidbody->velocity.x < 0) me->rigidbody->velocity.x = 0;
		push.x += 1;
	}
	//push.x *= 0.5f;

	//me->object = op->base._Get();
	//op->object = me->base._Get();

	// 衝突イベント
	//me->base._Get()->OnCollision();
	//op->base._Get()->OnCollision();
	return push;
}

// 指定した優先度に応じて押すべきベクトルを計算する
t2k::vec3 Collider::ResolvePushVec(ColliderSP me, ColliderSP op,int* osu, int priority) {
	t2k::vec3 push(0, 0, 0);
	// 押し出し距離の上限値
	float push_limit = 15;
 	if (osu[UP] == priority) {
		push.y = (op->pos.y - (op->height >> 1)) - (me->pos.y + (me->height >> 1));
		push.y = Clamp(push.y, push_limit, -push_limit);
		osu[UP] = 0;
	}
	else if (osu[RIGHT] == priority) {
		push.x = (op->pos.x + (op->width >> 1)) - (me->pos.x - (me->width >> 1));
		push.x = Clamp(push.x, push_limit, -push_limit);
		osu[RIGHT] = 0;
	}
	else if (osu[DOWN] == priority) {
		push.y = (op->pos.y + (op->height >> 1)) - (me->pos.y - (me->height >> 1));
		push.y = Clamp(push.y, push_limit, -push_limit);
		osu[DOWN] = 0;
	}
	else if (osu[LEFT] == priority) {
		push.x = (op->pos.x - (op->width >> 1)) - (me->pos.x + (me->width >> 1));
		push.x = Clamp(push.x, push_limit, -push_limit);
		osu[LEFT] = 0;
	}
	//DebugTrace("判定\n");
	return push;
}

// キャラと斜面の衝突判定
// （キャラの幅を考慮する）
// （押し出しはY方向のみなので厳密ではない）
t2k::vec3 Collider::CollisionRectToSlopeY(ColliderSP me, ColliderSP sl) {
	float deltaTime = Time::GetInstance()->deltaTime;
	// 衝突相手を一度忘れる
	me->object = nullptr;
	sl->object = nullptr;
	t2k::vec3 push(0, 0, 0);

	t2k::vec3 top = me->pos;
	t2k::vec3 btm = me->pos;
	top.y -= (me->height >> 1);
	btm.y += (me->height >> 1);


	t2k::vec3 sL = sl->pos + sl->floorL;
	t2k::vec3 sR = sl->pos + sl->floorR;

	// キャラの幅を考慮する場合（右上がり坂でキャラの右端になる）
	//if (sL.y > sR.y) {
	//	top.x += (me->width >> 1);
	//	btm.x += (me->width >> 1);
	//}								  
	//else {							  
	//	top.x -= (me->width >> 1);
	//	btm.x -= (me->width >> 1);
	//}

	bool hit = false;

	float rate = 0;
	float crossY = 0;
	if (sL.x <= top.x && top.x <= sR.x) {
		// 交点を求める
		// 坂道の幅のうち交点はどの割合の位置か
		rate = (top.x - sL.x) / (sR.x - sL.x);
		crossY = (sR.y - sL.y) * rate + sL.y;
		if (top.y <= crossY && crossY <= btm.y + 5) {
			hit = true;
		}
	}

	if (hit) {

		push = t2k::vec3(0, crossY - btm.y, 0);

		//push *= 0.9f;

		if (me->rigidbody) {
			me->rigidbody->velocity *= 0.5f;
			me->rigidbody->isOnGround = true;
		}
		//DrawStringEx(100, 150, 0xffffffff, "Hit!");
		// 衝突相手を覚える
		//me->object = sl->base._Get();
		//sl->object = me->base._Get();

		// 衝突イベント
		//me->base._Get()->OnCollision();
		//sl->base._Get()->OnCollision();
	}


	return push;
}

t2k::vec3 Collider::CollisionRectToThroughBridge(ColliderSP me, ColliderSP br) {
	t2k::vec3 push;

	me->object = nullptr;
	br->object = nullptr;
	// 幅と高さから、当たってるか判定
	if (!HitRect(me->pos, (me->width >> 1), (me->height >> 1), br->pos, (br->width >> 1), (br->height >> 1)))return push;
	// ↑当たってない

	float deltaTime = Time::GetInstance()->deltaTime;
	
	// ↓当たっている
	t2k::vec3 meV = me->rigidbody->velocity;
	// me の1フレーム前の位置
	t2k::vec3 mePrePos = me->pos - meV * deltaTime;
	// me の1フレーム前が brの上端より下に居ればばリターン
	float tyotto = 8;
	if (mePrePos.y + (me->height>> 1) > br->pos.y - ((br->height >> 1) - tyotto)) return push;

	push.y = (br->pos.y - (br->height >> 1)) - (me->pos.y + (me->height >> 1));
	push.y += 3;
	me->rigidbody->isOnGround = true;
	if (me->rigidbody->velocity.y > 0)me->rigidbody->velocity.y = 0;

	//me->object = br->base._Get();
	//br->object = me->base._Get();

	return push;
}

void Collider::Update() {
	if (!base.expired()) {
		pos = base.lock()->pos;
	}
}


//// キャラと斜面の衝突判定
//// （キャラの幅を考慮せず中心のY軸で判定している）
//// （斜面の法線方向に押し出す厳密バージョン）
//// 今回は使わない
//t2k::vec3 Collider::CollisionRectToSlope(ColliderSP me, ColliderSP sl) {
//	float deltaTime = Time::GetInstance()->deltaTime;
//	// 衝突相手を一度忘れる
//	me->object = nullptr;
//	sl->object = nullptr;
//	DrawStringEx(100, 200, 0xffffffff, "Collision");
//	t2k::vec3 push(0, 0, 0);
//
//	t2k::vec3 top = me->pos;
//	t2k::vec3 btm = me->pos;
//	top.y -= (me->height >> 1);
//	btm.y += (me->height >> 1);
//
//	t2k::vec3 sL = sl->pos + sl->floorL;
//	t2k::vec3 sR = sl->pos + sl->floorR;
//
//	bool hit = false;
//
//	float rate = 0;
//	float crossY = 0;
//	if (sL.x < top.x && top.x < sR.x) {
//		// 交点を求める
//		// 坂道の幅のうち交点はどの割合の位置か
//		rate = (top.x - sL.x) / (sR.x - sL.x);
//		crossY = (sR.y - sL.y) * rate + sL.y;
//		if (top.y <= crossY && crossY <= btm.y + 5) {
//			hit = true;
//		}
//	}
//
//	if (hit) {
//		t2k::vec3 ppos = (sR - sL) * rate + sL;
//		t2k::vec3 vec = btm - ppos;
//		float rad = vec3Angle(vec, sL - ppos);
//		float mag = vec3Length(vec) * sin(rad);
//		push = sL - sR;
//		push = RotateZ(push, PI_F / 2);
//
//		push = t2k::vec3Normalize(push) * mag;
//
//		if (me->rigidbody) {
//			me->rigidbody->velocity *= 0.5f;
//			me->rigidbody->isOnGround = true;
//		}
//		DrawStringEx(100, 150, 0xffffffff, "Hit!");
//		// 衝突相手を覚える
//		me->object = sl->base._Get();
//		sl->object = me->base._Get();
//
//		// 衝突イベント
//		me->base._Get()->OnCollision();
//		sl->base._Get()->OnCollision();
//	}
//
//
//	return push;
//}