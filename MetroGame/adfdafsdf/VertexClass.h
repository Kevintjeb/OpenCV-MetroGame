#pragma once
class VertexClass
{
public:
	float x;
	float y;
	float z;
	float normalx;
	float normaly;
	float normalz;
	float texcoordx;
	float texcoordy;
	float rColor;
	float gColor;
	float bColor;
	float alpha;
	VertexClass(float x, float y, float z, float nx, float ny, float nz, float tx, float ty, float r, float g, float b, float alpha);
	VertexClass();
	~VertexClass();
};

