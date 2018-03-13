#include "DXUT.h"
#include "image.h"
#include "../../library/lib_render_polygon.h"

Image::~Image() {
	mesh->shouldDelete = true;
}