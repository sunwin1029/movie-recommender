#include "UserInterface.h"

#include <limits>

using namespace std;

namespace {
constexpr int MENU_UNSELECTED = -1;
constexpr int MENU_EXIT = 0;
constexpr int MENU_ADD_MOVIE = 1;
constexpr int MENU_FIND_MOVIE = 2;
constexpr int MENU_PRINT_MOVIES = 3;
constexpr int MENU_PRINT_SORTED_MOVIES = 4;
constexpr int MENU_ADD_USER = 5;
constexpr int MENU_PRINT_USERS = 6;
constexpr int MENU_ADD_RATING = 7;
constexpr int MENU_PRINT_MOVIE_RATINGS = 8;
constexpr int MENU_RECOMMEND_MOVIES = 9;
constexpr int MENU_HELP = 10;
constexpr int MENU_STATISTICS = 11;
}

// 프로그램 전체 프로세스
void program(Manager& m) {
    int menu = MENU_UNSELECTED;

    printMenu();

    while(true) {
        menu = getInteger("잘못된 입력입니다!\n",
                          "메뉴를 선택해주세요(도움말 : \"10\")\n");
        if(menu == MENU_EXIT) break;
        execute(menu, m);
    }

    cout << "프로그램을 종료합니다!\n";
}

// 각 기능 실행 함수
void execute(int menu, Manager& m) {
    switch(menu) {
        case MENU_ADD_MOVIE:
            // 영화 추가
            addMovie(m);
            break;
        case MENU_FIND_MOVIE:
            // 제목으로 검색
            findMovieByTitle(m);
            break;
        case MENU_PRINT_MOVIES:
            // 전체 목록 출력
            printAllMovies(m);
            break;
        case MENU_PRINT_SORTED_MOVIES:
            // 평점순 정렬 출력
            printSortedMovies(m);
            break;
        case MENU_ADD_USER:
            // 사용자 추가
            addUser(m);
            break;
        case MENU_PRINT_USERS:
            // 사용자 목록 출력
            printUsers(m);
            break;
        case MENU_ADD_RATING:
            // 평점 입력
            addRating(m);
            break;
        case MENU_PRINT_MOVIE_RATINGS:
            // 영화별 평점 보기
            printRatingsOfMovie(m);
            break;
        case MENU_RECOMMEND_MOVIES:
            // 영화 추천
            recommendMovies(m);
            break;
        case MENU_HELP:
            // 도움말 출력
            printMenu();
            break;
        case MENU_STATISTICS:
            // 통계 보기
            printStatistics(m);
            break;
        default:
            cout << "잘못된 "
                    "메뉴입니다!\n";
            break;
    }
}

// 10. 사용 설명서 출력
void printMenu() {
    cout << "=== Movie Recommender ===\n";

    cout << "[ 영화 ]\n  1. 영화 추가\n  2. 제목으로 검색\n  3. 전체 목록 "
            "출력\n  4. 평점순 정렬 출력\n\n";

    cout << "[ 사용자 ]\n  5. 사용자 추가\n  6. 사용자 목록 출력\n\n";

    cout << "[ 평점 ]\n  7. 평점 입력\n  8. 영화별 평점 보기\n\n";

    cout << "[ 추천 ]\n  9. 영화 추천 받기\n\n";

    cout << "[ 도움말 ]\n  10. 메뉴 다시 보기\n\n";

    cout << "[ 통계 ]\n  11. 통계 보기\n\n";

    cout << "  0. 종료\n\n";

    cout << "선택 > ";
}

// 1. 영화 추가
void addMovie(Manager& m) {
    int id, year;
    string title, genre;

    // id 입력받기
    id = getInteger("잘못된 id입니다! 정수형으로 입력해주세요\n",
                    "영화 id를 입력하세요\n> ");

    // 영화 제목 입력받기
    cout << "영화 제목을 입력하세요\n> ";
    getline(cin, title);

    // 영화 장르 입력받기
    cout << "영화 장르를 입력하세요\n> ";
    getline(cin, genre);

    // 개봉연도 입력받기
    year = getInteger("잘못된 개봉연도입니다! 정수형으로 입력해주세요\n",
                      "영화 개봉연도를 입력하세요\n> ");

    // 실제 영화 등록
    m.addMovie(id, title, genre, year);
}

// 2. 제목으로 검색
void findMovieByTitle(Manager& m) {
    string title;

    cout << "찾으려는 영화 제목을 입력하세요\n> ";
    getline(cin, title);

    m.findMovie(title);
}

// 3. 전체 영화 목록 출력
void printAllMovies(Manager& m) {
    cout << "[전체 영화 목록입니다]\n\n";
    m.printMovieList();
}

// 4. 평점순 정렬 출력
void printSortedMovies(Manager& m) {
    cout << "[평점순 영화 목록입니다]\n\n";
    m.printSortedMovieList();
}

// 5. 사용자 추가
void addUser(Manager& m) {
    int id;
    string name, email;

    id = getInteger("id는 정수형 타입입니다!", "사용자 id를 입력하세요\n> ");

    cout << "사용자 이름을 입력하세요\n> ";
    getline(cin, name);

    cout << "사용자 email을 입력하세요\n> ";
    cin >> email;

    m.addUser(id, name, email);
}

// 6. 사용자 목록 출력
void printUsers(Manager& m) {
    cout << "[전체 사용자 목록입니다]\n\n";
    m.printUserList();
}

// 7. 평점 입력
void addRating(Manager& m) {
    int userId;
    int movieId;
    double score;

    userId = getInteger("사용자 id는 정수값입니다!\n",
                        "평점을 등록할 사용자 id를 입력해주세요\n> ");

    movieId = getInteger("영화 id는 정수값입니다!\n",
                         "평점을 등록할 영화 id를 입력해주세요\n> ");

    while(true) {
        cout << "영화의 평점을 입력해주세요\n> ";
        cin >> score;

        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "잘못된 평점 값입니다!\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }

    m.addRating(userId, movieId, score);
}

// 8. 영화별 평점 보기
void printRatingsOfMovie(Manager& m) {
    int movieId = getInteger("영화 id는 정수값입니다!\n",
                             "평점 목록을 확인할 영화 id를 입력해주세요\n> ");

    m.printRatingsOfMovie(movieId);
}

// 9. 영화 추천 받기
void recommendMovies(Manager& m) {
    int userId = getInteger("사용자 id는 정수값입니다!\n",
                            "추천받을 사용자 id를 입력해주세요\n> ");

    m.recommendMovies(userId);
}

// 11. 통계 보기
void printStatistics(Manager& m) {
    m.printStatistics();
}

// 기타 : 정수값 검증 함수
int getInteger(const std::string& warningMessage,
               const std::string& stringRequireMessage) {
    int val;

    while(true) {
        cout << stringRequireMessage;
        cin >> val;

        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << warningMessage << "\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return val;
    }
}
