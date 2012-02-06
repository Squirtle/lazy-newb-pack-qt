#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "DwarfFortress.h"
#include "IconLoader.h"

#include "OptionsTab.h"
#include "SetupTab.h"
#include "InitEditorWidget.h"
#include "GraphicsTab.h"
#include "AdvancedTab.h"

#include "LocalGameDataProvider.h"
#include "DFDataManager.h"

#include <manhattanstyle.h>
#include <fancytabwidget.h>

#include <QtilitiesCore>

#include <QMessageBox>
#include <QDirIterator>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_dataManager( new DFDataManager(this) ),
    m_init(false)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    if(m_init) return;
    m_init = true;
    const bool has_data = verifyLNPData();
    if( !has_data ) {
        hide();
        QMessageBox::critical(this, tr("Cannot find LNP Data"), tr("The Lazy Newb Pack data cannot be located. The program will now quit."));
        QTimer::singleShot(0, qApp, SLOT(quit()));
    } else {
        QString baseName = QApplication::style()->objectName();
#ifdef Q_WS_X11
        if (baseName == QLatin1String("windows")) {
           // Sometimes we get the standard windows 95 style as a fallback
           // e.g. if we are running on a KDE4 desktop
           QByteArray desktopEnvironment = qgetenv("DESKTOP_SESSION");
           if (desktopEnvironment == "kde")
               baseName = QLatin1String("plastique");
           else
               baseName = QLatin1String("cleanlooks");
       }
#endif
        qApp->setStyle(new ManhattanStyle(baseName));
        ui->actionQuit->setShortcut(QKeySequence::Quit);
        ui->tabs->AddTab(new SetupTab(this), IconLoader::load("lnp"), tr("Setup"));
        ui->tabs->AddTab(new OptionsTab(m_dataManager, this), IconLoader::load("configure"), tr("Options"));
        ui->tabs->AddTab(new InitEditorWidget(this), IconLoader::load("code-context"), tr("Init Editor"));
        ui->tabs->AddTab(new GraphicsTab(this), IconLoader::load("applications-graphics"), tr("Graphics"));
        ui->tabs->AddTab(new AdvancedTab(m_dataManager, this), IconLoader::load("placeholder"), tr("Advanced")); //TODO: Add real icon.
        FancyTabWidget::Mode default_mode = FancyTabWidget::Mode_LargeSidebar;
        ui->tabs->SetMode(FancyTabWidget::Mode(default_mode));
    }

    QTimer::singleShot(0, this, SLOT(loadLocalData()));
}


void MainWindow::loadLocalData()
{
     new LocalGameDataProvider(QDir::current().absolutePath()+QDir::separator() +"LNP", this);
}

bool MainWindow::verifyLNPData()
{
    QDirIterator it(".", QDir::NoDotAndDotDot | QDir::Dirs);
    while (it.hasNext()) {
        QString path = it.next();
        if (path.contains("LNP")) {
            return true;
        }
    }
    return false;
}

void MainWindow::on_actionQuit_triggered()
{
   qApp->quit();
}
