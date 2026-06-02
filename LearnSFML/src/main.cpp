#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

#include "renderer.hpp"

int main() {
    Renderer renderer;

    renderer.InitializeScene();
    renderer.StartSimulation();

    return 0;
}


