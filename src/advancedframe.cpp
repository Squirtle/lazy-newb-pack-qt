/* advancedframe.cpp
 * This is the source file which contains the code for the "Advanced" tab.
 */
#include "advancedframe.hpp"
#include "functions.hpp"
#include "DwarfFortress.h"

SoundFrame::SoundFrame()
    : QGroupBox(tr("Sound"))
{
    connect( &DwarfFortress::instance(), SIGNAL( dfFolderChanged() ), this, SLOT( dfFolderChanged() ));
    sound = new QPushButton(tr("Sound: ") + DwarfFortress::instance().getOption(tr("SOUND")));
    volume = new QLineEdit(DwarfFortress::instance().getOption(tr("VOLUME")));
    maxvolume = new QLabel(tr("/255"));
    box = new QHBoxLayout();

    connect(sound, SIGNAL(pressed()), this, SLOT(sound_pressed()));
    connect(volume, SIGNAL(textEdited(const QString&)), this, SLOT(volume_modified()));
    connect(volume, SIGNAL(editingFinished()), this, SLOT(volume_finished()));

    volume->setMaxLength(3);
    box->addWidget(sound);
    box->addWidget(volume);
    box->addWidget(maxvolume);

    setLayout(box);
}

void SoundFrame::dfFolderChanged()
{
    sound->setText("Sound: " + DwarfFortress::instance().getOption("SOUND"));
    volume->setText(DwarfFortress::instance().getOption("VOLUME"));
}

FPSFrame::FPSFrame()
    : QGroupBox(tr("FPS"))
{
    connect( &DwarfFortress::instance(), SIGNAL( dfFolderChanged() ), this, SLOT( dfFolderChanged() ));
    counter = new QPushButton(tr("FPS Counter: ") + DwarfFortress::instance().getOption(tr("FPS")));
    cFPScap = new QLineEdit(DwarfFortress::instance().getOption(tr("FPS_CAP")));
    gFPScap = new QLineEdit(DwarfFortress::instance().getOption(tr("G_FPS_CAP")));
    cFPSlabel = new QLabel(tr("Calculation FPS Cap:"));
    gFPSlabel = new QLabel(tr("Graphical FPS Cap:"));
    box = new QVBoxLayout();

    connect(counter, SIGNAL(pressed()), this, SLOT(counter_pressed()));
    connect(cFPScap, SIGNAL(textEdited(const QString&)), this, SLOT(cFPScap_modified()));
    connect(gFPScap, SIGNAL(textEdited(const QString&)), this, SLOT(gFPScap_modified()));
    connect(cFPScap, SIGNAL(editingFinished()), this, SLOT(cFPScap_finished()));
    connect(gFPScap, SIGNAL(editingFinished()), this, SLOT(gFPScap_finished()));

    cFPScap->setMaxLength(3);
    gFPScap->setMaxLength(3);

    box->addWidget(counter);
    box->addWidget(cFPSlabel);
    box->addWidget(cFPScap);
    box->addWidget(gFPSlabel);
    box->addWidget(gFPScap);

    setLayout(box);
}

void FPSFrame::dfFolderChanged()
{
    counter->setText("FPS Counter: " + DwarfFortress::instance().getOption("FPS"));
    cFPScap->setText(DwarfFortress::instance().getOption("FPS_CAP"));
    gFPScap->setText(DwarfFortress::instance().getOption("G_FPS_CAP"));
}

StartupFrame::StartupFrame()
    : QGroupBox(tr("Startup"))
{
    connect( &DwarfFortress::instance(), SIGNAL( dfFolderChanged() ), this, SLOT( dfFolderChanged() ));
    intro = new QPushButton(tr("Intro Movie: ") + DwarfFortress::instance().getOption(tr("INTRO")));
    windowed = new QPushButton(tr("Windowed: ") + DwarfFortress::instance().getOption(tr("WINDOWED")));
    box = new QVBoxLayout();

    connect(intro, SIGNAL(pressed()), this, SLOT(intro_pressed()));
    connect(windowed, SIGNAL(pressed()), this, SLOT(windowed_pressed()));

    box->addWidget(intro);
    box->addWidget(windowed);

    setLayout(box);
}

