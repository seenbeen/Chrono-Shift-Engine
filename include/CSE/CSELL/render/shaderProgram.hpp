#ifndef CSELL_RENDER_SHADERPROGRAM_HPP
#define CSELL_RENDER_SHADERPROGRAM_HPP

namespace CSELL { namespace Render {
    class Renderer;
    class Shader;

    class ShaderProgram {
    friend class Renderer;
        static ShaderProgram *activeShaderProgram;

        Renderer *renderer;
        Renderer **activeRenderer;

        bool ensureContext();

    protected:
        ShaderProgram();
        virtual ~ShaderProgram();

        virtual bool initShaderProgram() = 0;

        virtual bool attachShaderImplementation(Shader *shader) = 0;
        virtual bool linkShaderProgramImplementation() = 0;
        virtual bool useShaderProgramImplementation() = 0;

        // uniform setter implementations
        virtual bool setIntImplementation(const char *key, int value) = 0;
        virtual bool setFloatImplementation(const char *key, float value) = 0;
        virtual bool setMat4fImplementation(const char *key, float *value) = 0;
    public:

        bool attachShader(Shader *shader);
        bool linkShaderProgram();
        bool useShaderProgram();

        // uniform setters
        bool setInt(const char *key, int value);
        bool setFloat(const char *key, float value);
        bool setMat4f(const char *key, float *value);
    };
}}

#endif
