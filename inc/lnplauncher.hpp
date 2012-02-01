/* lnplauncher.hpp
 * This is the header file which contains the code for main LNP window, as well as the init files editor.
 */
#ifndef LNPLAUNDER_HPP
#define LNPLAUNDER_HPP
#include <QtGui>
#include "optionsframe.hpp"
#include "advancedframe.hpp"
#include "graphicsframe.hpp"

class InitDialog : public QDialog
{
    Q_OBJECT

public:
    InitDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);

public slots:
    void load_pressed();

private slots:
    void save_pressed();

private:
    QPushButton *save, *load;
    QTextEdit *init, *dinit;
    QGridLayout *grid;

};

class LNPLauncher : public QMainWindow
{
    Q_OBJECT

public:
    LNPLauncher();

private slots:
    void play_pressed();
    void init_pressed();
    void defaults_pressed();
    void reload(); // Reloads all options from the init files and RAWs.
    void open(const QString &path); // Opens the file, folder, or website located at path with the default program.
//  TODO:  void about(); // Opens an about dialog.


private:
    void create_actions();
    void create_menus();

    QTabWidget* tab;
    QPushButton* play, *init, *defaults;
    MainOptionsFrame* otab;
    AdvancedFrame* atab;
    GraphicsFrame* gtab;
    QGridLayout* grid;
    QWidget* central;

    QSignalMapper* mapper;
    QStringList linkList; //list of links and folders to be opened by the menu, to be used by the QSignalMapper

    InitDialog *dialog;

    QMenu *filemenu;
    QMenu *runmenu;
    QMenu *openmenu;
    QMenu *linksmenu;
//  QMenu *helpmenu;
    QAction *reloadAct;
    QAction *exitAct;
    QAction *dfAct;
    QAction *initAct;
    QAction *savefolderAct;
    QAction *utilsfolderAct;
    QAction *graphicsfolderAct;
    QAction *dffolderAct;
    QAction *lnpdatafolderAct;
    QAction *lnprootfolderAct;
    QAction *dfinitfolderAct;
    QAction *dfhomepageAct;
    QAction *dfwikiAct;
    QAction *dfforumsAct;
    QAction *lnpthreadAct;
//  QAction *aboutAct;
    
};
#endif //LNPLAUNDER_HPP
