/* lnplauncher.h
 * This is the source file which contains the code for main LNP window, as well as the init files editor.
 */
#include "lnplauncher.h"
#include "functions.h"
#include "DwarfFortress.h"
#include "DwarfFortressProcess.h"

#include <QFileDialog>
#include <QDesktopServices>
#include <QProcess>
#include <QProcessEnvironment>

LNPLauncher::LNPLauncher()
{
    connect( &DwarfFortress::instance(), SIGNAL( dataChanged() ), this, SLOT( dataChanged() ));
    df_location = new QLabel(tr("Using DF Installation at: %1").arg(DwarfFortress::instance().getDFFolder()));
    df_location->setAlignment(Qt::AlignHCenter);
    QPushButton *df_changeInstall = new QPushButton(tr("Choose DF Installation"));
    play = new QPushButton(tr("Play Dwarf Fortress!"));
    init = new QPushButton(tr("Init File Editor"));
    defaults = new QPushButton(tr("Defaults"));
    tab = new QTabWidget();
    otab = new MainOptionsFrame();
    atab = new AdvancedFrame();
    gtab = new GraphicsFrame();
    grid = new QGridLayout();
    central = new QWidget();
    dialog = new InitDialog();
    mapper = new QSignalMapper();

    dialog->resize(600, 500);

    connect(df_changeInstall, SIGNAL(pressed()), this, SLOT(change_install_pressed()));
    connect(play, SIGNAL(pressed()), this, SLOT(play_pressed()));
    connect(init, SIGNAL(pressed()), this, SLOT(init_pressed()));
    connect(defaults, SIGNAL(pressed()), this, SLOT(defaults_pressed()));
    
    grid->addWidget(df_location, 0, 0, 1, 3);
    grid->addWidget(df_changeInstall, 1, 0, 1, 3);
    grid->addWidget(tab, 2, 0, 1, 3);
    grid->addWidget(play, 3, 0, 1, 1);
    grid->addWidget(init, 3, 1, 1, 1);
    grid->addWidget(defaults, 3, 2, 1, 1);
    
    tab->addTab(otab, "Options");
    tab->addTab(gtab, "Graphics");
    tab->addTab(atab, "Advanced");
    
    central->setLayout(grid);
    setCentralWidget(central);

    create_actions();
    create_menus();
}

InitDialog::InitDialog(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
{
    save = new QPushButton(tr("Save"));
    load = new QPushButton(tr("Load"));
    grid = new QGridLayout();
    init = new QTextEdit();
    dinit = new QTextEdit();
    QSplitter *splitter = new QSplitter();

    QFile initfile(DwarfFortress::instance().getInitPath());
    QFile dinitfile(DwarfFortress::instance().getDInitPath());
    initfile.open(QFile::ReadOnly);
    QString *inittext = new QString(initfile.readAll());
    initfile.close();
    dinitfile.open(QFile::ReadOnly);
    QString *dinittext = new QString(dinitfile.readAll());
    dinitfile.close();
    init->setPlainText(*inittext);
    dinit->setPlainText(*dinittext);

    connect(save, SIGNAL(pressed()), this, SLOT(save_pressed()));
    connect(load, SIGNAL(pressed()), this, SLOT(load_pressed()));

    splitter->addWidget(init);
    splitter->addWidget(dinit);
    grid->addWidget(splitter, 0, 0, 1, 5);
    grid->addWidget(load, 1, 3, 1, 1);
    grid->addWidget(save, 1, 4, 1, 1);

    setLayout(grid);
}

void LNPLauncher::play_pressed()
{
    #ifdef Q_WS_X11
        QProcessEnvironment env(  QProcessEnvironment::systemEnvironment () );

        // Work around for bug in Debian/Ubuntu SDL patch.
        env.insert( "SDL_DISABLE_LOCK_KEYS", "1");

        // Center the screen.  Messes up resizing. TODO: who/what needs this?
        //env.insert( "SDL_VIDEO_CENTERED", "1");

        DwarfFortressProcess *df = new DwarfFortressProcess(this);
        df->setWorkingDirectory(DwarfFortress::instance().getDFFolder());
        df->setProcessEnvironment(env);
        df->start("./libs/Dwarf_Fortress");

    #endif
    #ifdef Q_WS_WIN
        QProcess::startDetached("\"" + DwarfFortress::instance().getDFFolder() + "/Dwarf Fortress.exe\"");
    #endif
}

void LNPLauncher::init_pressed()
{
    dialog->load_pressed();
    dialog->exec();
    reload();
}

void LNPLauncher::defaults_pressed()
{
    QMessageBox msg;
    msg.setText(tr("Are you sure that you want to reset all init settings to their defaults?"));
    msg.setInformativeText(tr("Note that this won't effect settings not controlled by the init and d_init files, such as the aquifers setting."));
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::Cancel);
    int sure = msg.exec();
    if (sure == QMessageBox::Yes)
    {
        QFile oldinit(DwarfFortress::instance().getInitPath()), newinit(tr("./LNP/Defaults/init.txt")), olddinit(DwarfFortress::instance().getDInitPath()), newdinit(tr("./LNP/Defaults/d_init.txt"));
        oldinit.open(QFile::ReadOnly);
        QByteArray *buffer = new QByteArray(oldinit.readAll());
        oldinit.close();
        newinit.open(QFile::WriteOnly | QFile::Truncate);
        newinit.write(*buffer);
        newinit.close();
        olddinit.open(QFile::ReadOnly);
        olddinit.close();
        newdinit.open(QFile::WriteOnly | QFile::Truncate);
        newdinit.write(*buffer);
        newdinit.close();
        delete buffer;
        QMessageBox success;
        success.setText(tr("Init settings restored to defaults!"));
        success.exec();
        reload();
    }
}

