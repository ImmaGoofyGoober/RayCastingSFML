#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>

#include "renderer.hpp"

// ADD MULTITHREADING, AND ADD PERFORMANCE BASED COLLISION CHECKING BY SPLITTING WINDOW INTO GRIDS AND CHECKING EACH GRID ONLY IF NEEDED

// ADD ERROR CHECKING

// ADD CMAKE

// CHECK FOR REDUNDANCY

// create seperate thread to check for collisions

// FIX ORBIT SPEED CHANGED BY FPS 

int main() {
    Renderer renderer;

    renderer.InitializeScene();
    renderer.StartSimulation();

    return 0;
}


