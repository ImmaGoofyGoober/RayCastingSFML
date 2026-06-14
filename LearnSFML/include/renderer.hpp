#ifndef RAYCASTER_RENDERER_HPP
#define RAYCASTER_RENDERER_HPP

#include <memory>
#include <vector>

#include "scene.hpp"
#include "raycaster.hpp"

class Renderer {
private:
	std::vector<std::unique_ptr<SceneObject>> sceneObjects_;

	bool mouseButtonLeftPressed_{ false };

public:
	RayCaster InitializeScene();
	void StartSimulation(RayCaster& rayCaster);
};

#endif 