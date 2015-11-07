/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    placeeditdialog.h
**
*/

#ifndef PLACEEDITDIALOG_H
#define PLACEEDITDIALOG_H

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

class PlaceEditDialog : public QDialog
{
    Q_OBJECT

 friend class PTNtab;

 public:

    PlaceEditDialog (QWidget * parent = 0);
    ~PlaceEditDialog ();

    //void show (const QString& nm, int t, int c);
    //QString getName () const;
    //int getTokens() const;
    //int getCapacity() const;
    //bool showAttributes();

 public slots:
 signals:
 private:

    QHBoxLayout * hlayout;
    QHBoxLayout * hlayout2;
    QVBoxLayout * vlayout;
    QVBoxLayout * vlayout2;
    QFormLayout * flayout;
    QLineEdit   * inputLabel;
    QSpinBox    * inputTokens;
    QSpinBox    * inputCapacity;
    QCheckBox   * chckBox;
    QLabel      * label;
    QPushButton * validateButton;
    QPushButton * cancelButton;
    QGroupBox   * groupBox;
};

#endif // PLACEEDITDIALOG_H

