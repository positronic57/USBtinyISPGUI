#ifndef BITSWIDGET_H
#define BITSWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QButtonGroup>

#include <vector>
#include <bitset>

class BitsWidget : public QWidget
{
    Q_OBJECT

public:
    enum BIT_BOXES_LAYOUT {
        Horisontal = 0,
        Vertical
    };

private:
    unsigned int number_of_bits = 8;
    BIT_BOXES_LAYOUT bits_orientation = Horisontal;
    std::bitset<64> value = 0;
    unsigned long bit_mask = 0xFF;
    std::vector<QCheckBox *>bit_box;
    QBoxLayout *box_layout = nullptr;
    QButtonGroup *bit_buttons_group = nullptr;
    void chageBitBoxesState();

public:
    explicit BitsWidget(QWidget *parent = nullptr);
    explicit BitsWidget(unsigned int nbr_of_bits, BitsWidget::BIT_BOXES_LAYOUT orientation, QWidget *parent = nullptr);
    virtual ~BitsWidget();
    void setNames(const QStringList &names);
    unsigned long as_ulong();
    QString toHexQtString();

public slots:
    void setValue(unsigned long);
    void setValue(QString);

signals:
    void valueChanged();

private slots:
    void bitValueChanged(int bit);

};

#endif // BITSWIDGET_H
