/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    arceditdialog.h
**************************************************************/

#ifndef __ARCEDITDIALOG_H
#define __ARCEDITDIALOG_H

#include <QDialog>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGroupBox>

class ArcEditDialog : public QDialog
{
  Q_OBJECT

 friend class PTNtab;

 public:

	ArcEditDialog (QWidget * parent);
	~ArcEditDialog ();

	// void showDialog(int w);
	// int getValue() const;

 public slots: /* */
 signals: /* */
 private:

	QHBoxLayout * hlayout;
	QVBoxLayout * vlayout;
	QFormLayout * flayout;
	QSpinBox    * inputWeight;
	QPushButton * validateButton;
	QPushButton * cancelButton;
    	QGroupBox * groupBox;
};

#endif 
 
