    #ifndef KEYBINDSWIDGET_H
#define KEYBINDSWIDGET_H

#include <QWidget>

class QPushButton;
class QListView;
class StringListModel;
class QGridLayout;

class KeybindsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KeybindsWidget(QWidget *parent = 0);
    
private slots:
    void load_pressed();
    void del_pressed();
    void refresh_pressed();
    void save_pressed();

private:
    QPushButton *m_load, *m_refresh, *m_save, *m_del;
    QListView *m_view;
    StringListModel *m_model;
    QStringList m_list;
};

#endif // KEYBINDSWIDGET_H
