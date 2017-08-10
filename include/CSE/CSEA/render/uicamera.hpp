#ifndef CSEA_RENDER_UICAMERA_HPP
#define CSEA_RENDER_UICAMERA_HPP
#include <CSE/CSEA/render/orthographiccamera.hpp>

namespace CSEA { namespace Render {
    class UICamera: public OrthographicCamera {
    public:
        UICamera(unsigned int vpWidth, unsigned int vpHeight);
    };
}}
#endif // CSEA_RENDER_UICAMERA_HPP
