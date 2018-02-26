#pragma once
#include <vector>
#include <memory>

class GameObject;
typedef std::shared_ptr<GameObject> GameObjectSP;
typedef std::weak_ptr<GameObject> GameObjectWP;

class AnimController;
typedef std::shared_ptr<AnimController> AnimControllerSP;

class Animation {
public:
	std::vector<float> time;
	std::vector<int> gfx_num;

	Animation(std::vector<float> _time, std::vector<int> _gfx_num) : time(_time), gfx_num(_gfx_num) {}
};


class AnimController {
private:
	std::vector<Animation> animation;
	float time;
	int frame;
	int state = 0;
	int nextState = 0;
	int idleState = 0;
	bool finish;

	int now_gfx_num;

public:

	GameObjectWP base;

	static AnimControllerSP Create(GameObjectSP _base);

	void AddAnimation(const Animation& anim) { animation.push_back(anim); }
	void SetNextState(int _nextState) { 
		nextState = _nextState; 
		if (state == idleState) finish = true;
	}
	void SetIdleNum(int num) { idleState = num; }
	void Switch() { finish = true; }
	int GetFrame() { return frame; }
	void NextFrame() { frame++; time = 0; }
	int GetNowGfxNum(){ return now_gfx_num; }
	int GetState() { return state; }
	void Reset() { frame = 0; time = 0; now_gfx_num = 0;finish = false; }

	void Update();
};