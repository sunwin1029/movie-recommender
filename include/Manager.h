#pragma once
#include <string>
#include <vector>

#include "Movie.h"
#include "MovieManager.h"
#include "Rating.h"
#include "RatingManager.h"
#include "User.h"
#include "UserManager.h"

class Manager {
   private:
    MovieManager movieManager;
    RatingManager ratingManager;
    UserManager userManager;

   public:
    Manager();

    // 전체 파일들을 load/save
    void loadAll();
    void saveAll() const;

    bool addMovie(int id, const std::string& title, const std::string& genre,
                  int year);
    bool addUser(int id, const std::string& name, const std::string& email);
    bool addRating(int userId, int movieId, double score);

    // id 기반 Movie, User, Rating 객체 찾기
    Movie* findMovieById(int id);
    User* findUserById(int id);

    // 제목으로 영화 찾기
    Movie* findMovieByTitle(const std::string& title);

    // 정렬된 영화 리스트 반환하기
    std::vector<Movie> getSortedMovies() const;
    std::vector<Rating> getRatingsofMovie(const Movie& movie) const;

    void printMovieList() const;
    void printMovieList(const std::vector<Movie>& sorted) const;
    void printUserList() const;

    // CSV 파일에 저장
    void saveMoviesToFile(const std::string& filename) const;
    void saveUsersToFile(const std::string& filename) const;
    void saveRatingsToFile(const std::string& filename) const;

    // CSV 파일에서 로드
    void loadMoviesFromFile(const std::string& filename);
    void loadUsersFromFile(const std::string& filename);
    void loadRatingsFromFile(const std::string& filename);
};

