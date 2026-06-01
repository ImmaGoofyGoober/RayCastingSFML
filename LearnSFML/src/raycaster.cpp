#include <cmath>
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>

#include "raycaster.hpp"
#include "scene.hpp"


// Ray Source
const sf::Drawable& Raycaster::GetRaySource() const {
    return raySource;
};

void Raycaster::UpdateRaySource(const sf::Vector2f mousePosition) {
    raySource.setPosition(mousePosition);
}

sf::Vector2f Raycaster::GetRaySourcePosition() {
    return raySource.getPosition();
}

// Ray
const sf::Drawable& Raycaster::GetRayVertices() const {
    return rayVertices;
}

void Raycaster::UpateRayPositions() {
    for (size_t i = 0; i < rayCount; ++i) {
        float angle = i;
        size_t rayStartIndex = i;
        size_t rayEndIndex = ++i;

        // Start of ray
        float rayStartX = raySource.getPosition().x + std::cos(angle) * rayDistance;
        float rayStartY = raySource.getPosition().y + std::sin(angle) * rayDistance;

        rayVertices[rayStartIndex].position = { rayStartX, rayStartY };
        rayVertices[rayStartIndex].color = sf::Color::Yellow;

        // End of ray
        float rayEndX = rayStartX + std::cos(angle) * rayLength;
        float rayEndY = rayStartY + std::sin(angle) * rayLength;

        rayVertices[rayEndIndex].position = { rayEndX , rayEndY };
        rayVertices[rayEndIndex].color = sf::Color::Yellow;
    }
}

void Raycaster::UpdateRayCollisions(const std::vector<std::unique_ptr<SceneObject>>& sceneObjects) {
    for (const auto& sO : sceneObjects) {
        for (size_t i = 0; i < rayCount; i += 2) {
            switch (sO->GetShapeType()) {
            case ShapeType::CIRCLE: {
                sf::Vector2f rayStartPoint = rayVertices[i].position;
                sf::Vector2f rayEndPoint = rayVertices[i + 1].position;

                sf::Vector2f rayDirection = { rayEndPoint.x - rayStartPoint.x, rayEndPoint.y - rayStartPoint.y };
                float rayLength = std::sqrt(rayDirection.x * rayDirection.x + rayDirection.y * rayDirection.y);
                sf::Vector2f normalizedRayDirection = { rayDirection.x / rayLength, rayDirection.y / rayLength };

                sf::Vector2f vectorToCircleCenter = { sO->GetPosition().x - rayStartPoint.x, sO->GetPosition().y - rayStartPoint.y };

                float circleToRayProjectionLength = (vectorToCircleCenter.x * normalizedRayDirection.x) + (vectorToCircleCenter.y * normalizedRayDirection.y);

                float distanceAlongRay = std::clamp(circleToRayProjectionLength, 0.0f, rayLength);

                sf::Vector2f closestPointToCircle = (rayStartPoint + distanceAlongRay * normalizedRayDirection);

                float distanceX = (sO->GetPosition().x - closestPointToCircle.x);
                float distanceY = (sO->GetPosition().y - closestPointToCircle.y);

                float distanceToCircleCenter = std::sqrt(distanceX * distanceX + distanceY * distanceY);

                if (distanceToCircleCenter > sO->GetRadius()) {
                    continue;
                }

                float distanceToCircleSurface = std::sqrt(sO->GetRadius() * sO->GetRadius() - distanceToCircleCenter * distanceToCircleCenter);

                sf::Vector2f collisionPoint = { closestPointToCircle - normalizedRayDirection * distanceToCircleSurface };

                std::cout << "Collision\n";
                std::cout << "Distance to circle center: " << distanceToCircleCenter << "\n";
                std::cout << "Radius: " << sO->GetRadius() << "\n\n";
                rayVertices[i + 1].position = collisionPoint;

                break;
            }
            default:
                break;
            }
        }
    }
}



