#pragma once
#include <Component/SimpleScene.h>

#include <vector>

class Laborator4 : public SimpleScene
{
	public:
		Laborator4();
		~Laborator4();

		void Init() override;

	private:


        std::unordered_map<int, glm::mat3> shifters;
        std::vector<int> keys;
        glm::mat3 keysAccumulator = glm::mat3(
                0, 0, 0, // translate cube 1
                1, 0, 0, // scale cube 2
                0, 0, 0  // rotate cube 3
                );

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

	protected:
		glm::mat4 modelMatrix;
		GLenum polygonMode;
};
