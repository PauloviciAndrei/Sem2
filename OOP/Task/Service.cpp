#include "Service.h"
#include <stdexcept>


Service::Service(Repository& repo) : repo(repo) {}


void Service::addTask(const std::string& description, int status, int id) {
    if (checkIfTaskExists(description))
        throw std::runtime_error("Task already exists!");
    if (description.empty())
        throw std::runtime_error("Description cannot be empty!");


    if (repo.getProgrammerNameById(id) == "None")
        throw std::runtime_error("Invalid programmer ID!");

    repo.addTask(description, status, id);
}

void Service::removeTask(int row) {
    if (row < 0 || row >= repo.getTasks().size())
        throw std::out_of_range("Invalid task index!");

    if (repo.getTasks()[row].getStatus() != 2)
        throw std::runtime_error("You can remove only closed tasks!");

    repo.removeTask(row);
}

void Service::startTask(int pos, int id) {
    if (pos < 0 || pos >= repo.getTasks().size())
        throw std::out_of_range("Invalid task index!");

    if (repo.getTasks()[pos].getStatus() != 0)
        throw std::runtime_error("Task cannot be started!");

    if (repo.getProgrammerNameById(id) == "None")
        throw std::runtime_error("Invalid programmer ID!");

    repo.startTask(pos, id);
}

void Service::finishTask(int pos) {
    if (pos < 0 || pos >= repo.getTasks().size())
        throw std::out_of_range("Invalid task index!");

    if (repo.getTasks()[pos].getStatus() != 1)
        throw std::runtime_error("Task is not in progress!");

    repo.finishTask(pos);
}

bool Service::checkIfTaskExists(const std::string& description) const {
    for (const auto& task : repo.getTasks()) {
        if (task.getDescription() == description)
            return true;
    }
    return false;
}

std::string Service::getProgrammerNameById(int id) const {
    return repo.getProgrammerNameById(id);
}

