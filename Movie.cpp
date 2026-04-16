#include "Movie.h"

#include <iostream>

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

std::string Movie::getTitle() const {
    return title;
}

std::string Movie::getGenre() const {
    return genre;
}

int Movie::getReleaseYear() const{
    return releaseYear;
}

int Movie::getRatingCount() const{
    return ratingCount;
}

bool Movie::addRating(double r) {
    // 유효성 검사
    if(r < 0.0 || r > 5.0) {
        std::cout << "잘못된 범위의 rating이 추가되었습니다!\n";
        return false;
    }
    totalRating += r;
    ratingCount++;
    return true;
}

void Movie::display() const {  // const 추가
    std::cout << id << ". " << title << " (" << releaseYear << ")"
              << "  평점: " << getAverageRating() << " (" << ratingCount
              << "건)" << std::endl;
}



void Movie::setReleaseYear(int year) {
    if(year < 1888 || year > 2100) {
        std::cerr << "유효하지 않는 연도입니다.\n";
        return;
    }

    releaseYear = year;
}

