#include "Manager.h"

#include <iostream>
#include <map>
#include <vector>

#include "Constants.h"
#include "Recommender.h"

Manager::Manager() : movieManager(), ratingManager(), userManager() {}

// CSV 파일 로드
void Manager::loadAll() {
    try {
        movieManager.loadFromFile("data/movies.csv");
    } catch(const std::exception& e) {
        std::cerr << "영화 데이터 로드 실패: " << e.what() << "\n";
    }

    try {
        userManager.loadFromFile("data/users.csv");
    } catch(const std::exception& e) {
        std::cerr << "사용자 데이터 로드 실패: " << e.what() << "\n";
    }

    try {
        ratingManager.loadFromFile("data/ratings.csv");
    } catch(const std::exception& e) {
        std::cerr << "평점 데이터 로드 실패: " << e.what() << "\n";
    }

    // ratings.csv에는 개별 평점만 저장하므로, 로드 후 Movie 객체에 다시 연결해 평균 평점을 재계산한다.
    for(const Rating &rating : ratingManager.getRatings()) {
        Movie* movie = movieManager.findMovieById(rating.getMovieId());

        if(movie != nullptr) {
            movie->addRating(rating.getScore());
        }
    }
}

// 11. 통계 보기
void Manager::printStatistics() const {
    try {
        std::cout << "[영화 통계입니다]\n\n";
        std::cout << "전체 평균 평점: " << movieManager.getAverageRating()
                  << "\n\n";

        std::cout << "[평점 상위 영화]\n";
        movieManager.printMovieList(
            movieManager.getTopMovies(AppConstants::TOP_STATISTICS_MOVIE_COUNT));

        // 장르별 평균은 실제 평점이 있는 영화만 대상으로 계산한다.
        std::map<std::string, double> averageByGenre =
            movieManager.getAverageRatingByGenre();

        if(averageByGenre.empty()) {
            std::cout << "장르별 평균 평점을 계산할 수 없습니다!\n";
            return;
        }

        std::cout << "[장르별 평균 평점]\n";
        for(const auto& genreAverage : averageByGenre) {
            std::cout << genreAverage.first << ": " << genreAverage.second
                      << "\n";
        }
    } catch(const std::exception& e) {
        std::cout << "통계를 계산할 수 없습니다: " << e.what() << "\n";
    }
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

    if(year < AppConstants::MIN_RELEASE_YEAR ||
       year > AppConstants::MAX_RELEASE_YEAR) {
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

    if(score < AppConstants::MIN_RATING_SCORE ||
       score > AppConstants::MAX_RATING_SCORE) {
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

// 9. 영화 추천 받기
void Manager::recommendMovies(int userId) {
    User* user = userManager.findUserById(userId);

    if(user == nullptr) {
        std::cout << "등록되지 않은 사용자입니다!\n";
        return;
    }

    std::vector<int> recommendedMovieIds = Recommender::recommend(
        userId, userManager.getUsers(), ratingManager.getRatings(),
        AppConstants::DEFAULT_RECOMMEND_COUNT);

    if(recommendedMovieIds.empty()) {
        std::cout << "추천할 영화가 없습니다!\n";
        return;
    }

    std::cout << "[추천 영화 목록입니다]\n\n";

    for(int movieId : recommendedMovieIds) {
        Movie* movie = movieManager.findMovieById(movieId);

        if(movie != nullptr) {
            std::cout << *movie;
        }
    }
}
