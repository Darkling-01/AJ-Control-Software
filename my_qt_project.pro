# Define project
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# Define target name
TARGET = my_qt_project
TEMPLATE = app

# Add source files
SOURCES += src/main.cpp \ 
           gui/mainWindow.cpp \
 	   src/examples/examples.cpp \
	   src/networking/serial.cpp

# Add header files
HEADERS += gui/mainWindow.h \
	   src/examples/examples.h \
	   src/networking/serial.h


# Add the Qtwidgets module for GUI-related features
QT += widgets

# Inlcude directories (if we have any custom includes)
INCLUDEPATH += $$PWD/gui \
	       $$PWD/src/examples \
	       $$PWD/src/networking

# If we need to link libraries or include other settings, add item here


# Additional settings for debugging or release mode


# Install path (optional)

# We can also add some resources files (e.g. .qrc) if required
RESOURCES += gui/stylesheet.qrc