void InitDialog::load_pressed()
{
    QFile initfile(DwarfFortress::instance().getInitPath()), dinitfile(DwarfFortress::instance().getDInitPath());
    initfile.open(QFile::ReadOnly);
    QString *inittext = new QString(initfile.readAll());
    initfile.close();
    dinitfile.open(QFile::ReadOnly);
    QString *dinittext = new QString(dinitfile.readAll());
    dinitfile.close();
    init->setPlainText(*inittext);
    dinit->setPlainText(*dinittext);
}

void InitDialog::save_pressed()
{
    QFile initfile(DwarfFortress::instance().getInitPath()), dinitfile(DwarfFortress::instance().getDInitPath());
    initfile.open(QFile::WriteOnly | QFile::Truncate | QFile::Text);
    QString *inittext = new QString(init->toPlainText());
    initfile.write(inittext->toAscii());
    initfile.close();
    dinitfile.open(QFile::WriteOnly | QFile::Truncate | QFile::Text);
    QString *dinittext = new QString(dinit->toPlainText());
    dinitfile.write(dinittext->toAscii());
    dinitfile.close();
}

<<<<<<< HEAD
=======
void LNPLauncher::change_install_pressed()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose DF Installation Directory"), QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    DwarfFortress::instance().setDFFolder(dir);
    df_location->setText(tr("Using DF Installation at: %1").arg(DwarfFortress::instance().getDFFolder()));
}

