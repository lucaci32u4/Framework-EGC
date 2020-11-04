#include "Laborator4.h"

#include <vector>
#include <string>

#include <Core/Engine.h>
#include "Transform3D.h"
#include <numeric>

using namespace std;

Laborator4::Laborator4()
{
}

Laborator4::~Laborator4()
{
}

void Laborator4::Init()
{
	polygonMode = GL_FILL;

	Mesh* mesh = new Mesh("box");
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	meshes[mesh->GetMeshID()] = mesh;

	float move = 3;
	float scale = 0.6;
	float rotate = 4;

	shifters[GLFW_KEY_W] = glm::mat3(0, 0, -move, 0, 0, 0, 0, 0, 0);
	shifters[GLFW_KEY_A] = glm::mat3(-move, 0, 0, 0, 0, 0, 0, 0, 0);
    shifters[GLFW_KEY_R] = glm::mat3(0, -move, 0, 0, 0, 0, 0, 0, 0);
    shifters[GLFW_KEY_1] = glm::mat3(0, 0, 0, scale, 0, 0, 0, 0, 0);
    shifters[GLFW_KEY_3] = glm::mat3(0, 0, 0, 0, 0, 0, rotate, 0, 0);
    shifters[GLFW_KEY_5] = glm::mat3(0, 0, 0, 0, 0, 0, 0, rotate, 0);
    shifters[GLFW_KEY_7] = glm::mat3(0, 0, 0, 0, 0, 0, 0, 0, rotate);
    shifters[GLFW_KEY_S] = - shifters[GLFW_KEY_W];
    shifters[GLFW_KEY_D] = - shifters[GLFW_KEY_A];
    shifters[GLFW_KEY_F] = - shifters[GLFW_KEY_R];
    shifters[GLFW_KEY_2] = - shifters[GLFW_KEY_1];
    shifters[GLFW_KEY_4] = - shifters[GLFW_KEY_3];
    shifters[GLFW_KEY_6] = - shifters[GLFW_KEY_5];
    shifters[GLFW_KEY_8] = - shifters[GLFW_KEY_7];

}

void Laborator4::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator4::Update(float deltaTimeSeconds)
{
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(-2.5f, 0.5f,-1.5f);
	modelMatrix *= Transform3D::Translate(keysAccumulator[0].x, keysAccumulator[0].y, keysAccumulator[0].z);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0.0f, 0.5f, -1.5f);
	modelMatrix *= Transform3D::Scale(keysAccumulator[1].x, keysAccumulator[1].x, keysAccumulator[1].x);
	RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(2.5f, 0.5f, -1.5f);
	modelMatrix *= Transform3D::RotateOX(keysAccumulator[2].x);
	modelMatrix *= Transform3D::RotateOY(keysAccumulator[2].y);
	modelMatrix *= Transform3D::RotateOZ(keysAccumulator[2].z);
	RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
}

void Laborator4::FrameEnd() {
	DrawCoordinatSystem();
}

void Laborator4::OnInputUpdate(float deltaTime, int mods) {
	keysAccumulator += deltaTime * std::accumulate(keys.begin(), keys.end(), glm::mat3(0), [&](const glm::mat3 & a, const int & b) { return a + shifters[b]; });
}

void Laborator4::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_SPACE)
	{
		switch (polygonMode)
		{
		case GL_POINT:
			polygonMode = GL_FILL;
			break;
		case GL_LINE:
			polygonMode = GL_POINT;
			break;
		default:
			polygonMode = GL_LINE;
			break;
		}
	}
    if (shifters.find(key) != shifters.end()) {
        keys.emplace_back(key);
    }

}

void Laborator4::OnKeyRelease(int key, int mods)
{
    if (shifters.find(key) != shifters.end()) {
        keys.erase(std::remove(keys.begin(), keys.end(), key), keys.end());
    }
}

void Laborator4::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator4::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator4::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator4::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator4::OnWindowResize(int width, int height)
{
}
