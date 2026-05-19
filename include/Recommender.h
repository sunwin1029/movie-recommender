#pragma once

#include <vector>

#include "Movie.h"
#include "Rating.h"
#include "User.h"

class Recommender {
   public:
    static std::vector<int> recommend(int targetUserId,
                                      const std::vector<User>& users,
                                      const std::vector<Movie>& movies,
                                      const std::vector<Rating>& ratings,
                                      int movieAmt);
};