#include "KeybindsWidget.h"

#include "DwarfFortress.h"
#include "functions.h"

#include "IKeybindsBundle.h"
#include "GameDataModel.h"

#include <QtilitiesCoreGui>
#include <QtilitiesCore>

#include <QPushButton>
#include <QListView>
#include <QGridLayout>
#include <QTimer>
#include <QListView>

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

    m_keybindsObserver = new QtilitiesCore::Observer("keybindsObserver", "", this);
    QtilitiesCoreGui::ObserverWidget* observer_widget = new QtilitiesCoreGui::ObserverWidget;
    observer_widget->setDisplayMode(Qtilities::TableView);
    observer_widget->setCustomTableModel(new GameDataModel(this));
    observer_widget->setObserverContext(m_keybindsObserver);
    QtilitiesCoreGui::ObserverHints* hints = observer_widget->activeHints();
    hints->setDisplayFlagsHint(Qtilities::Core::ObserverHints::ItemView);
    hints->setHierarchicalDisplayHint(Qtilities::Core::ObserverHints::FlatHierarchy);
    observer_widget->setCustomHints(hints);
    observer_widget->toggleUseObserverHints(false);
    observer_widget->initialize();
    observer_widget->tableView()->horizontalHeader()->hide();
    observer_widget->tableView()->verticalHeader()->hide();

    grid->addWidget(observer_widget, 0, 0, 3, 1);
    grid->addWidget(m_load, 0, 1, 1, 2);
    grid->addWidget(m_save, 1, 1, 1, 2);
    grid->addWidget(m_refresh, 2, 1, 1, 1);
    grid->addWidget(m_del, 2, 2, 1, 1);

    setLayout(grid);

    connect( OBJECT_MANAGER, SIGNAL(newObjectAdded(QObject*)), this, SLOT(globalObjectAdded(QObject*)));
    QTimer::singleShot(0, this, SLOT(gatherData()));
}

void KeybindsWidget::globalObjectAdded( QObject* obj )
{
    IKeybindsBundle *bundle = qobject_cast< IKeybindsBundle* >(obj);
    if( bundle ) {
        bundle->objectBase()->setObjectName(bundle->name());
        m_keybindsObserver->attachSubject( obj );
    }
}

void KeybindsWidget::gatherData()
{
    QList<QObject*> ifaces = OBJECT_MANAGER->registeredInterfaces("com.lazynewb.IKeybindsBundle/1.0");
    qDebug() << "gathering shit" << ifaces.length() << OBJECT_MANAGER->objectPool()->subjectCount();
    foreach(QObject* obj, ifaces) {
        IKeybindsBundle *bundle = qobject_cast< IKeybindsBundle* >(obj);
        qDebug() << "helllo" <<bundle;
        if( bundle ) {
            qDebug() << "Found keybinds bundle" << bundle->name() << bundle->objectBase();
            bundle->objectBase()->setObjectName(bundle->name());
            bool result = m_keybindsObserver->attachSubject( obj );
            qDebug() << "ATTACH RESULT" << result;
        }
    }
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
