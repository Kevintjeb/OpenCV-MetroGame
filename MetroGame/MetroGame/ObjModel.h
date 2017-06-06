#pragma once

#include <string>
#include <vector>
#include <list>
#include "texture.h"
#include <windows.h>
#include <gl/GL.h>
#include "Vect.h"
#include "VertexClass.h"

class ObjModel
{
private:
	class Vertex
	{
	public:
		int position;
		int normal;
		int texcoord; 
	};

	class Face
	{
	public:
		std::list<Vertex> vertices;
	};
	class MaterialInfo
	{
	public:
		MaterialInfo();
		std::string name;
		Texture* texture;
	};

	class ObjGroup
	{
	public:
		std::string name;
		int materialIndex;
		std::list<Face> faces;
		int beginIndex;
		int eindIndex;
	};

	GLuint listID;

	std::vector<GameLogic::Vec3f>	vertices;
	std::vector<GameLogic::Vec3f>	normals;
	std::vector<GameLogic::Vec2f>	texcoords;
	std::vector<ObjGroup*> groups;
	std::vector<MaterialInfo*> materials;
	std::vector<VertexClass> verts;

	void loadMaterialFile(const std::string &fileName, const std::string &dirName);
public:
	ObjModel(const std::string &filename);
	~ObjModel(void);
	void createDisplayList();
	void draw();
};

