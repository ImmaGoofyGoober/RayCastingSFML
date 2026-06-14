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


RayCaster Renderer::InitializeScene() {
    // RayCaster
    RayCaster rayCaster = RayCaster::Builder()
        .RaySourceRadius(20.f)
        .Position({800.f, 500.f})
        .RaySourceColor(sf::Color::Yellow)
        .VertexCount(4000)
        .RayLength(350.f)
        .RayColor(sf::Color::Yellow)
        .Build();

    // Circle
    sceneObjects_.push_back(Circle::Builder()
        .Radius(30.f)
        .Position({ 500.f, 500.f })
        .Color(sf::Color::Blue)
        .IsMoving(true)
        .IsOrbiting(true)
        .OrbitDistance(200.f)
        .OrbitAngle(1.f)
        .OrbitSpeed(1.f)
        .Build()
    );

    // Square 
     sceneObjects_.push_back(Square::Builder()
         .SideLength(40.f)
         .Position({ 300.f, 300.f })
         .RotationAngle(sf::degrees(35.f))
         .Color(sf::Color::Red)
         .IsMoving(false)
         .IsOrbiting(false)
         .OrbitDistance(0)
         .OrbitAngle(0)
         .OrbitSpeed(0)
         .Build()
     );

    return rayCaster;
}

void Renderer::StartSimulation(RayCaster& rayCaster) {
    std::string title = "Ray Casting Simulation";
    sf::RenderWindow window(sf::VideoMode({1280, 720}), title, sf::Style::Default);
	window.setFramerateLimit(60);
    
    sf::Clock clock;
    sf::Clock titleClock;

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseEvent->button == sf::Mouse::Button::Left) {
                    mouseButtonLeftPressed_ = true;
                }
            }
            if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonReleased>()) {
                if (mouseEvent->button == sf::Mouse::Button::Left) {
                    mouseButtonLeftPressed_ = false;
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();

        window.clear(sf::Color::Black);

        if (mouseButtonLeftPressed_) {
            sf::Vector2i mouseScreenPosition = sf::Mouse::getPosition(window);
            sf::Vector2f mouseWorldPosition = window.mapPixelToCoords(mouseScreenPosition);

            rayCaster.UpdateRaySource(mouseWorldPosition);
            rayCaster.UpdateRayPositions();
        }

        for (const auto& sceneObject : sceneObjects_) {
            sceneObject->SetPosition(sf::Vector2f{}, rayCaster.GetRaySourcePosition(), deltaTime);
        }

        for (const auto& sO : sceneObjects_) {
            window.draw(*sO);
        }

        rayCaster.UpdateRayPositions();
        rayCaster.UpdateRayCollisions(sceneObjects_);

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
