#pragma once

namespace AppConstants {
constexpr int CSV_HEADER_LINE = 1;

constexpr int MIN_RELEASE_YEAR = 1888;
constexpr int MAX_RELEASE_YEAR = 2100;

constexpr double MIN_RATING_SCORE = 0.0;
constexpr double MAX_RATING_SCORE = 5.0;
constexpr double NO_RATING_AVERAGE = 0.0;

constexpr int DEFAULT_RECOMMEND_COUNT = 3;
constexpr int MAX_SIMILAR_USERS = 3;
constexpr int MIN_SIMILARITY_SCORE = 0;
constexpr double MIN_RECOMMENDABLE_RATING = 3.0;
constexpr int TOP_STATISTICS_MOVIE_COUNT = 3;

constexpr int NO_COMMON_MOVIE_SIMILARITY = -1000000000;
constexpr int COMMON_MOVIE_WEIGHT = 10;
}
