#ifndef OBJECTS_HPP
#define OBJECTS_HPP

struct Particle {
    float radius;
    sf::CircleShape shape;
    float speed;
    float xPosition;
    float yPosition;
    int xDirection;
    int yDirection;
};

static Particle particle;

static std::vector<Particle> particles;

class UpdateParticle {
private:
    void UpdateXPositive(float& particleXPosition, const float particleSpeed, const float deltaTime);

    void UpdateYPositive(float& particleYPosition, const float particleSpeed, const float deltaTime);

    void UpdateXNegative(float& particleXPosition, const float particleSpeed, const float deltaTime);

    void UpdateYNegative(float& particleYPosition, const float particleSpeed, const float deltaTime);
public:
    void EdgeCollisionCheck(Particle& particle, const float deltaTime, const int windowSizeX, const int windowSizeY);

    void MoveParticle(Particle& particle, const float deltaTime);

    void ParticleCollisionCheck(Particle& particle1, Particle& particle2, const float deltaTime);
};

#endif 
