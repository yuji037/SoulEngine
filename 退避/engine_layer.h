#pragma once

class CollisionLayer {

	static const int MAX_LAYER = 10;
	static bool collisionTable[MAX_LAYER][MAX_LAYER];

public:
	static void Init();

	static void SetCanHit(int n1, int n2, bool value) {
		collisionTable[n1][n2] = value;
		collisionTable[n2][n1] = value;
	}
	static bool IsCanHit(int n1, int n2) {
		return collisionTable[n1][n2];
	}
};