#pragma once
#include <vector>
#include "ObjModel.h"
#include <iostream>
#include <string>
#include <map>

class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();
	ObjModel* getModel(int index);
	void insertModel(std::string pathfile);

private:
	std::vector<ObjModel*> models;
};

