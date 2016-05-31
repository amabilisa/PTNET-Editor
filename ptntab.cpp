/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    ptntab.cpp
**************************************************************/

#include "ptntab.h"
#include "xmlwriter.h"

PTNtab::PTNtab(const QString &id, QWidget * parent) 
	: QWidget(parent)
{
    this->id = id;
    name = id;
    createTab ();
}

PTNtab::PTNtab(const PTNET_ATTR &ptnet, const QString& file)
{
    id = ptnet.id;
    name = ptnet.name;
    filename = file;
    createTab ();
    // xml
    scene->from_Xml (ptnet.pages);
    view->centerOn(scene->itemsBoundingRect().center());
}

void PTNtab::createTab ()
{
    mode = normalMode;
    setWindowTitle(name);
    scaleVal = 100;

    view = new QGraphicsView(this);
    view->setAlignment(Qt::AlignCenter);
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setRenderHints(QPainter::SmoothPixmapTransform);
    layout = new QHBoxLayout;
    layout->addWidget(view);
    setLayout(layout);
    scene = new PTNscene(this);
    view->setScene (scene);
    undostack = new UndoStack(this);
    graphVis = new GraphVisualizer;

    arcEditDialog = new ArcEditDialog(this);
    placeEditDialog = new PlaceEditDialog(this);
    transEditDialog = new TransitionEditDialog(this);

    connect_sigs_slots ();
}

void PTNtab::nodesInserted (const QStringList& names)
{
    nodes_names << names;
}

void PTNtab::undo ()
{
    undostack->undo();
}

void PTNtab::redo ()
{
    undostack->redo();
}

bool PTNtab::canRedo ()
{
    return undostack->canRedo();
}

bool PTNtab::canUndo ()
{
    return undostack->canUndo();
}

/* add new node to the current scene */
void PTNtab::nodeInserted(const QPointF &itemPos,
            const QString &id)
{
    if(mode == addPlaceMode)
    {
       undostack->push(new AddPlaceCommand(itemPos, id, scene));
       nodes_names << id;
    }else
     {
       undostack->push(new AddTransitionCommand(itemPos, id, scene));
       nodes_names << id;
     }
}

/* set Mode */
void PTNtab::setMode (int mode)
{
    scene->setMode(mode);
    this->mode = mode;
    setCursorShape ();
}

/* get mode */
int PTNtab::getMode () const
{
    return mode;
}

/* change the cursor shape */
void PTNtab::setCursorShape ()
{
    QCursor cursor;

    if ((mode == normalMode)||(mode == animationMode))
        cursor.setShape(Qt::ArrowCursor);
    else
        cursor.setShape(Qt::CrossCursor);

    view->setCursor(cursor);
}

/* is scene empty */
bool PTNtab::isNetEmpty()
{
  return scene->items().isEmpty();
}

bool PTNtab::isSaved ()
{
    return undostack->isClean();
}

void PTNtab::scaleView (qreal val)
{
    view->resetMatrix();
    view->scale(val/100, val/100);
    scene->update(scene->sceneRect());
    scaleVal = val;
}

qreal PTNtab::scaleValue ()
{
    return scaleVal;
}

/* call this function when the delete Toolbar button is trigered */
void PTNtab::removeItems ()
{
    scene->removeItems ();
}

const QString& PTNtab::getFilename ()
{
    return filename;
}

void PTNtab::setFilename (const QString& filenm)
{
    filename = filenm;
    QFileInfo fileInfo(filename);
    name = fileInfo.baseName();
}

void PTNtab::cleanUndostack()
{
  undostack->setClean();
      // here clean all invisible items
}

PTNET_ATTR PTNtab::toXml() const
{
    PTNET_ATTR net;
    net.id = id;
    net.name = name;
    PAGE_ATTR page;
    page.id = "page0";
    page.name = name;

    foreach(QGraphicsItem * item, scene->items())
    {
        if(item->type() == Place::Type)
        {
            page.placeNodes << qgraphicsitem_cast<Place*>(item)->toXml();
            continue;
        }
        if(item->type() == Transition::Type)
        {
            page.transitionNodes << qgraphicsitem_cast<Transition*>(item)->toXml();
            continue;
        }
        if(item->type() == Arc::Type)
        {
            page.arcs << qgraphicsitem_cast<Arc*>(item)->toXml();
            continue;
        }
    }

    net.pages << page;
    return net;
}

