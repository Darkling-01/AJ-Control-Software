#include "examples.h"
#include <iostream>
#include <QString>
#include <QTextStream>
#include <QFile>

QString Examples::led_Blink()
{
   QFile file("src/examples/scripts/on_blink.txt");
   if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
     {
        return "Error: can't open file";
     }

   QTextStream in(&file);
   return in.readAll();
}

QString Examples::servo_motor()
{
    // code here
}

QString Examples::led_switch()
{
    // code here
}
