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
	static constexpr float raySourceRadius_{ 35.f };

	// Ray
	sf::VertexArray rayVertices_{};
	static constexpr size_t rayCount_{ 6 }; // Represents vertex count, every two vertices is one ray
	static constexpr float rayDistance_{ raySourceRadius_ }; // Distance from center of raySource
	static constexpr float rayLength_{ 300.f };

public:
	RayCaster(sf::Vector2u windowSize) : raySource_(raySourceRadius_), rayVertices_(sf::PrimitiveType::Lines, rayCount_) {
		raySource_.setFillColor(sf::Color::Yellow);
		raySource_.setOrigin({ raySource_.getRadius(), raySource_.getRadius() });
		raySource_.setPosition({ windowSize.x / 2.f, windowSize.y / 2.f });

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
