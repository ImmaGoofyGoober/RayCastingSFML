#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

#include "Objects.hpp"


// ADD MULTITHREADING, AND ADD PERFORMANCE BASED COLLISION CHECKING BY SPLITTING WINDOW INTO GRIDS AND CHECKING EACH GRID ONLY IF NEEDED

// ADD ERROR CHECKING

// ADD CMAKE

UpdateParticle updateParticle;

int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Nuclear Fission Test", sf::Style::None);
    window.setFramerateLimit(60);

    sf::Clock clock;


    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (event->is<sf::Event::MouseButtonReleased>()) {
                sf::Vector2i windowMousePos = sf::Mouse::getPosition(window);
                particle.radius = 10.f;
                particle.shape = sf::CircleShape(particle.radius);
                particle.shape.setFillColor(sf::Color::Blue);
                particle.speed = 500.f;
                particle.xPosition = windowMousePos.x;
                particle.yPosition = windowMousePos.y;
                particle.xDirection = 1;
                particle.yDirection = 1;
                particles.push_back(particle);
            }
        }

        float deltaTime = clock.restart().asSeconds();
        sf::Vector2u windowSize = window.getSize();

        window.clear(sf::Color(38, 38, 38));

        for (int i = 0; i < particles.size(); i++) {
            updateParticle.EdgeCollisionCheck(particles[i], deltaTime, windowSize.x, windowSize.y);
            updateParticle.MoveParticle(particles[i], deltaTime);
        }
        for (int i = 0; i < particles.size(); i++) {
            for (int j = i + 1; j < particles.size(); j++) {
                updateParticle.ParticleCollisionCheck(particles[i], particles[j], deltaTime);
            }
        }
        for (int i = 0; i < particles.size(); i++) {
            particles[i].shape.setPosition({ particles[i].xPosition, particles[i].yPosition });
            window.draw(particles[i].shape);
        }
        window.display();


        float fps = 1.0f / deltaTime;
        std::cout << fps << '\n';
    }
    std::cout << particles.size() << '\n';
    return 0;
}

