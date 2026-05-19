#pragma once

#include <vector>
#include "Rating.h"

class SimilarityCalculator {
    public:
        static int calculate(const std::vector<Rating>& userA,
        const std::vector<Rating>& userB);
};