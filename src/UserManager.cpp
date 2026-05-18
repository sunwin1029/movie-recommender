#include "UserManager.h"

#include <fstream>
#include <iostream>
#include <sstream>

UserManager::UserManager() : users(std::vector<User>()) {}

void UserManager::addUser(int id, const std::string& name,
                          const std::string& email) {
    User user = User(id, name, email);
    users.emplace_back(user);
}

User* UserManager::findUserById(int id) {
    for(User& u : users) {
        if(u.getId() == id) {
            return &u;
        }
    }
    return nullptr;
}

void UserManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if(!file.is_open()) {
        std::cerr << "파일을 열 수 없습니다: " << filename << "\n";
        return;
    }

    std::string line;
    getline(file, line);  // header skip

    while(getline(file, line)) {
        std::stringstream ss(line);
        std::string token;

        int id;
        std::string name;
        std::string email;

        getline(ss, token, ',');
        id = std::stoi(token);

        getline(ss, name, ',');

        getline(ss, email, ',');

        addUser(id, name, email);
    }
}

void UserManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);

    if(!file.is_open()) {
        std::cerr << "파일을 열 수 없습니다: " << filename << "\n";
        return;
    }

    file << "id,name,email\n";

    for(const User& user : users) {
        file << user.getId() << "," << user.getName() << ","
             << user.getEmail() << "\n";
    }
}

int UserManager::size() const {
    return static_cast<int>(users.size());
}
