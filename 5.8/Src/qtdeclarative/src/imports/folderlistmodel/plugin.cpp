/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtQml module of the Qt Toolkit.
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

#include <QtQml/qqmlextensionplugin.h>
#include <QtQml/qqml.h>

#include "qquickfolderlistmodel.h"

static void initResources()
{
#ifdef QT_STATIC
    Q_INIT_RESOURCE(qmake_Qt_labs_folderlistmodel);
#endif
}

QT_BEGIN_NAMESPACE

//![class decl]
class QmlFolderListModelPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    QmlFolderListModelPlugin(QObject *parent = 0) : QQmlExtensionPlugin(parent) { initResources(); }
    void registerTypes(const char *uri) Q_DECL_OVERRIDE
    {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("Qt.labs.folderlistmodel"));
#ifndef QT_NO_DIRMODEL
        qmlRegisterType<QQuickFolderListModel>(uri,1,0,"FolderListModel");
        qmlRegisterType<QQuickFolderListModel>(uri,2,0,"FolderListModel");
        qmlRegisterType<QQuickFolderListModel,1>(uri,2,1,"FolderListModel");
        qmlRegisterType<QQuickFolderListModel,2>(uri,2,2,"FolderListModel");
#endif
    }
};
//![class decl]

QT_END_NAMESPACE

#include "plugin.moc"