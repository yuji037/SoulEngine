#pragma once
#include <memory>

class Rigidbody;
typedef std::shared_ptr<Rigidbody> RigidbodySP;
typedef std::weak_ptr<Rigidbody> RigidbodyWP;

class Rigidbody {
private:

public:
	bool isGravity;
	bool isOnGround;
	float airResist;
	t2k::vec3 velocity;

	Rigidbody(bool _isGravity = true, float _airResist = 0):isGravity(_isGravity), airResist(_airResist) {}

	void Update();
};