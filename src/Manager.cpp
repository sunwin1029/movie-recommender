#include "Manager.h"

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

bool Manager::addMovie(int id, const std::string& title,
                       const std::string& genre, int year) {
    if(movieManager.findMovieById(id) != nullptr) {
        std::cout << "이미 존재하는 영화입니다!\n";
        return false;
    }

    if(year < 1888 || year > 2100) {
        std::cout << "잘못된 연도 범위입니다!\n";
        return false;
    }

    movieManager.addMovie(id, title, genre, year);
    return true;
}

bool Manager::addUser(int id, const std::string& name,
                      const std::string& email) {
    if(userManager.findUserById(id) != nullptr) {
        return false;
    }

    userManager.addUser(id, name, email);
    return true;
}

bool Manager::addRating(int userId, int movieId, double score) {
    Movie* movie = movieManager.findMovieById(movieId);
    User* user = userManager.findUserById(userId);

    if(movie == nullptr || user == nullptr) {
        return false;
    }

    if(!movie->addRating(score)) {
        return false;
    }

    ratingManager.addRating(userId, movieId, score);
    return true;
}

void Manager::printMovieList() const { movieManager.printMovieList(); }

void Manager::printMovieList(const std::vector<Movie>& sorted) const {
    movieManager.printMovieList(sorted);
}

void Manager::printUserList() const { userManager.printUsers(); }

Movie* Manager::findMovieByTitle(const std::string& title) {
    
    return movieManager.findMovieByTitle(title);
}

Movie* Manager::findMovieById(int id) { return movieManager.findMovieById(id); }

User* Manager::findUserById(int id) { return userManager.findUserById(id); }

std::vector<Movie> Manager::getSortedMovies() const {
    return movieManager.getSortedMovies();
}

std::vector<Rating> Manager::getRatingsofMovie(const Movie& movie) const {
    return ratingManager.getRatingsofMovie(movie);
}

void Manager::saveMoviesToFile(const std::string& filename) const {
    movieManager.saveToFile(filename);
}

void Manager::saveUsersToFile(const std::string& filename) const {
    userManager.saveToFile(filename);
}

void Manager::saveRatingsToFile(const std::string& filename) const {
    ratingManager.saveToFile(filename);
}

void Manager::loadMoviesFromFile(const std::string& filename) {
    movieManager.loadFromFile(filename);
}

void Manager::loadUsersFromFile(const std::string& filename) {
    userManager.loadFromFile(filename);
}

void Manager::loadRatingsFromFile(const std::string& filename) {
    ratingManager.loadFromFile(filename);
}
