#include "AdvancedTab.h"
#include "ui_AdvancedTab.h"

#include "ConfigButton.h"
#include "NumericOptionWidget.h"
#include "DwarfFortress.h"

#include <QtilitiesCore>

#include <QDebug>
#include <QPointer>
#include <QFile>

AdvancedTab::AdvancedTab( DFManagerPtr manager, QWidget * parent )
    : QWidget(parent)
    , ui(new Ui::AdvancedTab)
    , m_dataManager(manager)
{
    ui->setupUi(this);

    // Sound Group
    QVBoxLayout *sound_layout = new QVBoxLayout(this);
    ui->soundGroup->setLayout(sound_layout);

    ConfigButton* b = new ConfigButton("SOUND", "Sound", this);
    sound_layout->addWidget(b);

    NumericOptionWidget* num_opt = new NumericOptionWidget("VOLUME", "Volume", 1, []() {QList<int> l; l << 255; return l;} (), this);
    num_opt->setTooltips(QStringList("Volume out of 255"));
    sound_layout->addWidget(num_opt);

    // FPS Group
    QVBoxLayout *fps_layout = new QVBoxLayout(this);
    ui->fpsGroup->setLayout(fps_layout);

    b = new ConfigButton("FPS", "FPS Counter", this);
    fps_layout->addWidget(b);

    num_opt = new NumericOptionWidget("FPS_CAP", "Calculation FPS Cap", 1, []() {QList<int> l; l << 9999; return l;} (), this);
    num_opt->setTooltips(QStringList("Maximum FPS the game is allowed to run at"));
    fps_layout->addWidget(num_opt);

    num_opt = new NumericOptionWidget("G_FPS_CAP", "Graphical FPS Cap", 1, []() {QList<int> l; l << 9999; return l;} (), this);
    num_opt->setTooltips(QStringList("Maximum graphical FPS the game is allowed to run at"));
    fps_layout->addWidget(num_opt);

    //Startup Group
    ui->startupGroup->setLayout(new QVBoxLayout(ui->startupGroup));
    ui->startupGroup->layout()->addWidget(new ConfigButton("INTRO", "Intro moive", this));
    ui->startupGroup->layout()->addWidget(new ConfigButton("WINDOWED", "Windowed", this));

    //Processor priority button
    b = new ConfigButton("PRIORITY", "Processor Priority", []() {QStringList l; l << "IDLE" << "BELOW_NORMAL" << "NORMAL" << "HIGH" << "REALTIME"; return l;} (), this);
    ui->procButtonBox->addWidget(b);

    //Save Group
    QGridLayout *save_layout = new QGridLayout(this);
    ui->saveGroup->setLayout(save_layout);
    QStringList options, labels;
    options << "AUTOSAVE_PAUSE" << "INITIAL_SAVE" << "PAUSE_ON_LOAD" << "COMPRESSED_SAVES" << "AUTOBACKUP";
    labels << "Autosave Pause" << "Initial Save" << "Pause on Load" << "Compress Saves" << "Auto Backup";
    Q_ASSERT( options.length() == labels.length() );
    save_layout->addWidget(new ConfigButton("AUTOSAVE", "Autosave", []() {QStringList l; l << "NONE" << "YEARLY" << "SEASONAL"; return l;} (), this), 0 ,0);
    for (int i = 1; i < options.length() + 1; i++) {
        b = new ConfigButton(options.at(i - 1), labels.at(i - 1), this);
        save_layout->addWidget(b, i/2, i%2); // 2 is the number of columns
    }
}

AdvancedTab::~AdvancedTab()
{
    delete ui;
}
