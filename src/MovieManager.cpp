#include "MovieManager.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

MovieManager::MovieManager() : movies(std::vector<Movie>()) {}

void MovieManager::addMovie(int id, const std::string& title,
                            const std::string& genre, int year) {
    Movie movie = Movie(id, title, genre, year);
    movies.emplace_back(movie);
}

Movie* MovieManager::findMovieByTitle(const std::string& title) {
    for(Movie& m : movies) {
        if(m.getTitle() == title) {
            return &m;
        }
    }
    return nullptr;
}

Movie* MovieManager::findMovieById(int id) {
    for(Movie& m : movies) {
        if(m.getId() == id) {
            return &m;
        }
    }
    return nullptr;
}

std::vector<Movie> MovieManager::getSortedMovies() const {
    std::vector<Movie> sorted = movies;
    std::sort(sorted.begin(), sorted.end());

    return sorted;
}

void MovieManager::printMovieList() const {
    if(movies.size() < 1) {
        std::cout << "영화 목록이 존재하지 않습니다!\n";
        return;
    }
    for(const Movie& m : movies) {
        std::cout << m;
    }
    std::cout << "\n";
}

// 후처리된 영화 목록을 출력하고 싶은 경우
void MovieManager::printMovieList(const std::vector<Movie>& sorted) const {
    if(sorted.size() < 1) {
        std::cout << "영화 목록이 존재하지 않습니다!\n";
        return;
    }
    for(const Movie& m : sorted) {
        std::cout << m;
    }
    std::cout << "\n";
}

void MovieManager::loadFromFile(const std::string& filename) {
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
        std::string title;
        std::string genre;
        int year;

        getline(ss, token, ',');
        id = std::stoi(token);

        getline(ss, title, ',');

        getline(ss, genre, ',');

        getline(ss, token, ',');
        year = std::stoi(token);

        addMovie(id, title, genre, year);
    }
}

void MovieManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);

    if(!file.is_open()) {
        std::cerr << "파일을 열 수 없습니다: " << filename << "\n";
        return;
    }

    file << "id,title,genre,year\n";

    for(const Movie& movie : movies) {
        file << movie.getId() << "," << movie.getTitle() << ","
             << movie.getGenre() << "," << movie.getReleaseYear() << "\n";
    }
}

int MovieManager::size() const { return movies.size(); }