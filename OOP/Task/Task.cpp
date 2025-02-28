#include "Task.h"
#include <sstream>

Task::Task(std::string description, int status, int id)
        : description(std::move(description)), status(status), id(id) {}

std::string Task::getDescription() const {
    return description;
}

int Task::getStatus() const {
    return status;
}

int Task::getId() const {
    return id;
}

std::string Task::toString() const {
    std::string statusStr;
    std::string idStr = (id == -1) ? "None" : std::to_string(id);

    switch (status) {
        case 0:
            statusStr = "open";
            idStr = "None";
            break;
        case 1:
            statusStr = "in progress";
            break;
        case 2:
            statusStr = "closed";
            break;
        default:
            statusStr = "unknown";
            break;
    }

    return description + " | " + statusStr + " | " + idStr;
}

void Task::setStatus(int newStatus) {
    status = newStatus;
}

void Task::setId(int newId) {
    id = newId;
}

bool Task::operator<(const Task &other) const {
    if (status == other.status)
        return description < other.description;
    return status < other.status;
}
