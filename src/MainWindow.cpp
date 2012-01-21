#include "inc/MainWindow.h"
#include "ui_MainWindow.h"

#include "DwarfFortress.h"
#include "IconLoader.h"
#include "OptionsTab.h"
#include "SetupTab.h"
#include "InitEditorDialog.h"

#include <manhattanstyle.h>
#include <fancytabwidget.h>


#include <QMessageBox>
#include <QDirIterator>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
        ui->tabs->AddTab(new SetupTab(this), IconLoader::load("lnp"), tr("Setup"));
        ui->tabs->AddTab(new OptionsTab(this), IconLoader::load("configure"), tr("Options"));
        ui->tabs->AddTab(new InitEditorDialog(this), IconLoader::load("code-context"), tr("Init Editor"));
        FancyTabWidget::Mode default_mode = FancyTabWidget::Mode_LargeSidebar;
        ui->tabs->SetMode(FancyTabWidget::Mode(default_mode));
    }

}

MainWindow::~MainWindow()
{
    delete ui;
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
