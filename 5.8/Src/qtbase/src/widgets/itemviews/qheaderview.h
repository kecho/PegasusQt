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

#ifndef QHEADERVIEW_H
#define QHEADERVIEW_H

#include <QtWidgets/qtwidgetsglobal.h>
#include <QtWidgets/qabstractitemview.h>

QT_BEGIN_NAMESPACE


#ifndef QT_NO_ITEMVIEWS

class QHeaderViewPrivate;
class QStyleOptionHeader;

class Q_WIDGETS_EXPORT QHeaderView : public QAbstractItemView
{
    Q_OBJECT
    Q_PROPERTY(bool showSortIndicator READ isSortIndicatorShown WRITE setSortIndicatorShown)
    Q_PROPERTY(bool highlightSections READ highlightSections WRITE setHighlightSections)
    Q_PROPERTY(bool stretchLastSection READ stretchLastSection WRITE setStretchLastSection)
    Q_PROPERTY(bool cascadingSectionResizes READ cascadingSectionResizes WRITE setCascadingSectionResizes)
    Q_PROPERTY(int defaultSectionSize READ defaultSectionSize WRITE setDefaultSectionSize RESET resetDefaultSectionSize)
    Q_PROPERTY(int minimumSectionSize READ minimumSectionSize WRITE setMinimumSectionSize)
    Q_PROPERTY(int maximumSectionSize READ maximumSectionSize WRITE setMaximumSectionSize)
    Q_PROPERTY(Qt::Alignment defaultAlignment READ defaultAlignment WRITE setDefaultAlignment)

public:

    enum ResizeMode
    {
        Interactive,
        Stretch,
        Fixed,
        ResizeToContents,
        Custom = Fixed
    };
    Q_ENUM(ResizeMode)

    explicit QHeaderView(Qt::Orientation orientation, QWidget *parent = Q_NULLPTR);
    virtual ~QHeaderView();

    void setModel(QAbstractItemModel *model) Q_DECL_OVERRIDE;

    Qt::Orientation orientation() const;
    int offset() const;
    int length() const;
    QSize sizeHint() const Q_DECL_OVERRIDE;
    void setVisible(bool v) Q_DECL_OVERRIDE;
    int sectionSizeHint(int logicalIndex) const;

    int visualIndexAt(int position) const;
    int logicalIndexAt(int position) const;

    inline int logicalIndexAt(int x, int y) const;
    inline int logicalIndexAt(const QPoint &pos) const;

    int sectionSize(int logicalIndex) const;
    int sectionPosition(int logicalIndex) const;
    int sectionViewportPosition(int logicalIndex) const;

    void moveSection(int from, int to);
    void swapSections(int first, int second);
    void resizeSection(int logicalIndex, int size);
    void resizeSections(QHeaderView::ResizeMode mode);

    bool isSectionHidden(int logicalIndex) const;
    void setSectionHidden(int logicalIndex, bool hide);
    int hiddenSectionCount() const;

    inline void hideSection(int logicalIndex);
    inline void showSection(int logicalIndex);

    int count() const;
    int visualIndex(int logicalIndex) const;
    int logicalIndex(int visualIndex) const;

    void setSectionsMovable(bool movable);
    bool sectionsMovable() const;
#if QT_DEPRECATED_SINCE(5, 0)
    inline QT_DEPRECATED void setMovable(bool movable) { setSectionsMovable(movable); }
    inline QT_DEPRECATED bool isMovable() const { return sectionsMovable(); }
#endif

    void setSectionsClickable(bool clickable);
    bool sectionsClickable() const;
#if QT_DEPRECATED_SINCE(5, 0)
    inline QT_DEPRECATED void setClickable(bool clickable) { setSectionsClickable(clickable); }
    inline QT_DEPRECATED bool isClickable() const { return sectionsClickable(); }
#endif

    void setHighlightSections(bool highlight);
    bool highlightSections() const;

    ResizeMode sectionResizeMode(int logicalIndex) const;
    void setSectionResizeMode(ResizeMode mode);
    void setSectionResizeMode(int logicalIndex, ResizeMode mode);

    void setResizeContentsPrecision(int precision);
    int  resizeContentsPrecision() const;

#if QT_DEPRECATED_SINCE(5, 0)
    inline QT_DEPRECATED void setResizeMode(ResizeMode mode)
        { setSectionResizeMode(mode); }
    inline QT_DEPRECATED void setResizeMode(int logicalindex, ResizeMode mode)
        { setSectionResizeMode(logicalindex, mode); }
    inline QT_DEPRECATED ResizeMode resizeMode(int logicalindex) const
        { return sectionResizeMode(logicalindex); }
#endif

    int stretchSectionCount() const;

    void setSortIndicatorShown(bool show);
    bool isSortIndicatorShown() const;

    void setSortIndicator(int logicalIndex, Qt::SortOrder order);
    int sortIndicatorSection() const;
    Qt::SortOrder sortIndicatorOrder() const;

