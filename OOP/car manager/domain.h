//
// Created by Robert on 28.05.2024.
//

#ifndef CAR_MANAGER_DOMAIN_H
#define CAR_MANAGER_DOMAIN_H

#include <string>
using namespace std;

class Car {
private:
    string name;
    string model;
    int year;
    string color;

public:
    Car(string name, string model, int year, string color)
    : name(name), model(model), year(year), color(color) {}
    string get_name() const {
        return name;
    }
    string get_model() const {
        return model;
    }
    int get_year() const {
        return year;
    }
    string get_color() const {
        return color;
    }
    string to_string() const {
        return name + " | " + model + " | " + std::to_string(year) + " | " + color;
    }
};


#endif //CAR_MANAGER_DOMAIN_H
