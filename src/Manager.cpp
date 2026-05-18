#include "Manager.h"

#include <iostream>

Manager::Manager() : movieManager(), ratingManager(), userManager() {}

void Manager::loadAll() {
    movieManager.loadFromFile("data/movies.csv");
    userManager.loadFromFile("data/users.csv");
    ratingManager.loadFromFile("data/ratings.csv");
}

void Manager::saveAll() const {
    movieManager.saveToFile("data/movies.csv");
    userManager.saveToFile("data/users.csv");
    ratingManager.saveToFile("data/ratings.csv");
}

void Manager::addMovie(int id, const std::string& title,
                       const std::string& genre, int year) {
    if(movieManager.findMovieById(id) != nullptr) {
        std::cout << "이미 존재하는 영화입니다!\n";
        return;
    }

    if(year < 1888 || year > 2100) {
        std::cout << "잘못된 연도 범위입니다!\n";
        return;
    }

    movieManager.addMovie(id, title, genre, year);
    std::cout << "영화 등록이 성공했습니다!\n";
}

void Manager::addUser(int id, const std::string& name,
                      const std::string& email) {
    if(userManager.findUserById(id) != nullptr) {
        std::cout << "이미 존재하는 사용자입니다!\n";
        return;
    }

    userManager.addUser(id, name, email);
    std::cout << "사용자 등록이 성공했습니다!\n";
}

void Manager::addRating(int userId, int movieId, double score) {
    Movie* movie = movieManager.findMovieById(movieId);
    User* user = userManager.findUserById(userId);

    if(movie == nullptr || user == nullptr) {
        std::cout << "등록되지 않은 영화 또는 사용자입니다!\n";
        return;
    }

    if(!movie->addRating(score)) {
        std::cout << "잘못된 평점 범위입니다!\n";
        return;
    }

    ratingManager.addRating(userId, movieId, score);
    std::cout << "평점 등록이 성공했습니다!\n";
}

void Manager::printMovieList() const { movieManager.printMovieList(); }

void Manager::printMovieList(const std::vector<Movie>& sorted) const {
    movieManager.printMovieList(sorted);
}

void Manager::printUserList() const { userManager.printUsers(); }

Movie* Manager::findMovieByTitle(const std::string& title) {
    return movieManager.findMovieByTitle(title);
}

std::vector<Movie> Manager::getSortedMovies() const {
    return movieManager.getSortedMovies();
}

std::vector<Rating> Manager::getRatingsofMovie(const Movie& movie) const {
    return ratingManager.getRatingsofMovie(movie);
}
