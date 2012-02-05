#include "OptionsTab.h"
#include "ui_OptionsTab.h"

#include "ConfigButton.h"
#include "NumericOptionWidget.h"
#include "DwarfFortress.h"
#include "KeybindsWidget.h"
#include "IInitsBundle.h"

#include <QtilitiesCore>

#include <QDebug>
#include <QPointer>
#include <QMessageBox>
#include <QFile>

OptionsTab::OptionsTab( DFManagerPtr manager, QWidget * parent )
    : QWidget(parent)
    , ui(new Ui::OptionsTab)
    , m_dataManager(manager)
{
    ui->setupUi(this);

    // Options Group
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

    NumericOptionWidget* num_opt = new NumericOptionWidget("POPULATION_CAP", "Population Cap", 1, []() {QList<int> l; l << 999; return l;} (), this);
    num_opt->setTooltips(QStringList("Population Cap"));
    options_layout->addWidget(num_opt, options.length()/2, options.length()%2);

    num_opt = new NumericOptionWidget("BABY_CHILD_CAP", "Child Cap", 2, []() {QList<int> l; l << 999 << 9999; return l;}(), this);
    num_opt->setTooltips([this]() { QStringList l; l << tr("Absolute cap on the number of babies+children") << tr("New child cap as percentage of total population"); return l;}());
    options_layout->addWidget(num_opt, (options.length()+1)/2, (1+options.length())%2);

    // Mods Group
    m_aquifersButton = new QPushButton(tr("Aquifers: ") + DwarfFortress::instance().rawsFind("[AQUIFER]"));
    if (DwarfFortress::instance().rawsFind("[PET_EXOTIC]") == "YES") {
        m_exoticButton = new QPushButton(tr("Exotic Animals: ") + DwarfFortress::instance().rawsFind("[PET_EXOTIC]"));
    } else {
        m_exoticButton = new QPushButton(tr("Exotic Animals: ") + DwarfFortress::instance().rawsFind("[MOUNT_EXOTIC]"));
    }
    connect(m_aquifersButton, SIGNAL(pressed()), this, SLOT(aquifiersPressed()));
    connect(m_exoticButton, SIGNAL(pressed()), this, SLOT(exoticPressed()));

    QHBoxLayout *box = new QHBoxLayout(ui->modsGroup);
    box->addWidget(m_aquifersButton);
    box->addWidget(m_exoticButton);
    ui->modsGroup->setLayout(box);

    //Keybinds Group
    ui->keybindingsGroup->setLayout(new QHBoxLayout(ui->keybindingsGroup));
    ui->keybindingsGroup->layout()->addWidget(new KeybindsWidget(ui->keybindingsGroup));

    connect( &DwarfFortress::instance(), SIGNAL( dataChanged() ), this, SLOT( dfDataChanged() ));
    connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(defaultsPressed()));
}

OptionsTab::~OptionsTab()
{
    delete ui;
}

void OptionsTab::dfDataChanged()
{
    m_aquifersButton->setText("Aquifers: " + DwarfFortress::instance().rawsFind("[AQUIFER]"));
    if (DwarfFortress::instance().rawsFind("[PET_EXOTIC]") == "YES")
        m_exoticButton->setText("Exotic Animals: " + DwarfFortress::instance().rawsFind("[PET_EXOTIC]"));
    else
        m_exoticButton->setText("Exotic Animals: " + DwarfFortress::instance().rawsFind("[MOUNT_EXOTIC]"));
}

void OptionsTab::aquifiersPressed()
{
    if (DwarfFortress::instance().rawsFind("[AQUIFER]") == "YES")
        DwarfFortress::instance().rawsReplace("[AQUIFER]", "!AQUIFER!");
    else
        DwarfFortress::instance().rawsReplace("!AQUIFER!", "[AQUIFER]");
    m_aquifersButton->setText(tr("Aquifers: ") + DwarfFortress::instance().rawsFind("[AQUIFER]"));
}

void OptionsTab::exoticPressed()
{
    if (DwarfFortress::instance().rawsFind("[PET_EXOTIC]") == "YES" || DwarfFortress::instance().rawsFind("[MOUNT_EXOTIC]") == "YES") {
        DwarfFortress::instance().rawsReplace("[PET_EXOTIC]", "![PET]!");
        DwarfFortress::instance().rawsReplace("[MOUNT_EXOTIC]", "![MOUNT]!");
    } else {
        DwarfFortress::instance().rawsReplace("![PET]!", "[PET_EXOTIC]");
        DwarfFortress::instance().rawsReplace("![MOUNT]!", "[MOUNT_EXOTIC]");
    }
    if (DwarfFortress::instance().rawsFind("[PET_EXOTIC]") == "YES" || DwarfFortress::instance().rawsFind("[MOUNT_EXOTIC]") == "YES") {
        m_exoticButton->setText(tr("Exotic Animals: ") + "YES");
    } else {
        m_exoticButton->setText(tr("Exotic Animals: ") + "NO");
    }
}

void OptionsTab::defaultsPressed()
{
    QMessageBox msg(this);
    msg.setText(tr("Are you sure that you want to reset all init settings to their defaults?"));
    msg.setInformativeText(tr("Note that this won't effect settings not controlled by the init and d_init files, such as the aquifers setting."));
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg.setDefaultButton(QMessageBox::No);
    int sure = msg.exec();
    if (sure == QMessageBox::Yes) {

        QList<QObject*> ifaces = OBJECT_MANAGER->registeredInterfaces("com.lazynewb.IInitsBundle/1.0");
        foreach(QObject* iface, ifaces) {
            IInitsBundle* bundle = qobject_cast<IInitsBundle*>(iface);
            if( bundle && bundle->dataAvailable() && bundle->name() == "Defaults" ) {
               const bool result = m_dataManager->installInits(bundle);
               if( result ) {
                    QMessageBox::information(this, tr("Defaults Restored"), tr("Init settings restored to defaults!"));
               } else {
                    QMessageBox::warning(this, tr("Error"), tr("Init settings could not be restored."));
               }
               return;
            }
        }
        QMessageBox::warning(this, tr("Couldn't Find Data"), tr("The Default settings data could not be located."));

    }
}
