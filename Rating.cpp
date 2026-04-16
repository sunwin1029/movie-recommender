#include "Rating.h"
#include <iostream>
using namespace std;

// Rating::Rating(int userId, int movieId, double score)
//     : userId(userId), movieId(movieId), score(score) {
//     }

// Rating::Rating(int userId, int movieId, double score)
//     : userId(userId), movieId(movieId), score((score >= 0.0 && score <= 5.0) ? score : 0.0) {
//     }

// 범위 검사를 위해 초기화 리스트 대신, 생성자를 직접 정의하였습니다.
Rating::Rating(int userId, int movieId, double score) :
userId(userId), movieId(movieId), score(score) {
    if(this->score < 0.0 || this->score > 5.0) {
        cout << "잘못된 점수 범위가 입력되었습니다! 점수가 0으로 설정됩니다\n";
        this->score = 0.0;
    }
}

int Rating::getUserId() const { return userId; }

int Rating::getMovieId() const { return movieId; }

double Rating::getScore() const { return score; }


std::ostream& operator<<(std::ostream& os, const Rating& r) {
    os << "UserId : " << r.getUserId() << "\nMovieId : " << r.getMovieId()
       << "\nScore : " << r.getScore() << "\n";

    return os;
}