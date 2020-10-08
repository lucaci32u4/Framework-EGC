#pragma once

#include <Component/SimpleScene.h>
#include <vector>

class Laborator1 : public SimpleScene
{
    private:
        float currentTime = 0;
        float vibrationAccumulator = 0;

        std::unordered_map<int, glm::vec3> shifters;
        std::vector<int> keys;
        std::vector<std::string> objects;

        float clearGradient = 0;
        uint8_t clearColor = 0;

        int currentMeshIndex = 0;

        glm::vec3 objPositionModifier = glm::vec3(0);
	public:
		Laborator1();
		~Laborator1();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
};
