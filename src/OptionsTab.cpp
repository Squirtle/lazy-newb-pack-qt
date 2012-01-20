#include "inc/OptionsTab.h"
#include "ui_OptionsTab.h"

#include "ConfigButton.h"
#include "NumericOptionWidget.h"

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
    options << "ECONOMY" << "TEMPERATURE" << "WEATHER" << "CAVEINS" << "INVADERS" << "SHOW_FLOW_AMOUNTS";
    labels << "Economy" << "Temperature" << "Weather" << "Cave-ins" << "Invaders" << "Liquid Depth";
    Q_ASSERT( options.length() == labels.length() );
    for( int i = 0; i < options.length(); ++i ) {
        ConfigButton* b = new ConfigButton(options.at(i), labels.at(i), this);
        options_layout->addWidget(b, i/2, i%2); // 2 is the number of columns
    }

    NumericOptionWidget* num_opt = new NumericOptionWidget("POPULATION_CAP", "Population Cap", 1, this);
    num_opt->setTooltips(QStringList("Population Cap"));
    options_layout->addWidget(num_opt, options.length()/2, options.length()%2);

    num_opt = new NumericOptionWidget("BABY_CHILD_CAP", "Child Cap", 2, this);
    num_opt->setTooltips([this]() { QStringList l; l << tr("Absolute cap on the number of babies+children") << tr("New child cap as percentage of total population"); return l;}());
    options_layout->addWidget(num_opt, (options.length()+1)/2, (1+options.length())%2);


}

OptionsTab::~OptionsTab()
{
    delete ui;
}