void PTNtab::exportNet (const QString &imagefile)
{
    QRectF rect = scene->itemsBoundingRect();
    QImage image(QSize(rect.width(), rect.height()), QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::white);
    QPainter painter;

    painter.begin(&image);
    scene->render(&painter , QRectF(), rect.adjusted(-10,-10,10,10).normalized(),
              Qt::IgnoreAspectRatio);
    painter.end();

    image.save(imagefile);
}

bool PTNtab::checkNet ()
{
    bool ok = false;

        emit errorMessage ("  <strong style=\"color:blue;\">Starting " \
                           " animation of P/T Net: "+name+" ... </strong>");

    ok = checkMarking();

    if(!ok)
        emit errorMessage ("  <span style=\"color:red;\">Error:"\
                           "No firable transition found ...</span>");

    ok = checkNodesConnections();
    
    checkNodesNames();

    return ok;
}

//![0] check marking before animation
bool PTNtab::checkMarking()
{
  bool ok = false;

    foreach(QGraphicsItem * item ,scene->items())
    {
        if(item->type() == Transition::Type)
        {
            if(qgraphicsitem_cast<Transition*>(item)->isFirable ())
            {
                ok = true;
                break;
            }
        }
    }

  return ok;
}

//![1] check nodes connections!
bool PTNtab::checkNodesConnections()
{
    bool ok = true;

    foreach(QGraphicsItem * item , scene->items())
    {
        if(item->type() == Place::Type)
        {
            Place * place = qgraphicsitem_cast<Place*>(item);
            if(!place->hasRelations())
            {
                emit errorMessage ("  <span style=\"color:red;\">Error: Place "+
                                 place->getName()+" is not connected ...</span>");
                                ok = false;
            }
        }
        if(item->type() == Transition::Type)
        {
            Transition * transition = qgraphicsitem_cast<Transition*>(item);
            if(!transition->hasRelations())
            {
                emit errorMessage ("  <span style=\"color:red;\">Error: Transition "+
                              transition->getName()+" is not connected ...</span>");
                ok = false;
            }
        }
    }

  return ok;
}

//![2] check nodes names uniqueness!
void PTNtab::checkNodesNames()
{

    QStringList plnames;
    QStringList trnames;
    
    foreach(QGraphicsItem * item , scene->items())
    {
        if(item->type() == Place::Type)
            plnames << (qgraphicsitem_cast<Place*>(item))->getName();

        if(item->type() == Transition::Type)
            trnames << (qgraphicsitem_cast<Transition*>(item))->getName();
    }
    
    if(plnames.removeDuplicates())
                        emit errorMessage ("  <span style=\"color:orange;\">Warning: Places names are not unique !</span>");
  

    if(trnames.removeDuplicates())
                        emit errorMessage ("  <span style=\"color:orange;\">Warning: Transitions names are not unique !</span>");

}

/* error message */
void PTNtab::showErrorMessage (const QString &title, const QString &errorMsg)
{
    QMessageBox::critical(this, title, errorMsg);
}

GraphVisualizer * PTNtab::createGraphVis ()
{
    Marking initial_marking = scene->getInitialMarking ();
    QMap<QString, int> places_capacities = scene->getPlacesCapacities ();
    QList<TRANS_RELATION> pt_relations = scene->getRelations ();
    QMap<QString, QString> places_names = scene->getPlacesNames ();

    graphVis->visualize_graph(initial_marking, places_capacities, places_names, pt_relations);

    return graphVis;
}

GraphVisualizer * PTNtab::getGraphVis ()
{
    return graphVis;
}

void PTNtab::connect_sigs_slots ()
{
    connect (scene, SIGNAL (nodeInserted(const QPointF&, const QString&)),
             this,  SLOT (nodeInserted(const QPointF&, const QString&)));

    connect (scene, SIGNAL (arcInserted(QGraphicsItem *, QGraphicsItem *,
                    const QPainterPath &, const QString &, PTNscene *, int)),
             undostack,  SLOT (arcInserted(QGraphicsItem *, QGraphicsItem *,
                    const QPainterPath &, const QString &, PTNscene *, int)));

    connect (scene, SIGNAL (itemMoved(QGraphicsItem*, QPointF)),
             undostack,  SLOT (itemMoved(QGraphicsItem*, QPointF)));

    connect (scene, SIGNAL (nodeRemoved(QGraphicsItem*, PTNscene*)),
             undostack, SLOT (nodeRemoved(QGraphicsItem*, PTNscene*)));

    connect (scene, SIGNAL (arcRemoved(QGraphicsItem*, PTNscene*)),
             undostack,  SLOT (arcRemoved(QGraphicsItem*, PTNscene*)));

    connect (scene, SIGNAL (nodesInserted(const QStringList&)),
             this,  SLOT (nodesInserted(const QStringList&)));

    connect (undostack, SIGNAL(canRedoChanged (bool)),
                  this, SIGNAL(canRedoChange (bool)));
    connect (undostack, SIGNAL(canUndoChanged (bool)),
                  this, SIGNAL(canUndoChange (bool)));
    connect (undostack, SIGNAL(cleanChanged (bool)),
                  this, SIGNAL(netChanged (bool)));

    connect (scene, SIGNAL(itemDoubleClicked (QGraphicsItem*)),
                  this, SLOT(itemDoubleClicked (QGraphicsItem*)));
}

