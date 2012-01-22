#ifndef CONFIGBUTTON_H
#define CONFIGBUTTON_H

#include <QPushButton>

class ConfigButton : public QPushButton
{
    Q_OBJECT
public:
    /**
     * Constructor for a boolean (YES/NO) option
     * @param option_name the name of the option in the data file
     * @param pretty_label a user friendly name for the option
     */
    ConfigButton(const QString &option_name, const QString &pretty_label, QWidget *parent = 0);
    /**
     * Constructor for an option with multiple non-boolean options.
     * Example: the cpu PRIORITY option uses values IDLE. BELOW_NORMAL, NORMAL, etc.
     * Clicking the button will cycle through the values
     * @param option_name the name of the option in the data file
     * @param pretty_label a user friendly name for the option
     * @param option_values the list of valid values for the option
     */
    ConfigButton(const QString &option_name, const QString &pretty_label, const QStringList &option_values, QWidget *parent = 0);

    QString option() const;
    QString label() const;

public slots:
    void dfDataChanged();
    void pushed();

private:
    QString currentValue() const; /*!< convienence method to get the current value */
    QString m_option; /*!< The option this button controls */
    QString m_label; /*!< The label the user sees */
    QStringList m_values; /*!< the values for the option */

};

#endif // CONFIGBUTTON_H
