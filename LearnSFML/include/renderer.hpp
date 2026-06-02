#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>
#include <vector>

#include "scene.hpp"
#include "raycaster.hpp"

class Renderer {
private:
	// Scene
	std::vector<std::unique_ptr<SceneObject>> sceneObjects_;

	// Simulation
	bool mouseButtonLeftPressed_{ false };

public:
	void InitializeScene();
	void StartSimulation();

};

#endif 