void PTNtab::itemDoubleClicked (QGraphicsItem* item)
{
    if(item->type() == Place::Type)
	placeDoubleClicked (item);
    if(item->type() == Transition::Type)
	transitionDoubleClicked (item);
    if(item->type() == Arc::Type)
	arcDoubleClicked (item);

    item = 0;
}

void PTNtab::placeDoubleClicked (QGraphicsItem* item)
{
    Place * place = qgraphicsitem_cast<Place*>(item);
    QString old_name = place->getName();
    placeEditDialog->inputLabel->setText(old_name);
    placeEditDialog->inputTokens->setValue(place->getTokens());

    int c = place->getCapacity();
    if(c == omega)
	c=0;

    placeEditDialog->inputCapacity->setValue(c);
    placeEditDialog->exec();

    if(placeEditDialog->result() == QDialog::Rejected)
	return;

    QString new_name = placeEditDialog->inputLabel->text();
    place->setTokens(placeEditDialog->inputTokens->value());
    place->setCapacity(placeEditDialog->inputCapacity->value());

    int index = nodes_names.indexOf (old_name);
    
    if (new_name != old_name)
    {
      if(!nodes_names.contains(new_name))
      {
        nodes_names.replace (index, new_name); 
	place->setName(new_name);      
      }
      else
      {
        QMessageBox::StandardButton button = QMessageBox::warning(this, "Not a unique name", "The place name <strong>"+
                         new_name+"</strong> is already being used. Use it anyway ?", QMessageBox::Yes|QMessageBox::No, QMessageBox::No);
        
        if(button == QMessageBox::Yes)
        {
          nodes_names.replace (index, new_name); 
	  place->setName(new_name);            
        }
      }
    }
   
    if(!placeEditDialog->chckBox->isChecked ())
	place->setLabel_1();
    else
	place->setLabel_2();
}

void PTNtab::transitionDoubleClicked (QGraphicsItem* item)
{
    Transition * trans = qgraphicsitem_cast<Transition*>(item);
    QString old_name = trans->getName();
    transEditDialog->inputLabel->setText(old_name);
    transEditDialog->slider->setValue(trans->getRotation());
    transEditDialog->exec();

    if(transEditDialog->result() == QDialog::Rejected)
	return;

    QString new_name = transEditDialog->inputLabel->text();
    trans->setRotation (transEditDialog->slider->value());
    
    int index = nodes_names.indexOf (old_name);
            
    if (new_name != old_name)
    {
      if(!nodes_names.contains(new_name))
      {
        nodes_names.replace (index, new_name); 
	trans->setName(new_name);      
      }
      else
      {
        QMessageBox::StandardButton button = QMessageBox::warning(this, "Not a unique name", "The transition name <strong>"+
                         new_name+"</strong> is already being used. Use it anyway ?", QMessageBox::Yes|QMessageBox::No, QMessageBox::No);
        
        if(button == QMessageBox::Yes)
        {
          nodes_names.replace (index, new_name); 
	  trans->setName(new_name);            
        }
      }
    }
}

void PTNtab::arcDoubleClicked (QGraphicsItem* item)
{
    Arc* arc = qgraphicsitem_cast<Arc*>(item);
    /* set the SpinBox with the arc's current weight */	
    arcEditDialog->inputWeight->setValue(arc->getWeight());
    arcEditDialog->exec();
    /* update the arc's weight */
    if(arcEditDialog->result() == QDialog::Accepted)
	arc->setWeight(arcEditDialog->inputWeight->value());
}

PTNtab::~PTNtab ()
{
    delete placeEditDialog;
    delete transEditDialog;
    delete arcEditDialog;
    delete scene;
    delete graphVis;
    delete view;
    delete layout;
    delete undostack;
}
