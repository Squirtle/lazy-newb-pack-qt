#include "inc/NumericOptionWidget.h"

#include "inc/DwarfFortress.h"

#include <QSpinBox>
#include <QLabel>
#include <QString>
#include <QFormLayout>
#include <QList>

#include <QDebug>

NumberEditChain::NumberEditChain(int num_edits, QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    for(int i = 0; i < num_edits; ++i) {
        m_edits.push_back(new QSpinBox(this));
        m_edits.at(i)->setMinimum(0);
        connect(m_edits.at(i), SIGNAL(valueChanged(int)), SIGNAL(valuesChanged()));
        layout->addWidget(m_edits.at(i));
    }
}

int NumberEditChain::length() const
{
    return m_edits.length();
}

void NumberEditChain::setMinimum(int edit, int min)
{
    Q_ASSERT(edit >=0 && edit < m_edits.length());
    m_edits.at(edit)->setMinimum(min);
}

void NumberEditChain::setTooltips(const QStringList &tips)
{
    for(int i = 0; i < tips.length(); ++i) {
        setTooltip(i, tips.at(i));
    }
}

void NumberEditChain::setTooltip(int edit, const QString &tooltip)
{
    Q_ASSERT(edit >=0 && edit < m_edits.length());
    m_edits.at(edit)->setToolTip(tooltip);
}

void NumberEditChain::setValue(int edit, int value)
{
    Q_ASSERT(edit >=0 && edit < m_edits.length());
    m_edits.at(edit)->setValue(value);

}
void NumberEditChain::setValues(const QList<int> &values)
{
    for(int i = 0; i < values.length(); ++i) {
        setValue(i, values.at(i));
    }
}

QStringList NumberEditChain::values() const
{
    QStringList list;
    foreach(const QSpinBox* edit, m_edits) {
        list << edit->text();
    }
    return list;
}

NumericOptionWidget::NumericOptionWidget(const QString &option_name, const QString &pretty_label, int num_values, QWidget *parent)
    : QWidget(parent)
    , m_option( option_name )
{
    QFormLayout* layout = new QFormLayout(this);
    m_label = new QLabel(pretty_label, this);
    m_numberEdit = new NumberEditChain(num_values);
    layout->addRow(m_label, m_numberEdit);

    connect( &DwarfFortress::instance(), SIGNAL( dataChanged() ), this, SLOT( dfDataChanged() ));
    connect(m_numberEdit, SIGNAL(valuesChanged()), this, SLOT(valueChanged()));

    dfDataChanged();
}

void NumericOptionWidget::setTooltips(const QStringList &tips)
{
    Q_ASSERT(tips.length() == m_numberEdit->length());
    m_numberEdit->setTooltips(tips);
}

void NumericOptionWidget::valueChanged()
{
    const QStringList values = m_numberEdit->values();
    const QString value = values.length() == 1 ? values.first() : values.join(":");
    DwarfFortress::instance().setOption(m_option, value);
}

void NumericOptionWidget::dfDataChanged()
{
    const QString value = DwarfFortress::instance().getOption(m_option);
    QStringList values = value.split(":");
    //qDebug() << m_option << values;
    QList<int> int_values;
    foreach( const QString& v, values) {
        bool ok = false;
        int_values << v.toInt(&ok);
        Q_ASSERT(ok);
    }
    m_numberEdit->blockSignals(true);
    m_numberEdit->setValues(int_values);
    m_numberEdit->blockSignals(false);
}
