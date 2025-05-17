#include <QApplication>
#include "mainWindow.h"

int main(int argc, char *argv[]){

   // Create a Qt application instance
   QApplication app(argc, argv);

   // Create the MainWindow instance
   MainWindow window;

   // Show the main window
   window.show();

   // Execute the application (enter the event loop)
   return app.exec();
}


