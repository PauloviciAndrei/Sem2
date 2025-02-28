#include <iostream>
#include <QApplication>
#include <QPushButton>
#include "Window.h"
#include "Repository.h"
#include "Service.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Repository repo;
    Service service(repo);
    std::vector<Window*> windows;

    for (auto person : service.getProgrammers())
    {
        cout << "AICI";
        auto *window = new Window(service, person);// Pass Repository by reference
        windows.push_back(window);
        window->show();
    }
    return QApplication::exec();
}
