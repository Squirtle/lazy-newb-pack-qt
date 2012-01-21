#ifndef OPTIONSTAB_H
#define OPTIONSTAB_H

#include <QWidget>

class QPushButton;

namespace Ui {
class OptionsTab;
}

class OptionsTab : public QWidget
{
    Q_OBJECT
    
public:
    explicit OptionsTab(QWidget *parent = nullptr);
    ~OptionsTab();

private slots:
    void dfDataChanged();
    void exoticPressed();
    void aquifiersPressed();
    void editInitPressed();
    void defaultsPressed();


private:
    Ui::OptionsTab *ui;

    QPushButton *m_aquifersButton;
    QPushButton *m_exoticButton;

};

#endif // OPTIONSTAB_H
