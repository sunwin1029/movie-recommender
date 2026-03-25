#include "Movie.h"
using namespace std;

int main() {
    Movie m1(1, "기생충", "드라마", 2019);
    Movie m2(2, "인터스텔라", "SF", 2014);
    m1.display();
    m2.display();
    return 0;
}