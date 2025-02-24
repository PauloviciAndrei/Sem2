//
// Created by Robert on 18.06.2024.
//

#ifndef PROGRAMMERS_USER_H
#define PROGRAMMERS_USER_H

#include <string>
using namespace std;

class User {
private:
    string name;
    string type;

public:
    User(const string &name, const string &type) : name{name}, type{type} {};
    string getName() const {
        return name;
    }
    string getType() const {
        return type;
    }
};


#endif //PROGRAMMERS_USER_H
