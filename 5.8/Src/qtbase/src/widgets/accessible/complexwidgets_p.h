/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the plugins of the Qt Toolkit.
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

#ifndef COMPLEXWIDGETS_H
#define COMPLEXWIDGETS_H

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

#include <QtWidgets/private/qtwidgetsglobal_p.h>
#include <QtCore/qpointer.h>
#include <QtWidgets/qaccessiblewidget.h>
#include <QtWidgets/qabstractitemview.h>

QT_BEGIN_NAMESPACE

#ifndef QT_NO_ACCESSIBILITY

class QAbstractButton;
class QHeaderView;
class QTabBar;
class QComboBox;
class QTitleBar;
class QAbstractScrollArea;
class QScrollArea;

#ifndef QT_NO_SCROLLAREA
class QAccessibleAbstractScrollArea : public QAccessibleWidget
{
public:
    explicit QAccessibleAbstractScrollArea(QWidget *widget);

    enum AbstractScrollAreaElement {
        Self = 0,
        Viewport,
        HorizontalContainer,
        VerticalContainer,
        CornerWidget,
        Undefined
    };

    QAccessibleInterface *child(int index) const Q_DECL_OVERRIDE;
    int childCount() const Q_DECL_OVERRIDE;
    int indexOfChild(const QAccessibleInterface *child) const Q_DECL_OVERRIDE;
    bool isValid() const Q_DECL_OVERRIDE;
    QAccessibleInterface *childAt(int x, int y) const Q_DECL_OVERRIDE;

//protected:
    QAbstractScrollArea *abstractScrollArea() const;

private:
    QWidgetList accessibleChildren() const;
    AbstractScrollAreaElement elementType(QWidget *widget) const;
    bool isLeftToRight() const;
};

class QAccessibleScrollArea : public QAccessibleAbstractScrollArea
{
public:
    explicit QAccessibleScrollArea(QWidget *widget);
};
#endif // QT_NO_SCROLLAREA

#ifndef QT_NO_TABBAR
class QAccessibleTabBar : public QAccessibleWidget
{
public:
    explicit QAccessibleTabBar(QWidget *w);
    ~QAccessibleTabBar();

    int childCount() const Q_DECL_OVERRIDE;
    QString text(QAccessible::Text t) const Q_DECL_OVERRIDE;

    QAccessibleInterface* child(int index) const Q_DECL_OVERRIDE;
    int indexOfChild(const QAccessibleInterface *child) const Q_DECL_OVERRIDE;

protected:
    QTabBar *tabBar() const;
    mutable QHash<int, QAccessible::Id> m_childInterfaces;
};
#endif // QT_NO_TABBAR

#ifndef QT_NO_COMBOBOX
class QAccessibleComboBox : public QAccessibleWidget
{
public:
    explicit QAccessibleComboBox(QWidget *w);

    int childCount() const Q_DECL_OVERRIDE;
    QAccessibleInterface *childAt(int x, int y) const Q_DECL_OVERRIDE;
    int indexOfChild(const QAccessibleInterface *child) const Q_DECL_OVERRIDE;
    QAccessibleInterface* child(int index) const Q_DECL_OVERRIDE;

    QString text(QAccessible::Text t) const Q_DECL_OVERRIDE;

    // QAccessibleActionInterface
    QStringList actionNames() const Q_DECL_OVERRIDE;
    QString localizedActionDescription(const QString &actionName) const Q_DECL_OVERRIDE;
    void doAction(const QString &actionName) Q_DECL_OVERRIDE;
    QStringList keyBindingsForAction(const QString &actionName) const Q_DECL_OVERRIDE;

protected:
    QComboBox *comboBox() const;
};
#endif // QT_NO_COMBOBOX

#endif // QT_NO_ACCESSIBILITY

QT_END_NAMESPACE

#endif // COMPLEXWIDGETS_H
