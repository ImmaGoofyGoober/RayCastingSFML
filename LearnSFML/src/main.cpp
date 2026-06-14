#include "renderer.hpp"
#include "raycaster.hpp"


int main() {
    Renderer renderer;

    RayCaster rayCaster = renderer.InitializeScene();

    renderer.StartSimulation(rayCaster);

    return 0;
}


