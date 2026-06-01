#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>
#include <vector>

#include "scene.hpp"
#include "raycaster.hpp"

class Renderer {
private:
	// Scene
	std::vector<std::unique_ptr<SceneObject>> sceneObjects;

	// Simulation
	bool mouseButtonLeftPressed{ false };

public:
	void InitializeScene();
	void StartSimulation();

};

#endif 