/* advancedframe.hpp
 * This is the source file which contains the code for the "Options" tab.
 */
#include "optionsframe.hpp"
#include "functions.hpp"
#include "DwarfFortress.h"

OptionFrame::OptionFrame()
    :  QGroupBox(tr("Options"))
{
    connect( &DwarfFortress::instance(), SIGNAL( dfFolderChanged() ), this, SLOT( dfFolderChanged() ));
    economy = new QPushButton(tr("Economy: ") + DwarfFortress::instance().getOption(tr("ECONOMY")));
    temperature = new QPushButton(tr("Temperature: ") + DwarfFortress::instance().getOption(tr("TEMPERATURE")));
    weather = new QPushButton(tr("Weather: ") + DwarfFortress::instance().getOption(tr("WEATHER")));
    caveins = new QPushButton(tr("Cave-ins: ") + DwarfFortress::instance().getOption(tr("CAVEINS")));
    invaders = new QPushButton(tr("Invaders: ") + DwarfFortress::instance().getOption(tr("INVADERS")));
    liquid = new QPushButton(tr("Liquid Depth: ") + DwarfFortress::instance().getOption(tr("SHOW_FLOW_AMOUNTS")));
    popcap = new QPushButton(tr("Population Cap: ") + DwarfFortress::instance().getOption(tr("POPULATION_CAP")));
    childcap = new QPushButton(tr("Child Cap: ") + DwarfFortress::instance().getOption(tr("BABY_CHILD_CAP")));
    
    connect(economy, SIGNAL(pressed()), this, SLOT(economy_pressed()));
    connect(temperature, SIGNAL(pressed()), this, SLOT(temperature_pressed()));
    connect(weather, SIGNAL(pressed()), this, SLOT(weather_pressed()));
    connect(caveins, SIGNAL(pressed()), this, SLOT(caveins_pressed()));
    connect(invaders, SIGNAL(pressed()), this, SLOT(invaders_pressed()));
    connect(liquid, SIGNAL(pressed()), this, SLOT(liquid_pressed()));
    connect(popcap, SIGNAL(pressed()), this, SLOT(popcap_pressed()));
    connect(childcap, SIGNAL(pressed()), this, SLOT(childcap_pressed()));
    
    grid = new QGridLayout();
    grid->addWidget(economy, 0, 0, 1, 1);
    grid->addWidget(temperature, 1, 0, 1, 1);
    grid->addWidget(weather, 2, 0, 1, 1);
    grid->addWidget(caveins, 3, 0, 1, 1);
    grid->addWidget(invaders, 0, 1, 1, 1);
    grid->addWidget(liquid, 1, 1, 1, 1);
    grid->addWidget(popcap, 2, 1, 1, 1);
    grid->addWidget(childcap, 3, 1, 1, 1);

    setLayout(grid);
}

ModFrame::ModFrame()
    :  QGroupBox(tr("Mods"))
{
    connect( &DwarfFortress::instance(), SIGNAL( dfFolderChanged() ), this, SLOT( dfFolderChanged() ));
    aquifers = new QPushButton(tr("Aquifers: ") + DwarfFortress::instance().rawsFind(tr("[AQUIFER]")));
    if (DwarfFortress::instance().rawsFind(tr("[PET_EXOTIC]")) == tr("YES"))
        exotic = new QPushButton(tr("Exotic Animals: ") + DwarfFortress::instance().rawsFind(tr("[PET_EXOTIC]")));
    else
        exotic = new QPushButton(tr("Exotic Animals: ") + DwarfFortress::instance().rawsFind(tr("[MOUNT_EXOTIC]")));
    
    connect(aquifers, SIGNAL(pressed()), this, SLOT(aquifers_pressed()));
    connect(exotic, SIGNAL(pressed()), this, SLOT(exotic_pressed()));

    box = new QHBoxLayout();
    box->addWidget(aquifers);
    box->addWidget(exotic);

    setLayout(box);
}

KeyFrame::KeyFrame()
    :  QGroupBox(tr("Key Bindings"))
{
    load = new QPushButton(tr("Load"));
    refresh = new QPushButton(tr("Refresh List"));
    save = new QPushButton(tr("Save Current As"));
    del = new QPushButton(tr("Delete"));
    view = new QListView();
    grid = new QGridLayout();
    list = new QStringList();

    connect(load, SIGNAL(pressed()), this, SLOT(load_pressed()));
    connect(del, SIGNAL(pressed()), this, SLOT(del_pressed()));
    connect(refresh, SIGNAL(pressed()), this, SLOT(refresh_pressed()));
    connect(save, SIGNAL(pressed()), this, SLOT(save_pressed()));
    
    getKeybindings(*list);
    model = new StringListModel(*list);
    view->setModel(model);
    grid->addWidget(view, 0, 0, 3, 1);
    grid->addWidget(load, 0, 1, 1, 2);
    grid->addWidget(save, 1, 1, 1, 2);
    grid->addWidget(refresh, 2, 1, 1, 1);
    grid->addWidget(del, 2, 2, 1, 1);

    setLayout(grid);

}

