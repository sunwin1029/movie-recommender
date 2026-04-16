#include "UserInterface.h"

// 프로그램 전체 프로세스
void program(Manager& m) {
    int menu = -1;

    printMenu();

    while(true) {
        cout << "메뉴를 선택해주세요\n";
        cin >> menu;
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
            break;
        default:
            cout << "\n잘못된 메뉴입니다!\n";
            break;
    }

    
}

// 사용 설명서 출력
void printMenu() {
    cout << "=== Movie Recommender ===\n";

    cout << "[ 영화 ]\n\t1. 영화 추가\n\t2. 제목으로 검색\n\t3. 전체 목록 "
            "출력\n\t4. 평점순 정렬 출력\n\n";

    cout << "[ 사용자 ]\n\t5. 사용자 추가\n\t6. 사용자 목록 출력\n\n";

    cout << "[ 평점 ]\n\t7. 평점 입력\n\t8. 영화별 평점 보기\n\n";

    cout << "\t0. 종료\n\n";

    cout << "선택 > ";
}

// 1. 영화 추가

void addMovie(Manager& m) {
    int id, year;
    string title, genre;

    cout << "영화 id를 입력하세요\n> ";
    cin >> id;
    cin.ignore();
    cout << "영화 제목을 입력하세요\n> ";
    getline(cin, title);
    cout << "영화 장르를 입력하세요\n> ";
    getline(cin, genre);
    cout << "영화 개봉년도를 입력하세요\n> ";
    cin >> year;

    m.addMovie(id, title, genre, year);
}

// 2. 제목으로 검색
void findMovieByTitle(Manager& m) {
    string title;

    cout << "찾으려는 영화 제목을 입력하세요\n> ";
    cin.ignore();
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

    cout << "사용자 id를 입력하세요\n> ";
    cin >> id;

    // 중복 id 방지
    while(m.findUserById(id) != NULL) {
        cout << "중복된 사용자입니다!";
        cout << "사용자 id를 입력하세요\n> ";
        cin >> id;
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
