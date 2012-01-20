/* advancedframe.hpp
 * This is the header file which contains the code for the "Options" tab.
 */
#ifndef OPTIONSFRAME_HPP
#define OPTIONSFRAME_HPP
#include <QtGui>
#include "functions.hpp"

class OptionFrame : public QGroupBox
{
    Q_OBJECT

public:
    OptionFrame();
    
private slots:
    void economy_pressed();
    void temperature_pressed();
    void weather_pressed();
    void caveins_pressed();
    void invaders_pressed();
    void liquid_pressed();
    void popcap_pressed();
    void childcap_pressed();
    void dataChanged();

private:
    void populateButtons();

    QPushButton *economy, *temperature, *weather, *caveins, *invaders, *liquid, *popcap, *childcap;
    QGridLayout *grid;
    
};

class ModFrame : public QGroupBox
{
    Q_OBJECT

public:
    ModFrame();
    
private slots:
    void aquifers_pressed();
    void exotic_pressed();
    void dataChanged();

private:
    QPushButton *aquifers, *exotic;
    QHBoxLayout *box;

};

class KeyFrame : public QGroupBox
{
    Q_OBJECT

public:
    KeyFrame();

private slots:
    void load_pressed();
    void del_pressed();
    void refresh_pressed();
    void save_pressed();

private:
    QPushButton *load, *refresh, *save, *del;
    QListView *view;
    StringListModel *model;
    QGridLayout *grid;
    QStringList *list;

};

class MainOptionsFrame : public QFrame
{
    Q_OBJECT

public:
    MainOptionsFrame();
    
private:
    OptionFrame *oframe;
    ModFrame *mframe;
    KeyFrame *kframe;
    QVBoxLayout *vbox;
    
};
#endif //OPTIONSFRAME_HPP
