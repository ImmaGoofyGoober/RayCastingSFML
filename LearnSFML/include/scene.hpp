#ifndef RAYCASTER_SCENE_HPP
#define RAYCASTER_SCENE_HPP

#include <SFML/System/Vector2.hpp>
#include<SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

enum struct ShapeType {
	CIRCLE,
	SQUARE
};

// Scene Objects
class SceneObject {
private:

public:
	// Getter Functions
	virtual const sf::Drawable& GetShape() const = 0;
	virtual ShapeType GetShapeType() const = 0;
	virtual sf::Vector2f GetPosition() const = 0;
	virtual float GetRayCollisionDistance(const sf::Vector2f& rayOrigin, const sf::Vector2f& rayDirection, float rayLength) const = 0;

	// Setter Functions
	virtual void SetPosition(const sf::Vector2f& position, const sf::Vector2f& orbitPosition, float deltaTime) = 0;

	virtual ~SceneObject() = default;
};

// Circle
class Circle : public SceneObject{
private:
	sf::CircleShape circle_{};
	ShapeType shapeType_{ ShapeType::CIRCLE };
	const float radius_{};
	sf::Color color_{};

	const bool isOrbiting_{ false };
	const float orbitDistance_{};
	float orbitAngle_{};
	const float orbitSpeed_{};

	bool isMoving_{ false };

public:
	Circle(float radius, sf::Vector2f position, sf::Color color, bool isOrbiting, float orbitDistance, float orbitAngle, float orbitSpeed, bool isMoving)
		: circle_(radius),
		radius_(radius),
		color_(color),
		isOrbiting_(isOrbiting),
		orbitDistance_(orbitDistance),
		orbitAngle_(orbitAngle),
		orbitSpeed_(orbitSpeed),
		isMoving_(isMoving)
	{
		circle_.setPosition(position);
		circle_.setOrigin({ radius, radius });
		circle_.setFillColor(color);
	}

	class Build {
	private:
		float radius_{};
		sf::Color color_{};
		sf::Vector2f position_{};
		bool isOrbiting_{ false };
		float orbitDistance_{};
		float orbitAngle_{};
		float orbitSpeed_{};
		bool isMoving_{ false };

	public:
		Build& Radius(float radius) { radius_ = radius; return *this; };
		Build& Position(const sf::Vector2f position) { position_ = position; return *this; };
		Build& Color(const sf::Color color) { color_ = color; return *this; };
		Build& IsOrbiting(bool isOrbiting) { isOrbiting_ = isOrbiting; return *this; };
		Build& OrbitDistance(float orbitDistance) { orbitDistance_ = orbitDistance; return *this; };
		Build& OrbitAngle(float orbitAngle) { orbitAngle_ = orbitAngle; return *this; };
		Build& OrbitSpeed(float orbitSpeed) { orbitSpeed_ = orbitSpeed; return *this; };
		Build& IsMoving(bool isMoving) { isMoving_ = isMoving; return *this; };

		Circle build() { return Circle(radius_, position_, color_, isOrbiting_, orbitDistance_, orbitAngle_, orbitSpeed_, isMoving_); };
	};

	// Getter Functions
	const sf::Drawable& GetShape() const override;
	ShapeType GetShapeType() const override;
	sf::Vector2f GetPosition() const override;
	float GetRayCollisionDistance(const sf::Vector2f& rayOrigin, const sf::Vector2f& rayDirection, float rayLength) const override;
	float GetRadius() const;
	bool IsOrbiting() const;

	// Setter Functions
	void SetPosition(const sf::Vector2f& position, const sf::Vector2f& orbitPosition, float deltaTime) override;
};

// Square
class Square : public SceneObject {
private:
	sf::RectangleShape square_{};
	ShapeType shapeType_{ ShapeType::SQUARE };
	const float sideLength_{};
	const sf::Angle rotationAngle_{};
	sf::Color color_{};

	const bool isOrbiting_{ false };
	const float orbitDistance_{};
	float orbitAngle_{};
	const float orbitSpeed_{};
	
	bool isMoving_{};

public:
	Square(float sideLength, sf::Vector2f position, sf::Color color, sf::Angle rotationAngle, bool isMoving)
		: square_(sf::Vector2f{ sideLength, sideLength }),
		sideLength_(sideLength),
		rotationAngle_(rotationAngle),
		color_(color),
		isMoving_(isMoving)
	{
		square_.setFillColor(color);
		square_.setPosition(position);
		square_.setRotation(rotationAngle);
	}

	Square(float sideLength, sf::Vector2f position, sf::Color color, sf::Angle rotationAngle, float orbitDistance, float orbitAngle, float orbitSpeed, bool isMoving)
		: square_(sf::Vector2f{ sideLength, sideLength }),
		sideLength_(sideLength),
		rotationAngle_(rotationAngle),
		color_(color),
		isOrbiting_(true),
		orbitDistance_(orbitDistance),
		orbitAngle_(orbitAngle),
		orbitSpeed_(orbitSpeed),
		isMoving_(isMoving)
	{
		square_.setFillColor(color);
		square_.setPosition(position);
		square_.setRotation(rotationAngle);
	}

	// Getter Functions
	const sf::Drawable& GetShape() const override;
	ShapeType GetShapeType() const override;
	sf::Vector2f GetPosition() const override;
	sf::Angle GetRotationAngle() const;
	float GetRayCollisionDistance(const sf::Vector2f& rayOrigin, const sf::Vector2f& rayDirection, float rayLength) const override;
	bool IsOrbiting() const;

	// Setter Functions
	void SetPosition(const sf::Vector2f& position, const sf::Vector2f& orbitPosition, float deltaTime) override;
};
#endif
