/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Assistant of the Qt Toolkit.
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

#ifndef QHELPSEARCHENGINE_H
#define QHELPSEARCHENGINE_H

#include <QtHelp/qhelp_global.h>

#include <QtCore/QMap>
#include <QtCore/QUrl>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringList>

QT_BEGIN_NAMESPACE


class QHelpEngineCore;
class QHelpSearchQueryWidget;
class QHelpSearchResultWidget;
class QHelpSearchEnginePrivate;

class QHELP_EXPORT QHelpSearchQuery
{
public:
    enum FieldName { DEFAULT = 0, FUZZY, WITHOUT, PHRASE, ALL, ATLEAST };

    QHelpSearchQuery()
        : fieldName(DEFAULT) { wordList.clear(); }
    QHelpSearchQuery(FieldName field, const QStringList &wordList_)
        : fieldName(field), wordList(wordList_) {}

    FieldName fieldName;
    QStringList wordList;
};

class QHELP_EXPORT QHelpSearchEngine : public QObject
{
    Q_OBJECT

public:
    explicit QHelpSearchEngine(QHelpEngineCore *helpEngine, QObject *parent = Q_NULLPTR);
    ~QHelpSearchEngine();

    QHelpSearchQueryWidget* queryWidget();
    QHelpSearchResultWidget* resultWidget();

#ifdef QT_DEPRECATED
    QT_DEPRECATED int hitsCount() const;
#endif
    int hitCount() const;

    typedef QPair<QString, QString> SearchHit;
    QList<SearchHit> hits(int start, int end) const;

    QList<QHelpSearchQuery> query() const;

public Q_SLOTS:
    void reindexDocumentation();
    void cancelIndexing();

    void search(const QList<QHelpSearchQuery> &queryList);
    void cancelSearching();

Q_SIGNALS:
    void indexingStarted();
    void indexingFinished();

    void searchingStarted();
    void searchingFinished(int hits);

private Q_SLOTS:
    void indexDocumentation();

private:
    QHelpSearchEnginePrivate *d;
};

QT_END_NAMESPACE

#endif  // QHELPSEARCHENGINE_H