/*
 
>>>>>>> ramblurr/master
void LNPLauncher::create_actions()
{
    linkList << "$DF/data/save/" << "./LNP/Utilities/" << "./LNP/Graphics/" << "$DF" << "./LNP/Extras/data/" << "./LNP/" << "$DF/data/init/" << "http://www.bay12games.com/dwarves/"<< "http://df.magmawiki.com/" << "http://www.bay12forums.com/smf/" << "http://www.bay12forums.com/smf/index.php?topic=59026.0";

    if (getDFFolder() != "ERR")
        linkList.replaceInStrings("$DF", getDFFolder());
    else
        linkList.replaceInStrings("$DF", "DF Folder not found");

    reloadAct = new QAction(tr("&Re-load param set"), this);
    reloadAct->setShortcuts(QKeySequence::Open);
    reloadAct->setStatusTip(tr("Note: LNP loads when opened."));
    connect(reloadAct, SIGNAL(triggered()), this, SLOT(reload()));

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    dfAct = new QAction(tr("&Dwarf Fortress"), this);
    connect(dfAct, SIGNAL(triggered()), this, SLOT(play_pressed()));

    initAct = new QAction(tr("&Init File Editor"), this);
    connect(initAct, SIGNAL(triggered()), this, SLOT(init_pressed()));

    //In retrospect, the following could be made into a loop by using containers.

    savefolderAct = new QAction(tr("&Savegame Folder"), this);
    connect(savefolderAct, SIGNAL(triggered()), mapper, SLOT(map()));
    mapper->setMapping(savefolderAct, linkList[0]);

    utilsfolderAct = new QAction(tr("&Utilities Folder"), this);
    connect(utilsfolderAct, SIGNAL(triggered()), mapper, SLOT(map()));
    mapper->setMapping(utilsfolderAct, linkList[1]);

    graphicsfolderAct = new QAction(tr("&Graphics Folder"), this);
    connect(graphicsfolderAct, SIGNAL(triggered()), mapper, SLOT(map()));
    mapper->setMapping(graphicsfolderAct, linkList[2]);

    dffolderAct = new QAction(tr("&Dwarf Fortress Folder"), this);
    connect(dffolderAct, SIGNAL(triggered()), mapper, SLOT(map()));
    mapper->setMapping(dffolderAct, linkList[3]);

    lnpdatafolderAct = new QAction(tr("&LNP Data Folder"), this);
    connect(lnpdatafolderAct, SIGNAL(triggered()), mapper, SLOT(map()));
    mapper->setMapping(lnpdatafolderAct, linkList[4]);

    lnprootfolderAct = new QAction(tr("&LNP Root Folder"), this);
    connect(lnprootfolderAct, SIGNAL(triggered()), mapper, SLOT(map()));
    mapper->setMapping(lnprootfolderAct, linkList[5]);

    dfinitfolderAct = new QAction(tr("&DF Init Folder"), this);
    connect(dfinitfolderAct, SIGNAL(triggered()), mapper, SLOT(map()));
    mapper->setMapping(dfinitfolderAct, linkList[6]);

    dfhomepageAct = new QAction(tr("&DF Homepage"), this);
    connect(dfhomepageAct, SIGNAL(triggered()), mapper, SLOT(map()));
    mapper->setMapping(dfhomepageAct, linkList[7]);

    dfwikiAct = new QAction(tr("&DF Wiki"), this);
    connect(dfwikiAct, SIGNAL(triggered()), mapper, SLOT(map()));
    mapper->setMapping(dfwikiAct, linkList[8]);

    dfforumsAct = new QAction(tr("&DF Forums"), this);
    connect(dfforumsAct, SIGNAL(triggered()), mapper, SLOT(map()));
    mapper->setMapping(dfforumsAct, linkList[9]);

    lnpthreadAct = new QAction(tr("&LNP Forum Thread"), this);
    connect(lnpthreadAct, SIGNAL(triggered()), mapper, SLOT(map()));
    mapper->setMapping(lnpthreadAct, linkList[10]);

    connect(mapper, SIGNAL(mapped(const QString &)), this, SLOT(open(const QString &)));
}

void LNPLauncher::create_menus()
{
    filemenu = menuBar()->addMenu(tr("&File"));
    filemenu->addAction(reloadAct);
    filemenu->addAction(exitAct);

    runmenu = menuBar()->addMenu(tr("&Run"));
    runmenu->addAction(dfAct);
    runmenu->addAction(initAct);

    openmenu = runmenu->addMenu(tr("&Open Folder"));
    openmenu->addAction(savefolderAct);
    openmenu->addAction(utilsfolderAct);
    openmenu->addAction(graphicsfolderAct);
    openmenu->addSeparator();
    openmenu->addAction(dffolderAct);
    openmenu->addAction(lnpdatafolderAct);
    openmenu->addSeparator();
    openmenu->addAction(lnprootfolderAct);
    openmenu->addAction(dfinitfolderAct);

    linksmenu = menuBar()->addMenu(tr("&Links"));
    linksmenu->addAction(dfhomepageAct);
    linksmenu->addAction(dfwikiAct);
    linksmenu->addAction(dfforumsAct);
    linksmenu->addAction(lnpthreadAct);
}

void LNPLauncher::reload()
{
    otab->reload();
    gtab->reload();
    atab->reload();
}

void LNPLauncher::open(const QString &path)
{
    #ifdef Q_WS_X11
        QProcess::startDetached(tr("xdg-open \"") + path + tr("\""));
    #endif
    #ifdef Q_WS_WIN
        QProcess::startDetached(tr("start \"") + path + tr("\""));
    #endif
}
<<<<<<< HEAD
=======
*/


void LNPLauncher::dataChanged()
{
    df_location->setText(tr("Using DF Installation at: %1").arg(DwarfFortress::instance().getDFFolder()));
    delete dialog;
    dialog = new InitDialog();
}
>>>>>>> ramblurr/master
