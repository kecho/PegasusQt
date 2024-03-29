/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtWaylandCompositor module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qwlregion_p.h"

QT_BEGIN_NAMESPACE

namespace QtWayland {

Region::Region(struct wl_client *client, uint32_t id)
    : QtWaylandServer::wl_region(client, id, 1)
{
}

Region::~Region()
{
}

Region *Region::fromResource(struct ::wl_resource *resource)
{
    return static_cast<Region *>(Resource::fromResource(resource)->region_object);
}

void Region::region_destroy_resource(Resource *)
{
    delete this;
}

void Region::region_destroy(Resource *resource)
{
    wl_resource_destroy(resource->handle);
}

void Region::region_add(Resource *, int32_t x, int32_t y, int32_t w, int32_t h)
{
    m_region += QRect(x, y, w, h);
}

void Region::region_subtract(Resource *, int32_t x, int32_t y, int32_t w, int32_t h)
{
    m_region -= QRect(x, y, w, h);
}

}

QT_END_NAMESPACE
