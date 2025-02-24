//
// Created by Robert on 28.05.2024.
//

#ifndef CAR_MANAGER_GUI_H
#define CAR_MANAGER_GUI_H

#include <QLineEdit>
#include <QList>
#include <QListWidget>
#include <QPushButton>
#include <QWidget>

#include "service.h"

class GUI : public QWidget {
private:
    Service service;
    QListWidget* cars;
    QLineEdit* input;
    QPushButton* searchButton;
    QPushButton* clearButton;
public:
    GUI(QWidget *parent = Q_NULLPTR);
    void populateCars();
    void get_cars_by_name(string name);
    void addCarToListWidget(const Car& car);
};


#endif //CAR_MANAGER_GUI_H
