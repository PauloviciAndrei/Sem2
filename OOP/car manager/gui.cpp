#include "gui.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QColor>
#include <iostream>

// Assuming Car class and Service class are defined appropriately

GUI::GUI(QWidget *parent) : QWidget(parent) {
    service = Service();
    QVBoxLayout* layout = new QVBoxLayout();
    cars = new QListWidget();
    input = new QLineEdit();
    searchButton = new QPushButton("Search");
    clearButton = new QPushButton("Clear");

    layout->addWidget(cars);
    layout->addWidget(input);
    layout->addWidget(searchButton);
    layout->addWidget(clearButton);

    setLayout(layout);
    populateCars();

    QObject::connect(searchButton, &QPushButton::clicked, this, [this]() {
        get_cars_by_name(input->text().toStdString());
    });
    QObject::connect(clearButton, &QPushButton::clicked, this, [this]() {
        populateCars();
    });

    QOBject::connect(ui->listWidget, &QListWidget::itemClicked, this, [this](), {printFamily();});
}

void GUI::get_cars_by_name(std::string name) {
    cars->clear();
    std::vector<Car> cars_by_name = service.get_cars_by_name(name);
    for (const auto& car : cars_by_name) {
        addCarToListWidget(car);
    }
}

void GUI::populateCars() {
    cars->clear();
    std::vector<Car> servicecars = service.get_cars();
    for (const auto& car : servicecars) {
        addCarToListWidget(car);
    }
}

void GUI::addCarToListWidget(const Car& car) {
    QString carStr = QString::fromStdString(car.to_string());
    QListWidgetItem* item = new QListWidgetItem(carStr);

    // Extract car color from Car object and set the item's text color
    string color = car.get_color();
    QColor textColor;

    if (color == "red") {
        textColor = Qt::red;
    } else if (color == "blue") {
        textColor = Qt::blue;
    } else if (color == "green") {
        textColor = Qt::green;
    } else {
        textColor = Qt::white; // Default color
    }

    // Set the color using QBrush explicitly
    item->setForeground(QBrush(textColor));
    cars->addItem(item);
}
