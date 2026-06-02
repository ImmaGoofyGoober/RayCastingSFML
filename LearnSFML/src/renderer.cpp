#include <iostream>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <iomanip> 

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "renderer.hpp"
#include "scene.hpp"
#include "raycaster.hpp"


void Renderer::InitializeScene() {
    // Circle
    sceneObjects.push_back(std::make_unique<Circle>(30.f, sf::Vector2f{0.f,0.f}, sf::Color::Blue, 180.f, 1.f, 0.004f, true));

   // Square 
    sceneObjects.push_back(std::make_unique<Square>(60.f, sf::Vector2f{ 500.f, 500.f }, sf::Color::Red, sf::degrees(60.f), false));
}

void Renderer::StartSimulation() {
    std::string title = "Ray Casting Simulation";
    sf::RenderWindow window(sf::VideoMode({1280, 720}), title, sf::Style::Default);
	window.setFramerateLimit(60);
    
    sf::Clock clock;
    sf::Clock titleClock;

    RayCaster rayCaster(window.getSize());

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseEvent->button == sf::Mouse::Button::Left) {
                    mouseButtonLeftPressed = true;
                }
            }
            if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonReleased>()) {
                if (mouseEvent->button == sf::Mouse::Button::Left) {
                    mouseButtonLeftPressed = false;
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();

        window.clear(sf::Color::Black);

        // Update
        if (mouseButtonLeftPressed) {
            sf::Vector2i mouseScreenPosition = sf::Mouse::getPosition(window);
            sf::Vector2f mouseWorldPosition = window.mapPixelToCoords(mouseScreenPosition);

            rayCaster.UpdateRaySource(mouseWorldPosition);
            rayCaster.UpateRayPositions();
        }

        rayCaster.UpateRayPositions();
        rayCaster.UpdateRayCollisions(sceneObjects);

        for (const auto& sceneObject : sceneObjects) {
            sceneObject->SetPosition(sf::Vector2f{}, rayCaster.GetRaySourcePosition());
        }

        // Draw
        for (const auto& sO : sceneObjects) {
            window.draw(sO->GetShape());
        }

        window.draw(rayCaster.GetRaySource());
        window.draw(rayCaster.GetRayVertices());

        window.display();

        // FPS
        float fps = 1.0f / deltaTime;
        //std::cout << fps << '\n';

        if (titleClock.getElapsedTime().asSeconds() >= 0.1f) {
            std::ostringstream titleStream;
            titleStream << title << " - FPS: " << std::setprecision(3) << fps;
            window.setTitle(titleStream.str());
            titleClock.restart();
        }
    }
}
