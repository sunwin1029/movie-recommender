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

    void addMovie(int id, const std::string& title, const std::string& genre,
                  int year);
    void findMovie(const std::string& title);
    void addUser(int id, const std::string& name, const std::string& email);
    void addRating(int userId, int movieId, double score);

    // 제목으로 영화 찾기
    Movie* findMovieByTitle(const std::string& title);

    // 정렬된 영화 리스트 반환하기
    std::vector<Movie> getSortedMovies() const;
    std::vector<Rating> getRatingsofMovie(const Movie& movie) const;

    void printMovieList() const;
    void printMovieList(const std::vector<Movie>& sorted) const;
    void printUserList() const;
};
