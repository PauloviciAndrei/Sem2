#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include "ui.h"
#include <QApplication>
#include <QPushButton>
#include "gui.h"

void Initialize(Repository& repo);

int main(int argc, char* argv[])
{

        Repository repo{};
        Controller ctrl{};
        UI ui{ ctrl };
        ui.runApplication();
       // system("pause");
    /*
        QApplication a(argc, argv);
        Repository repo{};
        Controller ctrl{};
        gui GUI;
        GUI.show();
        return QApplication::exec();
    */
}
