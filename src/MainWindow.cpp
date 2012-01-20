#include "inc/MainWindow.h"
#include "ui_MainWindow.h"

#include "DwarfFortress.h"
#include "DwarfFortressProcess.h"

#include <QFileDialog>
#include <QDesktopServices>
#include <QProcess>
#include <QProcessEnvironment>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    resize(600,500);
    updateDFLocation();

    connect(ui->changeInstallButton, SIGNAL(clicked()), this, SLOT(changeDFPressed()));
    connect(ui->playButton, SIGNAL(clicked()), this, SLOT(playPressed()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeDFPressed()
{
    const QString dir = QFileDialog::getExistingDirectory(this, tr("Choose DF Installation Directory"), QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    DwarfFortress::instance().setDFFolder(dir);
    updateDFLocation();
}

void MainWindow::playPressed()
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

void MainWindow::updateDFLocation()
{
    if( DwarfFortress::instance().hasDF() ) {
        ui->dfInstallLabel->setText(tr("Using DF at:"));
        ui->dfLocationLabel->setText(DwarfFortress::instance().getDFFolder());
    } else {
        ui->dfInstallLabel->setText(tr("Could not find a Dwarf Fortress Installation!"));
        ui->dfLocationLabel->setText(QString());
    }
}
