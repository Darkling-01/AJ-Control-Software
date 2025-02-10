#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QAction>


class MainWindow : public QMainWindow
{
   // Program that handles Qt's C++ extensions
   Q_OBJECT 

public:

   explicit MainWindow(Qwidget *parent = nullptr);
   ~MainWindow(); 

private:

   QPushButton *button;    // a button widget
   QLabel *label;	   // a label widget

   QAction *newAction      // Action for "new" item menu
   QAction *exitAction     // Action for "exit" item menu   

};


#endif
