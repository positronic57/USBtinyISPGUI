#include "bitswidget.h"


BitsWidget::BitsWidget(QWidget *parent) : QWidget(parent)
{
   box_layout = new QHBoxLayout;
   bit_buttons_group = new QButtonGroup;
   bit_buttons_group->setExclusive(false);

   for(unsigned int bit = 0; bit < 8; bit++) {
       bit_box.push_back(new QCheckBox(QString("bit_%1").arg(7 - bit)));
       bit_buttons_group->addButton(bit_box[bit], 7 - bit);
       box_layout->addWidget(bit_box[bit]);
   }

   this->setLayout(box_layout);

   connect(bit_buttons_group,
           static_cast<void (QButtonGroup:: *)(int)>(&QButtonGroup::buttonClicked),
           this, &BitsWidget::bitValueChanged);
}

BitsWidget::BitsWidget(unsigned int nbr_of_bits, BIT_BOXES_LAYOUT orientation, QWidget *parent)
    :QWidget(parent)
{
    number_of_bits = nbr_of_bits > 64 ? 64 : nbr_of_bits;
    bits_orientation = orientation;

    bit_buttons_group = new QButtonGroup;
    bit_buttons_group->setExclusive(false);

    switch (bits_orientation) {
    case BIT_BOXES_LAYOUT::Horisontal:
        box_layout = new QHBoxLayout;
        break;
    case BIT_BOXES_LAYOUT::Vertical:
        box_layout = new QVBoxLayout;
        break;
    }

    bit_mask = 0;
    for(unsigned int bit = 0; bit < number_of_bits; bit++) {
        bit_mask |= (1 << bit);
        bit_box.push_back(new QCheckBox(QString("bit_%1").arg(number_of_bits - bit - 1)));
        bit_buttons_group->addButton(bit_box[bit], number_of_bits - bit - 1);
        box_layout->addWidget(bit_box[bit]);
    }

    this->setLayout(box_layout);

    connect(bit_buttons_group,
            static_cast<void (QButtonGroup:: *)(int)>(&QButtonGroup::buttonClicked),
            this, &BitsWidget::bitValueChanged);
}

BitsWidget::~BitsWidget()
{
    delete bit_buttons_group;
    delete box_layout;
    for(unsigned long bit = 0; bit < number_of_bits; bit++) {
        delete bit_box[bit];
    }

    bit_box.clear();
}

void BitsWidget::setNames(const QStringList &names)
{
    if (names.length() < static_cast<int>(number_of_bits)) {
        return;
    }
    for(unsigned int bit = 0; bit < number_of_bits; bit++) {
        bit_box[bit]->setText(names.at(number_of_bits - bit - 1));
    }
}

unsigned long BitsWidget::as_ulong()
{
    return value.to_ulong() & bit_mask;
}

QString BitsWidget::toHexQtString()
{
    return QString::number(value.to_ulong() & bit_mask, 16).toUpper();
}


void BitsWidget::chageBitBoxesState()
{
    for(unsigned int bit = 0; bit < number_of_bits; bit++) {
      bit_box[number_of_bits - bit - 1]->setChecked(value[bit]);
    }
}

void BitsWidget::setValue(unsigned long new_value)
{
    value = new_value;
    chageBitBoxesState();
}

void BitsWidget::setValue(QString new_value)
{
    value = new_value.toULong(nullptr, 16);
    chageBitBoxesState();
}

void BitsWidget::bitValueChanged(int bit)
{
    if (bit_buttons_group->button(bit)->isChecked()) {
        value[bit] = 1;
    }
    else {
        value[bit] = 0;
    }

    emit valueChanged();
}
