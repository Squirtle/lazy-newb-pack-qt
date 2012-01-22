#ifndef SETUPWIDGET_H
#define SETUPWIDGET_H

#include <QWidget>

namespace Ui {
class SetupTab;
}

class SetupTab : public QWidget
{
    Q_OBJECT
    
public:
    explicit SetupTab(QWidget *parent = 0);
    ~SetupTab();

private slots:
    void changeDFPressed();
    void playPressed();

private:
    void updateDFLocation();
    Ui::SetupTab *ui;
};

#endif // SETUPWIDGET_H
