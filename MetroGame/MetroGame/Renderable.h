#pragma once

#include "Vect.h"
#include "Model.h"
#include <string>
#include <vector>

namespace mg_gameLogic
{
	class Renderable
	{
	public:
		Vec3f position, rotation, scale;
		float angle;
		std::string model;

		Renderable();
		Renderable(const Renderable&);

		Renderable(Vec3f pos, float angle, Vec3f rot, Vec3f scale = Vec3f(1, 1, 1));
		Renderable(std::string model, Vec3f pos, float angle, Vec3f rot, Vec3f scale = Vec3f(1, 1, 1));
		~Renderable();
	};

	enum class LineType
	{
		Red, Blue, Green, NO_TYPE
	};

	class RenderableLine
	{
	public:
		std::vector<Vec3f> line;
		LineType type;

		RenderableLine();
		RenderableLine(const RenderableLine&);

		explicit RenderableLine(const std::vector<Vec2f>&);
	};
}