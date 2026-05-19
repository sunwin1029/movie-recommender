#include "Recommender.h"

#include <set>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>

#include "SimilarityCalculator.h"

// 비교 함수(유사도 높은순)
bool Compare(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    return a.second > b.second;
}

std::vector<int> Recommender::recommend(int targetUserId,
                                        const std::vector<User>& users,
                                        const std::vector<Rating>& ratings,
                                        int movieAmt) {
    
    std::vector<Rating> targetUserRatings; // 타겟 사용자가 작성한 평점
    std::set<int> targetUserWatchedMovies; // 타겟 사용자가 본 영화
    std::vector<std::pair<int, int>> similarities; // 타겟 사용자와의 유사도 {다른 사용자 id, 유사도}

    // 1. 타겟 사용자가 작성한 Rating 저장
    for(const Rating& rating : ratings) {
        if(rating.getUserId() == targetUserId) {
            targetUserRatings.emplace_back(rating);
        }
    }
    // 사용자가 본 영화가 없는 경우
    if(targetUserRatings.empty()) {
        return {};
    }

    // 타겟 사용자가 이미 시청한 영화 저장
    for(const Rating& rating : targetUserRatings) {
        targetUserWatchedMovies.insert(rating.getMovieId());
    }

    // 2. 타겟 사용자와 다른 사용자의 유사도 검사
    for(const User& user : users) {
        if(user.getId() == targetUserId) {
            continue;
        }

        std::vector<Rating> otherRatings;

        for(const Rating& rating : ratings) {
            if(rating.getUserId() == user.getId()) {
                otherRatings.emplace_back(rating);
            }
        }

        int similarity =
            SimilarityCalculator::calculate(targetUserRatings, otherRatings);

        if(similarity > 0) {
            similarities.push_back({user.getId(), similarity});
        }
    }

    std::sort(similarities.begin(), similarities.end(), Compare);

    std::map<int, double> movieScores;
    int similarUserLimit = 3; // 유사 사용자 수는 3명으로 임의 지정
    int usedUserCount = 0;

    // 3. 유사 사용자가 높게 평가한 후보 영화에 추천 점수 누적
    for(const std::pair<int, int>& similarityPair : similarities) {
        if(usedUserCount >= similarUserLimit) {
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
            if(rating.getScore() < 3.0) {
                continue;
            }

            // 영화에 가중치 부여
            movieScores[rating.getMovieId()] +=
                similarity * rating.getScore();
        }

        usedUserCount++;
    }

    // 4. 추천 점수 기준으로 영화 정렬
    std::vector<std::pair<int, double>> sortedMovies(movieScores.begin(),
                                                     movieScores.end());

    std::sort(sortedMovies.begin(), sortedMovies.end(),
              [](const std::pair<int, double>& a,
                 const std::pair<int, double>& b) {
                  return a.second > b.second;
              });

    std::vector<int> result;

    // 5. 상위 movieAmt개 영화 ID 반환
    int count = 0;
    for(size_t i = 0; i < sortedMovies.size() && count < movieAmt; i++) {
        result.push_back(sortedMovies[i].first);
        count++;
    }

    return result;
}
