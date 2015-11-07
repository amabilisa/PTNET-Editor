/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    transitioneditdialog.cpp
**************************************************************/

#include "transitioneditdialog.h"

TransitionEditDialog::TransitionEditDialog(QWidget *parent) :
    QDialog(parent)
{
   // setFixedSize (200, 150);
    setModal(true);
    setWindowTitle("Transition Attributes");

    inputLabel = new QLineEdit(this);
    inputLabel->setMaximumSize(200, 30);

     slider = new QSlider(Qt::Horizontal);
     slider->setFixedWidth(200);
     slider->setRange(-90, 90);
     slider->setSliderPosition (0);
     slider->setTickPosition(QSlider::TicksBelow);
     slider->setTickInterval(45);

    validateButton = new QPushButton("Ok");
    validateButton->setDefault(true);
    cancelButton = new QPushButton("Cancel");

    vlayout = new QVBoxLayout;
    flayout = new QFormLayout;
    hlayout = new QHBoxLayout;

    hlayout->addWidget(cancelButton);
    hlayout->addWidget(validateButton);
    hlayout->setStretch (0, 100);
    hlayout->setAlignment (cancelButton, Qt::AlignRight);
    hlayout->setAlignment (validateButton, Qt::AlignRight);

    flayout->addRow("<span style=\"text-decoration:"\
		"underline;\">L</span>abel : ", inputLabel);
    flayout->addRow("<span style=\"text-decoration:"\
		"underline;\">R</span>otation : ", slider);

    groupBox = new QGroupBox;
    groupBox->setLayout(flayout);

    vlayout->addWidget(groupBox);
    vlayout->addLayout(hlayout);

    setLayout(vlayout);

    connect (validateButton, SIGNAL (clicked ()), this, SLOT (accept ()));
    connect (cancelButton, SIGNAL (clicked ()), this, SLOT (reject ()));
    connect (slider, SIGNAL(valueChanged(int)), this, SLOT(showRotDegree(int)));
}

void TransitionEditDialog::showRotDegree(int d)
{
   QVariant v(d);
   QToolTip::showText ( slider->mapToGlobal(QPoint(90 + d - 35, 0)),
                       QString(v.toString()+" "), slider);
}

TransitionEditDialog::~TransitionEditDialog()
{
    delete inputLabel;
    delete slider;
    delete validateButton;
    delete cancelButton;
    delete hlayout;
    delete flayout;
    delete groupBox;
    delete vlayout;
}
