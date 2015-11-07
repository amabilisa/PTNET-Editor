/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    transitioneditdialog.h
**************************************************************/

#ifndef TRANSITIONEDITDIALOG_H
#define TRANSITIONEDITDIALOG_H

#include <QDialog>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QToolTip>

class TransitionEditDialog : public QDialog
{
    Q_OBJECT

friend class PTNtab;

public:
    explicit TransitionEditDialog(QWidget *parent = 0);
    ~TransitionEditDialog();
    
signals:
    
public slots:
    
   void showRotDegree(int d);

private:
   QHBoxLayout * hlayout;
   QVBoxLayout * vlayout;
   QFormLayout * flayout;
   QLineEdit   * inputLabel;
   QSlider     * slider;
   QPushButton * validateButton;
   QPushButton * cancelButton;
   QGroupBox * groupBox;

};

#endif // TRANSITIONEDITDIALOG_H
