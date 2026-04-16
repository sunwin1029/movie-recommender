#pragma once

class Rating {
   private:
    int userId;
    int movieId;
    double score;

   public:
    Rating(int userId, int movieId, double score);
    int getUserId() const;
    int getMovieId() const;
    double getScore() const;
};

std::ostream& operator<<(std::ostream& os, const Rating& r);