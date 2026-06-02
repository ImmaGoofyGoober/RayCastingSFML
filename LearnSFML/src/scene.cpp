#include <cmath>

#include <SFML/System/Vector2.hpp>
#include<SFML/Graphics/Drawable.hpp>

#include "scene.hpp"


// Circle
const sf::Drawable& Circle::GetShape() const {
	return circle_;
}

ShapeType Circle::GetShapeType() const {
	return shapeType_;
}

sf::Vector2f Circle::GetPosition() const{
	return circle_.getPosition();
}

float Circle::GetRadius() const {
	return radius_;
}

bool Circle::IsOrbiting() const {
	return isOrbiting_;
};

void Circle::SetPosition(const sf::Vector2f position) {
	if (isOrbiting_) {
		orbitAngle_ += orbitSpeed_;
		float circleX = position.x + std::cos(orbitAngle_) * orbitDistance_;
		float circleY = position.y + std::sin(orbitAngle_) * orbitDistance_;
		circle_.setPosition({ circleX, circleY });
	}
	else {
		circle_.setPosition(position);
	}
}

// Square
const sf::Drawable& Square::GetShape() const {
	return square_;
}

ShapeType Square::GetShapeType() const {
	return shapeType_;
}

sf::Vector2f Square::GetPosition() const {
	return square_.getPosition();
}

void Square::SetPosition(const sf::Vector2f position) {
	square_.setPosition(position);
}