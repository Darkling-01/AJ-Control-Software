#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QPushButton>
#include <QAction>
#include <QFile>
#include <QTextEdit>
#include <QTabWidget>
#include <QString>
#include "serial.h"
#include "examples.h"
#include <QUndoStack>

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
 
   QString currentFile;      // Stores the file name or path of the saved file
   bool isFileSaved;	     // Tracks if the file has been saved before
   bool isModified;          // Tracks if file has had any changes
   
   QTabWidget *tabWidget;    // Declare QTabWidget as a variable memeber
   QTextEdit *textEdit;
   QTextEdit *openFileInTab(QString file);
   QTextEdit *getActiveTextEdit();   
   QUndoStack *undoStack;

   void createActions();
   void createMenus();
   
   QMenu *fileMenu;
   QMenu *editMenu;
   QMenu *serialMenu;
   QMenu *examplesMenu;
   QMenu *settingsMenu;
   QAction *newAct;
   QActionGroup *alignmentGroup;
   QAction *openAct;
   QAction *saveAct;
   QAction *saveAsAct;
   QAction *undoAct;
   QAction *redoAct;
   QAction *quitAct;
   QAction *findDeviceAct;
   QAction *serialPortAct;
   QAction *leftAlignAct;
   QAction *rightAlignAct;
   QAction *justifyAct;
   QAction *centerAct;
   
   // Examples
   QAction *ledBlinkAct;
   QAction *servoMotorAct;
   QAction *ledSwitchAct;


private slots:
   void newFile();
   void open();
   bool save();
   void saveAs();
   // void print();
   bool maybeSave();
   void leftAlign();
   void rightAlign();
   void center();
   void justify();

   // Handles examples
   void handleExamplesTriggered();  // one slot for all menu actions
   
   // Communication
   void findDevice()
   {
      Serial serial;
      serial.findDevice();
   }
   
   void serialPort()
   {
      Serial serial;
      serial.serialPort();
   }

};

#endif
