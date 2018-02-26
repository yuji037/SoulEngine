#include "DXUT.h"
#include "engine_layer.h"
#include "../support/t2k_support.h"

bool CollisionLayer::collisionTable[CollisionLayer::MAX_LAYER][CollisionLayer::MAX_LAYER];

void CollisionLayer::Init() {
	static bool init = false;
	if (!init) {
		//for (bool b : collisionTable) {
		//	b = true;
		//}
		for (int i = 0; i < MAX_LAYER; ++i) {
			for (int k = 0; k < MAX_LAYER; ++k) {
				collisionTable[i][k] = true;
			}
		}
		init = true;
	}
}