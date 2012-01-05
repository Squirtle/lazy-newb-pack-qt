/* lnplauncher.hpp
 * This is the source file which contains the code for main LNP window, as well as the init files editor.
 */
#include "lnplauncher.hpp"
#include "functions.hpp"

LNPLauncher::LNPLauncher()
{
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

    dialog->resize(600, 500);

    connect(play, SIGNAL(pressed()), this, SLOT(play_pressed()));
    connect(init, SIGNAL(pressed()), this, SLOT(init_pressed()));
    connect(defaults, SIGNAL(pressed()), this, SLOT(defaults_pressed()));
    
    grid->addWidget(tab, 0, 0, 1, 3);
    grid->addWidget(play, 1, 0, 1, 1);
    grid->addWidget(init, 1, 1, 1, 1);
    grid->addWidget(defaults, 1, 2, 1, 1);
    
    tab->addTab(otab, "Options");
    tab->addTab(gtab, "Graphics");
    tab->addTab(atab, "Advanced");
    
//    setCentralWidget(tab);
    central->setLayout(grid);
    setCentralWidget(central);
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

    QFile initfile(getDFFolder() + tr("/data/init/init.txt")), dinitfile(getDFFolder() + tr("/data/init/d_init.txt"));
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
        QProcess::startDetached(tr("\"") + getDFFolder() + tr("/df\""));
    #endif
    #ifdef Q_WS_WIN
        QProcess::startDetached(tr("\"") + getDFFolder() + tr("/Dwarf Fortress.exe\""));
    #endif
}

void LNPLauncher::init_pressed()
{
    dialog->load_pressed();
    dialog->show();
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
        QFile oldinit(getDFFolder() + tr("/data/init/init.txt")), newinit(tr("./LNP/Defaults/init.txt")), olddinit(getDFFolder() + tr("/data/init/d_init.txt")), newdinit(tr("./LNP/Defaults/d_init.txt"));
        oldinit.open(QFile::ReadOnly);
        QByteArray *buffer = new QByteArray(oldinit.readAll());
        oldinit.close();
        newinit.open(QFile::WriteOnly | QFile::Truncate);
        newinit.write(*buffer);
        newinit.close();
        olddinit.open(QFile::ReadOnly);
        buffer = new QByteArray(olddinit.readAll());
        olddinit.close();
        newdinit.open(QFile::WriteOnly | QFile::Truncate);
        newdinit.write(*buffer);
        newdinit.close();
        delete buffer;
        QMessageBox success;
        success.setText(tr("Init settings restored to defaults!"));
        success.exec();
    }
}

void InitDialog::load_pressed()
{
    QFile initfile(getDFFolder() + tr("/data/init/init.txt")), dinitfile(getDFFolder() + tr("/data/init/d_init.txt"));
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
    QFile initfile(getDFFolder() + tr("/data/init/init.txt")), dinitfile(getDFFolder() + tr("/data/init/d_init.txt"));
    initfile.open(QFile::WriteOnly | QFile::Truncate | QFile::Text);
    QString *inittext = new QString(init->toPlainText());
    initfile.write(inittext->toAscii());
    initfile.close();
    dinitfile.open(QFile::WriteOnly | QFile::Truncate | QFile::Text);
    QString *dinittext = new QString(dinit->toPlainText());
    dinitfile.write(dinittext->toAscii());
    dinitfile.close();
}

/*
 
void LNPLauncher::create_actions()
{
    reloadAct = new QAction(tr("&Re-load param set"), this);
    reloadAct->setShortcuts(QKeySequence::Open);
    reloadAct->setStatusTip(tr("Note: LNP loads when opened."));
    connect(reloadAct, SIGNAL(triggered()), this, SLOT(reload()));

    resaveAct = new QAction(tr("&Re-save param set"), this);
    resaveAct->setShortcuts(QKeySequence::Save);
    resaveAct->setStatusTip(tr("Note: LNP automatically saves."));
    connect(resaveAct, SIGNAL(triggered()), this, SLOT(resave()));

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(exit()));

    dfAct = new QAction(tr("&Dwarf Fortress"), this);
    connect(dfAct, SIGNAL(triggered()), this, SLOT(play_pressed()));

    initAct = new QAction(tr("&Init File Editor"), this);
    connect(initAct, SIGNAL(triggered()), this, SLOT(init_pressed()));

    savefolderAct = new QAction(tr("&Savegame Folder"), this);
    connect(savefolderAct, SIGNAL(triggered()), this, SLOT(folder(getDFFolder() + tr("/data/save/"))));

    utilsfolderAct = new QAction(tr("&Utilities Folder"), this);
    connect(utilsfolderAct, SIGNAL(triggered()), this, SLOT(folder(tr("./LNP/Utilities/"))));

    graphicsfolderAct = new QAction(tr("&Graphics Folder"), this);
    connect(graphicsfolderAct, SIGNAL(triggered()), this, SLOT(folder(tr("./LNP/Graphics/"))));

    dffolderAct = new QAction(tr("&Dwarf Fortress Folder"), this);
    connect(dffolderAct, SIGNAL(triggered()), this, SLOT(folder(getDFFolder())));

    lnpdatafolderAct = new QAction(tr("&LNP Data Folder"), this);
    connect(lnpdatafolderAct, SIGNAL(triggered()), this, SLOT(folder(tr("./LNP/Extras/data/")))); //Check this one on a Windows machine. Proabaly would be a good idea to check all of them that aren't super obvious, actually.

    lnprootfolderAct = new QAction(tr("&LNP Root Folder"), this);
    connect(lnprootfolderAct, SIGNAL(triggered()), this, SLOT(folder(tr("./LNP/"))));

    dfinitfolderAct = new QAction(tr("&DF Init Folder"), this);
    connect(dfinitfolderAct, SIGNAL(triggered()), this, SLOT(folder(getDFFolder() + tr("/data/init/"))));

    dfhomepageAct = new QAction(tr("&DF Homepage"), this);
    connect(dfhomepageAct, SIGNAL(triggered()), this, SLOT(link(tr("http://www.bay12games.com/dwarves/"))));

    dfwikiAct = new QAction(tr("&DF Wiki"), this);
    connect(dfhomepageAct, SIGNAL(triggered()), this, SLOT(link(tr("http://df.magmawiki.com/"))));

    dfforumsAct = new QAction(tr("&DF Forums"), this);
    connect(dfhomepageAct, SIGNAL(triggered()), this, SLOT(link(tr("http://www.bay12forums.com/smf/"))));

    lnpthreadAct = new QAction(tr("&LNP Forum Thread"), this);
    connect(dfhomepageAct, SIGNAL(triggered()), this, SLOT(link(tr("http://www.bay12forums.com/smf/index.php?topic=59026.0"))));
}
*/
