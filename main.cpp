#include "Movie.h"
#include "Rating.h"
#include "User.h"
using namespace std;

int main() {
    Movie m1(1, "기생충", "드라마", 2019);
    Movie m2(2, "인터스텔라", "SF", 2014);
    Rating r1(1, 1, 6.7);
    Rating r2(2, 2, 3.3);
    User u1(1, "서해승", "sunwin1029@gmail.com");
    r1.display();
    r2.display();
    m2.display();
    u1.display();
    return 0;
}