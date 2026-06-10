#include "UserManager.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

#include "Constants.h"
#include "CsvUtils.h"

// 생성자
UserManager::UserManager() : users() {}

// 사용자 추가
void UserManager::addUser(int id, const std::string& name,
                          const std::string& email) {
    users.emplace_back(id, name, email);
}

// 사용자 목록 출력
void UserManager::printUsers() const {
    if(users.empty()) {
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
    int lineNum = AppConstants::CSV_HEADER_LINE;

    while(getline(file, line)) {
        lineNum++;

        if(line.empty()) {
            continue;
        }

        try {
            std::vector<std::string> fields = CsvUtils::parseCsvLine(line);

            int id;
            std::string name;
            std::string email;

            if(fields.size() < 3) {
                throw std::invalid_argument("사용자 필드 누락");
            }
            if(fields.size() > 3) {
                throw std::invalid_argument("사용자 필드 개수 오류");
            }

            if(fields[0].empty()) {
                throw std::invalid_argument("사용자 id 누락");
            }
            id = std::stoi(fields[0]);

            name = fields[1];
            if(name.empty()) {
                throw std::invalid_argument("사용자 이름 누락");
            }

            email = fields[2];
            if(email.empty()) {
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
        file << user.getId() << "," << CsvUtils::escapeCsvField(user.getName())
             << "," << CsvUtils::escapeCsvField(user.getEmail()) << "\n";
    }
}

// 총 User 수 반환
int UserManager::size() const {
    return users.size();
}
