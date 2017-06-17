#ifndef CSELL_RENDERER_CAMERA_HPP
#define CSELL_RENDERER_CAMERA_HPP
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// TODO: Swap to quaternions x.x
namespace CSELL { namespace Renderer {
    class Camera {
        glm::mat4 projectionMatrix, viewMatrix;
        glm::vec3 positionVector, targetVector, rightVector;

    protected:
        virtual glm::mat4 getProjectionMatrix();

    public:
        enum Axis { X, Y, Z };

        Camera(int screenWidth, int screenHeight);

        void setScreenLocation(int screenX, int screenY);
        void resize(int screenWidth, int screenHeight);

        void setPosition(float x, float y, float z);
        void setTarget(float x, float y, float z);
        void setRight(float x, float y, float z);

        void constructViewMatrix();

        void rotateAboutLocalAxis(Camera::Axis axis, float angle);
    };

    class OrthographicCamera: public Camera {
    protected:
        glm::mat4 getProjectionMatrix();
    public:
        OrthographicCamera(int screenWidth, int screenHeight, float unitsW, float unitsH);
    };

    class PerspectiveCamera: public Camera {
    protected:
        glm::mat4 getProjectionMatrix();
    public:
        PerspectiveCamera(int screenWidth, int screenHeight, float fov, float aspectRatio, float near, float far);
    };
}}
#endif
