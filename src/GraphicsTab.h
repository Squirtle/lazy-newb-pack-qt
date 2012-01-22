#ifndef GRAPHICSWIDGET_H
#define GRAPHICSWIDGET_H

#include <QWidget>

namespace Ui {
class GraphicsTab;
}

class GraphicsTab : public QWidget
{
    Q_OBJECT
    
public:
    explicit GraphicsTab(QWidget *parent = 0);
    ~GraphicsTab();
    
private:
    Ui::GraphicsTab *ui;
};

#endif // GRAPHICSWIDGET_H
