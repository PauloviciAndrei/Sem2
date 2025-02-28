#include "Window.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QCheckBox>
#include <iostream>

Window::Window(Service& service,const Programmer &user, QWidget *parent) :
        service{service}, user{user}, QWidget(parent) {
    service.registerObserver(this);
    this->setWindowTitle(QString::fromStdString(this->user.getName() + " " + to_string(this->user.getId())));

    auto *layout = new QVBoxLayout(this);
    tasks = new QListWidget(this);
    layout->addWidget(tasks);
    this->setLayout(layout);

    removeTaskBt = new QPushButton("Remove task", this);
    layout->addWidget(removeTaskBt);
    QObject::connect(removeTaskBt, &QPushButton::clicked, this, &Window::removeTask);

    startTaskBt = new QPushButton("Start task", this);
    layout->addWidget(startTaskBt);
    QObject::connect(startTaskBt, &QPushButton::clicked, this, &Window::startTask);

    finishTaskBt = new QPushButton("Finish task", this);
    layout->addWidget(finishTaskBt);
    QObject::connect(finishTaskBt, &QPushButton::clicked, this, &Window::finishTask);

    addTaskBt = new QPushButton("Add task", this);
    descriptionInput = new QLineEdit();
    layout->addWidget(addTaskBt);
    layout->addWidget(this->descriptionInput);
    QObject::connect(addTaskBt, &QPushButton::clicked, this, &Window::addTask);

    showOnlyMyTasks = new QCheckBox("Show only my tasks", this);
    layout->addWidget(showOnlyMyTasks);
    QObject::connect(showOnlyMyTasks, &QCheckBox::stateChanged, this, &Window::updateTasksList);

    updateTasksList();
}

void Window::updateTasksList() {
    tasks->clear();
    bool filterMyTasks = showOnlyMyTasks->isChecked();

    for (const auto &task : service.getTasks()) {
        if (filterMyTasks && task.getId() != user.getId())
            continue;

        QString taskText = QString::fromStdString(task.toString() + " (" + service.getProgrammerNameById(task.getId()) + ")");
        QListWidgetItem* item = new QListWidgetItem(taskText, tasks);

        if (task.getId() == user.getId())
            item->setBackground(Qt::green);
    }
}

void Window::update() const {
    const_cast<Window*>(this)->updateTasksList();
}

void Window::removeTask() {
    int row = tasks->currentRow();
    if (row < 0) return;

    if(service.getTasks()[row].getStatus() != 2)
        QMessageBox::critical((QWidget *)this, "Error", "You can remove only closed tasks!");
    else
        service.removeTask(row);
}

void Window::addTask() {
    string description = descriptionInput->text().toStdString();
    int status = 0;
    int id = this->user.getId();

    try {
        service.addTask(description, status, id);
        updateTasksList();
    }
    catch (exception &e) {
        QMessageBox::critical((QWidget*) this, "Error", e.what());
    }
}

void Window::startTask() {
    int row = tasks->currentRow();
    if (row < 0) return;

    if (service.getTasks()[row].getStatus() != 0)
        QMessageBox::critical((QWidget *)this, "Error", "Can't do that!");
    else
        service.startTask(row, user.getId());

    updateTasksList();
}

void Window::finishTask() {
    int row = tasks->currentRow();
    if (row < 0) return;

    if (service.getTasks()[row].getStatus() != 1 || service.getTasks()[row].getId() != this->user.getId())
        QMessageBox::critical((QWidget *)this, "Error", "You can't finish a task that is not yours!");
    else
        service.finishTask(row);

    updateTasksList();
}
