#include "ModelLoader.h"



ModelLoader::ModelLoader()
{
}


ModelLoader::~ModelLoader()
{
}

ObjModel * ModelLoader::getModel(int index)
{
	if (models.size() < index) return nullptr;
	return models[index];
}

void ModelLoader::insertModel(std::string pathfile)
{
	models.push_back(new ObjModel(pathfile));
}
