#ifndef EDITDIALOG_H
#define EDITDIALOG_H


#include <QDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QLabel>
#include <QGroupBox>

#include "defs.h"

class EditDialog : public QDialog
{
 public:
	EditDialog(QWidget * parent = 0, Qt::WindowFlags f = 0);
	~EditDialog();

 protected:

    QHBoxLayout * hlayout;
    QHBoxLayout * hlayout2;
    QVBoxLayout * vlayout;
    QVBoxLayout * vlayout2;
    QFormLayout * flayout;
    QLineEdit   * inputLabel;
    QPushButton * validateButton;
    QPushButton * cancelButton;
    QGroupBox   * groupBox;

};

#endif // EDITDIALOG_H 
