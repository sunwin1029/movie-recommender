#include "UserInterface.h"

// 프로그램 전체 프로세스
void program() {
    int menu = -1;

    while(true) {
        printMenu();
        std::cin >> menu;
        if(menu == 0) break;

        execute(menu);
    }

    std::cout << "프로그램을 종료합니다!\n";
}

// 각 기능 실행 함수
void execute(int menu) {
    switch(menu) {
        case 1:
            // 영화 추가
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
            std::cout << "\n잘못된 메뉴입니다!\n";
            break;
    }
}

// 사용 설명서 출력
void printMenu() {
    std::cout << "=== Movie Recommender ===\n";

    std::cout << "[ 영화 ]\n\t1. 영화 추가\n\t2. 제목으로 검색\n\t3. 전체 목록 "
                 "출력\n\t4. 평점순 정렬 출력\n\n";

    std::cout << "[ 사용자 ]\n\t5. 사용자 추가\n\t6. 사용자 목록 출력\n\n";

    std::cout << "[ 평점 ]\n\t7. 평점 입력\n\t8. 영화별 평점 보기\n\n";

    std::cout << "\t0. 종료\n\n";

    std::cout << "선택 > ";
}