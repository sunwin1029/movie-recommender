#include "Manager.h"

#include <iostream>

Manager::Manager() : movieManager(), ratingManager(), userManager() {}

// CSV 파일 로드
void Manager::loadAll() {
    movieManager.loadFromFile("data/movies.csv");
    userManager.loadFromFile("data/users.csv");
    ratingManager.loadFromFile("data/ratings.csv");

    for(const Rating& rating)
}

// CSV 파일에 저장
void Manager::saveAll() const {
    movieManager.saveToFile("data/movies.csv");
    userManager.saveToFile("data/users.csv");
    ratingManager.saveToFile("data/ratings.csv");
}

// 1. 영화 추가
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
}

// 2. 제목으로 검색
void Manager::findMovie(const std::string& title) {
    Movie* movie = movieManager.findMovieByTitle(title);

    if(movie == nullptr) {
        std::cout << "존재하지 않는 영화입니다!\n";
        return;
    }

    std::cout << *movie;
}

// 3. 전체 영화 목록 출력
void Manager::printMovieList() const { movieManager.printMovieList(); }

// 4. 평점순 영화 목록 출력
void Manager::printSortedMovieList() const {
    movieManager.printMovieList(movieManager.getSortedMovies());
}

// 5. 사용자 추가
void Manager::addUser(int id, const std::string& name,
                      const std::string& email) {
    if(userManager.findUserById(id) != nullptr) {
        std::cout << "이미 존재하는 사용자입니다!\n";
        return;
    }
    userManager.addUser(id, name, email);
}

// 6. 사용자 목록 출력
void Manager::printUserList() const {
    userManager.printUsers();
}

// 7. 평점 입력
void Manager::addRating(int userId, int movieId, double score) {
    Movie* movie = movieManager.findMovieById(movieId);
    User* user = userManager.findUserById(userId);

    if(movie == nullptr || user == nullptr) {
        std::cout << "등록되지 않은 영화 또는 사용자입니다!\n";
        return;
    }

    if(score < 0.0 || score > 5.0) {
        std::cout << "잘못된 평점 범위입니다!\n";
        return;
    }

    movie->addRating(score);
    ratingManager.addRating(userId, movieId, score);
}

// 8. 영화별 평점 보기
void Manager::printRatingsOfMovie(int movieId) {
    Movie* movie = movieManager.findMovieById(movieId);

    if(movie == nullptr) {
        std::cout << "등록되지 않은 영화입니다!\n";
        return;
    }

    std::cout << movie->getTitle() << " 의 평점 목록입니다.\n";
    ratingManager.printRatingsOfMovie(movieId);
}
