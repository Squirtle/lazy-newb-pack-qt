#include "inc/ConfigButton.h"

#include "inc/DwarfFortress.h"

#include <QDebug>

ConfigButton::ConfigButton( const QString& option_name, const QString& pretty_label , QWidget * parent )
    : QPushButton( parent )
    , m_option( option_name )
    , m_label( pretty_label )
{
    m_values << "YES" << "NO";
    connect( &DwarfFortress::instance(), SIGNAL( dataChanged() ), this, SLOT( dfDataChanged() ));
    connect( this, SIGNAL(clicked(bool)), this, SLOT(pushed()));
    dfDataChanged();
}

ConfigButton::ConfigButton( const QString& option_name, const QString& pretty_label, const QStringList &option_values, QWidget * parent )
    : QPushButton( parent )
    , m_option( option_name )
    , m_label( pretty_label )
    , m_values( option_values )
{
    connect( &DwarfFortress::instance(), SIGNAL( dataChanged() ), this, SLOT( dfDataChanged() ));
    connect( this, SIGNAL(clicked(bool)), this, SLOT(pushed()));
    dfDataChanged();
}

QString ConfigButton::option() const
{
    return m_option;
}

QString ConfigButton::label() const
{
    return m_label;
}

void ConfigButton::dfDataChanged()
{
    setText(QString("%1: %2").arg(m_label).arg(DwarfFortress::instance().getOption(m_option)));
}

void ConfigButton::pushed()
{
    // cycle to next value
    const int curr_idx = m_values.indexOf(currentValue());
    int next_idx = (curr_idx+1) % m_values.length();
    Q_ASSERT( next_idx >= 0 && next_idx < m_values.length() );
    DwarfFortress::instance().setOption(m_option, m_values.at(next_idx));
    dfDataChanged();
}

QString ConfigButton::currentValue() const
{
    return DwarfFortress::instance().getOption(m_option);
}
