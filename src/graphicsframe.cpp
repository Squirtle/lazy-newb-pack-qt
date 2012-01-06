/* advancedframe.hpp
 * This is the source file which contains the code for the "Graphics" tab.
 */
#include "graphicsframe.hpp"

ChangeFrame::ChangeFrame()
    : QGroupBox(tr("Change Graphics"))
{
    view = new QListView();
    install = new QPushButton(tr("Install Graphics"));
    upgrade = new QPushButton(tr("Upgrade Savegames"));
    truetype = new QPushButton(tr("TrueType Fonts: ") + getOption("TRUETYPE"));
    update = new QPushButton(tr("Update List"));
    grid = new QGridLayout();

    list = new QStringList(getContents(tr("./LNP/Graphics/"), true));
    model = new StringListModel(*list);

    connect(install, SIGNAL(pressed()), this, SLOT(install_pressed()));
    connect(upgrade, SIGNAL(pressed()), this, SLOT(upgrade_pressed()));
    connect(truetype, SIGNAL(pressed()), this, SLOT(truetype_pressed()));
    connect(update, SIGNAL(pressed()), this, SLOT(update_pressed()));

    view->setModel(model);
    grid->addWidget(view, 0, 0, 1, 2);
    grid->addWidget(install, 1, 0, 1, 1);
    grid->addWidget(upgrade, 1, 1, 1, 1);
    grid->addWidget(truetype, 2, 0, 1, 1);
    grid->addWidget(update, 2, 1, 1, 1);

    setLayout(grid);
}

AdvancedGraphicsFrame::AdvancedGraphicsFrame()
    : QGroupBox(tr("Advanced"))
{
    open = new QPushButton(tr("Open Graphics Folder"));
    simplify = new QPushButton(tr("Simplify Graphic Folders"));
    grid = new QGridLayout();

    grid->addWidget(open, 0, 0, 1, 1);
    grid->addWidget(simplify, 0, 1, 1, 1);

    setLayout(grid);
}

GraphicsFrame::GraphicsFrame()
{
    changeframe = new ChangeFrame();
    advancedgraphicsframe = new AdvancedGraphicsFrame();
    box = new QVBoxLayout();

    box->addWidget(changeframe);
    box->addWidget(advancedgraphicsframe);

    setLayout(box);
}

void ChangeFrame::install_pressed()
{
    bool sure;
    QMessageBox dialog;
    dialog.setText(tr("Are you sure you want to install ") + model->data(view->currentIndex(), Qt::DisplayRole).toString() + tr("?  You will override your current RAWs and init files if you do."));
    dialog.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    dialog.setDefaultButton(QMessageBox::Cancel);
    sure = dialog.exec();
    if (sure)
    {
        QDir dir1(tr("./LNP/Keybinds/") + model->data(view->currentIndex(), Qt::DisplayRole).toString()), dir2(getDFFolder());
        cpDir(dir1, dir2);
        QMessageBox success;
        success.setText(model->data(view->currentIndex(), Qt::DisplayRole).toString() + tr(" succesfully installed."));
        success.exec();
    }
}

void ChangeFrame::upgrade_pressed()
{
    QDir dir1(tr("./LNP/Graphics/") + model->data(view->currentIndex(), Qt::DisplayRole).toString() + tr("/raws/"));
    QDirIterator dit(getDFFolder() + tr("/data/save/"));
    if (!dit.hasNext())
    {
        QMessageBox error;
        error.setText(tr("No saves exist!"));
        error.exec();
    }
    else
    {
        bool sure;
        QMessageBox dialog;
        dialog.setText(tr("Are you sure you want to upgrade your saves to use this graphics pack?  You will lose all mods you have made to their raws"));
        dialog.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        dialog.setDefaultButton(QMessageBox::Cancel);
        sure = dialog.exec();
        if (sure)
        {
            while (dit.hasNext())
                cpDir(dir1, dit.path() + tr("/raws/"));
            QMessageBox success;
            success.setText(tr("Successfully upgraded saves!"));
            success.exec();
        }
    }
}

void ChangeFrame::truetype_pressed()
{
    if (getOption(tr("TRUETYPE")) == tr("YES"))
        setOption(tr("TRUETYPE"), tr("NO"));
    else
        setOption(tr("TRUETYPE"), tr("YES"));
    truetype->setText(tr("TrueType Fonts: ") + getOption(tr("TRUETYPE")));
}

void ChangeFrame::update_pressed()
{
    list = new QStringList(getContents(tr("./LNP/Graphics/"), true));
    model = new StringListModel(*list);
    view->setModel(model);
    view->update();
}
