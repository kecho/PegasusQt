/****************************************************************************
**
** Copyright (C) 2015 Klaralvdalens Datakonsult AB (KDAB).
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef OPENGLVERTEXARRAYOBJECT_H
#define OPENGLVERTEXARRAYOBJECT_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of other Qt classes.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtGui/qopenglvertexarrayobject.h>
#include <Qt3DRender/private/graphicscontext_p.h>

QT_BEGIN_NAMESPACE

namespace Qt3DRender {
namespace Render {

class OpenGLVertexArrayObject
{
public:
    OpenGLVertexArrayObject();

    void setGraphicsContext(GraphicsContext *ctx);
    void bind();
    void release();
    void create();
    bool isCreated() const;

    QOpenGLVertexArrayObject *vao() { return m_vao.data(); }
    const QOpenGLVertexArrayObject *vao() const { return m_vao.data(); }
    void setVao(QOpenGLVertexArrayObject *vao) { m_vao.reset(vao); }

    void setSpecified(bool b) { m_specified = b; }
    bool isSpecified() const { return m_specified; }

private:
    GraphicsContext *m_ctx;
    QScopedPointer<QOpenGLVertexArrayObject> m_vao;
    bool m_specified;
    bool m_supportsVao;
    bool m_createdEmulatedVAO;

    friend class GraphicsContext;

    void saveVertexAttribute(const GraphicsContext::VAOVertexAttribute &attr);
    inline void saveIndexAttribute(HGLBuffer glBufferHandle) { m_indexAttribute = glBufferHandle; }

    QVector<GraphicsContext::VAOVertexAttribute> m_vertexAttributes;
    GraphicsContext::VAOIndexAttribute m_indexAttribute;
};

} // namespace Render
} // namespace Qt3DRender

QT_END_NAMESPACE

#endif // OPENGLVERTEXARRAYOBJECT_H
