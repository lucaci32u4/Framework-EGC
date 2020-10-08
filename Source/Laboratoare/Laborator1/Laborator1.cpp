#include "Laborator1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator1::Laborator1()
{
}

Laborator1::~Laborator1()
{
}

void Laborator1::Init()
{
	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("utah_teapot");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mesh->GetMeshID()] = mesh;
		objects.emplace_back(mesh->GetMeshID());

		mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
        objects.emplace_back(mesh->GetMeshID());

        mesh = new Mesh("sphere");
        mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
        objects.emplace_back(mesh->GetMeshID());

		shifters[GLFW_KEY_W] = glm::vec3(0, 0, -1);
		shifters[GLFW_KEY_S] = - shifters[GLFW_KEY_W];
        shifters[GLFW_KEY_A] = glm::vec3(-1, 0, 0);
        shifters[GLFW_KEY_D] = - shifters[GLFW_KEY_A];
        shifters[GLFW_KEY_Q] = glm::vec3(0, -1, 0);
        shifters[GLFW_KEY_E] = - shifters[GLFW_KEY_Q];

	}
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
    currentTime += deltaTimeSeconds;
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	glClearColor(clearGradient, clearGradient, clearGradient, 1);

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	float powerMultiplier = 15;
	float speedMultiplier = 0.7;
	float distanceMultiplier = 1.3;
	float position = sin(currentTime * speedMultiplier);
	float speed = cos(currentTime * speedMultiplier); // derivative of position
	vibrationAccumulator += abs(speed) * powerMultiplier * deltaTimeSeconds;
	float angle = vibrationAccumulator;
	glm::vec3 angles = glm::vec3(angle, angle + M_PI / 3, angle + 2 * M_PI / 3);
	glm::vec3 scale = glm::abs(glm::sin(angles));
	glm::vec3 base = glm::vec3(0.8);
	scale = base + (glm::vec3(1) - base) * scale;
	scale = scale * glm::vec3(speed < 0 ? -1 : +1, 1, 1);

	RenderMesh(meshes[objects[currentMeshIndex % objects.size()]],
            glm::vec3(position * distanceMultiplier, 0, +0.3), scale);

	// render the object

	float moveModifier = 0.8;
	std::for_each(keys.begin(), keys.end(), [&](int k){
	    objPositionModifier += deltaTimeSeconds * moveModifier * shifters[k];
	});

	RenderMesh(meshes["box"], glm::vec3(1, 0.5f, -2) + objPositionModifier, glm::vec3(0.5f));

	// render the object again but with different properties
	RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, -2));

}

void Laborator1::FrameEnd()
{
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input
};

void Laborator1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_F) {
		currentMeshIndex++;
	}

	if (shifters.find(key) != shifters.end()) {
	    keys.emplace_back(key);
	}

	if (key == GLFW_KEY_SPACE) {
	    clearColor = clearColor ^ 70u;
	    clearGradient = clearColor / 255.0;
	}
}

void Laborator1::OnKeyRelease(int key, int mods)
{
    if (shifters.find(key) != shifters.end()) {
        keys.erase(std::remove(keys.begin(), keys.end(), key), keys.end());
    }
}

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}