MainOptionsFrame::MainOptionsFrame()
{
    setFrameStyle(QFrame::NoFrame);
    oframe = new OptionFrame();
    mframe = new ModFrame();
    kframe = new KeyFrame();
    vbox = new QVBoxLayout();
    
    vbox->addWidget(oframe);
    vbox->addWidget(mframe);
    vbox->addWidget(kframe);

    setLayout(vbox);
    
}

void OptionFrame::dfFolderChanged()
{
    populateButtons();
}

void ModFrame::dfFolderChanged()
{
    aquifers->setText("Aquifers: " + DwarfFortress::instance().rawsFind("[AQUIFER]"));
    if (DwarfFortress::instance().rawsFind("[PET_EXOTIC]") == "YES")
        exotic->setText("Exotic Animals: " + DwarfFortress::instance().rawsFind("[PET_EXOTIC]"));
    else
        exotic->setText("Exotic Animals: " + DwarfFortress::instance().rawsFind("[MOUNT_EXOTIC]"));

}

void OptionFrame::populateButtons()
{
    economy->setText(tr("Economy: ") + DwarfFortress::instance().getOption("ECONOMY"));
    temperature->setText(tr("Temperature: ") + DwarfFortress::instance().getOption("TEMPERATURE"));
    weather->setText(tr("Weather: ") + DwarfFortress::instance().getOption("WEATHER"));
    caveins->setText(tr("Cave-ins: ") + DwarfFortress::instance().getOption("CAVEINS"));
    invaders->setText(tr("Invaders: ") + DwarfFortress::instance().getOption("INVADERS"));
    liquid->setText(tr("Liquid Depth: ") + DwarfFortress::instance().getOption("SHOW_FLOW_AMOUNTS"));
    popcap->setText(tr("Population Cap: ") + DwarfFortress::instance().getOption("POPULATION_CAP"));
    childcap->setText(tr("Child Cap: ") + DwarfFortress::instance().getOption("BABY_CHILD_CAP"));
}

void OptionFrame::economy_pressed()
{
    if (DwarfFortress::instance().getOption("ECONOMY") == "YES")
        DwarfFortress::instance().setOption("ECONOMY", "NO");
    else
        DwarfFortress::instance().setOption("ECONOMY", "YES");
    economy->setText(tr("Economy: ") + DwarfFortress::instance().getOption("ECONOMY"));
}

void OptionFrame::temperature_pressed()
{
    if (DwarfFortress::instance().getOption(tr("TEMPERATURE")) == tr("YES"))
        DwarfFortress::instance().setOption(tr("TEMPERATURE"), tr("NO"));
    else
        DwarfFortress::instance().setOption(tr("TEMPERATURE"), tr("YES"));
    temperature->setText(tr("Temperature: ") + DwarfFortress::instance().getOption(tr("TEMPERATURE")));
}

void OptionFrame::weather_pressed()
{
    if (DwarfFortress::instance().getOption(tr("WEATHER")) == tr("YES"))
        DwarfFortress::instance().setOption(tr("WEATHER"), tr("NO"));
    else
        DwarfFortress::instance().setOption(tr("WEATHER"), tr("YES"));
    weather->setText(tr("Weather: ") + DwarfFortress::instance().getOption(tr("WEATHER")));
}

void OptionFrame::caveins_pressed()
{
    if (DwarfFortress::instance().getOption(tr("CAVEINS")) == tr("YES"))
        DwarfFortress::instance().setOption(tr("CAVEINS"), tr("NO"));
    else
        DwarfFortress::instance().setOption(tr("CAVEINS"), tr("YES"));
    caveins->setText(tr("Cave-ins: ") + DwarfFortress::instance().getOption(tr("CAVEINS")));
}

void OptionFrame::invaders_pressed()
{
    if (DwarfFortress::instance().getOption(tr("INVADERS")) == tr("YES"))
        DwarfFortress::instance().setOption(tr("INVADERS"), tr("NO"));
    else
        DwarfFortress::instance().setOption(tr("INVADERS"), tr("YES"));
    invaders->setText(tr("Invaders: ") + DwarfFortress::instance().getOption(tr("INVADERS")));
}

void OptionFrame::liquid_pressed()
{
    if (DwarfFortress::instance().getOption(tr("SHOW_FLOW_AMOUNTS")) == tr("YES"))
        DwarfFortress::instance().setOption(tr("SHOW_FLOW_AMOUNTS"), tr("NO"));
    else
        DwarfFortress::instance().setOption(tr("SHOW_FLOW_AMOUNTS"), tr("YES"));
    liquid->setText(tr("Liquid Depth: ") + DwarfFortress::instance().getOption(tr("SHOW_FLOW_AMOUNTS")));
}

void OptionFrame::popcap_pressed()
{
    bool ok;
    QString newcap = QInputDialog::getText(this, tr("Population Cap"), tr("New population cap:"), QLineEdit::Normal, tr(""), &ok);
    if (ok && !newcap.isEmpty())
    {
        DwarfFortress::instance().setOption(tr("POPULATION_CAP"), newcap);
    }
    popcap->setText(tr("Population Cap: ") + DwarfFortress::instance().getOption(tr("POPULATION_CAP")));
}