void StartupFrame::dfFolderChanged()
{
    intro->setText("Intro Movie: " + DwarfFortress::instance().getOption("INTRO"));
    windowed->setText("Windowed: " + DwarfFortress::instance().getOption("WINDOWED"));
}

SaveFrame::SaveFrame()
    : QGroupBox(tr("Save-related"))
{
    connect( &DwarfFortress::instance(), SIGNAL( dfFolderChanged() ), this, SLOT( dfFolderChanged() ));
    autosave = new QPushButton(tr("Autosave: ") + DwarfFortress::instance().getOption(tr("AUTOSAVE")));
    autopause = new QPushButton(tr("Autosave Pause: ") + DwarfFortress::instance().getOption(tr("AUTOSAVE_PAUSE")));
    initsave = new QPushButton(tr("Initial Save: ") + DwarfFortress::instance().getOption(tr("INITIAL_SAVE")));
    pauseonload = new QPushButton(tr("Pause on Load: ") + DwarfFortress::instance().getOption(tr("PAUSE_ON_LOAD")));
    compress = new QPushButton(tr("Compress Saves: ") + DwarfFortress::instance().getOption(tr("COMPRESSED_SAVES")));
    autobackup = new QPushButton(tr("Auto Backup: ") + DwarfFortress::instance().getOption(tr("AUTOBACKUP")));
    grid = new QGridLayout();

    connect(autosave, SIGNAL(pressed()), this, SLOT(autosave_pressed()));
    connect(autopause, SIGNAL(pressed()), this, SLOT(autopause_pressed()));
    connect(initsave, SIGNAL(pressed()), this, SLOT(initsave_pressed()));
    connect(pauseonload, SIGNAL(pressed()), this, SLOT(pauseonload_pressed()));
    connect(compress, SIGNAL(pressed()), this, SLOT(compress_pressed()));
    connect(autobackup, SIGNAL(pressed()), this, SLOT(autobackup_pressed()));

    grid->addWidget(autosave, 0, 0);
    grid->addWidget(initsave, 1, 0);
    grid->addWidget(compress, 2, 0);
    grid->addWidget(autopause, 0, 1);
    grid->addWidget(pauseonload, 1, 1);
    grid->addWidget(autobackup, 2, 1);

    setLayout(grid);
}

void SaveFrame::dfFolderChanged()
{
    autosave->setText("Autosave: " + DwarfFortress::instance().getOption("AUTOSAVE"));
    autopause->setText("Autosave Pause: " + DwarfFortress::instance().getOption("AUTOSAVE_PAUSE"));
    initsave->setText("Initial Save: " + DwarfFortress::instance().getOption("INITIAL_SAVE"));
    pauseonload->setText("Pause on Load: " + DwarfFortress::instance().getOption("PAUSE_ON_LOAD"));
    compress->setText("Compress Saves: " + DwarfFortress::instance().getOption("COMPRESSED_SAVES"));
    autobackup->setText("Auto Backup: " + DwarfFortress::instance().getOption("AUTOBACKUP"));
}

AdvancedFrame::AdvancedFrame()
{
    connect( &DwarfFortress::instance(), SIGNAL( dfFolderChanged() ), this, SLOT( dfFolderChanged() ));
    procpriority = new QPushButton(tr("Processor Priority: ") + DwarfFortress::instance().getOption(tr("PRIORITY")));
    soundframe = new SoundFrame();
    fpsframe = new FPSFrame();
    startupframe = new StartupFrame();
    saveframe = new SaveFrame();
    grid = new QGridLayout();

    connect(procpriority, SIGNAL(pressed()), this, SLOT(procpriority_pressed()));

    grid->addWidget(soundframe, 0, 0, 1, 1);
    grid->addWidget(fpsframe, 0, 1, 2, 1);
    grid->addWidget(startupframe, 1, 0, 1, 1);
    grid->addWidget(procpriority, 2, 0, 1, 2);
    grid->addWidget(saveframe, 3, 0, 1, 2);

    setLayout(grid);
}

void AdvancedFrame::dfFolderChanged()
{
    procpriority->setText("Processor Priority: " + DwarfFortress::instance().getOption("PRIORITY"));
}

