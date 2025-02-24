#ifndef PROGRAMMERS_WINDOW_H
#define PROGRAMMERS_WINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include "Repository.h"
#include "User.h"
#include "Observer.h"

class Window : public QWidget, public Observer {
private:
    Repository& repo;  // Change to reference
    User user;
    QListWidget *issues;
    QPushButton *addIssueBt, *resolveIssueBt, *removeIssueBt;
    QLineEdit *descriptionInput;

public:
    Window(Repository& repo, User &user, QWidget *parent = Q_NULLPTR);  // Pass Repository by reference
    ~Window() override = default;
    void update() const override;

public slots:
    void removeIssue();
    void addIssue();
    void resolveIssue();
    void updateResolveButton();
};

#endif //PROGRAMMERS_WINDOW_H
