/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    graphdock.h
**************************************************************/

#ifndef GRAPHDOCK_H
#define GRAPHDOCK_H

#include <QDockWidget>
#include <QGraphicsView>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
//#include <QComboBox>
//#include <QFormLayout>

#include "graphvisualizer.h"

class GraphDock : public QDockWidget
{
    Q_OBJECT

 public:
    explicit GraphDock(QWidget * parent = 0);
    ~GraphDock();

    void setGraph (GraphVisualizer * graphScene);

 public slots:

    void zoom (int val);

 private:

    QWidget * widget;
    QGraphicsView * view;
    //QFormLayout * flayout;
    QHBoxLayout * hlayout;
    QVBoxLayout * vlayout;
    QSlider * slider;
    //QComboBox * comboBox;
};

#endif // GRAPHDOCK_H
