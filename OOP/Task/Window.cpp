#include "Window.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QCheckBox>
#include <iostream>

Window::Window(Repository& repo, Programmer &user, QWidget *parent) :
        repo{repo}, user{user}, QWidget(parent) {  // Pass Repository by reference
    repo.registerObserver(this);
    this->setWindowTitle(QString::fromStdString(this->user.getName() + " " + to_string(this->user.getId())));

    auto *layout = new QVBoxLayout(this);
    tasks = new QListWidget(this);
    for (const auto &issue : repo.getTasks())
        tasks->addItem(QString::fromStdString(issue.toString()));


    layout->addWidget(tasks);
    this->setLayout(layout);

    removeTaskBt = new QPushButton("Remove task", this);
    layout->addWidget(removeTaskBt);

    QObject::connect(removeTaskBt, &QPushButton::clicked, this, &Window::removeIssue);

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
    QObject::connect(addTaskBt, &QPushButton::clicked, this, &Window::addIssue);

    showOnlyMyPatients = new QCheckBox("Show only my patients", this);
    layout->addWidget(showOnlyMyPatients);

    //layout->addWidget(resolveIssueBt);
    //QObject::connect(issues, &QListWidget::clicked, this, &Window::updateResolveButton);
    //QObject::connect(resolveIssueBt, &QPushButton::clicked, this, &Window::resolveIssue);

}

void Window::update() const {
    tasks->clear();
    for (const auto &issue : repo.getTasks())
        tasks->addItem(QString::fromStdString(issue.toString()));
}

void Window::removeIssue() {
    int row = tasks->currentRow();
    repo.removeTask(row);
}

void Window::addIssue() {
    string description = descriptionInput->text().toStdString();
    int status = 0;
    int id = this->user.getId();

    try {
        repo.addTask(description, status, id);
    }
    catch (exception &e) {
        QMessageBox::critical((QWidget*) this, "Error", e.what());
    }
}

void Window::startTask()
{
    int row = tasks->currentRow();
    if (repo.getTasks()[row].getStatus() != 0)
        QMessageBox::critical((QWidget *)this, "Error", "Can't do that!.");
    else
        repo.startTask(row, user.getId());
}

void Window::finishTask()
{
    int row = tasks->currentRow();
    if (repo.getTasks()[row].getStatus() != 1 && repo.getTasks()[row].getId() != this->user.getId())
        QMessageBox::critical((QWidget *)this, "Error", "Can't do that!.");
    else
        repo.finishTask(row);
}



