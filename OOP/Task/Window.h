#ifndef PROGRAMMERS_WINDOW_H
#define PROGRAMMERS_WINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include "Repository.h"
#include "Programmer.h"
#include "Observer.h"
#include <QCheckBox>

class Window : public QWidget, public Observer {
private:
    Repository& repo;  // Change to reference
    Programmer user;
    QListWidget *tasks;
    QPushButton *addTaskBt,  *removeTaskBt, *startTaskBt, *finishTaskBt;
    QLineEdit *descriptionInput;
    QCheckBox *showOnlyMyPatients;

public:
    Window(Repository& repo, Programmer &user, QWidget *parent = Q_NULLPTR);  // Pass Repository by reference
    ~Window() override = default;
    void update() const override;

public slots:
    void removeIssue();
    void addIssue();
    void resolveIssue();
    void updateResolveButton();
    void startTask();
    void finishTask();
};

#endif //PROGRAMMERS_WINDOW_H
