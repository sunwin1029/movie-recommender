#include "RatingManager.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>

// 생성자
RatingManager::RatingManager() : ratings(std::vector<Rating>()) {}


// 평점 추가
void RatingManager::addRating(int userId, int movieId, double score) {
    ratings.emplace_back(Rating(userId, movieId, score));
}

// 평점 목록 반환
const std::vector<Rating>& RatingManager::getRatings() const {
    return ratings;
}

// 사용자별 평점 반환
std::vector<Rating> RatingManager::getRatingsByUser(int userId) const {
    std::vector <Rating> userRating;

    for(const Rating& rating: ratings) {
        if(rating.getUserId() == userId) {
            userRating.emplace_back(rating);
        }
    }

    return userRating;
}

// 영화별 평점 출력
void RatingManager::printRatingsOfMovie(int movieId) const {
    bool found = false;

    for(const Rating& rating : ratings) {
        if(rating.getMovieId() == movieId) {
            std::cout << rating << std::endl;
            found = true;
        }
    }

    if(!found) {
        std::cout << "해당 영화는 아직 평점이 없습니다!\n";
    }
}

// ratings.csv에는 평균 평점이 아니라 사용자-영화-점수 형태의
// 개별 평점만 저장한다. 평균 평점 계산은 Manager에서 영화와 연결해 처리한다.
void RatingManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if(!file.is_open()) {
        throw std::runtime_error("파일을 열 수 없습니다: " + filename);
    }

    ratings.clear();

    std::string line;
    getline(file, line);  // header skip
    int lineNum = 1;

    while(getline(file, line)) {
        lineNum++;

        if(line.empty()) {
            continue;
        }

        try {
            std::stringstream ss(line);
            std::string token;

            int userId;
            int movieId;
            double score;

            if(!getline(ss, token, ',')) {
                throw std::invalid_argument("사용자 id 누락");
            }
            userId = std::stoi(token);

            if(!getline(ss, token, ',')) {
                throw std::invalid_argument("영화 id 누락");
            }
            movieId = std::stoi(token);

            if(!getline(ss, token, ',')) {
                throw std::invalid_argument("평점 누락");
            }
            score = std::stod(token);
            if(score < 0.0 || score > 5.0) {
                throw std::out_of_range("평점 범위 오류");
            }

            addRating(userId, movieId, score);
        } catch(const std::exception& e) {
            std::cerr << filename << ":" << lineNum << "번째 줄 건너뜀: "
                      << e.what() << "\n";
        }
    }
}


// CSV 파일 저장
void RatingManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);

    if(!file.is_open()) {
        std::cerr << "파일을 열 수 없습니다: " << filename << "\n";
        return;
    }

    file << "userId,movieId,score\n";

    for(const Rating& rating : ratings) {
        file << rating.getUserId() << "," << rating.getMovieId() << ","
             << rating.getScore() << "\n";
    }
}

// 총 Rating 수 반환
int RatingManager::size() const { return ratings.size(); }