void OptionFrame::childcap_pressed()
{
    bool ok1, ok2;
    QString newcap1 = QInputDialog::getText(this, tr("Child Cap"), tr("New absolute child cap:"), QLineEdit::Normal, tr(""), &ok1);
    QString newcap2 = QInputDialog::getText(this, tr("Child Cap"), tr("New child cap as a percentage of total population:"), QLineEdit::Normal, tr(""), &ok2);
    if ((!ok1 || newcap1.isEmpty()) && (ok2 && !newcap2.isEmpty()))
    {
        DwarfFortress::instance().setOption(tr("BABY_CHILD_CAP"), DwarfFortress::instance().getOption(tr("BABY_CHILD_CAP")).left(DwarfFortress::instance().getOption(tr("BABY_CHILD_CAP")).indexOf(tr(":"))) + tr(":") + newcap2);
    }
    else if ((ok1 && !newcap1.isEmpty()) && (!ok2 || newcap2.isEmpty()))
    {
        DwarfFortress::instance().setOption(tr("BABY_CHILD_CAP"), newcap1 + tr(":") + DwarfFortress::instance().getOption(tr("BABY_CHILD_CAP")).right(DwarfFortress::instance().getOption(tr("BABY_CHILD_CAP")).size() - DwarfFortress::instance().getOption(tr("BABY_CHILD_CAP")).indexOf(tr(":")) - 1));
    }
    else if (ok1 && ok2 && !newcap1.isEmpty() && !newcap2.isEmpty())
    {   
        DwarfFortress::instance().setOption(tr("BABY_CHILD_CAP"), newcap1 + tr(":") + newcap2);
    }
    childcap->setText(tr("Child Cap: ") + DwarfFortress::instance().getOption(tr("BABY_CHILD_CAP")));
}

void ModFrame::aquifers_pressed()
{
    if (DwarfFortress::instance().rawsFind(tr("[AQUIFER]")) == tr("YES"))
        DwarfFortress::instance().rawsReplace(tr("[AQUIFER]"), tr("!AQUIFER!"));
    else
        DwarfFortress::instance().rawsReplace(tr("!AQUIFER!"), tr("[AQUIFER]"));
    aquifers->setText(tr("Aquifers: ") + DwarfFortress::instance().rawsFind("[AQUIFER]"));
}

void ModFrame::exotic_pressed()
{
    if (DwarfFortress::instance().rawsFind(tr("[PET_EXOTIC]")) == tr("YES") || DwarfFortress::instance().rawsFind(tr("[MOUNT_EXOTIC]")) == tr("YES"))
    {
        DwarfFortress::instance().rawsReplace(tr("[PET_EXOTIC]"), tr("![PET]!"));
        DwarfFortress::instance().rawsReplace(tr("[MOUNT_EXOTIC]"), tr("![MOUNT]!"));
    }
    else
    {
        DwarfFortress::instance().rawsReplace(tr("![PET]!"), tr("[PET_EXOTIC]"));
        DwarfFortress::instance().rawsReplace(tr("![MOUNT]!"), tr("[MOUNT_EXOTIC]"));
    }
    if (DwarfFortress::instance().rawsFind(tr("[PET_EXOTIC]")) == tr("YES") || DwarfFortress::instance().rawsFind(tr("[MOUNT_EXOTIC]")) == tr("YES"))
        exotic->setText(tr("Exotic Animals: ") + tr("YES"));
    else
        exotic->setText(tr("Exotic Animals: ") + tr("NO"));
}

void KeyFrame::load_pressed()
{
    const QString keybinds_filename( model->data(view->currentIndex(), Qt::DisplayRole).toString() );
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

void KeyFrame::del_pressed()
{
    const QString selected = model->data(view->currentIndex(), Qt::DisplayRole).toString();
    QFile file("./LNP/Keybinds/" + selected);
    bool ok = file.remove();
    if(!ok) {
        QMessageBox::critical(this, tr("Delete Failed"), tr("Could not delete the file '%1'").arg(file.fileName()));
    }
    model->removeRow(view->currentIndex().row());
    view->update();
    QMessageBox::information(this, tr("Deleted File"), tr("Sucessfully deleted the file '%1'").arg(file.fileName()));
}

void KeyFrame::refresh_pressed()
{
    getKeybindings(*list);
    model = new StringListModel(*list);
    view->setModel(model);
    view->update();
}

void KeyFrame::save_pressed()
{
    bool ok;
    QString newfilename = QInputDialog::getText(this, tr("Save Keybinding"), tr("Save current keybindings as:"), QLineEdit::Normal, model->data(view->currentIndex(), Qt::DisplayRole).toString(), &ok);
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
        getKeybindings(*list);
        model = new StringListModel(*list);
        view->setModel(model);
        view->update();
    }
}
