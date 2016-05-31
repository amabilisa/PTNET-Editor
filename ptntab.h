/*  PTNET Editor
**    A place/transition Net EDITOR
**
**   (C) 2013 Issam Abdallah  (iabdallah@yandex.com)
**
**    License: GPLv2  http://www.gnu.org/licenses/gpl-2.0.html
**
**    ptntab.h
**************************************************************/

#ifndef PTNTAB_H
#define PTNTAB_H

#include <QGraphicsView>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>

#include "undostack.h"
#include "graphvisualizer.h"

#include "placeeditdialog.h"
#include "transitioneditdialog.h"
#include "arceditdialog.h"

class PTNtab : public QWidget
{
    Q_OBJECT

public:

    explicit PTNtab(const QString &id, QWidget * parent = 0);
    PTNtab(const PTNET_ATTR &ptnet, const QString& file);
    ~PTNtab ();

    void setMode (int mode);
    int  getMode () const;
    void setCursorShape ();
    void removeItems ();
    void undo ();
    void redo ();
    bool canRedo ();
    bool canUndo ();
    void cleanUndostack();
    void scaleView (qreal val);
    qreal scaleValue ();
    void showErrorMessage (const QString &title, const QString &errorMsg);
    const QString& getFilename ();
    void setFilename (const QString& filenm);
    void exportNet (const QString &imagefile);
    bool isNetEmpty();
    bool isSaved ();
    PTNET_ATTR toXml() const;
    bool checkNet ();
    bool checkMarking();
    bool checkNodesConnections();
    void checkNodesNames();

    GraphVisualizer * createGraphVis ();
    GraphVisualizer * getGraphVis ();

    void placeDoubleClicked (QGraphicsItem* item);
    void transitionDoubleClicked (QGraphicsItem* item);
    void arcDoubleClicked (QGraphicsItem* item);

signals:

    void canRedoChange (bool canRedo);
    void canUndoChange (bool canUndo);
    void netChanged (bool changed);
    void errorMessage (const QString &msg);

public slots:

    void nodeInserted(const QPointF &itemPos, const QString &id);
    void nodesInserted (const QStringList& names);
    void itemDoubleClicked (QGraphicsItem* item);

private:

    // xml attributes
    QString id, name;

    PTNscene * scene;
    QGraphicsView * view;
    UndoStack  * undostack;
    GraphVisualizer * graphVis;
    QHBoxLayout * layout;

    int mode;
    qreal scaleVal;
    QStringList nodes_names;
    QString filename;

    PlaceEditDialog * placeEditDialog;
    TransitionEditDialog * transEditDialog;
    ArcEditDialog * arcEditDialog;

    void createTab ();
    void connect_sigs_slots ();
};

#endif // PTNTAB_H
