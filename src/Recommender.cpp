#include "Recommender.h"

#include <algorithm>
#include <map>
#include <set>
#include <utility>
#include <vector>

#include "Constants.h"
#include "SimilarityCalculator.h"

namespace {
using Similarity = std::pair<int, int>;
using MovieScore = std::pair<int, double>;

bool compareBySimilarity(const Similarity& a, const Similarity& b) {
    return a.second > b.second;
}

bool compareByMovieScore(const MovieScore& a, const MovieScore& b) {
    return a.second > b.second;
}

std::vector<Rating> getRatingsByUser(int userId,
                                     const std::vector<Rating>& ratings) {
    std::vector<Rating> userRatings;

    for(const Rating& rating : ratings) {
        if(rating.getUserId() == userId) {
            userRatings.emplace_back(rating);
        }
    }

    return userRatings;
}

std::set<int> getWatchedMovieIds(const std::vector<Rating>& ratings) {
    std::set<int> watchedMovieIds;

    for(const Rating& rating : ratings) {
        watchedMovieIds.insert(rating.getMovieId());
    }

    return watchedMovieIds;
}

std::vector<Similarity> calculateSimilarities(
    int targetUserId, const std::vector<Rating>& targetUserRatings,
    const std::vector<User>& users, const std::vector<Rating>& ratings) {
    std::vector<Similarity> similarities;

    for(const User& user : users) {
        if(user.getId() == targetUserId) {
            continue;
        }

        std::vector<Rating> otherRatings = getRatingsByUser(user.getId(), ratings);
        int similarity =
            SimilarityCalculator::calculate(targetUserRatings, otherRatings);

        if(similarity > AppConstants::MIN_SIMILARITY_SCORE) {
            similarities.emplace_back(user.getId(), similarity);
        }
    }

    std::sort(similarities.begin(), similarities.end(), compareBySimilarity);

    return similarities;
}

std::map<int, double> accumulateCandidateScores(
    const std::vector<Similarity>& similarities,
    const std::set<int>& targetUserWatchedMovies,
    const std::vector<Rating>& ratings) {
    std::map<int, double> movieScores;
    int usedUserCount = 0;

    for(const Similarity& similarityPair : similarities) {
        if(usedUserCount >= AppConstants::MAX_SIMILAR_USERS) {
            break;
        }

        int similarUserId = similarityPair.first;
        int similarity = similarityPair.second;

        for(const Rating& rating : ratings) {
            // 유사 사용자의 Rating 찾기
            if(rating.getUserId() != similarUserId) {
                continue;
            }

            // 타겟 사용자가 이미 본 영화인 경우
            if(targetUserWatchedMovies.find(rating.getMovieId()) !=
               targetUserWatchedMovies.end()) {
                continue;
            }

            // 추천할만한 영화가 아닌 경우 (유사 사용자가 안좋게 평가할 영화를 추천할 이유 없음)
            if(rating.getScore() < AppConstants::MIN_RECOMMENDABLE_RATING) {
                continue;
            }

            // 영화에 가중치 부여
            movieScores[rating.getMovieId()] +=
                similarity * rating.getScore();
        }

        usedUserCount++;
    }

    return movieScores;
}

std::vector<int> getTopMovieIds(const std::map<int, double>& movieScores,
                                int movieAmt) {
    std::vector<MovieScore> sortedMovies(movieScores.begin(), movieScores.end());
    std::sort(sortedMovies.begin(), sortedMovies.end(), compareByMovieScore);

    std::vector<int> result;

    int count = 0;
    for(size_t i = 0; i < sortedMovies.size() && count < movieAmt; i++) {
        result.push_back(sortedMovies[i].first);
        count++;
    }

    return result;
}
}

std::vector<int> Recommender::recommend(int targetUserId,
                                        const std::vector<User>& users,
                                        const std::vector<Rating>& ratings,
                                        int movieAmt) {
    std::vector<Rating> targetUserRatings =
        getRatingsByUser(targetUserId, ratings);

    if(targetUserRatings.empty()) {
        return {};
    }

    std::set<int> targetUserWatchedMovies =
        getWatchedMovieIds(targetUserRatings);
    std::vector<Similarity> similarities = calculateSimilarities(
        targetUserId, targetUserRatings, users, ratings);
    std::map<int, double> movieScores = accumulateCandidateScores(
        similarities, targetUserWatchedMovies, ratings);

    return getTopMovieIds(movieScores, movieAmt);
}
