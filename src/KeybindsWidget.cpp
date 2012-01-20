#include "inc/KeybindsWidget.h"

#include "DwarfFortress.h"
#include "functions.hpp"

#include <QPushButton>
#include <QListView>
#include <QGridLayout>

KeybindsWidget::KeybindsWidget(QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *grid = new QGridLayout();
    m_load = new QPushButton(tr("Load"));
    m_refresh = new QPushButton(tr("Refresh List"));
    m_save = new QPushButton(tr("Save Current As"));
    m_del = new QPushButton(tr("Delete"));
    m_view = new QListView();

    connect(m_load, SIGNAL(pressed()), this, SLOT(load_pressed()));
    connect(m_del, SIGNAL(pressed()), this, SLOT(del_pressed()));
    connect(m_refresh, SIGNAL(pressed()), this, SLOT(refresh_pressed()));
    connect(m_save, SIGNAL(pressed()), this, SLOT(save_pressed()));

    getKeybindings(m_list);
    m_model = new StringListModel(m_list);
    m_view->setModel(m_model);
    grid->addWidget(m_view, 0, 0, 3, 1);
    grid->addWidget(m_load, 0, 1, 1, 2);
    grid->addWidget(m_save, 1, 1, 1, 2);
    grid->addWidget(m_refresh, 2, 1, 1, 1);
    grid->addWidget(m_del, 2, 2, 1, 1);

    setLayout(grid);
}


void KeybindsWidget::load_pressed()
{
    const QString keybinds_filename( m_model->data(m_view->currentIndex(), Qt::DisplayRole).toString() );
    QFile file1("./LNP/Keybinds/" + keybinds_filename);
    QFile file2(DwarfFortress::instance().getInterfacePath());
    bool ok = file1.open(QFile::ReadOnly);
    if(!ok) {
        QMessageBox::critical(this, "Error Opening File", QString("The keybinds file '%1' could not be opened").arg(keybinds_filename));
        return;
    }

    QByteArray buffer(file1.readAll());
    file1.close();
    ok = file2.open(QFile::WriteOnly | QFile::Truncate);
    if(!ok) {
        QMessageBox::critical(this, tr("Error Opening File"), tr("The interface file '%1' could not be opened").arg(file2.fileName()));
        return;
    }
    file2.write(buffer);
    file2.close();
    QMessageBox::information(this, tr("Keybinds Opened"), tr("Successfully opened the keybinds file '%1'").arg(keybinds_filename));
}

void KeybindsWidget::del_pressed()
{
    const QString selected = m_model->data(m_view->currentIndex(), Qt::DisplayRole).toString();
    QFile file("./LNP/Keybinds/" + selected);
    bool ok = file.remove();
    if(!ok) {
        QMessageBox::critical(this, tr("Delete Failed"), tr("Could not delete the file '%1'").arg(file.fileName()));
    }
    m_model->removeRow(m_view->currentIndex().row());
    m_view->update();
    QMessageBox::information(this, tr("Deleted File"), tr("Sucessfully deleted the file '%1'").arg(file.fileName()));
}

void KeybindsWidget::refresh_pressed()
{
    getKeybindings(m_list);
    m_model = new StringListModel(m_list);
    m_view->setModel(m_model);
    m_view->update();
}

void KeybindsWidget::save_pressed()
{
    bool ok;
    QString newfilename = QInputDialog::getText(this, tr("Save Keybinding"), tr("Save current keybindings as:"), QLineEdit::Normal, m_model->data(m_view->currentIndex(), Qt::DisplayRole).toString(), &ok);
    QFile newfile("./LNP/Keybinds/" + newfilename);
    QFile file(DwarfFortress::instance().getInterfacePath());
    if(!ok) // the user pressed cancel
        return;

    int sure = -1;
    if (newfile.exists())
    {
        QMessageBox dialog;
        dialog.setInformativeText(tr("This keybinding already exists.  Do you want to override it?"));
        dialog.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        dialog.setDefaultButton(QMessageBox::Cancel);
        sure = dialog.exec();
    }
    if (sure == QMessageBox::Yes || !newfile.exists())
    {
        bool ok = file.open(QFile::ReadOnly);
        if(!ok) {
            QMessageBox::critical(this, tr("Error Opening File"), tr("The file '%1' could not be opened").arg(file.fileName()));
            return;
        }
        QByteArray buffer(file.readAll());
        file.close();
        ok = newfile.open(QFile::WriteOnly | QFile::Truncate);
        if(!ok) {
            QMessageBox::critical(this, tr("Error Opening File"), tr("The file '%1' could not be opened").arg(newfile.fileName()));
            return;
        }
        newfile.write(buffer);
        newfile.close();
        QMessageBox::information(this, tr("Keybindings Saved"), tr("Sucessfully saved current keybindings as '%1'").arg(newfilename));
        getKeybindings(m_list);
        m_model = new StringListModel(m_list);
        m_view->setModel(m_model);
        m_view->update();
    }
}
