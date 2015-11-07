/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    graphdock.cpp
**************************************************************/

#include "graphdock.h"

GraphDock::GraphDock(QWidget * parent)
    :QDockWidget(parent)
{
    view = new QGraphicsView;
    slider = new QSlider(Qt::Horizontal);
    slider->setMaximum(150);
    slider->setFixedWidth(100);
    slider->setRange(50, 150);
    slider->setSliderPosition(100);

    connect(slider, SIGNAL(valueChanged(int)),
            this, SLOT(zoom(int)));

    /*comboBox = new QComboBox;
    QStringList text;
    text << "dot" << "neato" << "fdp" << "sfdp";
    comboBox->addItems(text);*/

    //flayout = new QFormLayout;
    //flayout->addRow("Graph Layout: ", comboBox);
    hlayout = new QHBoxLayout;
    //hlayout->setStretch(0,100);
    //hlayout->addLayout(flayout);
    hlayout->addWidget(slider);
    vlayout = new QVBoxLayout;
    vlayout->addLayout(hlayout);
    vlayout->addWidget(view);
    widget = new QWidget;
    widget->setLayout(vlayout);
    setWidget(widget);
}

void GraphDock::zoom (int val)
{
    qreal v = val;
    view->resetMatrix();
    view->scale(v/100, v/100);
}

void GraphDock::setGraph (GraphVisualizer * graphScene)
{
    view->setScene(graphScene);
    view->centerOn(graphScene->itemsBoundingRect().center());
    show();
}

GraphDock::~GraphDock()
{
    delete slider;
    //delete comboBox;
    delete view;
    delete widget;
}
