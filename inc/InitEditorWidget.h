#ifndef INITEDITORWIDGET_H
#define INITEDITORWIDGET_H

#include <QWidget>


class QAbstractButton;

namespace Ui {
class InitEditorWidget;
}

class InitEditorWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit InitEditorWidget(QWidget *parent = 0);
    ~InitEditorWidget();
    

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    void read_files();
    Ui::InitEditorWidget *ui;
};

#endif // INITEDITORWIDGET_H
