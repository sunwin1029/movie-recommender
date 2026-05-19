#include "MovieManager.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

// 생성자
MovieManager::MovieManager() : movies(std::vector<Movie>()) {}

// 영화 추가
void MovieManager::addMovie(int id, const std::string& title,
                            const std::string& genre, int year) {
    Movie movie = Movie(id, title, genre, year);
    movies.emplace_back(movie);
}

// 제목으로 영화 검색
Movie* MovieManager::findMovieByTitle(const std::string& title) {
    for(Movie& m : movies) {
        if(m.getTitle() == title) {
            return &m;
        }
    }
    return nullptr;
}

// id로 영화 검색
Movie* MovieManager::findMovieById(int id) {
    for(Movie& m : movies) {
        if(m.getId() == id) {
            return &m;
        }
    }
    return nullptr;
}

// 평점순 영화 목록 반환
std::vector<Movie> MovieManager::getSortedMovies() const {
    std::vector<Movie> sorted = movies;
    std::sort(sorted.begin(), sorted.end());

    return sorted;
}

// 영화 목록 반환
const std::vector<Movie>& MovieManager::getMovies() const {
    return movies;
}

// 영화 목록 출력
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

// 전달받은 영화 목록 출력
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

// CSV 파일 로드
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

// CSV 파일 저장
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

// 총 Movie 수 반환
int MovieManager::size() const { return movies.size(); }
