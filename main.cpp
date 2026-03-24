#include "Movie.h"
int main()
{
    Movie m1("기생충", "드라마", "봉준호",
             2019, 4.8);
    Movie m2("인터스텔라", "SF",
             "크리스토퍼 놀란", 2014, 4.9);
    m1.display();
    // 기생충 (2019) [드라마] 평점: 4.8
    m2.display();
    // 인터스텔라 (2014) [SF] 평점: 4.9
    m1.setRating(5.0);
    m1.setRating(6.0); // → 5.0으로 보정
    cout << m1.getTitle() << ": "
         << m1.getRating() << endl;
    return 0;
}