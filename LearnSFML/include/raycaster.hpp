#ifndef RAYCASTER_RAYCASTER_HPP
#define RAYCASTER_RAYCASTER_HPP

#include <memory>
#include <vector>

#include <SFML/System/Vector2.hpp>
#include<SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "scene.hpp"

class RayCaster {
private:
	// RaySource
	sf::CircleShape raySource_{};
	float raySourceRadius_{};

	// Ray
	sf::VertexArray rayVertices_{};
	size_t vertexCount_{};
	float rayDistance_{}; // Distance from center of raySource
	float rayLength_{};
	sf::Color rayColor_{};

public:
	RayCaster(float raySourceRadius, float rayLength, size_t vertexCount, sf::Vector2f position, sf::Color raySourceColor, sf::Color rayColor)
		: raySource_(raySourceRadius), 
		raySourceRadius_(raySourceRadius), 
		rayVertices_(sf::PrimitiveType::Lines, vertexCount), 
		vertexCount_(vertexCount), 
		rayDistance_(raySourceRadius),
		rayLength_(rayLength),
		rayColor_(rayColor)
	{
		raySource_.setFillColor(raySourceColor);
		raySource_.setOrigin({ raySource_.getRadius(), raySource_.getRadius() });
		raySource_.setPosition(position);

		UpdateRayPositions();
	}

	// RaySource
	const sf::Drawable& GetRaySource() const;
	void UpdateRaySource(const sf::Vector2f mousePosition);
	sf::Vector2f GetRaySourcePosition();

	//Ray
	const sf::Drawable& GetRayVertices() const;
	void UpdateRayPositions();
	void UpdateRayCollisions(const std::vector<std::unique_ptr<SceneObject>>& sceneObjects);

};

#endif 
