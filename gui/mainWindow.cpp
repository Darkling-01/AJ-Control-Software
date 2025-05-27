// mainWindow.cpp will handle the creation and layout of UI components

#include "mainWindow.h"
#include "examples.h"

#include <QApplication>
#include <QMenuBar>
#include <QAction>
#include <QMainWindow>
#include <QKeySequence>
#include <QIcon>
#include <QWidget>
#include <QFileDialog>
#include <QFile>
#include <QTextEdit>   // allows basic editing and essential for a code editor.
#include <QTextStream>
#include <QString>
#include <QMessageBox>
#include <QTabWidget>
#include <QLabel>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QDir>


MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
{
   // Set window title and size
   setWindowTitle("Micro Duck Software");
   setGeometry(100, 100, 1030, 690);  

   // Calling the file to add style (color)
   QFile file(":/qss/default.qss");
   file.open(QFile::ReadOnly);
   QString stylesheet = QLatin1String(file.readAll());

   qApp->setStyleSheet(stylesheet);
   undoStack = new QUndoStack(this);
   createActions();
   createMenus();
   
   // Create and initialize tabWidget
   tabWidget = new QTabWidget(this);
   // set the QTabWidget as central widget
   setCentralWidget(tabWidget);
   
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
   // use getSaveFileName(), if file does not exit, then a file will be created
   // opens the dialog and choose location
   QString filename = QFileDialog::getSaveFileName(this, tr("Save File"), 
			"~/Desktop/untitled.cpp");
     // Check if user selected a file.
     if(!filename.isEmpty())
     {
	// Create and write to the file.
	QFile file(filename);
	if(file.open(QIODevice::WriteOnly | QIODevice::Text))
	  {
	    QTextStream stream(&file);
	    stream << "// Your code goes here.\n";
            file.close();

	    // Mark the file as saved and store the filename
	    currentFile = filename;
	    isFileSaved = true;
	
	    // Open the file in the editor  
            openFileInTab(filename);
 	  }
	// Handle error opening file
	else
	 {
	   QMessageBox::critical(nullptr, "Error", "Could not open file.");
	 }
   
     }
}

QTextEdit* MainWindow::getActiveTextEdit()
{
   // Assuming tabWidget is the QTabWidget containing QTextEdit tabs
   QWidget *currentWidget = tabWidget->currentWidget();
   if (currentWidget) {
       return qobject_cast<QTextEdit*>(currentWidget);
   }
   return nullptr;  // Return nullptr if no valid QTextEdit found
}


// Tab is display when new or opening file.
QTextEdit* MainWindow::openFileInTab(const QString filePath)
{
   // QTextEdit widget to display the file's content
   textEdit = new QTextEdit(this);

   QFile fileObj(filePath);
   if(fileObj.open(QIODevice::ReadOnly | QIODevice::Text))
     {
	// in() used to read data from the stream
	QTextStream in(&fileObj);
	QString fileContent = in.readAll();
	fileObj.close();

	textEdit->setPlainText(fileContent);
     } 

   // Create a new tab and set the QTextEdit as its widget
   tabWidget->addTab(textEdit, QFileInfo(filePath).fileName());
   // returns the QTextEdit pointer
   return textEdit;
}

void MainWindow::open()
{
   QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath(),
			tr("*.cpp *.c"));
   // Check is filename is empty (or canceled by user)
   if(filename.isEmpty())
     {
	return;	   // Do nothing if no file is selected
     }

    currentFile = filename;	// Save the file path for later 

   // Create QFile instance
   QFile file(filename);
   if(file.open(QIODevice::ReadOnly | QIODevice::Text))
     {
	QTextStream in(&file);
	QString fileContent = in.readAll();
        isFileSaved = true;
	openFileInTab(file.fileName());
 
	file.seek(file.size());   // Move to the end of the file
        
        // Now, append new content to the file
        QTextStream out(&file);
        // out << "\nNew content appended.";  // Example of what you want to append
	file.close();
     }

}

void MainWindow::save()
{
   // Get the active QTextEdit (the one the user is editing)
   QTextEdit *textEdit = getActiveTextEdit();  // You need a way to access the active QTextEdit
   
   
   // If it's a new unsaved file, prompt user for a save location
   if(!isFileSaved)
     {
   	QString filename = QFileDialog::getSaveFileName(
		this, tr("Save File"), currentFile);
	// If the user chooses a valid filename, save the content
	if(!filename.isEmpty())
	  {
	     currentFile = filename;    // Store the new filename
	     isFileSaved = true;	// Mark the file saved

	     QFile file(currentFile);
	     if(file.open(QIODevice::WriteOnly | QIODevice::Text))
	       {
                 // isModified = true;
	          QTextStream out(&file);
		  out << textEdit->toPlainText();   // Save the content of the editor
		  file.close();
	       }
	  }
    }

   else
   {
      // If the file is already save, just save it directly
      QFile file(currentFile);
      if(file.open(QIODevice::WriteOnly | QIODevice::Text))
      {
         QTextStream out(&file);
         out << textEdit->toPlainText();    // Save the content to the editor
         file.close();
      }
	else {
            qDebug() << "Failed to open file for saving! Check permissions or file path.";
        }
   }
}

