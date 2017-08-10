#include <CSE/CSEA/render/uicamera.hpp>
#include <iostream>
namespace CSEA { namespace Render {
    UICamera::UICamera(unsigned int vpWidth, unsigned int vpHeight)
        : OrthographicCamera(0.0f, vpWidth, vpHeight, 0.0f, -1.0f, 0.0f) {}
}}
