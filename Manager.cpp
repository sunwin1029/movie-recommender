#include "Manager.h"

Manager::Manager()
    : movies(std::vector<Movie>()),
      ratings(std::vector<Rating>()),
      users(std::vector<User>()) {}

void Manager::addMovie(int id, const std::string& title,
                       const std::string& genre, int year) {
    movies.emplace_back(Movie(id, title, genre, year));
}

void Manager::addUser(int id, const std::string& name,
                      const std::string& email) {
    users.emplace_back(User(id, name, email));
}

void Manager::addRating(int userId, int movieId, double score) {
    Movie* m = findMovieById(movieId);
    User* u = findUserById(userId);

    if(m == NULL || u == NULL) {
        std::cout << "잘못된 입력입니다!\n";
        return;
    }

    if(!(m->addRating(score))) {
        std::cout << "점수 범위가 잘못됐습니다!\n";
        return;
    }

    ratings.emplace_back(Rating(userId, movieId, score));
}

void Manager::printMovieList() const {
    std::cout << "[전체 영화 출력]\n";
    for(const Movie& m : movies) {
        std::cout << m;
    }
    std::cout << "\n";
}

void Manager::printUserList() const {
    std::cout << "[전체 사용자 출력]\n";
    for(const User& u : users) {
        std::cout << u;
    }
}

Movie* Manager::findMovieByTitle(const std::string& title) {
    for(Movie& m : movies) {
        if(m.getTitle() == title) {
            return &m;
        }
    }
    return NULL;
}

Movie* Manager::findMovieById(int id) {
    for(Movie& m : movies) {
        if(m.getId() == id) {
            return &m;
        }
    }
    return NULL;
}

User* Manager::findUserById(int id) {
    for(User& u : users) {
        if(u.getId() == id) {
            return &u;
        }
    }
    return NULL;
}
