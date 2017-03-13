#ifndef SFENGINE_LIGHT_OBJECT_H
#define SFENGINE_LIGHT_OBJECT_H


#include "../Level/LevelObject.h"

#include "../Utils/Vec.hpp"
#include "GlobalLightSource.h"

namespace Engine
{
	struct Edge
	{
		sf::Vector2f Start;
		sf::Vector2f End;

		//Polar form
		float r = 0.f;
		float mag = 0.f;
	};

	struct light_stc_data_type
	{
		sf::Glsl::Vec4 light_color;
		sf::Glsl::Vec2 light_position;
		float light_attenuation;
		float light_intensity;
	};

	struct edge_data_type
	{
		sf::Glsl::Vec4 *Edges;
	};

	struct shadow_caster_data_type
	{
		sf::Glsl::Vec2 EdgeStart;
		sf::Glsl::Vec2 EdgeEnd;
	};

	class Light {
	public:
		Light() = default;
		Light(const Light &other)
			:
			Position(other.Position),
			Radius(other.Radius),
			Color(other.Color),
			Expand(other.Expand),
      Attenuation(other.Attenuation),
      Intensity(other.Intensity),
      CastSoftShadow(other.CastSoftShadow),
      ID(GenerateID())
		{}
		float Attenuation = 0.f;
		sf::Vector2f Position;
		float Radius = 0.f;
		sf::Color Color;
		float Expand = 0.f;
		std::uint32_t ID = 0;
		float Intensity = 1.f;
		sf::CircleShape Circle;
    bool CastSoftShadow = false;
		sf::VertexArray LightVerts;
		sf::VertexArray Shadowverts;
	};

	struct LightObject {
		std::vector<Edge> Edges;
    std::uint32_t ID;
    sf::FloatRect Bounds;

    sf::FloatRect GetGlobalBounds() const {
      return Bounds;
    }
	};
}
#endif
