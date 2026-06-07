#include "MovieManager.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <sstream>
#include <vector>

#include "Constants.h"

// 생성자
MovieManager::MovieManager() : movies() {}

// 영화 추가
void MovieManager::addMovie(int id, const std::string& title,
                            const std::string& genre, int year) {
    movies.emplace_back(id, title, genre, year);
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

// 평점 상위 영화 목록 반환
std::vector<Movie> MovieManager::getTopMovies(int count) const {
    std::vector<Movie> sorted = getSortedMovies();

    if(count < static_cast<int>(sorted.size())) {
        sorted.resize(count);
    }

    return sorted;
}

// 장르별 평균 평점 반환
std::map<std::string, double> MovieManager::getAverageRatingByGenre() const {
    std::map<std::string, double> totalByGenre;
    std::map<std::string, int> countByGenre;

    for(const Movie& movie : movies) {
        // 평점이 없는 영화까지 포함하면 0점 영화처럼 평균이 왜곡되므로 제외한다.
        if(movie.getRatingCount() == 0) {
            continue;
        }

        totalByGenre[movie.getGenre()] += movie.getAverageRating();
        countByGenre[movie.getGenre()]++;
    }

    std::map<std::string, double> averageByGenre;

    for(const auto& genreTotal : totalByGenre) {
        const std::string& genre = genreTotal.first;
        averageByGenre[genre] = genreTotal.second / countByGenre[genre];
    }

    return averageByGenre;
}

// 전체 평균 평점 반환
double MovieManager::getAverageRating() const {
    double total = 0.0;
    int ratedMovieCount = 0;

    for(const Movie& movie : movies) {
        // 통계의 전체 평균은 "등록된 영화 수"가 아니라 "평점이 있는 영화 수"를 기준으로 한다.
        if(movie.getRatingCount() == 0) {
            continue;
        }

        total += movie.getAverageRating();
        ratedMovieCount++;
    }

    if(ratedMovieCount == 0) {
        throw std::runtime_error("평점이 등록된 영화가 없습니다.");
    }

    return total / ratedMovieCount;
}

// 영화 목록 반환
const std::vector<Movie>& MovieManager::getMovies() const {
    return movies;
}

// 영화 목록 출력
void MovieManager::printMovieList() const {
    if(movies.empty()) {
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
    if(sorted.empty()) {
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
        throw std::runtime_error("파일을 열 수 없습니다: " + filename);
    }

    movies.clear();

    std::string line;
    getline(file, line);  // header skip
    int lineNum = AppConstants::CSV_HEADER_LINE;

    while(getline(file, line)) {
        lineNum++;

        if(line.empty()) {
            continue;
        }

        try {
            std::stringstream ss(line);
            std::string token;

            int id;
            std::string title;
            std::string genre;
            int year;

            if(!getline(ss, token, ',')) {
                throw std::invalid_argument("영화 id 누락");
            }
            id = std::stoi(token);

            if(!getline(ss, title, ',') || title.empty()) {
                throw std::invalid_argument("영화 제목 누락");
            }

            if(!getline(ss, genre, ',') || genre.empty()) {
                throw std::invalid_argument("영화 장르 누락");
            }

            if(!getline(ss, token, ',')) {
                throw std::invalid_argument("개봉연도 누락");
            }
            year = std::stoi(token);
            if(year < AppConstants::MIN_RELEASE_YEAR ||
               year > AppConstants::MAX_RELEASE_YEAR) {
                throw std::out_of_range("개봉연도 범위 오류");
            }

            addMovie(id, title, genre, year);
        } catch(const std::exception& e) {
            std::cerr << filename << ":" << lineNum << "번째 줄 건너뜀: "
                      << e.what() << "\n";
        }
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
