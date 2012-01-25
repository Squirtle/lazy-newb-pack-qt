#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "DFDataManager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init();

private slots:
    void on_actionQuit_triggered();
    void loadLocalData();

private:
    bool verifyLNPData();
    void setupOptionsGroup();

    Ui::MainWindow *ui;
    DFManagerPtr m_dataManager;
    bool m_init;
};

#endif // MAINWINDOW_H
