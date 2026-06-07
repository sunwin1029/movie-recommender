#include "SimilarityCalculator.h"

#include <cmath>

#include "Constants.h"

// 사용자 간 유사도는 "공통으로 본 영화 수"와 "평점 차이"를 함께 본다.
// 공통 영화가 많을수록 가중치를 주고, 같은 영화에 준 평점 차이가 클수록 점수를 낮춘다.

int SimilarityCalculator::calculate(const std::vector<Rating>& userA,
                                           const std::vector<Rating>& userB) {
    int unitedMovieAmt = 0;
    double scoreDiffSum = 0.0;

    for(const Rating& ratingA : userA) {
        for(const Rating& ratingB : userB) {
            if(ratingA.getMovieId() == ratingB.getMovieId()) {
                unitedMovieAmt++;
                scoreDiffSum += std::abs(ratingA.getScore() - ratingB.getScore());
            }
        }
    }

    if(unitedMovieAmt == 0) {
        // 비교 기준이 되는 공통 영화가 없으면 취향을 판단할 수 없으므로 추천 계산에서 제외한다.
        return AppConstants::NO_COMMON_MOVIE_SIMILARITY;
    }

    return unitedMovieAmt * AppConstants::COMMON_MOVIE_WEIGHT - scoreDiffSum;
}
