#pragma once
#include <string>
#include <vector>

#include "BaseManager.h"
#include "Rating.h"
#include "Movie.h"

class RatingManager : public BaseManager {
   private:
    std::vector<Rating> ratings;

   public:
    RatingManager();

    void addRating(int userId, int movieId, double score);
    std::vector<Rating> getRatingsofMovie(const Movie& movie) const;

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;
};