#include "User.h"
using namespace std;

User::User(int id, const string& name, const string& email)
    : id(id), name(name), email(email) {}

int User::getId() const { return id; }

std::string User::getName() const { return name; }

std::string User::getEmail() const { return email; }

std::ostream& operator<<(std::ostream& os, const User& u) {
    os << "ID : " << u.getId() << "\nName : " << u.getName()
       << "\nEmail : " << u.getEmail() << "\n";
    return os;
}
