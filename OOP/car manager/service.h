//
// Created by Robert on 28.05.2024.
//

#ifndef CAR_MANAGER_SERVICE_H
#define CAR_MANAGER_SERVICE_H

#include "repository.h"

class Service {
private:
    CarRepository repo;
public:
    vector<Car> get_cars();
    vector<Car> get_cars_by_name(string name);
};


#endif //CAR_MANAGER_SERVICE_H
