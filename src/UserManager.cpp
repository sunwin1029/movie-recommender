#include "UserManager.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
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
        throw std::runtime_error("파일을 열 수 없습니다: " + filename);
    }

    users.clear();

    std::string line;
    getline(file, line);  // header skip
    int lineNum = 1;

    while(getline(file, line)) {
        lineNum++;

        if(line.empty()) {
            continue;
        }

        try {
            std::stringstream ss(line);
            std::string token;

            int id;
            std::string name;
            std::string email;

            if(!getline(ss, token, ',')) {
                throw std::invalid_argument("사용자 id 누락");
            }
            id = std::stoi(token);

            if(!getline(ss, name, ',') || name.empty()) {
                throw std::invalid_argument("사용자 이름 누락");
            }

            if(!getline(ss, email, ',') || email.empty()) {
                throw std::invalid_argument("사용자 email 누락");
            }

            addUser(id, name, email);
        } catch(const std::exception& e) {
            std::cerr << filename << ":" << lineNum << "번째 줄 건너뜀: "
                      << e.what() << "\n";
        }
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
