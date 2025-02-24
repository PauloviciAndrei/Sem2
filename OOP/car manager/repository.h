//
// Created by Robert on 28.05.2024.
//

#ifndef CAR_MANAGER_REPOSITORY_H
#define CAR_MANAGER_REPOSITORY_H

#include "domain.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

class CarRepository {
private:
    vector<Car> cars;
public:
    CarRepository() { load_data(); }
    vector<Car> get_cars();
    vector<Car> get_cars_by_name(string name);
    void load_data();
};


#endif //CAR_MANAGER_REPOSITORY_H
