#include "User.h"

#include <iostream>
using namespace std;

User::User(int id, const string& name, const string& email)
    : id(id), name(name), email(email) {}

void User::display() const {
    std::cout << "ID : " << id << "\nName : " << name << "\nEmail : " << email
              << "\n";
}

int User::getId() { return id; }

std::string User::getName() const { return name; }

std::string User::getEmail() const { return email; }