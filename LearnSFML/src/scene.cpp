#include <cmath>

#include <SFML/System/Vector2.hpp>
#include<SFML/Graphics/Drawable.hpp>
#include <SFML/System/Angle.hpp>

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

float Circle::GetRayCollisionDistance(const sf::Vector2f& rayOrigin, const sf::Vector2f& rayDirection, float rayLength) const {
	float directionLength = std::sqrt((rayDirection.x * rayDirection.x) + (rayDirection.y * rayDirection.y));

	if (directionLength == 0.f) {
		return rayLength;
	}

	sf::Vector2f normalizedRayDirection = rayDirection / directionLength;
	sf::Vector2f circleOrigin = circle_.getPosition();
	sf::Vector2f rayToCircle = { circleOrigin - rayOrigin };

	float distanceToCircleCenter = std::sqrt(rayToCircle.x * rayToCircle.x + rayToCircle.y * rayToCircle.y);

	if (distanceToCircleCenter <= radius_) {
		return 0.f;
	}

	float scalar = { (normalizedRayDirection.x * rayToCircle.x) + (normalizedRayDirection.y * rayToCircle.y)};

	if (scalar < 0.f || scalar > rayLength + radius_) { 
		return rayLength; 
	}

	sf::Vector2f closestPointToCircle = rayOrigin + (normalizedRayDirection * scalar);
	sf::Vector2f rayToCollisionPoint = circleOrigin - closestPointToCircle;

	float distanceToCollisionPoint = std::sqrt(rayToCollisionPoint.x * rayToCollisionPoint.x + rayToCollisionPoint.y * rayToCollisionPoint.y);

	if (distanceToCollisionPoint <= radius_) {	
		float distanceToCircleEdge = std::sqrt(radius_ * radius_ - distanceToCollisionPoint * distanceToCollisionPoint);
		return scalar - distanceToCircleEdge;
	}
	else {
		return rayLength;
	}
};

float Circle::GetRadius() const {
	return radius_;
}

bool Circle::IsOrbiting() const {
	return isOrbiting_;
};

void Circle::SetPosition(const sf::Vector2f& position, const sf::Vector2f& orbitPosition, float deltaTime) {
	if (isMoving_ && isOrbiting_) {
		orbitAngle_ += orbitSpeed_ * deltaTime;
		float circleX = orbitPosition.x + std::cos(orbitAngle_) * orbitDistance_;
		float circleY = orbitPosition.y + std::sin(orbitAngle_) * orbitDistance_;
		circle_.setPosition({ circleX, circleY });
	}
	else if(isMoving_){
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

float Square::GetRayCollisionDistance(const sf::Vector2f& rayOrigin, const sf::Vector2f& rayDirection, float rayLength) const {
	// check if square is rotated by comparing rotationAngle == 0.f

	return 1.f;
};

void Square::SetPosition(const sf::Vector2f& position, const sf::Vector2f& orbitPosition, float deltaTime) {
	if (isMoving_ && isOrbiting_) {
		orbitAngle_ += orbitSpeed_ * deltaTime;
		float squareX = orbitPosition.x + std::cos(orbitAngle_) * orbitDistance_;
		float squareY = orbitPosition.y + std::sin(orbitAngle_) * orbitDistance_;
		square_.setPosition({ squareX, squareY });
	}
	else if(isMoving_){
		square_.setPosition(position);
	}
}

bool Square::IsOrbiting() const {
	return isOrbiting_;
};

sf::Angle Square::GetRotationAngle() const {
	return rotationAngle_;
};