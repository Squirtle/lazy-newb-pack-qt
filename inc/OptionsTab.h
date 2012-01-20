#ifndef OPTIONSTAB_H
#define OPTIONSTAB_H

#include <QWidget>

namespace Ui {
class OptionsTab;
}

class OptionsTab : public QWidget
{
    Q_OBJECT
    
public:
    explicit OptionsTab(QWidget *parent = nullptr);
    ~OptionsTab();
    
private:
    Ui::OptionsTab *ui;
};

#endif // OPTIONSTAB_H
