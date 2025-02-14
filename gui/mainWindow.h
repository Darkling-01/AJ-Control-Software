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

protected:
#ifndef QT_NO_CONTEXTMENU
   void contextMenuEvent(QContextMenuEvent *event) override;
#endif  // QT_NO_CONTEXTMENU

private:
   QPushButton *button;    // a button widget
   QLabel *label;	   // a label widget

   QAction *newAction;      // Action for "new" item menu
   QAction *exitAction;     // Action for "exit" item menu   

   void createActions();
   void createMenu();

   QMenu *fileMenu;
   QMenu *editMenu;
   QMenu *serialMenu;
   QMenu *exmaples;
   QMenu *settings;
   QAction *newAct;
   QActionGroup *alignmentGroup;
   QAction *openAct;
   QAction *saveAct;
   QAction *undoAct;
   QAction *redoAct;

private slots:
   void newFile();
   void open();
   void save();
   // void print();
   void undo();
   void redo();

};

#endif
