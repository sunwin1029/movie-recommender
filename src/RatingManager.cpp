#include "RatingManager.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

#include "MovieManager.h"
#include "UserManager.h"

RatingManager::RatingManager() : ratings(std::vector<Rating>()) {}

void RatingManager::addRating(int userId, int movieId, double score) {
    ratings.emplace_back(Rating(userId, movieId, score));
}

std::vector<Rating> RatingManager::getRatingsofMovie(const Movie& movie) const {

}

void RatingManager::loadFromFile(const std::string& filename) {
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

        int userId;
        int movieId;
        double score;

        getline(ss, token, ',');
        userId = std::stoi(token);

        getline(ss, token, ',');
        movieId = std::stoi(token);

        getline(ss, token, ',');
        score = std::stod(token);

        addRating(userId, movieId, score);
    }
}

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

int RatingManager::size() const { return ratings.size(); }
