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

// 이미 본 영화는 다시 추천하지 않기 위해 target user의 시청 이력을 set으로 보관한다.
std::set<int> getWatchedMovieIds(const std::vector<Rating>& ratings) {
    std::set<int> watchedMovieIds;

    for(const Rating& rating : ratings) {
        watchedMovieIds.insert(rating.getMovieId());
    }

    return watchedMovieIds;
}

// target user와 공통 영화가 있는 사용자만 유사 사용자 후보로 남긴다.
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

// 유사도가 높은 사용자의 높은 평점 영화일수록 더 큰 추천 점수를 받는다.
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
            // 유사 사용자가 남긴 평점만 추천 후보 계산에 사용한다.
            if(rating.getUserId() != similarUserId) {
                continue;
            }

            // 이미 본 영화는 새 추천 결과로 의미가 없으므로 제외한다.
            if(targetUserWatchedMovies.find(rating.getMovieId()) !=
               targetUserWatchedMovies.end()) {
                continue;
            }

            // 유사 사용자가 낮게 평가한 영화는 취향이 비슷해도 추천 근거가 약하므로 제외한다.
            if(rating.getScore() < AppConstants::MIN_RECOMMENDABLE_RATING) {
                continue;
            }

            // 평점에 사용자 유사도를 곱해 "비슷한 사용자가 높게 평가한 영화"를 우선한다.
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

// recommend()는 movie id만 반환하고, 영화 객체 조회와 출력은 Manager가 담당한다.
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
