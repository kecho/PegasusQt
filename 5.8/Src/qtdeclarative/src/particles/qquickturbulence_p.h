/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtQuick module of the Qt Toolkit.
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

#ifndef TURBULENCEAFFECTOR_H
#define TURBULENCEAFFECTOR_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//
#include "qquickparticleaffector_p.h"
#include <QQmlListProperty>

QT_BEGIN_NAMESPACE

class QQuickParticlePainter;

class QQuickTurbulenceAffector : public QQuickParticleAffector
{
    Q_OBJECT
    Q_PROPERTY(qreal strength READ strength WRITE setStrength NOTIFY strengthChanged)
    Q_PROPERTY(QUrl noiseSource READ noiseSource WRITE setNoiseSource NOTIFY noiseSourceChanged)
    public:
    explicit QQuickTurbulenceAffector(QQuickItem *parent = 0);
    ~QQuickTurbulenceAffector();
    virtual void affectSystem(qreal dt);

    qreal strength() const
    {
        return m_strength;
    }

    QUrl noiseSource() const
    {
        return m_noiseSource;
    }
Q_SIGNALS:

    void strengthChanged(qreal arg);

    void noiseSourceChanged(QUrl arg);

public Q_SLOTS:

    void setStrength(qreal arg)
    {
        if (m_strength != arg) {
            m_strength = arg;
            Q_EMIT strengthChanged(arg);
        }
    }

    void setNoiseSource(QUrl arg)
    {
        if (m_noiseSource != arg) {
            m_noiseSource = arg;
            Q_EMIT noiseSourceChanged(arg);
            initializeGrid();
        }
    }

protected:
    virtual void geometryChanged(const QRectF &newGeometry,
                                 const QRectF &oldGeometry);
private:
    void ensureInit();
    void mapUpdate();
    void initializeGrid();
    qreal boundsRespectingField(int x, int y);
    qreal m_strength;
    qreal m_lastT;
    int m_gridSize;
    qreal** m_field;
    QPointF** m_vectorField;
    bool m_inited;
    QUrl m_noiseSource;
};

QT_END_NAMESPACE
#endif // TURBULENCEAFFECTOR_H
