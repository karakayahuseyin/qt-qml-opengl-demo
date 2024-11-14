#include "opengl_renderer.hpp"
#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include <QQuickFramebufferObject>
#include <QOpenGLExtraFunctions>

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos, 1.0);\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "  FragColor = vec4(0.2f, 0.7f, 0.8f, 1.0f);\n"
                                   "}\n";

OpenGLRenderer::OpenGLRenderer() {
    initializeOpenGLFunctions();

    QOpenGLExtraFunctions *f = QOpenGLContext::currentContext()->extraFunctions();

    // Shader Programını Oluşturma
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    checkShaderCompileErrors(vertexShader, "VERTEX");

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    checkShaderCompileErrors(fragmentShader, "FRAGMENT");

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkProgramLinkErrors(shaderProgram);

    // Shader'ları Sil
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // VBO ve VAO Oluşturma
    f->glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    f->glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Vertex Attribute Ayarı
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void OpenGLRenderer::render() {
    QOpenGLExtraFunctions *f = QOpenGLContext::currentContext()->extraFunctions();
    // Shader Programını Kullan
    glUseProgram(shaderProgram);

    // VAO'yu Bağla ve Çizim İşlemi
    f->glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Kaynakları Serbest Bırakma
    f->glBindVertexArray(0);
}

QOpenGLFramebufferObject* OpenGLRenderer::createFramebufferObject(const QSize &size) {
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::Depth);
    return new QOpenGLFramebufferObject(size, format);
}

void OpenGLRenderer::checkShaderCompileErrors(GLuint shader, const std::string& type) {
    GLint success;
    GLchar infoLog[1024];
    if (type == "VERTEX" || type == "FRAGMENT") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            qWarning() << "ERROR::SHADER_COMPILATION_ERROR of type:" << type.c_str() << "\n" << infoLog;
        }
    }
}

void OpenGLRenderer::checkProgramLinkErrors(GLuint program) {
    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        qWarning() << "ERROR::PROGRAM_LINKING_ERROR:\n" << infoLog;
    }
}
