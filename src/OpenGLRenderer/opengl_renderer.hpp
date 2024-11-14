#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include <QQuickFramebufferObject>

class OpenGLRenderer : public QQuickFramebufferObject::Renderer, protected QOpenGLFunctions {
public:
    OpenGLRenderer();

    void render() override;
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override;

private:
    void checkShaderCompileErrors(GLuint shader, const std::string& type);
    void checkProgramLinkErrors(GLuint program);

    float vertices[9] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    unsigned int VBO;  // Vertex Buffer Object
    unsigned int VAO;  // Vertex Array Object
    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int shaderProgram;
};
