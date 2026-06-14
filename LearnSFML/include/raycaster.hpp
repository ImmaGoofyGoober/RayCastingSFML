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
	float rayLength_{};
	sf::Color rayColor_{};

public:
	RayCaster(float raySourceRadius, sf::Vector2f position, sf::Color raySourceColor, size_t vertexCount, float rayLength, sf::Color rayColor)
		: raySource_(raySourceRadius),
		raySourceRadius_(raySourceRadius),
		rayVertices_(sf::PrimitiveType::Lines, vertexCount),
		vertexCount_(vertexCount),
		rayLength_(rayLength),
		rayColor_(rayColor)
	{
		raySource_.setPosition(position);
		raySource_.setOrigin({ raySourceRadius, raySourceRadius });
		raySource_.setFillColor(raySourceColor);

		UpdateRayPositions();
	}

	class Build {
	private:
		float raySourceRadius_{};
		sf::Vector2f position_{};
		sf::Color raySourceColor_{};
		size_t vertexCount_{};
		float rayDistance_{};
		float rayLength_{};
		sf::Color rayColor_{};

	public:
		Build& RaySourceRadius(float raySourceRadius) { raySourceRadius_ = raySourceRadius; return *this; };
		Build& Position(const sf::Vector2f position) { position_ = position; return *this; };
		Build& RaySourceColor(const sf::Color raySourceColor) { raySourceColor_ = raySourceColor; return *this; };
		Build& VertexCount(size_t vertexCount) { vertexCount_ = vertexCount; return *this; };
		Build& RayLength(float rayLength) { rayLength_ = rayLength; return *this; };
		Build& RayColor(const sf::Color rayColor) { rayColor_ = rayColor; return *this; };

		RayCaster build() { return RayCaster(raySourceRadius_, position_, raySourceColor_, vertexCount_, rayLength_, rayColor_); };
	};

	// RaySource
	const sf::Drawable& GetRaySource() const;
    float GetRaySourceRadius() const;
	sf::Vector2f GetRaySourcePosition() const;
	void UpdateRaySource(const sf::Vector2f mousePosition);

	//Ray
	const sf::Drawable& GetRayVertices() const;
	void UpdateRayPositions();
	void UpdateRayCollisions(const std::vector<std::unique_ptr<SceneObject>>& sceneObjects);

};

#endif 