void SoundFrame::sound_pressed()
{
    if (DwarfFortress::instance().getOption(tr("SOUND")) == "YES")
        DwarfFortress::instance().setOption(tr("SOUND"), "NO");
    else
        DwarfFortress::instance().setOption(tr("SOUND"), "YES");
    sound->setText(tr("Sound: ") + DwarfFortress::instance().getOption(tr("SOUND")));
}

void FPSFrame::counter_pressed()
{
    if (DwarfFortress::instance().getOption(tr("FPS")) == "YES")
        DwarfFortress::instance().setOption(tr("FPS"), "NO");
    else
        DwarfFortress::instance().setOption(tr("FPS"), "YES");
    counter->setText(tr("FPS Counter: ") + DwarfFortress::instance().getOption(tr("FPS")));
}

void StartupFrame::intro_pressed()
{
    if (DwarfFortress::instance().getOption(tr("INTRO")) == "YES")
        DwarfFortress::instance().setOption(tr("INTRO"), "NO");
    else
        DwarfFortress::instance().setOption(tr("INTRO"), "YES");
    intro->setText(tr("Intro Movie: ") + DwarfFortress::instance().getOption(tr("INTRO")));
}

void StartupFrame::windowed_pressed()
{
    if (DwarfFortress::instance().getOption(tr("WINDOWED")) == "YES")
        DwarfFortress::instance().setOption(tr("WINDOWED"), "NO");
    else
        DwarfFortress::instance().setOption(tr("WINDOWED"), "YES");
    windowed->setText(tr("Windowed: ") + DwarfFortress::instance().getOption(tr("WINDOWED")));
}

void SaveFrame::autosave_pressed()
{
    QString frequencies[] = {tr("NONE"), tr("YEARLY"), tr("SEASONAL")};
    unsigned int newfrequency = 0;
    for (unsigned int i = 0; i < sizeof(frequencies)/sizeof(frequencies[0]); i++)
    {
        if (frequencies[i] == DwarfFortress::instance().getOption(tr("AUTOSAVE")))
            {
                newfrequency = i + 1;
            }
    }
    if (newfrequency > sizeof(frequencies)/sizeof(frequencies[0]) - 1)
        newfrequency = 0;
    DwarfFortress::instance().setOption(tr("AUTOSAVE"), frequencies[newfrequency]);
    autosave->setText(tr("Autosave: ") + DwarfFortress::instance().getOption(tr("AUTOSAVE")));
}

void SaveFrame::autopause_pressed()
{
    if (DwarfFortress::instance().getOption(tr("AUTOSAVE_PAUSE")) == "YES")
        DwarfFortress::instance().setOption(tr("AUTOSAVE_PAUSE"), "NO");
    else
        DwarfFortress::instance().setOption(tr("AUTOSAVE_PAUSE"), "YES");
    autopause->setText(tr("Autosave Pause: ") + DwarfFortress::instance().getOption(tr("AUTOSAVE_PAUSE")));
}

void SaveFrame::initsave_pressed()
{
    if (DwarfFortress::instance().getOption(tr("INITIAL_SAVE")) == "YES")
        DwarfFortress::instance().setOption(tr("INITIAL_SAVE"), "NO");
    else
        DwarfFortress::instance().setOption(tr("INITIAL_SAVE"), "YES");
    initsave->setText(tr("Initial Save: ") + DwarfFortress::instance().getOption(tr("INITIAL_SAVE")));
}

void SaveFrame::pauseonload_pressed()
{
    if (DwarfFortress::instance().getOption(tr("PAUSE_ON_LOAD")) == "YES")
        DwarfFortress::instance().setOption(tr("PAUSE_ON_LOAD"), "NO");
    else
        DwarfFortress::instance().setOption(tr("PAUSE_ON_LOAD"), "YES");
    pauseonload->setText(tr("Pause on Load: ") + DwarfFortress::instance().getOption(tr("PAUSE_ON_LOAD")));
}

void SaveFrame::compress_pressed()
{
    if (DwarfFortress::instance().getOption(tr("COMPRESSED_SAVES")) == "YES")
        DwarfFortress::instance().setOption(tr("COMPRESSED_SAVES"), "NO");
    else
        DwarfFortress::instance().setOption(tr("COMPRESSED_SAVES"), "YES");
    compress->setText(tr("Compress Saves: ") + DwarfFortress::instance().getOption(tr("COMPRESSED_SAVES")));
}

