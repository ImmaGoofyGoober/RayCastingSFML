#ifndef SCENE_HPP
#define SCENE_HPP

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

	// Setter Functions
	virtual void SetPosition(const sf::Vector2f position) = 0;

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

public:
	Circle(float radius, sf::Vector2f position, sf::Color color)
		: circle_(radius),
		radius_(radius),
		color_(color)
	{
		circle_.setFillColor(color_);
		circle_.setOrigin({ radius_, radius_ });
		circle_.setPosition(position);
	}

	Circle(float radius, sf::Vector2f orbitPosition, sf::Color color, float orbitDistance, float orbitAngle, float orbitSpeed)
		: circle_(radius),
		radius_(radius),
		color_(color),
		isOrbiting_(true),
		orbitDistance_(orbitDistance),
		orbitAngle_(orbitAngle),
		orbitSpeed_(orbitSpeed)
	{
		circle_.setFillColor(color);
		circle_.setOrigin({ radius, radius });
		circle_.setPosition(orbitPosition);
	}

	// Getter Functions
	const sf::Drawable& GetShape() const override;
	ShapeType GetShapeType() const override;
	sf::Vector2f GetPosition() const override;
	float GetRadius() const;
	bool IsOrbiting() const;

	// Setter Functions
	void SetPosition(const sf::Vector2f position) override;
};

// Square
class Square : public SceneObject {
private:
	sf::RectangleShape square_{};
	ShapeType shapeType_{ ShapeType::SQUARE };
	const float sideLength_{};
	sf::Color color_{};

public:
	Square(float sideLength, sf::Vector2f position, sf::Color color, sf::Angle rotationAngle)
		: square_(sf::Vector2f{ sideLength, sideLength }),
		sideLength_(sideLength),
		color_(color)
	{
		square_.setFillColor(color);
		square_.setPosition(position);
		square_.setRotation(rotationAngle);
	}

	// Getter Functions
	const sf::Drawable& GetShape() const override;
	ShapeType GetShapeType() const override;
	sf::Vector2f GetPosition() const override;

	// Setter Functions
	void SetPosition(const sf::Vector2f position) override;
};
#endif
