#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <iomanip> 
#include <ranges>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "renderer.hpp"
#include "scene.hpp"
#include "raycaster.hpp"


RayCaster Renderer::InitializeScene() {
    // RayCaster
    RayCaster rayCaster = RayCaster::Builder()
        .RaySourceRadius(20.f)
        .Position({800.f, 500.f})
        .RaySourceColor(sf::Color::Yellow)
        .VertexCount(14000)
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
        .SideLength(50.f)
        .Position({ 200.f, 400.f })
        .Color(sf::Color::Red)
        .RotationAngle(sf::degrees(25.f))
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
            window.draw(*sceneObject);
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
