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

// ��`���m�̏Փ˔���

t2k::vec3 Collider::CollisionRectToRect(ColliderSP me, ColliderSP op) {
	t2k::vec3 push(0, 0, 0);
	me->object = nullptr;
	op->object = nullptr;
	// ���ƍ�������A�������Ă邩����
	if (!HitRect(me->pos, (me->width >> 1), (me->height >> 1), op->pos, (op->width >> 1), (op->height >> 1)))return push;
	// ���������ĂȂ�

	float deltaTime = Time::GetInstance()->deltaTime;

	// ���������Ă�
	if (!me->rigidbody)return push;
	// ���蔲���鑊��Ȃ�Փ˃C�x���g�̂�
	if (op->isTrigger) {

		//me->object = op->base._Get();
		//op->object = me->base._Get();

		// �Փ˃C�x���g
		//me->base._Get()->OnCollision();
		//op->base._Get()->OnCollision();
		return push;
	}
	// me �̑��x
	t2k::vec3 meV = me->rigidbody->velocity;

	// ���ׂ�ׂ����_�p�̓񕪐��̖@���x�N�g���̐錾
	t2k::vec3 searchNormalV;
	// �ʒu�֌W�𒲂ׂ�
	t2k::vec3 dis = me->pos - op->pos;

	// ��ӂɋ߂��Ȃ璅�n���t���OON
	if (dis.y < (float)(op->height>>1) * -0.9f) {
		me->rigidbody->isOnGround = true;
	}
	// ���ӂɋ߂��Ȃ璅�n���t���OON
	bool ceiling = false;
	if (dis.y > (float)(op->height >> 1) * 0.9f) {
		ceiling = true;
	}

	int osu[4] = { 0 };
	if (dis.x > 0) {
		if (dis.y <= 0) {
			// �ʒu�֌W�F�E��
			// �@���x�N�g�������͉E��
			searchNormalV = t2k::vec3(1, 1, 0);
			osu[UP] = osu[RIGHT] = 1;
		}
		else {
			// �ʒu�֌W�F�E��
			// �@���x�N�g�������͍���
			searchNormalV = t2k::vec3(-1, 1, 0);
			osu[RIGHT] = osu[DOWN] = 1;
		}
	}
	else {
		if (dis.y > 0) {
			// �ʒu�֌W�F����
			// �@���x�N�g�������͍���
			searchNormalV = t2k::vec3(-1, -1, 0);
			osu[DOWN] = osu[LEFT] = 1;
		}
		else {
			// �ʒu�֌W�F����
			// �@���x�N�g�������͉E��
			searchNormalV = t2k::vec3(1, -1, 0);
			osu[LEFT] = osu[UP] = 1;
		}
	}
	// ���n���͉������̑��x���󂯂Ă邱�Ƃɂ��Ȃ��ƒn�ʂ�����Ȃ�
	if (me->rigidbody->isOnGround) {
		meV.y = 500;
	}
	if (ceiling) {
		meV.y = -510;
	}
	// meV �Ƃ̓��ς��o��
	float dot = t2k::vec3Dot(meV, searchNormalV);

	// ���ς����Ȃ甽���v���̖ʂ���̉����o����D��
	if (dis.x > 0) {
		if (dis.y <= 0) {
			// �ʒu�֌W�F�E��
			if (dot > 0) osu[UP]++;
			else osu[RIGHT]++;
		}
		else {
			// �ʒu�֌W�F�E��
			if (dot > 0) osu[RIGHT]++;
			else osu[DOWN]++;
		}
	}
	else {
		if (dis.y > 0) {
			// �ʒu�֌W�F����
			if (dot > 0) osu[DOWN]++;
			else osu[LEFT]++;
		}
		else {
			// �ʒu�֌W�F����
			if (dot > 0) osu[LEFT]++;
			else osu[UP]++;
		}
	}
	// ���̉����o����A���̃`�b�v�ɓ������ĂȂ����OK
	t2k::vec3 push1;
	t2k::vec3 push2;
	push1 = ResolvePushVec(me, op, osu, 2);
	// ������
	me->pos += push1;
	GameEngine* ge = GameEngine::GetInstance();
	if (ge->CollisionToAllCheck(me)) {
		// �܂��������Ă�̂Ŏ����
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
		// ��։���
		me->rigidbody->isOnGround = true;
		if (me->rigidbody->velocity.y > 0) me->rigidbody->velocity.y = 0;
		
		push.y += 2;
	}
	
	if (push.y > 0){
		// ���։���
		//DrawStringEx(100, 340, 0xffffffff, "���� %d", osu[DOWN]);
		if (me->rigidbody->velocity.y < 0) me->rigidbody->velocity.y = 0;
		push.y -= 2;
	}
	// ���E�ǂ��炩�ɓ������Ă�
	if (push.x < 0) {
		// ���։���
		//DrawStringEx(100, 370, 0xffffffff, "���� %d", osu[LEFT]);
		if(me->rigidbody->velocity.x > 0) me->rigidbody->velocity.x = 0;
		push.x -= 1;
	}
	if (push.x > 0){
		// �E�։���
		//DrawStringEx(100, 400, 0xffffffff, "�E�� %d", osu[RIGHT]);
		if (me->rigidbody->velocity.x < 0) me->rigidbody->velocity.x = 0;
		push.x += 1;
	}
	//push.x *= 0.5f;

	//me->object = op->base._Get();
	//op->object = me->base._Get();

	// �Փ˃C�x���g
	//me->base._Get()->OnCollision();
	//op->base._Get()->OnCollision();
	return push;
}

