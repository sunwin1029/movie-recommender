#pragma once

namespace AppConstants {
// CSV 헤더를 건너뛴 뒤 실제 데이터 줄 번호를 맞추기 위한 기준값
constexpr int CSV_HEADER_LINE = 1;

// 영화 데이터 검증 범위
constexpr int MIN_RELEASE_YEAR = 1888;
constexpr int MAX_RELEASE_YEAR = 2100;

// 평점 데이터 검증 및 아직 평점이 없는 영화의 기본 평균값
constexpr double MIN_RATING_SCORE = 0.0;
constexpr double MAX_RATING_SCORE = 5.0;
constexpr double NO_RATING_AVERAGE = 0.0;

// 추천/통계 메뉴에서 사용할 기본 개수와 필터 기준
constexpr int DEFAULT_RECOMMEND_COUNT = 3;
constexpr int MAX_SIMILAR_USERS = 3;
constexpr int MIN_SIMILARITY_SCORE = 0;
constexpr double MIN_RECOMMENDABLE_RATING = 3.0;
constexpr int TOP_STATISTICS_MOVIE_COUNT = 3;

// 공통으로 본 영화가 없으면 추천 후보 계산에서 제외되도록 충분히 낮은 값을 사용한다.
constexpr int NO_COMMON_MOVIE_SIMILARITY = -1000000000;
constexpr int COMMON_MOVIE_WEIGHT = 10;
}
