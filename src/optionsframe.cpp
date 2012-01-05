/* advancedframe.hpp
 * This is the source file which contains the code for the "Options" tab.
 */
#include "optionsframe.hpp"
#include "functions.hpp"

OptionFrame::OptionFrame()
    :  QGroupBox(tr("Options"))
{
    economy = new QPushButton(tr("Economy: ") + getOption(tr("ECONOMY")));
    temperature = new QPushButton(tr("Temperature: ") + getOption(tr("TEMPERATURE")));
    weather = new QPushButton(tr("Weather: ") + getOption(tr("WEATHER")));
    caveins = new QPushButton(tr("Cave-ins: ") + getOption(tr("CAVEINS")));
    invaders = new QPushButton(tr("Invaders: ") + getOption(tr("INVADERS")));
    liquid = new QPushButton(tr("Liquid Depth: ") + getOption(tr("SHOW_FLOW_AMOUNTS")));
    popcap = new QPushButton(tr("Population Cap: ") + getOption(tr("POPULATION_CAP")));
    childcap = new QPushButton(tr("Child Cap: ") + getOption(tr("BABY_CHILD_CAP")));
    
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
    aquifers = new QPushButton(tr("Aquifers: ") + rawsFind(tr("[AQUIFER]")));
    if (rawsFind(tr("[PET_EXOTIC]")) == tr("YES"))
        exotic = new QPushButton(tr("Exotic Animals: ") + rawsFind(tr("[PET_EXOTIC]")));
    else
        exotic = new QPushButton(tr("Exotic Animals: ") + rawsFind(tr("[MOUNT_EXOTIC]")));
    
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

void OptionFrame::economy_pressed()
{
    if (getOption(tr("ECONOMY")) == tr("YES"))
        setOption(tr("ECONOMY"), tr("NO"));
    else
        setOption(tr("ECONOMY"), tr("YES"));
    economy->setText(tr("Economy: ") + getOption(tr("ECONOMY")));
}

void OptionFrame::temperature_pressed()
{
    if (getOption(tr("TEMPERATURE")) == tr("YES"))
        setOption(tr("TEMPERATURE"), tr("NO"));
    else
        setOption(tr("TEMPERATURE"), tr("YES"));
    temperature->setText(tr("Temperature: ") + getOption(tr("TEMPERATURE")));
}

void OptionFrame::weather_pressed()
{
    if (getOption(tr("WEATHER")) == tr("YES"))
        setOption(tr("WEATHER"), tr("NO"));
    else
        setOption(tr("WEATHER"), tr("YES"));
    weather->setText(tr("Weather: ") + getOption(tr("WEATHER")));
}

void OptionFrame::caveins_pressed()
{
    if (getOption(tr("CAVEINS")) == tr("YES"))
        setOption(tr("CAVEINS"), tr("NO"));
    else
        setOption(tr("CAVEINS"), tr("YES"));
    caveins->setText(tr("Cave-ins: ") + getOption(tr("CAVEINS")));
}

void OptionFrame::invaders_pressed()
{
    if (getOption(tr("INVADERS")) == tr("YES"))
        setOption(tr("INVADERS"), tr("NO"));
    else
        setOption(tr("INVADERS"), tr("YES"));
    invaders->setText(tr("Invaders: ") + getOption(tr("INVADERS")));
}

void OptionFrame::liquid_pressed()
{
    if (getOption(tr("SHOW_FLOW_AMOUNTS")) == tr("YES"))
        setOption(tr("SHOW_FLOW_AMOUNTS"), tr("NO"));
    else
        setOption(tr("SHOW_FLOW_AMOUNTS"), tr("YES"));
    liquid->setText(tr("Liquid Depth: ") + getOption(tr("SHOW_FLOW_AMOUNTS")));
}

void OptionFrame::popcap_pressed()
{
    bool ok;
    QString newcap = QInputDialog::getText(this, tr("Population Cap"), tr("New population cap:"), QLineEdit::Normal, tr(""), &ok);
    if (ok && !newcap.isEmpty())
    {
        setOption(tr("POPULATION_CAP"), newcap);
    }
    popcap->setText(tr("Population Cap: ") + getOption(tr("POPULATION_CAP")));
}

void OptionFrame::childcap_pressed()
{
    bool ok1, ok2;
    QString newcap1 = QInputDialog::getText(this, tr("Child Cap"), tr("New absolute child cap:"), QLineEdit::Normal, tr(""), &ok1);
    QString newcap2 = QInputDialog::getText(this, tr("Child Cap"), tr("New child cap as a percentage of total population:"), QLineEdit::Normal, tr(""), &ok2);
    if ((!ok1 || newcap1.isEmpty()) && (ok2 && !newcap2.isEmpty()))
    {
        setOption(tr("BABY_CHILD_CAP"), getOption(tr("BABY_CHILD_CAP")).left(getOption(tr("BABY_CHILD_CAP")).indexOf(tr(":"))) + tr(":") + newcap2);
    }
    else if ((ok1 && !newcap1.isEmpty()) && (!ok2 || newcap2.isEmpty()))
    {
        setOption(tr("BABY_CHILD_CAP"), newcap1 + tr(":") + getOption(tr("BABY_CHILD_CAP")).right(getOption(tr("BABY_CHILD_CAP")).size() - getOption(tr("BABY_CHILD_CAP")).indexOf(tr(":")) - 1));
    }
    else if (ok1 && ok2 && !newcap1.isEmpty() && !newcap2.isEmpty())
    {   
        setOption(tr("BABY_CHILD_CAP"), newcap1 + tr(":") + newcap2);
    }
    childcap->setText(tr("Child Cap: ") + getOption(tr("BABY_CHILD_CAP")));
}

void ModFrame::aquifers_pressed()
{
    if (rawsFind(tr("[AQUIFER]")) == tr("YES"))
        rawsReplace(tr("[AQUIFER]"), tr("!AQUIFER!"));
    else
        rawsReplace(tr("!AQUIFER!"), tr("[AQUIFER]"));
    aquifers->setText(tr("Aquifers: ") + rawsFind("[AQUIFER]"));
}

void ModFrame::exotic_pressed()
{
    if (rawsFind(tr("[PET_EXOTIC]")) == tr("YES") || rawsFind(tr("[MOUNT_EXOTIC]")) == tr("YES"))
    {
        rawsReplace(tr("[PET_EXOTIC]"), tr("![PET]!"));
        rawsReplace(tr("[MOUNT_EXOTIC]"), tr("![MOUNT]!"));
    }
    else
    {
        rawsReplace(tr("![PET]!"), tr("[PET_EXOTIC]"));
        rawsReplace(tr("![MOUNT]!"), tr("[MOUNT_EXOTIC]"));
    }
    if (rawsFind(tr("[PET_EXOTIC]")) == tr("YES") || rawsFind(tr("[MOUNT_EXOTIC]")) == tr("YES"))
        exotic->setText(tr("Exotic Animals: ") + tr("YES"));
    else
        exotic->setText(tr("Exotic Animals: ") + tr("NO"));
}

void KeyFrame::load_pressed()
{
    QFile file1(tr("./LNP/Keybinds/") + model->data(view->currentIndex(), Qt::DisplayRole).toString()), file2(getDFFolder() + tr("/data/init/interface.txt"));
    bool ok1 = file1.open(QFile::ReadOnly);
    QByteArray *buffer = new QByteArray(file1.readAll());
    file1.close();
    bool ok2 = file2.open(QFile::WriteOnly | QFile::Truncate);
    file2.write(*buffer);
    file2.close();
    delete buffer;
    bool ok = ok1 && ok2;
    if (ok)
    {
        QMessageBox msg;
        msg.setText(tr("Sucessfully loaded ") + model->data(view->currentIndex(), Qt::DisplayRole).toString());
        msg.exec();
    }
    else
    {
        //error handling
    }
}

void KeyFrame::del_pressed()
{
    QString selected = model->data(view->currentIndex(), Qt::DisplayRole).toString();
    QFile file(tr("./LNP/Keybinds/") + selected);
    bool ok1 = file.remove();
    bool ok2 = model->removeRow(view->currentIndex().row());
    view->update();
    if (ok1)
    {
        QMessageBox msg;
        msg.setText(tr("Sucessfully deleted ") + selected);
        msg.exec();
    }
    else
    {
        //error handling
    }
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
    //TODO: Error handling bluh
    bool ok;
    QString newfilename = QInputDialog::getText(this, tr("Save Keybinding"), tr("Save current keybindings as:"), QLineEdit::Normal, model->data(view->currentIndex(), Qt::DisplayRole).toString(), &ok);
    QFile newfile(tr("./LNP/Keybinds/") + newfilename), file(getDFFolder() + tr("/data/init/interface.txt"));
    if (ok)
    {
        int sure = -1;
        if (newfile.exists()) 
        {
            QMessageBox dialog;
            dialog.setText(("This keybinding already exists.  Do you want to override it?"));
            dialog.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
            dialog.setDefaultButton(QMessageBox::Cancel);
            sure = dialog.exec();
        }
        if (sure == QMessageBox::Yes || !newfile.exists())
        {
            bool ok1 = file.open(QFile::ReadOnly);
            QByteArray *buffer = new QByteArray(file.readAll());
            file.close();
            bool ok2 = newfile.open(QFile::WriteOnly | QFile::Truncate);
            newfile.write(*buffer);
            newfile.close();
            delete buffer;
            bool ok3 = ok1 && ok2;
            if (ok3)
            {
                QMessageBox msg;
                msg.setText(tr("Sucessfully saved current keybindings as ") + newfilename);
                msg.exec();
            }
            getKeybindings(*list);
            model = new StringListModel(*list);
            view->setModel(model);
            view->update();
        }
    }
}
