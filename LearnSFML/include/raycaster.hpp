#ifndef RAYCASTER_HPP
#define RAYCASTER_HPP

#include <memory>
#include <vector>

#include <SFML/System/Vector2.hpp>
#include<SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "scene.hpp"

class Raycaster {
private:
	// RaySource
	sf::CircleShape raySource{};
	static constexpr float raySourceRadius{ 35.f };

	// Ray
	sf::VertexArray rayVertices{};
	static constexpr size_t rayCount{ 2 };
	static constexpr float rayDistance{ raySourceRadius }; // Distance from center of raySource
	static constexpr float rayLength{ 300.f };

public:
	Raycaster(sf::Vector2u windowSize) : raySource(raySourceRadius), rayVertices(sf::PrimitiveType::Lines, rayCount) {
		raySource.setFillColor(sf::Color::Yellow);
		raySource.setOrigin({ raySource.getRadius(), raySource.getRadius() });
		raySource.setPosition({ windowSize.x / 2.f, windowSize.y / 2.f });

		UpateRayPositions();
	}

	// RaySource
	const sf::Drawable& GetRaySource() const;
	void UpdateRaySource(const sf::Vector2f mousePosition);
	sf::Vector2f GetRaySourcePosition();

	//Ray
	const sf::Drawable& GetRayVertices() const;
	void UpateRayPositions();
	void UpdateRayCollisions(const std::vector<std::unique_ptr<SceneObject>>& sceneObjects);

};

#endif 

// make ray source orbit static circle
// allow for rays to collide with other rays
// right click to move static circle, left click to move ray source (only move circle the mouse is hovering over)
// Pass reference to scene into updateRays() function to calculate collision with ray's and objects