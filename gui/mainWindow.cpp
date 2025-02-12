// mainWindow.cpp will handle the creation and layout of UI components

#include "mainWindow.h"
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QMainWindow>


MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
{

   // Set window title and size
   setWindowTitle("AJ-Drone");
   setGeometry(150, 100, 1080, 900);
}



MainWindow::~MainWindow()
{
   // Destructor code (if needed, for exmaple, deleting objects)
   // For now, it's empty, but can be used to add cleanup code here later if needed

}


void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
   // Code Here

}

void MainWindow::newFile()
{
   // Code Here
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


