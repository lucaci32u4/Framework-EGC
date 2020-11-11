#pragma once

#include <include/glm.h>
#include <include/math.h>

namespace Laborator {
    class Camera {
    public:
        Camera() {
            position = glm::vec3(0, 2, 5);
            forward = glm::vec3(0, 0, -1);
            up = glm::vec3(0, 1, 0);
            right = glm::vec3(1, 0, 0);
            distanceToTarget = 2;
        }

        Camera(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up) {
            Set(position, center, up);
        }

        ~Camera() {}

        // Update camera
        void Set(const glm::vec3 &position, const glm::vec3 &center, const glm::vec3 &up) {
            this->position = position;
            forward = glm::normalize(center - position);
            right = glm::cross(forward, up);
            this->up = glm::cross(right, forward);
        }

        void MoveForward(float distance) {
            position += glm::normalize(glm::vec3(forward.x, 0, forward.z)) * distance;
            // movement will keep the camera at the same height always
            // Example: If you rotate up/down your head and walk forward you will still keep the same relative distance (height) to the ground!
            // Translate the camera using the DIR vector computed from forward
        }

        void TranslateForward(float distance) {
            position += distance * forward;
        }

        void TranslateUpword(float distance) {
            position += distance * up;
        }

        void TranslateRight(float distance) {
            position += distance * right;
        }

        void RotateFirstPerson_OX(float angle) {
            glm::mat4 mat = glm::rotate(glm::mat4(1), angle, right);
            forward = glm::vec3(mat * glm::vec4(forward, 1));
            up = glm::vec3(mat * glm::vec4(up, 1));
        }

        void RotateFirstPerson_OY(float angle) {
            glm::mat4 mat = glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0));
            forward = glm::vec3(mat * glm::vec4(forward, 1));
            right = glm::vec3(mat * glm::vec4(right, 1));
            up = glm::normalize(glm::cross(right, forward));
        }

        void RotateFirstPerson_OZ(float angle) {
            glm::mat4 mat = glm::rotate(glm::mat4(1), angle, forward);
            right = glm::vec3(mat * glm::vec4(right, 1));
            up = glm::vec3(mat * glm::vec4(up, 1));
        }

        void RotateThirdPerson_OX(float angle) {
            position += forward * distanceToTarget;
            RotateFirstPerson_OX(angle);
            position -= forward * distanceToTarget;
        }

        void RotateThirdPerson_OY(float angle) {
            position += forward * distanceToTarget;
            RotateFirstPerson_OY(angle);
            position -= forward * distanceToTarget;
        }

        void RotateThirdPerson_OZ(float angle) {
            position += forward * distanceToTarget;
            RotateFirstPerson_OZ(angle);
            position -= forward * distanceToTarget;
        }

        glm::mat4 GetViewMatrix() {
            // Returns the View Matrix
            return glm::lookAt(position, position + forward, up);
        }

        glm::vec3 GetTargetPosition() {
            return position + forward * distanceToTarget;
        }

    public:
        float distanceToTarget;
        glm::vec3 position;
        glm::vec3 forward;
        glm::vec3 right;
        glm::vec3 up;
    };
}