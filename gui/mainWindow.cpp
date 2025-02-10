// mainWindow.cpp will handle the creation and layout of UI components

#include <mainwindow.h>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QMainWindow>


MainWindow:MainWindow(QWidget *parent)
   : QMainWindow(parent)
{

   // Set window title and size
   setWindowTitle("AJ-Drone");
   setGeometry(100, 100, 500, 400);
   


}


