#ifndef RAYCASTER_SCENE_HPP
#define RAYCASTER_SCENE_HPP

#include <memory>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

enum struct ShapeType {
	CIRCLE,
	SQUARE
};

// Scene Objects
class SceneObject : public sf::Drawable {
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

public:
	// Getter Functions
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
	void draw(sf::RenderTarget& target, sf::RenderStates) const override;

	sf::CircleShape circle_{};
	ShapeType shapeType_{ ShapeType::CIRCLE };
	const float radius_{};
	sf::Color color_{};
	bool isMoving_{ false };

	const bool isOrbiting_{ false };
	const float orbitDistance_{};
	float orbitAngle_{};
	const float orbitSpeed_{};

public:
	Circle(float radius, sf::Vector2f position, sf::Color color, bool isMoving, bool isOrbiting, float orbitDistance, float orbitAngle, float orbitSpeed)
		: circle_(radius),
		radius_(radius),
		color_(color),
		isMoving_(isMoving),
		isOrbiting_(isOrbiting),
		orbitDistance_(orbitDistance),
		orbitAngle_(orbitAngle),
		orbitSpeed_(orbitSpeed)
	{
		circle_.setPosition(position);
		circle_.setOrigin({ radius, radius });
		circle_.setFillColor(color);
	}

	class Builder {
	private:
		float radius_{};
		sf::Vector2f position_{};
		sf::Color color_{};
		bool isMoving_{ false };
		bool isOrbiting_{ false };
		float orbitDistance_{};
		float orbitAngle_{};
		float orbitSpeed_{};

	public:
		Builder& Radius(float radius) { radius_ = radius; return *this; };
		Builder& Position(const sf::Vector2f position) { position_ = position; return *this; };
		Builder& Color(const sf::Color color) { color_ = color; return *this; };
		Builder& IsMoving(bool isMoving) { isMoving_ = isMoving; return *this; };
		Builder& IsOrbiting(bool isOrbiting) { isOrbiting_ = isOrbiting; return *this; };
		Builder& OrbitDistance(float orbitDistance) { orbitDistance_ = orbitDistance; return *this; };
		Builder& OrbitAngle(float orbitAngle) { orbitAngle_ = orbitAngle; return *this; };
		Builder& OrbitSpeed(float orbitSpeed) { orbitSpeed_ = orbitSpeed; return *this; };

		std::unique_ptr<Circle> Build() { return std::make_unique<Circle>(radius_, position_, color_, isMoving_, isOrbiting_, orbitDistance_, orbitAngle_, orbitSpeed_); };
	};

	// Getter Functions
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
	void draw(sf::RenderTarget& target, sf::RenderStates) const override;

	sf::RectangleShape square_{};
	ShapeType shapeType_{ ShapeType::SQUARE };
	const float sideLength_{};
	const sf::Angle rotationAngle_{};
	sf::Color color_{};
	bool isMoving_{ false };

	const bool isOrbiting_{ false };
	const float orbitDistance_{};
	float orbitAngle_{};
	const float orbitSpeed_{};

public:
	Square(float sideLength, sf::Vector2f position, sf::Angle rotationAngle, sf::Color color, bool isMoving, bool isOrbiting, float orbitDistance, float orbitAngle, float orbitSpeed)
		: square_(sf::Vector2f{ sideLength, sideLength }),
		sideLength_(sideLength),
		rotationAngle_(rotationAngle),
		color_(color),
		isMoving_(isMoving),
		isOrbiting_(isOrbiting),
		orbitDistance_(orbitDistance),
		orbitAngle_(orbitAngle),
		orbitSpeed_(orbitSpeed)
	{
		square_.setFillColor(color);
		square_.setPosition(position);
		square_.setRotation(rotationAngle);
	}

	class Builder {
	private:
		float sideLength_{};
		sf::Vector2f position_{};
		sf::Angle rotationAngle_{};
		sf::Color color_{};
		bool isMoving_{ false };
		bool isOrbiting_{ false };
		float orbitDistance_{};
		float orbitAngle_{};
		float orbitSpeed_{};

	public:
		Builder& SideLength(float sideLength) { sideLength_ = sideLength; return *this; };
		Builder& Position(sf::Vector2f position) { position_ = position; return *this; };
		Builder& RotationAngle(sf::Angle rotationAngle) { rotationAngle_ = rotationAngle; return *this; };
		Builder& Color(sf::Color color) { color_ = color; return *this; };
		Builder& IsMoving(bool isMoving) { isMoving_ = isMoving; return *this; };
		Builder& IsOrbiting(bool isOrbiting) { isOrbiting_ = isOrbiting; return *this; };
		Builder& OrbitDistance(float orbitDistance) { orbitDistance_ = orbitDistance; return *this; };
		Builder& OrbitAngle(float orbitAngle) { orbitAngle_ = orbitAngle; return *this; };
		Builder& OrbitSpeed(float orbitSpeed) { orbitSpeed_ = orbitSpeed; return *this; };

		std::unique_ptr<Square> Build() { return std::make_unique<Square>(sideLength_, position_, rotationAngle_, color_, isMoving_, isOrbiting_, orbitDistance_, orbitAngle_, orbitSpeed_); };
	};

	// Getter Functions
	ShapeType GetShapeType() const override;
	sf::Vector2f GetPosition() const override;
	sf::Angle GetRotationAngle() const;
	float GetRayCollisionDistance(const sf::Vector2f& rayOrigin, const sf::Vector2f& rayDirection, float rayLength) const override;
	bool IsOrbiting() const;

	// Setter Functions
	void SetPosition(const sf::Vector2f& position, const sf::Vector2f& orbitPosition, float deltaTime) override;
};
#endif
