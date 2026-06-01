#include <SFML/Graphics.hpp>

#include "Objects.hpp"


void UpdateParticle::UpdateXPositive(float& particleXPosition, const float particleSpeed, const float deltaTime) {
    particleXPosition += particleSpeed * deltaTime;
}

void UpdateParticle::UpdateYPositive(float& particleYPosition, const float particleSpeed, const float deltaTime) {
    particleYPosition += particleSpeed * deltaTime;
}

void UpdateParticle::UpdateXNegative(float& particleXPosition, const float particleSpeed, const float deltaTime) {
    particleXPosition -= particleSpeed * deltaTime;
}

void UpdateParticle::UpdateYNegative(float& particleYPosition, const float particleSpeed, const float deltaTime) {
    particleYPosition -= particleSpeed * deltaTime;
}

void UpdateParticle::EdgeCollisionCheck(Particle& particle, const float deltaTime, const int windowSizeX, const int windowSizeY) {
    particle.xPosition = std::clamp(particle.xPosition, particle.radius, windowSizeX - particle.radius);
    particle.yPosition = std::clamp(particle.yPosition, particle.radius, windowSizeY - particle.radius);

    if (particle.xPosition == particle.radius || particle.xPosition == windowSizeX - particle.radius)
        particle.xDirection = -particle.xDirection;
    if (particle.yPosition == particle.radius || particle.yPosition == windowSizeY - particle.radius)
        particle.yDirection = -particle.yDirection;
}

void UpdateParticle::MoveParticle(Particle& particle, const float deltaTime) {
    if (particle.xDirection == 1) {
        UpdateXPositive(particle.xPosition, particle.speed, deltaTime);
    }
    else if (particle.xDirection == -1) {
        UpdateXNegative(particle.xPosition, particle.speed, deltaTime);
    }
    if (particle.yDirection == 1) {
        UpdateYPositive(particle.yPosition, particle.speed, deltaTime);
    }
    else if (particle.yDirection == -1) {
        UpdateYNegative(particle.yPosition, particle.speed, deltaTime);
    }
}

void UpdateParticle::ParticleCollisionCheck(Particle& particle1, Particle& particle2, const float deltaTime) {
    float differenceX = particle1.xPosition - particle2.xPosition;
    float differenceY = particle1.yPosition - particle2.yPosition;
    float distance = differenceX * differenceX + differenceY * differenceY;
    float minDistance = particle1.radius + particle2.radius;
    //VISUALIZE THIS MATH
    if (distance <= minDistance * minDistance) {
        particle1.xDirection = -particle1.xDirection;
        particle1.yDirection = -particle1.yDirection;
        particle2.xDirection = -particle2.xDirection;
        particle2.yDirection = -particle2.yDirection;
    }
}
