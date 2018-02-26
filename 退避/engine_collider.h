#pragma once
#include <memory>
#include "../support/vec3.h"

class Collider;
typedef std::shared_ptr<Collider> ColliderSP;

class GameObject;
typedef std::shared_ptr<GameObject> GameObjectSP;
typedef std::weak_ptr<GameObject> GameObjectWP;

class Sprite;

class Rigidbody;
typedef std::shared_ptr<Rigidbody> RigidbodySP;


//class Collider {
//public:
//	enum Type {
//		Sphere,
//		Box
//	};
//	Type type;
//
//	Vector3 centerPos;
//	
//	union Info
//	{
//		float radius;
//		BoxShape boxShape;
//		Info() {}
//	};
//	Info info;
//
//	Collider(Type _type) :
//		type(_type),
//		centerPos(0, 0, 0)
//	{
//		switch (_type) {
//		case Type::Sphere:
//			info.radius = 1;
//			break;
//		case Type::Box:
//			info.boxShape.half_width = 0.5f;
//			info.boxShape.half_height = 0.5f;
//			info.boxShape.half_depth = 0.5f;
//			break;
//		}
//	}
//};


class Collider {
public:
	enum Type {
		NONE,
		RECT,
		SLOPE,
		THROUGH_BRIDGE
	};
private:
	Type type = Type::NONE;
public:
	GameObjectWP base;
	t2k::vec3 pos;
	int width;
	int height;
	t2k::vec3 floorL;
	t2k::vec3 floorR;
	// 衝突相手
	GameObject* object;

	// baseオブジェクトが衝突によって動くかどうか
	bool baseCollisionMove;
	// すり抜けるかどうか
	bool isTrigger;
	// 衝突イベントがあるか
	bool isEventOnCollision;
	RigidbodySP rigidbody;

	static ColliderSP Create(GameObjectSP _base, Type _type, t2k::vec3 _floorL = t2k::vec3(0, 0, 0), t2k::vec3 _floorR = t2k::vec3(0, 0, 0));
	// 画像から幅・高さを取得
	void SetSpriteRect(Sprite* _sprite);

	inline GameObjectSP GetBase() { return base.lock(); }
	inline Type GetType() { return type; }

	enum OSU {
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	static t2k::vec3 CollisionRectToRect(ColliderSP me, ColliderSP op);
	static t2k::vec3 ResolvePushVec(ColliderSP me, ColliderSP op, int* osu, int priority);
	//static t2k::vec3 CollisionRectToSlope(ColliderSP me, ColliderSP sl);
	static t2k::vec3 CollisionRectToSlopeY(ColliderSP me, ColliderSP sl);
	static t2k::vec3 CollisionRectToThroughBridge(ColliderSP me, ColliderSP br);

	void Update();
};