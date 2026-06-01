#include <cmath>

#include <SFML/System/Vector2.hpp>
#include<SFML/Graphics/Drawable.hpp>

#include "scene.hpp"


// Orbiting Circle
const sf::Drawable& OrbitingCircle::GetShape() const {
	return orbitingCircle;
}

ShapeType OrbitingCircle::GetShapeType() const {
	return shapeType;
}

sf::Vector2f OrbitingCircle::GetPosition() const{
	return orbitingCircle.getPosition();
}

float OrbitingCircle::GetRadius() const {
	return orbitingCircleRadius;
}

void OrbitingCircle::SetPosition(const sf::Vector2f raySourcePosition) {
	orbitAngle += orbitSpeed;
	float circleX = raySourcePosition.x + std::cos(orbitAngle) * orbitDistance;
	float circleY = raySourcePosition.y + std::sin(orbitAngle) * orbitDistance;
	orbitingCircle.setPosition({ circleX, circleY });
}