#ifndef OPTIONSTAB_H
#define OPTIONSTAB_H

#include "DFDataManager.h"

#include <QWidget>

class QPushButton;

namespace Ui {
class OptionsTab;
}

class OptionsTab : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsTab(DFManagerPtr manager, QWidget* parent = nullptr);
    ~OptionsTab();

private slots:
    void dfDataChanged();
    void exoticPressed();
    void aquifiersPressed();
    void defaultsPressed();


private:
    Ui::OptionsTab *ui;

    QPushButton *m_aquifersButton;
    QPushButton *m_exoticButton;
    DFManagerPtr m_dataManager;
};

#endif // OPTIONSTAB_H
