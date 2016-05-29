#-------------------------------------------------
#
# Project created by QtCreator 2013-07-25T23:35:13
#
#-------------------------------------------------

QT       += core gui xml xmlpatterns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR=build 		#Target file directory
OBJECTS_DIR=build/objs  #Intermediate object files directory
MOC_DIR=build/moc 	#Intermediate moc files directory
RCC_DIR=build/resources

TARGET = ptnet
TEMPLATE = app
RESOURCES = resources.qrc

CONFIG += link_pkgconfig
PKGCONFIG = libgvc
PKGCONFIG += libgvc

SOURCES += main.cpp\
        mainwindow.cpp \
    tabwidget.cpp \
    arcedgeselectionrectangle.cpp \
    sceneselectionrectangle.cpp \
    dockwidget.cpp \
    ptntab.cpp \
    ptnscene.cpp \
    transition.cpp \
    transitioneditdialog.cpp \
    place.cpp \
    placeeditdialog.cpp \
    commands.cpp \
    arceditdialog.cpp \
    arc.cpp \
    graphdock.cpp \
    graphnode.cpp \
    graphvisualizer.cpp \
    graphgenerator.cpp \
    graphedge.cpp \
    messagehandler.cpp \
    xmlparser.cpp \
    xmlwriter.cpp \
    undostack.cpp 


HEADERS  += mainwindow.h \
    tabwidget.h \
    arcedgeselectionrectangle.h \
    sceneselectionrectangle.h \
    xmlwriter.h \
    dockwidget.h \
    messagehandler.h \
    xmlparser.h \
    defs.h \
    ptntab.h \
    ptnscene.h \
    transition.h \
    transitioneditdialog.h \
    place.h \
    placeeditdialog.h \
    commands.h \
    arceditdialog.h \
    arc.h \
    graphdock.h \
    graphnode.h \
    graphedge.h \
    graphvisualizer.h \
    graphgenerator.h \
    undostack.h \
    boost_graph.h

