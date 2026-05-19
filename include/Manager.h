#pragma once
#include <string>

#include "MovieManager.h"
#include "RatingManager.h"
#include "UserManager.h"
#include "Recommender.h"

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
    void printRatingsOfMovie(int movieId);
    void recommendMovies(int userId, int amt);

    void printMovieList() const;
    void printSortedMovieList() const;
    void printUserList() const;
};
