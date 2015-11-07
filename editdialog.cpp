#include "editdialog.h"

EditDialog::EditDialog(QWidget * parent, Qt::WindowFlags f)
	:QDialog(parent, f) 
{
  setModal(true);
  inputLabel = new QLineEdit(tr("labeltext"), 0);
  inputLabel->setFixedSize(120, 25);

 

 
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
    
    vlayout->addLayout(flayout);

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



}

EditDialog::~EditDialog()
{
    delete inputLabel;

    delete validateButton;
    delete cancelButton;
    delete hlayout;
    delete flayout;
    delete vlayout;
    delete groupBox;
    delete hlayout2;
    delete vlayout2;
}

