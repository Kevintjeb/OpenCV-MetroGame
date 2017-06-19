#pragma once

#include "Vect.h"
#include <string>
#include <vector>

namespace mg_gameLogic
{
	class Renderable
	{
	public:
		GameLogic::Vec3f position, rotation, scale;
		float angle;
		std::string model;

		Renderable();
		Renderable(const Renderable&);

		Renderable(GameLogic::Vec3f pos, float angle, GameLogic::Vec3f rot, GameLogic::Vec3f scale = GameLogic::Vec3f(1, 1, 1));
		Renderable(std::string model, GameLogic::Vec3f pos, float angle, GameLogic::Vec3f rot, GameLogic::Vec3f scale = GameLogic::Vec3f(1, 1, 1));
		~Renderable();
	};

	enum class LineType
	{
		Red, Blue, Green, NO_TYPE
	};

	class RenderableLine
	{
	public:
		std::vector<GameLogic::Vec3f> line;
		LineType type;

		RenderableLine();
		RenderableLine(const RenderableLine&);

		explicit RenderableLine(const std::vector<GameLogic::Vec2f>&, LineType);
	};
}