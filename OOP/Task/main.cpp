#include <iostream>
#include <QApplication>
#include <QPushButton>
#include "Window.h"
#include "Repository.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Repository repo;

    for (auto &person : repo.getUsers())
    {
        auto *window = new Window(repo, person);// Pass Repository by reference
        window->show();
    }
    return QApplication::exec();
}
