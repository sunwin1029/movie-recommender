#pragma once
#include <string>
#include <vector>

#include "BaseManager.h"
#include "Rating.h"

class RatingManager : public BaseManager {
   private:
    std::vector<Rating> ratings;

   public:
    RatingManager();

    void addRating(int userId, int movieId, double score);
    void printRatingsOfMovie(int movieId) const;

    const std::vector<Rating>& getRatings() const;
    std::vector<Rating> getRatingsByUser(int userId) const;

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;
};
