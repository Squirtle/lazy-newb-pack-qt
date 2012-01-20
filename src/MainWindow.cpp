#include "inc/MainWindow.h"
#include "ui_MainWindow.h"

#include "DwarfFortress.h"
#include "DwarfFortressProcess.h"

#include "InitEditorDialog.h"

#include <QFileDialog>
#include <QDesktopServices>
#include <QProcess>
#include <QProcessEnvironment>
#include <QPointer>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    updateDFLocation();

    connect(ui->changeInstallButton, SIGNAL(clicked()), this, SLOT(changeDFPressed()));
    connect(ui->playButton, SIGNAL(clicked()), this, SLOT(playPressed()));
    connect(ui->initEditButton, SIGNAL(clicked()), this, SLOT(editInitPressed()));
    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(defaultsPressed()));

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

void MainWindow::editInitPressed()
{
    QPointer<InitEditorDialog> dlg = new InitEditorDialog( this ); //the dlg-on-heap-variant
    dlg->exec();
    delete dlg;
}

void MainWindow::defaultsPressed()
{
    QMessageBox msg(this);
    msg.setText(tr("Are you sure that you want to reset all init settings to their defaults?"));
    msg.setInformativeText(tr("Note that this won't effect settings not controlled by the init and d_init files, such as the aquifers setting."));
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg.setDefaultButton(QMessageBox::No);
    int sure = msg.exec();
    if (sure == QMessageBox::Yes)
    {
        QFile oldinit(DwarfFortress::instance().getInitPath()), newinit("./LNP/Defaults/init.txt");
        QFile olddinit(DwarfFortress::instance().getDInitPath()), newdinit(tr("./LNP/Defaults/d_init.txt"));

        Q_ASSERT(newinit.exists());
        Q_ASSERT(newdinit.exists());

        oldinit.remove();
        olddinit.remove();
        newinit.copy(DwarfFortress::instance().getInitPath());
        newdinit.copy(DwarfFortress::instance().getDInitPath());

        QMessageBox::information(this, tr("Defaults Restored"), tr("Init settings restored to defaults!"));
        DwarfFortress::instance().notifyChange();
    }
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
