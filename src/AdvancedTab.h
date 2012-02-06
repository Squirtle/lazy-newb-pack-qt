#ifndef ADVANCEDTAB_H
#define ADVANCEDTAB_H

#include "DFDataManager.h"

#include <QWidget>

namespace Ui {
class AdvancedTab;
}

class AdvancedTab : public QWidget
{
    Q_OBJECT

public:
    explicit AdvancedTab(DFManagerPtr manager, QWidget* parent = nullptr);
    ~AdvancedTab();

private:
    Ui::AdvancedTab *ui;

    DFManagerPtr m_dataManager;
};

#endif // ADVANCEDTAB_H
