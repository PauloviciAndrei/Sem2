#ifndef PROGRAMMERS_WINDOW_H
#define PROGRAMMERS_WINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include "Repository.h"
#include "Programmer.h"
#include "Observer.h"
#include "Service.h"
#include <QCheckBox>

class Window : public QWidget, public Observer {
private:
    Service& service;
    Programmer user;
    QListWidget *tasks;
    QPushButton *addTaskBt,  *removeTaskBt, *startTaskBt, *finishTaskBt;
    QLineEdit *descriptionInput;
    QCheckBox *showOnlyMyTasks;

public:
    Window(Service& service, const Programmer &user, QWidget *parent = Q_NULLPTR);

    ~Window() override = default;
    void update() const override;

public slots:
    void removeTask();
    void addTask();
    void startTask();
    void finishTask();
    void updateTasksList();
};

#endif //PROGRAMMERS_WINDOW_H
