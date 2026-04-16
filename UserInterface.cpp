#include "UserInterface.h"

// 프로그램 전체 프로세스
void program(Manager& m) {
    int menu = -1;

    while(true) {
        printMenu();
        cin >> menu;
        if(menu == 0) break;

        execute(menu);
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

            break;
        case 3:
            // 전체 목록 출력
            break;
        case 4:
            // 평점순 정렬 출력
            break;
        case 5:
            // 사용자 추가
            break;
        case 6:
            // 사용자 목록 출력
            break;
        case 7:
            // 평점 입력
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
    cout << "영화 제목을 입력하세요\n> ";
    cin >> title;
    cout << "영화 장르를 입력하세요\n> ";
    cin >> genre;
    cout << "영화 개봉년도를 입력하세요\n> ";
    cin >> year;

    m.addMovie(id, title, genre, year);
}

// 2. 제목으로 검색
void findMovieByTitle(Manager &m) {
    string title;

    cout << "찾으려는 영화 제목을 입력하세요\n> ";
    cin >> title;

    cout << m.findMovieByTitle(title);
}

// 3. 전체 목록 출력
void printAllMovies(Manager& m) {
    m.printMovieList();
}

// 4. 평점순 정렬 출력