    bool stretchLastSection() const;
    void setStretchLastSection(bool stretch);

    bool cascadingSectionResizes() const;
    void setCascadingSectionResizes(bool enable);

    int defaultSectionSize() const;
    void setDefaultSectionSize(int size);
    void resetDefaultSectionSize();

    int minimumSectionSize() const;
    void setMinimumSectionSize(int size);
    int maximumSectionSize() const;
    void setMaximumSectionSize(int size);

    Qt::Alignment defaultAlignment() const;
    void setDefaultAlignment(Qt::Alignment alignment);

    void doItemsLayout() Q_DECL_OVERRIDE;
    bool sectionsMoved() const;
    bool sectionsHidden() const;

#ifndef QT_NO_DATASTREAM
    QByteArray saveState() const;
    bool restoreState(const QByteArray &state);
#endif

    void reset() Q_DECL_OVERRIDE;

public Q_SLOTS:
    void setOffset(int offset);
    void setOffsetToSectionPosition(int visualIndex);
    void setOffsetToLastSection();
    void headerDataChanged(Qt::Orientation orientation, int logicalFirst, int logicalLast);

Q_SIGNALS:
    void sectionMoved(int logicalIndex, int oldVisualIndex, int newVisualIndex);
    void sectionResized(int logicalIndex, int oldSize, int newSize);
    void sectionPressed(int logicalIndex);
    void sectionClicked(int logicalIndex);
    void sectionEntered(int logicalIndex);
    void sectionDoubleClicked(int logicalIndex);
    void sectionCountChanged(int oldCount, int newCount);
    void sectionHandleDoubleClicked(int logicalIndex);
    void geometriesChanged();
    void sortIndicatorChanged(int logicalIndex, Qt::SortOrder order);

protected Q_SLOTS:
    void updateSection(int logicalIndex);
    void resizeSections();
    void sectionsInserted(const QModelIndex &parent, int logicalFirst, int logicalLast);
    void sectionsAboutToBeRemoved(const QModelIndex &parent, int logicalFirst, int logicalLast);

protected:
    QHeaderView(QHeaderViewPrivate &dd, Qt::Orientation orientation, QWidget *parent = Q_NULLPTR);
    void initialize();

    void initializeSections();
    void initializeSections(int start, int end);
    void currentChanged(const QModelIndex &current, const QModelIndex &old) Q_DECL_OVERRIDE;

    bool event(QEvent *e) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *e) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    bool viewportEvent(QEvent *e) Q_DECL_OVERRIDE;

    virtual void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;
    virtual QSize sectionSizeFromContents(int logicalIndex) const;

    int horizontalOffset() const Q_DECL_OVERRIDE;
    int verticalOffset() const Q_DECL_OVERRIDE;
    void updateGeometries() Q_DECL_OVERRIDE;
    void scrollContentsBy(int dx, int dy) Q_DECL_OVERRIDE;

    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>()) Q_DECL_OVERRIDE;
    void rowsInserted(const QModelIndex &parent, int start, int end) Q_DECL_OVERRIDE;

    QRect visualRect(const QModelIndex &index) const Q_DECL_OVERRIDE;
    void scrollTo(const QModelIndex &index, ScrollHint hint) Q_DECL_OVERRIDE;

    QModelIndex indexAt(const QPoint &p) const Q_DECL_OVERRIDE;
    bool isIndexHidden(const QModelIndex &index) const Q_DECL_OVERRIDE;

    QModelIndex moveCursor(CursorAction, Qt::KeyboardModifiers) Q_DECL_OVERRIDE;
    void setSelection(const QRect& rect, QItemSelectionModel::SelectionFlags flags) Q_DECL_OVERRIDE;
    QRegion visualRegionForSelection(const QItemSelection &selection) const Q_DECL_OVERRIDE;
    void initStyleOption(QStyleOptionHeader *option) const;

    friend class QTableView;
    friend class QTreeView;

private:
    Q_PRIVATE_SLOT(d_func(), void _q_sectionsRemoved(const QModelIndex &parent, int logicalFirst, int logicalLast))
    Q_PRIVATE_SLOT(d_func(), void _q_layoutAboutToBeChanged())
    Q_DECLARE_PRIVATE(QHeaderView)
    Q_DISABLE_COPY(QHeaderView)
};

inline int QHeaderView::logicalIndexAt(int ax, int ay) const
{ return orientation() == Qt::Horizontal ? logicalIndexAt(ax) : logicalIndexAt(ay); }
inline int QHeaderView::logicalIndexAt(const QPoint &apos) const
{ return logicalIndexAt(apos.x(), apos.y()); }
inline void QHeaderView::hideSection(int alogicalIndex)
{ setSectionHidden(alogicalIndex, true); }
inline void QHeaderView::showSection(int alogicalIndex)
{ setSectionHidden(alogicalIndex, false); }

#endif // QT_NO_ITEMVIEWS

QT_END_NAMESPACE

#endif // QHEADERVIEW_H
