/* functions.hpp
 * This header file contains various functions which are used throughout the code, along with the StringListModel class.
 */
#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <QtGui>
#include <stdlib.h>
#include <string>
#include <iostream>

// This is a custom model (stolen from the qt docs) which is used instead of QStringListModel because QStringListModel allows the user to edit the strings, which isn't something that is wanted.
class StringListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    StringListModel(const QStringList &strings, QObject *parent = 0)
        : QAbstractListModel(parent), stringList(strings) {}

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

private:
    QStringList stringList;
};

void getKeybindings(QStringList& list); // Writes the list of keybinding files in ./LNP/Keybinds/ to list.
bool copyFile(QFile& file1, QFile& file2); // Copies file1 to file2.
QStringList getContents(QString dirname, bool folders); // Returns the contents of the directory dirname, either files or folders.
void cpDir1(QDir from, QStringList &list); // These are seperated because cpDir calls itself recursively in a way that wouldn't work if cpDir1 were combined with cpDir2.
void cpDir2(QDir from, QDir to, QStringList list);
void cpDir(QDir from, QDir to); // Uses cpDir1 and cpDir2 to copy everything in from to to.

#endif
