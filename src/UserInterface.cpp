#include "UserInterface.h"

using namespace std;

// 프로그램 전체 프로세스
void program(Manager& m) {
    int menu = -1;

    printMenu();

    while(true) {
        menu = getInteger("잘못된 입력입니다!\n",
                          "메뉴를 선택해주세요(도움말 : \"9\")\n");
        if(menu == 0) break;
        execute(menu, m);
    }

    cout << "프로그램을 종료합니다!\n";
}

// 각 기능 실행 함수
void execute(int menu, Manager& m) {
    switch(menu) {
        case 1:
            // 영화 추가
            addMovie(m);
            break;
        case 2:
            // 제목으로 검색
            findMovieByTitle(m);
            break;
        case 3:
            // 전체 목록 출력
            printAllMovies(m);
            break;
        case 4:
            // 평점순 정렬 출력
            printSortedMovies(m);
            break;
        case 5:
            // 사용자 추가
            addUser(m);
            break;
        case 6:
            // 사용자 목록 출력
            printUsers(m);
            break;
        case 7:
            // 평점 입력
            addRating(m);
            break;
        case 8:
            // 영화별 평점 보기
            printRatingsOfMovie(m);
            break;
        case 9:
            // 도움말 출력
            printMenu();
            break;
        default:
            cout << "잘못된 "
                    "메뉴입니다!\n";
            break;
    }
}

// 9. 사용 설명서 출력
void printMenu() {
    cout << "=== Movie Recommender ===\n";

    cout << "[ 영화 ]\n  1. 영화 추가\n  2. 제목으로 검색\n  3. 전체 목록 "
            "출력\n  4. 평점순 정렬 출력\n\n";

    cout << "[ 사용자 ]\n  5. 사용자 추가\n  6. 사용자 목록 출력\n\n";

    cout << "[ 평점 ]\n  7. 평점 입력\n  8. 영화별 평점 보기\n\n";

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
            cin.ignore(1000, '\n');
            cout << "잘못된 평점 값입니다!\n";
            continue;
        }

        cin.ignore(1000, '\n');
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

// 정수값 검증 함수
int getInteger(const std::string& warningMessage,
               const std::string& stringRequireMessage) {
    int val;

    while(true) {
        cout << stringRequireMessage;
        cin >> val;

        if(cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << warningMessage << "\n";
            continue;
        }

        cin.ignore(1000, '\n');
        return val;
    }
}