void MainWindow::saveAs()
{  
   QTextEdit *textEdit = getActiveTextEdit();

   // open a dialog to new save location
   QString filename = QFileDialog::getSaveFileName(this, tr("save as"), currentFile);
   currentFile = filename;
   
   QFile file(currentFile);
   if(file.open(QIODevice::WriteOnly | QIODevice::Text))
      {
         QTextStream out(&file);
         out << textEdit -> toPlainText();
         file.close();
      }

   else
      {
          QMessageBox::critical(nullptr, "Error", "Could not give new file name.");
      }

}


// Examples Tab
void MainWindow::handleExamplesTriggered()
{

   // 
   QAction* action = qobject_cast<QAction*>(sender());

   if(!action) return;

   QString exampleName = action->data().toString();   // From QAction
   QString fileName = exampleName + ".cpp";

   

   Examples examples;
   QString code;

   if(exampleName == "led_Blink") 
     code = examples.led_Blink();
   else if(exampleName == "servo_motor")
     code = examples.servo_motor();
   else if(exampleName == "led_switch")
     code = examples.led_switch();
   else
     code = "//Unknown Example";


   QString filePath = QDir::homePath() + "/Desktop/" + fileName;
   QFile file(filePath);
   if(file.open(QIODevice::WriteOnly | QIODevice::Text))
   {
      QTextStream stream(&file);
      stream << code;
      file.close();

      openFileInTab(filePath);
   }
}

void MainWindow::leftAlign()
{
   // code here

}

void MainWindow::rightAlign()
{
   // Code here
}

void MainWindow::center()
{
   // Code here
}

void MainWindow::justify()
{
   // Code here
}

void MainWindow::createActions()
{
   // &New is used to displayed for the action, and '&' character is defining
   // keyboard shortcut (Alt + N)

   // File menu
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

   saveAsAct = new QAction(QIcon::fromTheme("document-save-as"), tr("&SaveAs"), this);
   saveAsAct->setShortcuts(QKeySequence::SaveAs);
   saveAsAct->setStatusTip(tr("Saving file as"));
   connect(saveAsAct, &QAction::triggered, this, &MainWindow::saveAs);

   // Edit menu
   redoAct = new QAction(QIcon::fromTheme("document-redo"), tr("&Redo") , this);
   redoAct->setShortcuts(QKeySequence::Redo);
   redoAct->setStatusTip(tr("Redo"));
   connect(redoAct, &QAction::triggered, undoStack, &QUndoStack::redo);

   undoAct = new QAction(QIcon::fromTheme("document-undo"), tr("&Undo"), this);
   undoAct->setShortcuts(QKeySequence::Undo);
   undoAct->setStatusTip("Undo text.");
   connect(undoAct, &QAction::triggered, undoStack, &QUndoStack::undo);
   
   quitAct = new QAction(QIcon::fromTheme("document-exit"), tr("&Exit"), this);
   quitAct->setShortcuts(QKeySequence::Quit);
   quitAct->setStatusTip("Exit");
   connect(quitAct, &QAction::triggered, this, &QWidget::close);

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

   // Example menu
   ledBlinkAct = new QAction(tr("Blink"), this);
   ledBlinkAct->setStatusTip("Blink");
   ledBlinkAct->setData("led_Blink");
   connect(ledBlinkAct, &QAction::triggered, this, &MainWindow::handleExamplesTriggered);

   servoMotorAct = new QAction(tr("Servo Motor"), this);
   servoMotorAct->setStatusTip("Servo Motor");
   servoMotorAct->setData("servo_motor");
   connect(servoMotorAct, &QAction::triggered, this, &MainWindow::handleExamplesTriggered);

   ledSwitchAct = new QAction(tr("Led Switch"), this);
   ledSwitchAct->setStatusTip("Led Switch");
   ledSwitchAct->setData("led_switch");
   connect(ledSwitchAct, &QAction::triggered, this, &MainWindow::handleExamplesTriggered);

   // Serial menu
   findDeviceAct = new QAction(tr("Find Device"), this);
   connect(findDeviceAct, &QAction::triggered, this, &MainWindow::findDevice);

   serialPortAct = new QAction(tr("Serial Port"), this);
   connect(serialPortAct, &QAction::triggered, this, &MainWindow::serialPort);

   // Setting menu
   
}

void MainWindow::createMenus()
{
   fileMenu = menuBar()->addMenu(tr("&File"));
   fileMenu->addAction(newAct);
   fileMenu->addAction(openAct);
   fileMenu->addAction(saveAct);
   fileMenu->addAction(saveAsAct);
   fileMenu->addAction(quitAct);

   editMenu = menuBar()->addMenu(tr("&Edit"));
   editMenu->addAction(redoAct);
   editMenu->addAction(undoAct);

   serialMenu = menuBar()->addMenu(tr("&Serial"));
   serialMenu->addAction(findDeviceAct);
   serialMenu->addAction(serialPortAct);

   examplesMenu = menuBar()->addMenu("&Examples");
   examplesMenu->addAction(ledBlinkAct);
   examplesMenu->addAction(servoMotorAct);
   examplesMenu->addAction(ledSwitchAct);

   settingsMenu = menuBar()->addMenu("&Settings");
}
