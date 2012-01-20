#include "inc/OptionsTab.h"
#include "ui_OptionsTab.h"

#include "ConfigButton.h"

#include <QDebug>

OptionsTab::OptionsTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OptionsTab)
{
    ui->setupUi(this);

    QGridLayout *options_layout = new QGridLayout(this);
    ui->optionsGroup->setLayout(options_layout);
    QStringList options;
    QStringList labels;
    options << "ECONOMY" << "TEMPERATURE" << "WEATHER" << "CAVEINS" << "INVADERS" << "SHOW_FLOW_AMOUNTS"
            << "POPULATION_CAP" << "BABY_CHILD_CAP";
    labels << "Economy" << "Temperature" << "Weather" << "Cave-ins" << "Invaders" << "Liquid Depth"
           << "Population Cap" << "Child Cap";
    Q_ASSERT( options.length() == labels.length() );
    for( int i = 0; i < options.length(); ++i ) {
        ConfigButton* b = new ConfigButton(options.at(i), labels.at(i), this);
        options_layout->addWidget(b, i/2, i%2); // 2 is the number of columns
    }
}

OptionsTab::~OptionsTab()
{
    delete ui;
}
