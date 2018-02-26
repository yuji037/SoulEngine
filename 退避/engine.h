#pragma once
#include <map>
#include <list>
#include "engine_gameobject.h"
#include "engine_collider.h"
#include "engine_animation_controller.h"

#define		VIEW_MODE				0
#define		DEBUG					0
#define		DISPLAY_COLLIDER_RECT	0

typedef std::map< std::string, std::list<GameObjectSP> > GameObjectMap;
typedef std::list< GameObjectSP > GameObjectList;
typedef std::list< CameraSP > CameraList;
typedef std::list< ColliderSP > ColliderList;
typedef std::list< AnimControllerSP > AnimControllerList;

class GameEngine {
private:
	GameObjectMap object_map;
	GameObjectList rogic_list;
	GameObjectList render_list;
	CameraList cam_list;
	ColliderList col_list;
	AnimControllerList anim_list;

	bool sceneSwitchInitialized;
	bool addedObject;

	static GameEngine* instance;
	GameEngine( );

public:
	static GameEngine* GetInstance( );

	GameObjectList* getObjects( std::string name );
	GameObjectSP getObject( std::string name, int num = 0);
	CameraSP getCamera( int num = 0 );

	void DeleteBySceneSwitch( );
	void AddObject(std::string name, GameObjectSP obj);
	void RogicSort(){ rogic_list.sort(GameObject::RogicCompare); }
	void RenderSort(){ render_list.sort(GameObject::RenderCompare); }
	void AddCollider( ColliderSP obj );
	void AddAnimCon(AnimControllerSP obj);
	void Update( );
	void Collision();
	bool CollisionToAllCheck(ColliderSP me);
	void UpdateAnimation();
};