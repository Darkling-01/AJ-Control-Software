#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QPushButton>
#include <QAction>
#include <QFile>
#include <QTextEdit>
#include <QTabWidget>


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
  // QPushButton *button;    // a button widget
  // QLabel *label;	   // a label widget

  // QAction *newAction;      // Action for "new" item menu
  //  QAction *exitAction;     // Action for "exit" item menu   

   QTabWidget *tabWidget;    // Declare QTabWidget as a variable memeber

   QTextEdit *openFileInTab(QString file);

   void createActions();
   void createMenus();

   QMenu *fileMenu;
   QMenu *editMenu;
   QMenu *serialMenu;
   QMenu *exmaples;
   QMenu *settings;
   QAction *newAct;
   QActionGroup *alignmentGroup;
   QAction *openAct;
   QAction *saveAct;
   QAction *saveAsAct;
   QAction *undoAct;
   QAction *redoAct;
   QAction *quitAct;
   QAction *leftAlignAct;
   QAction *rightAlignAct;
   QAction *justifyAct;
   QAction *centerAct;


private slots:
   void newFile();
   void open();
   void save();
   void saveAs();
   // void print();
   void undo();
   void redo();
   void leftAlign();
   void rightAlign();
   void center();
   void justify();
};

#endif