void SaveFrame::autobackup_pressed()
{
    if (DwarfFortress::instance().getOption(tr("AUTOBACKUP")) == "YES")
        DwarfFortress::instance().setOption(tr("AUTOBACKUP"), "NO");
    else
        DwarfFortress::instance().setOption(tr("AUTOBACKUP"), "YES");
    autobackup->setText(tr("Auto Backup: ") + DwarfFortress::instance().getOption(tr("AUTOBACKUP")));
}

void AdvancedFrame::procpriority_pressed()
{
    QStringList priorities;
    priorities << "IDLE" << "BELOW_NORMAL" << "NORMAL" << "HIGH" << "REALTIME";
    unsigned int newpriority = 0;
    for(int i = 0; i < priorities.length(); ++i) {
        if (priorities.at(i) == DwarfFortress::instance().getOption("PRIORITY")) {
            newpriority = i + 1;
        }
    }
    if (newpriority > priorities.length() - 1)
        newpriority = 0;
    DwarfFortress::instance().setOption(tr("PRIORITY"), priorities[newpriority]);
    procpriority->setText(tr("Processor Priority: ") + DwarfFortress::instance().getOption(tr("PRIORITY")));
}

void SoundFrame::volume_modified()
{
    QString newvolumestring = volume->text();
    bool ok;
    int newvolume = newvolumestring.toInt(&ok, 10);
    if (ok)
    {
        if (newvolume > 255)
            newvolume = 255;
        if (newvolume < 0)
            newvolume = 0;
        newvolumestring = QString::number(newvolume);
        DwarfFortress::instance().setOption(tr("VOLUME"), newvolumestring);
    }
}

void FPSFrame::cFPScap_modified()
{
    QString newcapstring = cFPScap->text();
    bool ok;
    int newcap = newcapstring.toInt(&ok, 10);
    if (ok)
    {
        if (newcap > 999)
            newcap = 999;
        if (newcap < 0)
            newcap = 0;
        newcapstring = QString::number(newcap);
        DwarfFortress::instance().setOption(tr("FPS_CAP"), newcapstring);
    }
}

void FPSFrame::gFPScap_modified()
{
    QString newcapstring = gFPScap->text();
    bool ok;
    int newcap = newcapstring.toInt(&ok, 10);
    if (ok)
    {
        if (newcap > 999)
            newcap = 999;
        if (newcap < 0)
            newcap = 0;
        newcapstring = QString::number(newcap);
        DwarfFortress::instance().setOption(tr("G_FPS_CAP"), newcapstring);
    }
}

void SoundFrame::volume_finished()
{
    QString newvolumestring = volume->text();
    bool ok;
    int newvolume = newvolumestring.toInt(&ok, 10);
    if (ok)
    {
        if (newvolume > 255)
            newvolume = 255;
        if (newvolume < 0)
            newvolume = 0;
        newvolumestring = QString::number(newvolume);
        DwarfFortress::instance().setOption(tr("VOLUME"), newvolumestring);
        volume->setText(newvolumestring);
    }
}

void FPSFrame::cFPScap_finished()
{
    QString newcapstring = cFPScap->text();
    bool ok;
    int newcap = newcapstring.toInt(&ok, 10);
    if (ok)
    {
        if (newcap > 999)
            newcap = 999;
        if (newcap < 0)
            newcap = 0;
        newcapstring = QString::number(newcap);
        DwarfFortress::instance().setOption(tr("FPS_CAP"), newcapstring);
        cFPScap->setText(newcapstring);
    }
}

void FPSFrame::gFPScap_finished()
{
    QString newcapstring = gFPScap->text();
    bool ok;
    int newcap = newcapstring.toInt(&ok, 10);
    if (ok)
    {
        if (newcap > 999)
            newcap = 999;
        if (newcap < 0)
            newcap = 0;
        newcapstring = QString::number(newcap);
        DwarfFortress::instance().setOption(tr("G_FPS_CAP"), newcapstring);
        gFPScap->setText(newcapstring);
    }
}
