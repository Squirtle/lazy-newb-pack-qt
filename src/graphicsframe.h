/* advancedframe.h
 * This is the header file which contains the code for the "Graphics" tab.
 */
#ifndef GRAHPICSFRAME_HPP
#define GRAHPICSFRAME_HPP
#include <QtGui>
#include "functions.h"

class ChangeFrame : public QGroupBox
{
    Q_OBJECT

public:
    ChangeFrame();
    void reload();

private slots:
    void install_pressed();
    void upgrade_pressed();
    void truetype_pressed();
    void update_pressed();

private:
    QListView *view;
    StringListModel *model;
    QStringList *list;
    QPushButton *install, *upgrade, *truetype, *update;
    QGridLayout *grid;

};

class AdvancedGraphicsFrame : public QGroupBox
{
    Q_OBJECT

public:
    AdvancedGraphicsFrame();

private slots:
    /*
    void open_pressed();
    void simplify_pressed();
    */

private:
    QPushButton *open, *simplify;
    QGridLayout *grid;

};

class GraphicsFrame : public QFrame
{
    Q_OBJECT

public:
    GraphicsFrame();
    void reload();

private:
    ChangeFrame *changeframe;
    AdvancedGraphicsFrame *advancedgraphicsframe;
    QVBoxLayout *box;

};
#endif //GRAHPICSFRAME_HPP
