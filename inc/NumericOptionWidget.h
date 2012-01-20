#ifndef NUMERICOPTIONWIDGET_H
#define NUMERICOPTIONWIDGET_H

#include <QWidget>

class QLabel;
class QSpinBox;
class NumberEditChain;

class NumericOptionWidget : public QWidget
{
    Q_OBJECT
public:
    NumericOptionWidget(const QString &option_name, const QString &pretty_label, int num_values, QWidget *parent = nullptr);

    void setTooltips(const QStringList &tips);

public slots:
    void dfDataChanged();
    void valueChanged();

private:
    QLabel *m_label;
    NumberEditChain *m_numberEdit;
    QString m_option;
};

class NumberEditChain : public QWidget {
    Q_OBJECT
public:
    NumberEditChain(int num_edits, QWidget *parent = nullptr);
    ~NumberEditChain() = default;

    int length() const;

    void setMinimum(int edit, int min);
    void setTooltips(const QStringList &tips);
    void setTooltip(int edit, const QString &tooltip);
    void setValue(int edit, int value);

    void setValues(const QList<int> &values);
    QStringList values() const;

signals:
    void valuesChanged();

private:
    QList<QSpinBox*> m_edits;
};

#endif // NUMERICOPTIONWIDGET_H
