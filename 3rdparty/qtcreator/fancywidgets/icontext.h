/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2011 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (info@qt.nokia.com)
**
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
** If you have questions regarding the use of this file, please contact
** Nokia at info@qt.nokia.com.
**
**************************************************************************/

#ifndef ICONTEXT_H
#define ICONTEXT_H


#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QPointer>
#include <QtGui/QWidget>

namespace Core {

class Context
{
public:
    Context() {}

    explicit Context(const char *c1) { add(c1); }
    Context(const char *c1, const char *c2) { add(c1); add(c2); }
    Context(const char *c1, const char *c2, const char *c3) { add(c1); add(c2); add(c3); }
    Context(const char *base, int offset);
    void add(const char *c);
    bool contains(const char *c) const;
    bool contains(int c) const { return d.contains(c); }
    int size() const { return d.size(); }
    bool isEmpty() const { return d.isEmpty(); }
    int at(int i) const { return d.at(i); }

    // FIXME: Make interface slimmer.
    typedef QList<int>::const_iterator const_iterator;
    const_iterator begin() const { return d.begin(); }
    const_iterator end() const { return d.end(); }
    int indexOf(int c) const { return d.indexOf(c); }
    void removeAt(int i) { d.removeAt(i); }
    void prepend(int c) { d.prepend(c); }
    void add(const Context &c) { d += c.d; }
    void add(int c) { d.append(c); }
    bool operator==(const Context &c) const { return d == c.d; }

private:
    QList<int> d;
};

class IContext : public QObject
{
    Q_OBJECT
public:
    IContext(QObject *parent = 0) : QObject(parent), m_widget(0) {}

    virtual Context context() const { return m_context; }
    virtual QWidget *widget() const { return m_widget; }
    virtual QString contextHelpId() const { return m_contextHelpId; }

    virtual void setContext(const Context &context) { m_context = context; }
    virtual void setWidget(QWidget *widget) { m_widget = widget; }
    virtual void setContextHelpId(const QString &id) { m_contextHelpId = id; }

protected:
    Context m_context;
    QPointer<QWidget> m_widget;
    QString m_contextHelpId;
};

} // namespace Core

#endif //ICONTEXT_H
