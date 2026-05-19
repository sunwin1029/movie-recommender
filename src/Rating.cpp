#include "Rating.h"

Rating::Rating(int userId, int movieId, double score) :
userId(userId), movieId(movieId), score(score) {}

int Rating::getUserId() const { return userId; }

int Rating::getMovieId() const { return movieId; }

double Rating::getScore() const { return score; }


std::ostream& operator<<(std::ostream& os, const Rating& r) {
    os << "UserId : " << r.getUserId() << "\nMovieId : " << r.getMovieId()
       << "\nScore : " << r.getScore() << "\n";

    return os;
}
