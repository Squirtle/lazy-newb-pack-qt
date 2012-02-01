/* advancedframe.cpp
 * This is the source file which contains the code for the "Advanced" tab.
 */
#include "advancedframe.hpp"
#include "functions.hpp"

SoundFrame::SoundFrame()
    : QGroupBox(tr("Sound"))
{
    sound = new QPushButton(tr("Sound: ") + getOption(tr("SOUND")));
    volume = new QLineEdit(getOption(tr("VOLUME")));
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

FPSFrame::FPSFrame()
    : QGroupBox(tr("FPS"))
{
    counter = new QPushButton(tr("FPS Counter: ") + getOption(tr("FPS")));
    cFPScap = new QLineEdit(getOption(tr("FPS_CAP")));
    gFPScap = new QLineEdit(getOption(tr("G_FPS_CAP")));
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

StartupFrame::StartupFrame()
    : QGroupBox(tr("Startup"))
{
    intro = new QPushButton(tr("Intro Movie: ") + getOption(tr("INTRO")));
    windowed = new QPushButton(tr("Windowed: ") + getOption(tr("WINDOWED")));
    box = new QVBoxLayout();

    connect(intro, SIGNAL(pressed()), this, SLOT(intro_pressed()));
    connect(windowed, SIGNAL(pressed()), this, SLOT(windowed_pressed()));

    box->addWidget(intro);
    box->addWidget(windowed);

    setLayout(box);
}

SaveFrame::SaveFrame()
    : QGroupBox(tr("Save-related"))
{
    autosave = new QPushButton(tr("Autosave: ") + getOption(tr("AUTOSAVE")));
    autopause = new QPushButton(tr("Autosave Pause: ") + getOption(tr("AUTOSAVE_PAUSE")));
    initsave = new QPushButton(tr("Initial Save: ") + getOption(tr("INITIAL_SAVE")));
    pauseonload = new QPushButton(tr("Pause on Load: ") + getOption(tr("PAUSE_ON_LOAD")));
    compress = new QPushButton(tr("Compress Saves: ") + getOption(tr("COMPRESSED_SAVES")));
    autobackup = new QPushButton(tr("Auto Backup: ") + getOption(tr("AUTOBACKUP")));
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

AdvancedFrame::AdvancedFrame()
{
    procpriority = new QPushButton(tr("Processor Priority: ") + getOption(tr("PRIORITY")));
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

void SoundFrame::sound_pressed()
{
    if (getOption(tr("SOUND")) == tr("YES"))
        setOption(tr("SOUND"), tr("NO"));
    else
        setOption(tr("SOUND"), tr("YES"));
    sound->setText(tr("Sound: ") + getOption(tr("SOUND")));
}

void FPSFrame::counter_pressed()
{
    if (getOption(tr("FPS")) == tr("YES"))
        setOption(tr("FPS"), tr("NO"));
    else
        setOption(tr("FPS"), tr("YES"));
    counter->setText(tr("FPS Counter: ") + getOption(tr("FPS")));
}

void StartupFrame::intro_pressed()
{
    if (getOption(tr("INTRO")) == tr("YES"))
        setOption(tr("INTRO"), tr("NO"));
    else
        setOption(tr("INTRO"), tr("YES"));
    intro->setText(tr("Intro Movie: ") + getOption(tr("INTRO")));
}

void StartupFrame::windowed_pressed()
{
    if (getOption(tr("WINDOWED")) == tr("YES"))
        setOption(tr("WINDOWED"), tr("NO"));
    else
        setOption(tr("WINDOWED"), tr("YES"));
    windowed->setText(tr("Windowed: ") + getOption(tr("WINDOWED")));
}

void SaveFrame::autosave_pressed()
{
    QString frequencies[] = {tr("NONE"), tr("YEARLY"), tr("SEASONAL")};
    unsigned int newfrequency = 0;
    for (unsigned int i = 0; i < sizeof(frequencies)/sizeof(frequencies[0]); i++)
    {
        if (frequencies[i] == getOption(tr("AUTOSAVE")))
            {
                newfrequency = i + 1;
            }
    }
    if (newfrequency > sizeof(frequencies)/sizeof(frequencies[0]) - 1)
        newfrequency = 0;
    setOption(tr("AUTOSAVE"), frequencies[newfrequency]);
    autosave->setText(tr("Autosave: ") + getOption(tr("AUTOSAVE")));
}

void SaveFrame::autopause_pressed()
{
    if (getOption(tr("AUTOSAVE_PAUSE")) == tr("YES"))
        setOption(tr("AUTOSAVE_PAUSE"), tr("NO"));
    else
        setOption(tr("AUTOSAVE_PAUSE"), tr("YES"));
    autopause->setText(tr("Autosave Pause: ") + getOption(tr("AUTOSAVE_PAUSE")));
}

void SaveFrame::initsave_pressed()
{
    if (getOption(tr("INITIAL_SAVE")) == tr("YES"))
        setOption(tr("INITIAL_SAVE"), tr("NO"));
    else
        setOption(tr("INITIAL_SAVE"), tr("YES"));
    initsave->setText(tr("Initial Save: ") + getOption(tr("INITIAL_SAVE")));
}

void SaveFrame::pauseonload_pressed()
{
    if (getOption(tr("PAUSE_ON_LOAD")) == tr("YES"))
        setOption(tr("PAUSE_ON_LOAD"), tr("NO"));
    else
        setOption(tr("PAUSE_ON_LOAD"), tr("YES"));
    pauseonload->setText(tr("Pause on Load: ") + getOption(tr("PAUSE_ON_LOAD")));
}

void SaveFrame::compress_pressed()
{
    if (getOption(tr("COMPRESSED_SAVES")) == tr("YES"))
        setOption(tr("COMPRESSED_SAVES"), tr("NO"));
    else
        setOption(tr("COMPRESSED_SAVES"), tr("YES"));
    compress->setText(tr("Compress Saves: ") + getOption(tr("COMPRESSED_SAVES")));
}

void SaveFrame::autobackup_pressed()
{
    if (getOption(tr("AUTOBACKUP")) == tr("YES"))
        setOption(tr("AUTOBACKUP"), tr("NO"));
    else
        setOption(tr("AUTOBACKUP"), tr("YES"));
    autobackup->setText(tr("Auto Backup: ") + getOption(tr("AUTOBACKUP")));
}

void AdvancedFrame::procpriority_pressed()
{
    QStringList priorities;
    priorities << "IDLE" << "BELOW_NORMAL" << "NORMAL" << "HIGH" << "REALTIME";
    unsigned int newpriority = 0;
    for(int i = 0; i < priorities.length(); ++i) {
        if (priorities.at(i) == getOption("PRIORITY")) {
            newpriority = i + 1;
        }
    }
    if (newpriority > priorities.length() - 1)
        newpriority = 0;
    setOption(tr("PRIORITY"), priorities[newpriority]);
    procpriority->setText(tr("Processor Priority: ") + getOption(tr("PRIORITY")));
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
        setOption(tr("VOLUME"), newvolumestring);
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
        setOption(tr("FPS_CAP"), newcapstring);
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
        setOption(tr("G_FPS_CAP"), newcapstring);
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
        setOption(tr("VOLUME"), newvolumestring);
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
        setOption(tr("FPS_CAP"), newcapstring);
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
        setOption(tr("G_FPS_CAP"), newcapstring);
        gFPScap->setText(newcapstring);
    }
}

void SoundFrame::reload()
{
    sound->setText(tr("Sound: ") + getOption(tr("SOUND")));
    volume->setText(getOption(tr("VOLUME")));
}

void FPSFrame::reload()
{
    counter->setText(tr("FPS Counter: ") + getOption(tr("FPS")));
    cFPScap->setText(getOption(tr("FPS_CAP")));
    gFPScap->setText(getOption(tr("G_FPS_CAP")));
}

void StartupFrame::reload()
{
    windowed->setText(tr("Windowed: ") + getOption(tr("WINDOWED")));
    intro->setText(tr("Intro Movie: ") + getOption(tr("INTRO")));
}

void SaveFrame::reload()
{
    autosave->setText(tr("Autosave: ") + getOption(tr("AUTOSAVE")));
    autopause->setText(tr("Autosave Pause: ") + getOption(tr("AUTOSAVE_PAUSE")));
    initsave->setText(tr("Initial Save: ") + getOption(tr("INITIAL_SAVE")));
    pauseonload->setText(tr("Pause on Load: ") + getOption(tr("PAUSE_ON_LOAD")));
    compress->setText(tr("Compress Saves: ") + getOption(tr("COMPRESSED_SAVES")));
    autobackup->setText(tr("Auto Backup: ") + getOption(tr("AUTOBACKUP")));
}

void AdvancedFrame::reload()
{
    soundframe->reload();
    fpsframe->reload();
    startupframe->reload();
    saveframe->reload();
    procpriority->setText(tr("Processor Priority: ") + getOption(tr("PRIORITY")));
}
