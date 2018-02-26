#pragma once

// Release用とDebug用のライブラリを両方とも同じディレクトリに置いた場合
#ifdef _DEBUG
#define BULLET_STR "_Debug.lib"
#else _REREASE
#define BULLET_STR ".lib"
#endif

// 必要無いものはコメントアウト
#pragma comment(lib,"BulletCollision" BULLET_STR)
#pragma comment(lib,"BulletDynamics" BULLET_STR)
//#pragma comment(lib,"BulletFileLoader" BULLET_STR)
//#pragma comment(lib,"BulletMultiThreaded" BULLET_STR)
//#pragma comment(lib,"BulletSoftBody" BULLET_STR)
//#pragma comment(lib,"BulletSoftBodySolvers_OpenCL_Mini" BULLET_STR)
//#pragma comment(lib,"BulletWorldImporter" BULLET_STR)
//#pragma comment(lib,"BulletXmlWorldImporter" BULLET_STR)
//#pragma comment(lib,"ConvexDecomposition" BULLET_STR)
//#pragma comment(lib,"GIMPACTUtils" BULLET_STR)
//#pragma comment(lib,"GLUI" BULLET_STR)
//#pragma comment(lib,"HACD" BULLET_STR)
#pragma comment(lib,"LinearMath" BULLET_STR)
//#pragma comment(lib,"MiniCL" BULLET_STR)
//#pragma comment(lib,"OpenGLSupport" BULLET_STR)