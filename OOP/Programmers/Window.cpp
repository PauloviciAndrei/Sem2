#include "Window.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <iostream>

Window::Window(Repository& repo, User &user, QWidget *parent) :
        repo{repo}, user{user}, QWidget(parent) {  // Pass Repository by reference
    repo.registerObserver(this);
    this->setWindowTitle(QString::fromStdString(this->user.getName() + " " + this->user.getType()));

    auto *layout = new QVBoxLayout(this);
    issues = new QListWidget(this);
    for (const auto &issue : repo.getIssues())
        issues->addItem(QString::fromStdString(issue.toString()));

    layout->addWidget(issues);
    this->setLayout(layout);

    removeIssueBt = new QPushButton("Remove issue", this);
    layout->addWidget(removeIssueBt);

    QObject::connect(removeIssueBt, &QPushButton::clicked, this, &Window::removeIssue);

    if (user.getType() == "Tester") {
        addIssueBt = new QPushButton("Add issue", this);
        descriptionInput = new QLineEdit();
        layout->addWidget(addIssueBt);
        layout->addWidget(this->descriptionInput);
        QObject::connect(addIssueBt, &QPushButton::clicked, this, &Window::addIssue);
    }
    else if (user.getType() == "Programmer") {
        resolveIssueBt = new QPushButton("Resolve issue", this);
        resolveIssueBt->setEnabled(false);

        layout->addWidget(resolveIssueBt);
        QObject::connect(issues, &QListWidget::clicked, this, &Window::updateResolveButton);
        QObject::connect(resolveIssueBt, &QPushButton::clicked, this, &Window::resolveIssue);
    }
}

void Window::update() const {
    issues->clear();
    for (const auto &issue : repo.getIssues())
        issues->addItem(QString::fromStdString(issue.toString()));
}

void Window::removeIssue() {
    int row = issues->currentRow();
    if (repo.getIssues()[row].getStatus())
        QMessageBox::critical((QWidget *)this, "Error", "Invalid Selection.");
    else
        repo.removeIssue(row);
}

void Window::addIssue() {
    string description = descriptionInput->text().toStdString();
    bool status = true;
    string name = this->user.getName();
    string solver = "";

    try {
        repo.addIssue(description, status, name, solver);
    }
    catch (exception &e) {
        QMessageBox::critical((QWidget*) this, "Error", e.what());
    }
}

void Window::resolveIssue() {
    int row = issues->currentRow();
    string solver = user.getName();
    repo.resolveIssue(row, solver);
    resolveIssueBt->setEnabled(false);
}

void Window::updateResolveButton()
{
    if (repo.getIssues()[issues->currentRow()].getStatus())
        resolveIssueBt->setEnabled(true);
    else
        resolveIssueBt->setEnabled(false);
}
