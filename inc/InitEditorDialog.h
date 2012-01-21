#ifndef INITEDITORDIALOG_H
#define INITEDITORDIALOG_H

#include <QWidget>

class QPushButton;
class QTextEdit;
class QGridLayout;

class InitEditorDialog : public QWidget
{
    Q_OBJECT

public:
    explicit InitEditorDialog(QWidget *parent = 0);

public slots:
    void load_pressed();

private slots:
    void save_pressed();

private:
    QPushButton *save, *load;
    QTextEdit *init, *dinit;
    QGridLayout *grid;
};

#endif // INITEDITORDIALOG_H
