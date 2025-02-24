//
// Created by Robert on 28.05.2024.
//
#include <iostream>
#include "service.h"

vector<Car> Service::get_cars() {
    vector<Car> cars = repo.get_cars();
    sort(cars.begin(), cars.end(), [](const Car& a, const Car& b) {
        return a.get_name() < b.get_name();
    });
    return cars;
}

vector<Car> Service::get_cars_by_name(std::string name) {
    vector<Car> cars_by_name, cars = repo.get_cars();
    for (const Car &car: cars) {
        if (car.get_name() == name) {
            cars_by_name.push_back(car);
        }
    }
    return cars_by_name;
}