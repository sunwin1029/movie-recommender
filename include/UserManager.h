#pragma once
#include <string>
#include <vector>

#include "BaseManager.h"
#include "User.h"

class UserManager : public BaseManager {
   private:
    std::vector<User> users;

   public:
    UserManager();

    void addUser(int id, const std::string& name, const std::string& email);
    
    void printUsers() const;
    const std::vector<User>& getUsers() const;

    User* findUserById(int id);

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;
};