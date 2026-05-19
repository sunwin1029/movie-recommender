#include "UserManager.h"

#include <fstream>
#include <iostream>
#include <sstream>

// 생성자
UserManager::UserManager() : users(std::vector<User>()) {}

// 사용자 추가
void UserManager::addUser(int id, const std::string& name,
                          const std::string& email) {
    User user = User(id, name, email);
    users.emplace_back(user);
}

// 사용자 목록 출력
void UserManager::printUsers() const {
    if(users.size() < 1) {
        std::cout << "사용자 목록이 존재하지 않습니다!\n";
        return;
    }

    for(const User& user : users) {
        std::cout << user;
    }

    std::cout << "\n";
}

// 사용자 목록 반환
const std::vector<User>& UserManager::getUsers() const {
    return users;
}


// id로 사용자 검색
User* UserManager::findUserById(int id) {
    for(User& u : users) {
        if(u.getId() == id) {
            return &u;
        }
    }
    return nullptr;
}

// CSV 파일 로드
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

// CSV 파일 저장
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

// 총 User 수 반환
int UserManager::size() const {
    return users.size();
}
