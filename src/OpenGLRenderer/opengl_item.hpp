#include <QQuickFramebufferObject>
#include "opengl_renderer.hpp"

class OpenGLItem : public QQuickFramebufferObject {
    Q_OBJECT
public:
    OpenGLItem(QQuickItem *parent = nullptr);
    Renderer *createRenderer() const override;
};
