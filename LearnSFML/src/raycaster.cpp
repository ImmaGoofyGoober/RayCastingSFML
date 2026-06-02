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
    for (const auto& sceneObject : sceneObjects) {
        for (size_t i = 0; i < rayCount; i += 2) {
            switch (sceneObject->GetShapeType()) {
            case ShapeType::CIRCLE: {
                Circle* circle = dynamic_cast<Circle*>(sceneObject.get());

                break;
            }
            case ShapeType::SQUARE: {

                break;
            }
            default:
                break;
            }
        }
    }
}