// �w�肵���D��x�ɉ����ĉ����ׂ��x�N�g�����v�Z����
t2k::vec3 Collider::ResolvePushVec(ColliderSP me, ColliderSP op,int* osu, int priority) {
	t2k::vec3 push(0, 0, 0);
	// �����o�������̏���l
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
	//DebugTrace("����\n");
	return push;
}

// �L�����ƎΖʂ̏Փ˔���
// �i�L�����̕����l������j
// �i�����o����Y�����݂̂Ȃ̂Ō����ł͂Ȃ��j
t2k::vec3 Collider::CollisionRectToSlopeY(ColliderSP me, ColliderSP sl) {
	float deltaTime = Time::GetInstance()->deltaTime;
	// �Փˑ������x�Y���
	me->object = nullptr;
	sl->object = nullptr;
	t2k::vec3 push(0, 0, 0);

	t2k::vec3 top = me->pos;
	t2k::vec3 btm = me->pos;
	top.y -= (me->height >> 1);
	btm.y += (me->height >> 1);


	t2k::vec3 sL = sl->pos + sl->floorL;
	t2k::vec3 sR = sl->pos + sl->floorR;

	// �L�����̕����l������ꍇ�i�E�オ���ŃL�����̉E�[�ɂȂ�j
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
		// ��_�����߂�
		// �⓹�̕��̂�����_�͂ǂ̊����̈ʒu��
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
		// �Փˑ�����o����
		//me->object = sl->base._Get();
		//sl->object = me->base._Get();

		// �Փ˃C�x���g
		//me->base._Get()->OnCollision();
		//sl->base._Get()->OnCollision();
	}


	return push;
}

t2k::vec3 Collider::CollisionRectToThroughBridge(ColliderSP me, ColliderSP br) {
	t2k::vec3 push;

	me->object = nullptr;
	br->object = nullptr;
	// ���ƍ�������A�������Ă邩����
	if (!HitRect(me->pos, (me->width >> 1), (me->height >> 1), br->pos, (br->width >> 1), (br->height >> 1)))return push;
	// ���������ĂȂ�

	float deltaTime = Time::GetInstance()->deltaTime;
	
	// ���������Ă���
	t2k::vec3 meV = me->rigidbody->velocity;
	// me ��1�t���[���O�̈ʒu
	t2k::vec3 mePrePos = me->pos - meV * deltaTime;
	// me ��1�t���[���O�� br�̏�[��艺�ɋ���΂΃��^�[��
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


//// �L�����ƎΖʂ̏Փ˔���
//// �i�L�����̕����l���������S��Y���Ŕ��肵�Ă���j
//// �i�Ζʂ̖@�������ɉ����o�������o�[�W�����j
//// ����͎g��Ȃ�
//t2k::vec3 Collider::CollisionRectToSlope(ColliderSP me, ColliderSP sl) {
//	float deltaTime = Time::GetInstance()->deltaTime;
//	// �Փˑ������x�Y���
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
//		// ��_�����߂�
//		// �⓹�̕��̂�����_�͂ǂ̊����̈ʒu��
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
//		// �Փˑ�����o����
//		me->object = sl->base._Get();
//		sl->object = me->base._Get();
//
//		// �Փ˃C�x���g
//		me->base._Get()->OnCollision();
//		sl->base._Get()->OnCollision();
//	}
//
//
//	return push;
//}