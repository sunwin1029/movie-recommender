#include "SimilarityCalculator.h"

#include <cmath>

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