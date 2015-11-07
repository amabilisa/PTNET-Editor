/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    placeeditdialog.cpp
**************************************************************/

#include "placeeditdialog.h"

PlaceEditDialog::PlaceEditDialog (QWidget * parent):
    QDialog (parent)
{
    //setFixedSize (200, 200);
    setModal(true);
    setWindowTitle(tr("Place Attributes"));

    inputLabel = new QLineEdit(tr("labeltext"), 0);
    inputLabel->setFixedSize(120, 25);

    inputTokens = new QSpinBox;
    inputTokens->setMinimum(0);
    inputTokens->setMaximum(999);
    inputTokens->setFixedSize(120, 25);
    inputTokens->setValue(0);

     inputCapacity = new QSpinBox;
     inputCapacity->setMinimum(0);
     inputCapacity->setMaximum(100);
     inputCapacity->setFixedSize(120, 25);

    chckBox = new QCheckBox(tr("Show Attributes"), 0);
    chckBox->setChecked (false);
    label = new QLabel (tr("(k = 0 : No capacity restriction)"));

    validateButton = new QPushButton(tr("Ok"));
    validateButton->setDefault(true);
    cancelButton = new QPushButton(tr("Cancel"));

    vlayout  = new QVBoxLayout;
    vlayout2 = new QVBoxLayout;
    hlayout  = new QHBoxLayout;
    hlayout2 = new QHBoxLayout;
    flayout  = new QFormLayout;

    flayout->addRow(tr("<span style=\"text-decoration:\
           underline;\">L</span>abel  : "), inputLabel);
    flayout->addRow(tr("<span style=\"text-decoration:\
           underline;\">T</span>okens : "), inputTokens);
    hlayout->addWidget (inputCapacity);
    hlayout->addWidget (label);
    flayout->addRow (tr("<span style=\"text-decoration:\
                     underline;\">C</span>apacity : "), hlayout);
    vlayout->addLayout(flayout);
    vlayout->addWidget(chckBox);
    groupBox = new QGroupBox (this);
    groupBox->setFlat (false);
    groupBox->setLayout (vlayout);

    hlayout2->addWidget(cancelButton);
    hlayout2->addWidget(validateButton);
    hlayout2->setStretch (0, 100);
    hlayout2->setAlignment (cancelButton, Qt::AlignRight);
    hlayout2->setAlignment (validateButton, Qt::AlignRight);

    vlayout2->addWidget(groupBox);
    vlayout2->addLayout(hlayout2);

    setLayout(vlayout2);

    connect (validateButton, SIGNAL (clicked ()), this, SLOT (accept ()));
    connect (cancelButton, SIGNAL (clicked ()), this, SLOT (reject ()));
}

/* 
void PlaceEditDialog::show (const QString& nm, int t, int c)
{
    inputLabel->setText (nm);
    inputTokens->setValue (t);

    if(c == omega)
       inputCapacity->setValue (0);
    else
       inputCapacity->setValue (c);

    exec ();
}

QString PlaceEditDialog::getName () const
{
  return inputLabel->text();
}

int PlaceEditDialog::getTokens() const
{
  return inputTokens->value ();
}

int PlaceEditDialog::getCapacity() const
{
  return inputCapacity->value();
}

bool PlaceEditDialog::showAttributes()
{
  return chckBox->isChecked ();
}
*/

PlaceEditDialog::~PlaceEditDialog()
{
    delete label;
    delete inputLabel;
    delete inputTokens;
    delete inputCapacity;
    delete chckBox;

    delete validateButton;
    delete cancelButton;
    delete groupBox;
}

