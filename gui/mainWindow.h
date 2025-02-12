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
   explicit MainWindow(QWidget *parent = nullptr);
   ~MainWindow(); 

private:
   QPushButton *button;    // a button widget
   QLabel *label;	   // a label widget

   QAction *newAction;      // Action for "new" item menu
   QAction *exitAction;     // Action for "exit" item menu   

private slots:
   void newFile();
   void open();
   void save();
   // void print();
   void undo();
   void redo();

protected:
#ifndef QT_NO_CONTEXTMENU
   void contextMenuEvent(QContextMenuEvent *event) override;
#endif  // QT_NO_CONTEXTMENU

};

#endif
