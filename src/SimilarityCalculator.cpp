#include "SimilarityCalculator.h"

#include <cmath>

// 사용자간의 유사도 (취향) 정도를 반환하는 함수
// 기준
// 1. 공통으로 본 영화 기준(공통으로 본 영화 수가 많을수록 취향이 같음)
// 2. 10(만점) - 평점 차이(평점이 다를수록 취향이 다름)

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
        return -1e9;
    }

    return unitedMovieAmt * 10 - scoreDiffSum;
}