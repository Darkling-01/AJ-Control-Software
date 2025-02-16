// mainWindow.cpp will handle the creation and layout of UI components

#include "mainWindow.h"
#include <QMenuBar>
#include <QAction>
#include <QMainWindow>
#include <QKeySequence>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
{
   // Set window title and size
   setWindowTitle("AJ-Drone");
   setGeometry(150, 100, 1080, 900);   

   createActions();
   createMenus();
}

MainWindow::~MainWindow()
{
   // Destructor code (if needed, for exmaple, deleting objects)
   // For now, it's empty, but can be used to add cleanup code here later if needed

}

// Events are sent to widgets when action is associated
#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
   

}
#endif  // QT_NO_CONTEXTMENU


void MainWindow::newFile()
{
    
}

void MainWindow::open()
{
   // Code Here
}

void MainWindow::save()
{
   // Code Here
}

void MainWindow::redo()
{
   // Code Here
}

void MainWindow::undo()
{
   // Code Here
}

void MainWindow::leftAlign()
{
   // code here

}

void MainWindow::rightAlign()
{

}

void MainWindow::center()
{

}

void MainWindow::justify()
{

}

void MainWindow::createActions()
{
   // &New is used to displayed for the action, and '&' character is defining
   // keyboard shortcut (Alt + N)
   newAct = new QAction(QIcon::fromTheme("document-new"), tr("&New"), this);
   newAct->setShortcuts(QKeySequence::New);
   newAct->setStatusTip(tr("Create a new file."));
   connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

   openAct = new QAction(QIcon::fromTheme("document-open"), tr("&Open"), this);
   openAct->setShortcuts(QKeySequence::Open);
   openAct->setStatusTip(tr("Open a new file."));
   connect(openAct, &QAction::triggered, this, &MainWindow::open);

   saveAct = new QAction(QIcon::fromTheme("document-save"), tr("&Save"), this); 
   saveAct->setShortcuts(QKeySequence::Save);
   saveAct->setStatusTip(tr("Save file."));
   connect(saveAct, &QAction::triggered, this, &MainWindow::save);

   redoAct = new QAction(QIcon::fromTheme("document-redo"), tr("&Redo") , this);
   redoAct->setShortcuts(QKeySequence::Redo);
   redoAct->setStatusTip(tr("Redo"));
   connect(redoAct, &QAction::triggered, this, &MainWindow::redo);

   leftAlignAct = new QAction(tr("&Left Align"),this);
   leftAlignAct->setCheckable(true);
   leftAlignAct->setStatusTip("Left Align of text.");
   connect(leftAlignAct, &QAction::triggered, this, &MainWindow::leftAlign);

   rightAlignAct = new QAction(tr("&Right Align"), this);
   rightAlignAct->setCheckable(true);
   rightAlignAct->setStatusTip("Right Align of text.");
   connect(rightAlignAct, &QAction::triggered, this, &MainWindow::rightAlign);

   centerAct = new QAction(tr("&Center"), this);
   centerAct->setCheckable(true);
   centerAct->setStatusTip("Center the text.");
   connect(centerAct, &QAction::triggered, this, &MainWindow::center);

   justifyAct = new QAction(tr("&Justify"), this);
   justifyAct->setCheckable(true);
   justifyAct->setStatusTip("Justify the text");
   connect(justifyAct, &QAction::triggered, this, &MainWindow::justify);

   

   alignmentGroup = new QActionGroup(this);
   alignmentGroup->addAction(leftAlignAct);
   alignmentGroup->addAction(rightAlignAct);
   alignmentGroup->addAction(centerAct);
   alignmentGroup->addAction(justifyAct);
   leftAlignAct->setChecked(true);
}

void MainWindow::createMenus()
{
   fileMenu = menuBar()->addMenu(tr("&File"));
   fileMenu->addAction(newAct);
   fileMenu->addAction(openAct);
   fileMenu->addAction(saveAct);

   editMenu = menuBar()->addMenu(tr("&Edit"));
   editMenu->addAction(redoAct);
}


