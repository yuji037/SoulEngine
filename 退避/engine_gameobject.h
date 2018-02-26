#pragma once
#include "engine_transform.h"
#include <memory>

// ëOï˚êÈåæ
class Sprite;
typedef std::shared_ptr< Sprite > SpriteSP;

class AnimController;
typedef std::shared_ptr<AnimController> AnimControllerSP;

class Camera;
typedef std::shared_ptr< Camera > CameraSP;

class Collider;
typedef std::shared_ptr<Collider> ColliderSP;

class Rigidbody;
typedef std::shared_ptr<Rigidbody> RigidbodySP;

class GameObject;
typedef std::shared_ptr< GameObject > GameObjectSP;
typedef std::weak_ptr< GameObject > GameObjectWP;

class GameObject : public Translation {
protected:
	GameObject(t2k::vec3 _pos = t2k::vec3(0, 0, 0), float _scale = 1, float _rotation = 0) 
		: Translation(_pos, _scale, _rotation), Layer(0) {
		rogic_priority = 0;
		render_priority = 0;
		isAlive = true;
	}

	bool isAlive;
	int rogic_priority;
	int render_priority;

public:

	int Layer;
	inline bool IsAlive( ) { return isAlive; }
	inline void SetLife( bool _isAlive ) { isAlive = _isAlive; }
	virtual ~GameObject( ) {}

	static bool RogicCompare( GameObjectSP g1, GameObjectSP g2){ return ( g1->rogic_priority < g2->rogic_priority ); }
	static bool RenderCompare( GameObjectSP g1, GameObjectSP g2 ) { return ( g1->render_priority < g2->render_priority ); }

	inline void SetRogicPriority( int num ) { rogic_priority = num; }
	inline void SetRenderPriority( int num ) { render_priority = num; }

	inline int GetRogicPriority( ){ return rogic_priority; }
	inline int GetRenderPriority( ){ return render_priority; }

	virtual void Update( ) {}
	virtual void Render( CameraSP cam ) {}
	virtual void OnCollision(){}
};
