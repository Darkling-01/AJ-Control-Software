// mainWindow.cpp will handle the creation and layout of UI components

#include "mainWindow.h"
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


MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
{
   // Set window title and size
   setWindowTitle("AJ-Drone");
   setGeometry(100, 100, 1030, 690);   

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
			"home/desktop/untitled.cpp");
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

// Tab is display when new or opening file.
QTextEdit* MainWindow::openFileInTab(QString file)
{
   // QTextEdit widget to display the file's content
   textEdit = new QTextEdit(this);

   QFile fileObj(file);
   if(fileObj.open(QIODevice::ReadOnly | QIODevice::Text))
     {
	// in() used to read data from the stream
	QTextStream in(&fileObj);
	QString fileContent = in.readAll();
	fileObj.close();

	textEdit->setPlainText(fileContent);
     } 

   // Create a new tab and set the QTextEdit as its widget
   tabWidget->addTab(textEdit, file);
   // returns the QTextEdit pointer
   return textEdit;
}

void MainWindow::open()
{
   // Code Here
}

void MainWindow::save()
{
   QTextEdit *textEdit = new QTextEdit(this);
   
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
	          QTextStream out(&file);
		  out << textEdit->toPlainText();   // Save the content of the editor
		  file.close();
	       }
	  }
    }

   else{
   // now save the content to the file{
   QFile file(currentFile);
   if(file.open(QIODevice::WriteOnly | QIODevice::Text))
     {
        QTextStream out(&file);
        out << textEdit->toPlainText();
        file.close();
     }
  }
}

void MainWindow::saveAs()
{
   
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

   saveAsAct = new QAction(QIcon::fromTheme("document-save-as"), tr("&SaveAs"), this);
   saveAsAct->setShortcuts(QKeySequence::SaveAs);
   saveAsAct->setStatusTip(tr("Saving file as"));
   connect(saveAsAct, &QAction::triggered, this, &MainWindow::saveAs);

   redoAct = new QAction(QIcon::fromTheme("document-redo"), tr("&Redo") , this);
   redoAct->setShortcuts(QKeySequence::Redo);
   redoAct->setStatusTip(tr("Redo"));
   connect(redoAct, &QAction::triggered, this, &MainWindow::redo);

   undoAct = new QAction(QIcon::fromTheme("document-undo"), tr("&Undo"), this);
   undoAct->setShortcuts(QKeySequence::Undo);
   undoAct->setStatusTip("Undo text.");
   connect(undoAct, &QAction::triggered, this, &MainWindow::undo);
   
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
}


