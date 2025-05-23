#include "examples.h"
#include <iostream>
#include <QString>
#include <QTextStream>
#include <QFile>

QString Examples::led_Blink()
{
   QFile file("src/examples/scripts/on_blink.cpp");
   if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
     {
        return "Error: can't open file";
     }

   QTextStream in(&file);
   return in.readAll();
}

QString Examples::servo_motor()
{
   QFile file("src/examples/scripts/servo_motor.cpp");
   if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
     {
        return "Error: can't open file";
     }
   QTextStream in(&file);
   return in.readAll();

}

QString Examples::led_switch()
{
   QFile file("src/examples/scripts/led_switch.cpp");
   if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
     {
        return "Error: can't open file";
     }

   QTextStream in(&file);
   return in.readAll();
}


