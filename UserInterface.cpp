#include "UserInterface.h"

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
            getRatingsofMovie(m);
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

    // id 입력받기(중복 검사)
    while(true) {
        id = getInteger("잘못된 id입니다! 정수형으로 입력해주세요\n",
                        "영화 id를 입력하세요\n> ");

        if(m.findMovieById(id) != NULL) {
            cout << "중복된 id입니다!\n";
            continue;
        }

        break;
    }

    // 영화 제목 입력받기
    cout << "영화 제목을 입력하세요\n> ";
    getline(cin, title);

    // 영화 장르 입력받기
    cout << "영화 장르를 입력하세요\n> ";
    getline(cin, genre);

    // 개봉연도 입력받기(범위 검사)
    while(true) {
        year = getInteger("잘못된 개봉연도입니다! 정수형으로 입력해주세요\n",
                          "영화 개봉연도를 입력하세요\n");

        if(year < 1888 || year > 2100) {
            cout << "유효하지 않는 연도가 입력됐습니다! \n";
            continue;
        }

        break;
    }

    m.addMovie(id, title, genre, year);
}

// 2. 제목으로 검색
void findMovieByTitle(Manager& m) {
    string title;

    cout << "찾으려는 영화 제목을 입력하세요\n> ";
    getline(cin, title);

    Movie* movie = m.findMovieByTitle(title);

    if(movie == NULL) {
        cout << "존재하지 않는 영화입니다\n";
    } else {
        cout << *movie;
    }
}

// 3. 전체 영화 목록 출력
void printAllMovies(Manager& m) {
    cout << "[전체 영화 목록입니다]\n\n";
    m.printMovieList();
}

// 4. 평점순 정렬 출력
void printSortedMovies(Manager& m) {
    cout << "[평점순 영화 목록입니다]\n\n";
    m.printMovieList(m.getSortedMovies());
}

// 5. 사용자 추가
void addUser(Manager& m) {
    int id;
    string name, email;

    id = getInteger("id는 정수형 타입입니다!", "사용자 id를 입력하세요\n> ");

    // 중복 id 방지
    while(m.findUserById(id) != NULL) {
        cout << "중복된 사용자입니다!";
        id =
            getInteger("id는 정수형 타입입니다!", "사용자 id를 입력하세요\n> ");
    }
    cin.ignore();

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
    int movieId, userId;
    double score;
    // 영화 제목은 우연히 겹칠 수도 있으니, id로 찾기(우선은)
    cout << "평점을 등록하고 싶은 영화 id를 알려주세요\n";
    cin >> movieId;
    Movie* movie;

    // 영화 id 검증
    while((movie = m.findMovieById(movieId)) == NULL) {
        cout << "등록되지 않은 영화입니다\n";
        cout << "평점을 등록하고 싶은 영화 id를 알려주세요\n";
        cin >> movieId;
    }

    cout << "평점을 등록하고 싶은 사용자의 id를 알려주세요\n";
    cin >> userId;
    User* user;

    while((user = m.findUserById(userId)) == NULL) {
        cout << "등록되지 않은 사용자입니다\n";
        cout << "평점을 등록하고 싶은 사용자의 id를 알려주세요\n";
        cin >> userId;
    }

    cout << "영화의 평점을 입력해주세요\n";
    cin >> score;

    m.addRating(userId, movieId, score);
}

// 8. 영화별 평점 보기
void getRatingsofMovie(Manager& m) {
    string movieName;  // 영화 제목
    Movie* movie;      // 영화 객체

    cout << "평점 목록을 확인하고 싶은 영화 이름을 입력해주세요(종료 : -1)\n";
    cin.ignore();
    getline(cin, movieName);

    if(movieName == "-1") {
        return;
    }

    movie = m.findMovieByTitle(movieName);

    while(movie == NULL) {
        cout << "등록되지 않은 영화입니다\n";
        cout << "평점 목록을 확인하고 싶은 영화 이름을 입력해주세요(종료 : "
                "-1)\n";
        getline(cin, movieName);

        if(movieName == "-1") {
            return;
        }

        movie = m.findMovieByTitle(movieName);
    }

    std::vector<Rating> ratingList = m.getRatingsofMovie(*movie);

    cout << movie->getTitle() << " 의 평점 목록입니다.\n";

    for(Rating& r : ratingList) {
        cout << r << std::endl;
    }
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
