#include "opengl_item.hpp"

OpenGLItem::OpenGLItem(QQuickItem *parent) : QQuickFramebufferObject(parent) {
    setFlag(ItemHasContents, true);
    // Constructor implementation
}

QQuickFramebufferObject::Renderer *OpenGLItem::createRenderer() const {
    // Return your renderer implementation
    return new OpenGLRenderer();
}