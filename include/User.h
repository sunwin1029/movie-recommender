#pragma once
#include <string>
#include <iostream>

class User {
   private:
    int id;
    std::string name;
    std::string email;

   public:
    // 생성자
    User(int id, const std::string& name, const std::string& email);

    int getId() const;
    const std::string& getName() const;
    const std::string& getEmail() const;
    
};

std::ostream& operator<<(std::ostream& os, const User& u);
