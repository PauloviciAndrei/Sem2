//
// Created by Robert on 28.05.2024.
//

#include "repository.h"

vector<Car> CarRepository::get_cars() {
    return cars;
}

std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    size_t end = str.find_last_not_of(" \t\n\r");
    return (start == std::string::npos || end == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

void CarRepository::load_data() {
    string filename = "../cars.txt";
    ifstream fin(filename);
    string line;
    while (getline(fin, line)) {
        istringstream iss(line);
        string name, model, color, year;

        getline(iss, name, '|');
        getline(iss, model, '|');
        getline(iss, year, '|');
        getline(iss, color, '|');

        name = trim(name);
        model = trim(model);
        year = trim(year);
        color = trim(color);

        int yearint = stoi(year);
        cars.push_back(Car(name, model, yearint, color));
    }
}