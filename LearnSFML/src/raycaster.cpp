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
const sf::Drawable& RayCaster::GetRaySource() const {
    return raySource_;
};

void RayCaster::UpdateRaySource(const sf::Vector2f mousePosition) {
    raySource_.setPosition(mousePosition);
}

sf::Vector2f RayCaster::GetRaySourcePosition() {
    return raySource_.getPosition();
}

// Ray
const sf::Drawable& RayCaster::GetRayVertices() const {
    return rayVertices_;
}

void RayCaster::UpdateRayPositions() {
    for (size_t i = 0; i < vertexCount_; ++i) {
        float angle = i;
        size_t rayStartIndex = i;
        size_t rayEndIndex = ++i;

        // Start of ray
        float rayStartX = raySource_.getPosition().x + std::cos(angle) * rayDistance_;
        float rayStartY = raySource_.getPosition().y + std::sin(angle) * rayDistance_;
        rayVertices_[rayStartIndex].position = { rayStartX, rayStartY };
        rayVertices_[rayStartIndex].color = rayColor_;

        // End of ray
        float rayEndX = rayStartX + std::cos(angle) * rayLength_;
        float rayEndY = rayStartY + std::sin(angle) * rayLength_;
        rayVertices_[rayEndIndex].position = { rayEndX , rayEndY };
        rayVertices_[rayEndIndex].color = rayColor_;
    }
}

void RayCaster::UpdateRayCollisions(const std::vector<std::unique_ptr<SceneObject>>& sceneObjects) {
    for (size_t i = 0; i < vertexCount_; ++i) {
        float angle = i;
        size_t rayStartIndex = i;
        size_t rayEndIndex = ++i;
 
        float rayStartX = raySource_.getPosition().x + std::cos(angle) * rayDistance_;
        float rayStartY = raySource_.getPosition().y + std::sin(angle) * rayDistance_;
        float rayEndX = rayStartX + std::cos(angle) * rayLength_;
        float rayEndY = rayStartY + std::sin(angle) * rayLength_;

        sf::Vector2f rayOrigin = { rayStartX, rayStartY };
        sf::Vector2f rayDirection = { (rayEndX - rayStartX), (rayEndY - rayStartY) };

        float closestCollisionDistance{ rayLength_ };
        float currentCollisionDistance{};

        for (const auto& sceneObject : sceneObjects) {
            currentCollisionDistance = sceneObject->GetRayCollisionDistance(rayOrigin, rayDirection, rayLength_);

            if (currentCollisionDistance < closestCollisionDistance) {
                closestCollisionDistance = currentCollisionDistance;
                // std::cout << "Collision Point Along Ray: " << closestCollisionDistance << "\n\n";
            }   
        }

        float rayEndXX = rayStartX + std::cos(angle) * closestCollisionDistance;
        float rayEndYY = rayStartY + std::sin(angle) * closestCollisionDistance;
        rayVertices_[rayEndIndex].position = { rayEndXX , rayEndYY };
    }
}



