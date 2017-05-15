#include "VertexClass.h"



VertexClass::VertexClass(float x, float y, float z, float nx, float ny, float nz, float tx, float ty, float r, float g, float b, float alpha)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->normalx = nx;
	this->normaly = ny;
	this->normalz = nz;
	this->texcoordx = tx;
	this->texcoordy = ty;
	this->rColor = r;
	this->gColor = g;
	this->bColor = b;
	this->alpha = alpha;
}


VertexClass::~VertexClass()
{
}
