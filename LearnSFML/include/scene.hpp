#ifndef SCENE_HPP
#define SCENE_HPP

#include <SFML/System/Vector2.hpp>
#include<SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>

enum struct ShapeType {
	CIRCLE
};

// Scene Objects
class SceneObject {
private:

public:
	// Getter Functions
	virtual const sf::Drawable& GetShape() const = 0;
	virtual ShapeType GetShapeType() const = 0;
	virtual sf::Vector2f GetPosition() const = 0;
	virtual float GetRadius() const {
		return  0.0;
	};

	// Setter Functions
	virtual void SetPosition(const sf::Vector2f position) = 0;

	virtual ~SceneObject() = default;
};

class OrbitingCircle : public SceneObject{
private:
	sf::CircleShape orbitingCircle{};
	ShapeType shapeType = ShapeType::CIRCLE;
	const float orbitingCircleRadius{};
	sf::Color orbitingCircleColor{};

	const float orbitDistance{};
	float orbitAngle{};
	const float orbitSpeed{};

public:
	OrbitingCircle(float oCR, float oD, float oA, float oS, sf::Color oCC) : orbitingCircle(oCR), orbitingCircleRadius(oCR), orbitDistance(oD), orbitAngle(oA), orbitSpeed(oS), orbitingCircleColor(oCC) {
		orbitingCircle.setFillColor(orbitingCircleColor);
		orbitingCircle.setOrigin({ orbitingCircleRadius, orbitingCircleRadius });
		orbitingCircle.setPosition({500, 500});
	}

	// Getter Functions
	const sf::Drawable& GetShape() const override;
	ShapeType GetShapeType() const override;
	sf::Vector2f GetPosition() const override;
	float GetRadius() const override;

	// Setter Functions
	void SetPosition(const sf::Vector2f raySourcePosition) override;
};

#endif
