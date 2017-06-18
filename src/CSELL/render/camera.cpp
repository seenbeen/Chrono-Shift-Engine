#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <CSE/CSELL/render/camera.hpp>
/*
// TODO: Swap to quaternions x.x
namespace CSELL { namespace Renderer {
    class Camera {
        friend class RenderEngine;
        glm::mat4 projectionMatrix, viewMatrix;
        glm::vec3 positionVector, targetVector, rightVector;

        unsigned int screenX, screenY, viewWidth, viewHeight;

        void constructViewMatrix();
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

        void rotateAboutLocalAxis(Camera::Axis axis, float angle);
    };

    class OrthographicCamera: public Camera {
    protected:
        glm::mat4 getProjectionMatrix();
    public:
        OrthoCamera(int screenWidth, int screenHeight, float unitsW, float unitsH);
    };

    class PerspectiveCamera: public Camera {
    protected:
        glm::mat4 getProjectionMatrix();
    public:
        PerspectiveCamera(int screenWidth, int screenHeight, float fov, float aspectRatio, float near, float far);
    };
}}
*/
