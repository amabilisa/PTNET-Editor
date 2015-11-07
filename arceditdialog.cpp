/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    arc.cpp
**************************************************************/

#include "arceditdialog.h"

ArcEditDialog::ArcEditDialog(QWidget * parent):QDialog(parent)
{
 //setFixedSize (200, 150);
 setModal(true);
 setWindowTitle(tr("Arc attributes"));

 inputWeight = new QSpinBox;
 inputWeight->setMinimum(1);
 inputWeight->setMaximum(10);
 inputWeight->setMaximumSize(60, 30);
 inputWeight->setValue(1);

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

 flayout->addRow("<span style=\"text-decoration:underline;\">W</span>eight : ", inputWeight);
 groupBox = new QGroupBox (this);
 groupBox->setFlat (false);
 groupBox->setLayout (flayout);

 vlayout->addWidget(groupBox);
 vlayout->addLayout(hlayout);

 this->setLayout(vlayout);

 connect(validateButton, SIGNAL(clicked()), this, SLOT(accept()));
 connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

/*
void ArcEditDialog::showDialog(int w)
{
 inputWeight->setValue(w);
 exec();
}

int ArcEditDialog::getValue() const
{
  return inputWeight->value();
}
*/
ArcEditDialog::~ArcEditDialog()
{
 delete inputWeight;
 delete groupBox;
 delete validateButton;
 delete cancelButton;
}
   
