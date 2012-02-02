/* lnplauncher.h
 * This is the header file which contains the code for main LNP window, as well as the init files editor.
 */
#ifndef LNPLAUNDER_HPP
#define LNPLAUNDER_HPP
#include <QtGui>
#include "optionsframe.h"
#include "advancedframe.h"
#include "graphicsframe.h"

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
<<<<<<< HEAD:inc/lnplauncher.hpp
    void reload(); // Reloads all options from the init files and RAWs.
    void open(const QString &path); // Opens the file, folder, or website located at path with the default program.
//  TODO:  void about(); // Opens an about dialog.

=======
    void change_install_pressed();
/*  void reload(); // Reloads all options from the init files and RAWs.
    void resave(); // Resaves all options to the init files and RAWs.
    // The reload and resave functions present a problem because there is no easy way to access all the options selected in the launcher. We'll probably have to end up adding functions which will allow us to access them.
    void exit(); // Closes the LNP GUI.
    void folder(QString path); // Opens the folder in the default file browser.
    void link(QString URL); // Opens the link in the default web browser.
    void about(); // Opens an about dialog.
*/
>>>>>>> ramblurr/master:src/lnplauncher.h

    void dataChanged();

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
<<<<<<< HEAD:inc/lnplauncher.hpp

    QMenu *filemenu;
=======
    QLabel *df_location;
/*  QMenu *filemenu;
>>>>>>> ramblurr/master:src/lnplauncher.h
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
