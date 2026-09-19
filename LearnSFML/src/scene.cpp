#include <cmath>
#include <algorithm>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "scene.hpp"


// Circle
void Circle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(circle_, states);
}

ShapeType Circle::GetShapeType() const {
	return shapeType_;
}

sf::Vector2f Circle::GetPosition() const{
	return circle_.getPosition();
}

float Circle::GetRayCollisionDistance(const sf::Vector2f& rayOrigin, const sf::Vector2f& rayDirection, float rayLength) const {
	sf::Vector2f circleOrigin = circle_.getPosition();

	float directionLength = std::sqrt((rayDirection.x * rayDirection.x) + (rayDirection.y * rayDirection.y));
	sf::Vector2f normalizedRayDirection = rayDirection / directionLength;

	if (directionLength == 0.f) {
		return rayLength;
	}

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
}

float Circle::GetRadius() const {
	return radius_;
}

bool Circle::IsOrbiting() const {
	return isOrbiting_;
}

void Circle::SetPosition(const sf::Vector2f& position, const sf::Vector2f& orbitPosition, float deltaTime) {
	if (isMoving_ && isOrbiting_) {
		orbitAngle_ += orbitSpeed_ * deltaTime;
		float circleX = orbitPosition.x + std::cos(orbitAngle_) * orbitDistance_;
		float circleY = orbitPosition.y + std::sin(orbitAngle_) * orbitDistance_;
		circle_.setPosition({ circleX, circleY });
	}
	else if (isMoving_) {
		circle_.setPosition(position);
	}
}

// Square
void Square::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(square_, states);
};

ShapeType Square::GetShapeType() const {
	return shapeType_;
}

sf::Vector2f Square::GetPosition() const {
	return square_.getPosition();
}

float Square::GetRayCollisionDistance(const sf::Vector2f& rayOrigin, const sf::Vector2f& rayDirection, float rayLength) const {
	sf::Vector2f squareOrigin = square_.getPosition();

	float directionLength = std::sqrt((rayDirection.x * rayDirection.x) + (rayDirection.y * rayDirection.y));
	sf::Vector2f normalizedRayDirection = rayDirection / directionLength;
	float halfSideLength = sideLength_ * 0.5f;

	sf::Vector2f rayToSquare = squareOrigin - rayOrigin;

	sf::Vector2f squareXAxis = { 1.0f, 0.0f };
	sf::Vector2f squareYAxis = { 0.0f, 1.0f };

	if (rotationAngle_.asRadians() != 0.f) {
		squareXAxis = { std::cos(rotationAngle_.asRadians()), std::sin(rotationAngle_.asRadians()) };
		squareYAxis = { -std::sin(rotationAngle_.asRadians()), std::cos(rotationAngle_.asRadians()) };
	}

	float alignedRayToSquareDistanceX = (rayToSquare.x * squareXAxis.x) + (rayToSquare.y * squareXAxis.y);
	float alignedRayToSquareDistanceY = (rayToSquare.x * squareYAxis.x) + (rayToSquare.y * squareYAxis.y);

	float scalarX = (normalizedRayDirection.x * squareXAxis.x) + (normalizedRayDirection.y * squareXAxis.y);
	float scalarY = (normalizedRayDirection.x * squareYAxis.x) + (normalizedRayDirection.y * squareYAxis.y);

	float scaledNearDistanceX = (alignedRayToSquareDistanceX - halfSideLength) / scalarX;
	float scaledFarDistanceX = (alignedRayToSquareDistanceX + halfSideLength) / scalarX;
	float scaledNearDistanceY = (alignedRayToSquareDistanceY - halfSideLength) / scalarY;
	float scaledFarDistanceY = (alignedRayToSquareDistanceY + halfSideLength) / scalarY;

	float xCollisionMin = std::min(scaledNearDistanceX, scaledFarDistanceX);
	float xCollisionMax = std::max(scaledNearDistanceX, scaledFarDistanceX);
	float yCollisionMin = std::min(scaledNearDistanceY, scaledFarDistanceY);
	float yCollisionMax = std::max(scaledNearDistanceY, scaledFarDistanceY);

	float nearCollision = std::max(xCollisionMin, yCollisionMin);
	float farCollision = std::min(xCollisionMax, yCollisionMax);
	
	if (nearCollision <= farCollision && farCollision >= 0.f && nearCollision <= rayLength) {
		return nearCollision;
	}
	else {
		return rayLength;
	}
}

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
}

sf::Angle Square::GetRotationAngle() const {
	return rotationAngle_;
}	
