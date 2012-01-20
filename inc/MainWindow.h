#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void changeDFPressed();
    void playPressed();
    void editInitPressed();
    void defaultsPressed();
    
private:
    bool verifyLNPData();
    void updateDFLocation();
    void setupOptionsGroup();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
