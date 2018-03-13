#include "DXUT.h"
#include "mesh_renderer.h"
#include "../../library/lib_render_polygon.h"

MeshRenderer::~MeshRenderer() {
	mesh->shouldDelete = true;
}