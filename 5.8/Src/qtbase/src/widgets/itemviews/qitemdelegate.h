/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWidgets module of the Qt Toolkit.
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

#ifndef QITEMDELEGATE_H
#define QITEMDELEGATE_H

#include <QtWidgets/qtwidgetsglobal.h>
#include <QtWidgets/qabstractitemdelegate.h>
#include <QtCore/qstring.h>
#include <QtGui/qpixmap.h>
#include <QtCore/qvariant.h>

QT_BEGIN_NAMESPACE


#ifndef QT_NO_ITEMVIEWS

class QItemDelegatePrivate;
class QItemEditorFactory;

class Q_WIDGETS_EXPORT QItemDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
    Q_PROPERTY(bool clipping READ hasClipping WRITE setClipping)

public:
    explicit QItemDelegate(QObject *parent = Q_NULLPTR);
    ~QItemDelegate();

    bool hasClipping() const;
    void setClipping(bool clip);

    // painting
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE;

    // editing
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;

    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;

    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const Q_DECL_OVERRIDE;

    // editor factory
    QItemEditorFactory *itemEditorFactory() const;
    void setItemEditorFactory(QItemEditorFactory *factory);

protected:
    virtual void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option,
                             const QRect &rect, const QString &text) const;
    virtual void drawDecoration(QPainter *painter, const QStyleOptionViewItem &option,
                                const QRect &rect, const QPixmap &pixmap) const;
    virtual void drawFocus(QPainter *painter, const QStyleOptionViewItem &option,
                           const QRect &rect) const;
    virtual void drawCheck(QPainter *painter, const QStyleOptionViewItem &option,
                           const QRect &rect, Qt::CheckState state) const;
    void drawBackground(QPainter *painter, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const;

    void doLayout(const QStyleOptionViewItem &option,
                  QRect *checkRect, QRect *iconRect, QRect *textRect, bool hint) const;

    QRect rect(const QStyleOptionViewItem &option, const QModelIndex &index, int role) const;

    bool eventFilter(QObject *object, QEvent *event) Q_DECL_OVERRIDE;
    bool editorEvent(QEvent *event, QAbstractItemModel *model,
                     const QStyleOptionViewItem &option, const QModelIndex &index) Q_DECL_OVERRIDE;

    QStyleOptionViewItem setOptions(const QModelIndex &index,
                                    const QStyleOptionViewItem &option) const;

    QPixmap decoration(const QStyleOptionViewItem &option, const QVariant &variant) const;
    QPixmap *selected(const QPixmap &pixmap, const QPalette &palette, bool enabled) const;

    QRect doCheck(const QStyleOptionViewItem &option, const QRect &bounding,
                const QVariant &variant) const;
    QRect textRectangle(QPainter *painter, const QRect &rect,
                        const QFont &font, const QString &text) const;

private:
    Q_DECLARE_PRIVATE(QItemDelegate)
    Q_DISABLE_COPY(QItemDelegate)
};

#endif // QT_NO_ITEMVIEWS

QT_END_NAMESPACE

#endif // QITEMDELEGATE_H
