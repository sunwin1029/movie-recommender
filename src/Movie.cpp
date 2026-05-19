#include "Movie.h"

// 기본 생성자
Movie::Movie() : id(0), releaseYear(0), totalRating(0.0), ratingCount(0) {}

// 4인자 생성자
Movie::Movie(int id, const std::string& title, const std::string& genre,
             int year)
    : id(id),
      title(title),
      genre(genre),
      releaseYear(year),
      totalRating(0.0),
      ratingCount(0) {}

double Movie::getAverageRating() const {
    if(ratingCount == 0) return 0.0;  // 0 나눗셈 방어
    return totalRating / ratingCount;
}

std::string Movie::getTitle() const { return title; }

std::string Movie::getGenre() const { return genre; }

int Movie::getId() const { return id; }

int Movie::getReleaseYear() const { return releaseYear; }

int Movie::getRatingCount() const { return ratingCount; }

void Movie::addRating(double r) {
    totalRating += r;
    ratingCount++;
}

std::ostream& operator<<(std::ostream& os, const Movie& m) {
    os << m.getId() << ". " << m.getTitle() << " (" << m.getReleaseYear() << ")"
       << "  평점: " << m.getAverageRating() << " (" << m.getRatingCount()
       << "건)" << std::endl;

    return os;
}

bool Movie::operator<(const Movie& other) const {
    if(getAverageRating() == other.getAverageRating()) {
        return title < other.title;
    }
    // 평점이 큰 영화가 앞에 오도록
    return getAverageRating() > other.getAverageRating();
}

bool Movie::operator==(const Movie& other) const {
    return id == other.id;
}
