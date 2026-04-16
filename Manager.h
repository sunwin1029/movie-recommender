#pragma once
#include <vector>
#include <iostream>
#include <algorithm>

#include "Movie.h"
#include "Rating.h"
#include "User.h"

class Manager {
   private:
    std::vector<Movie> movies;
    std::vector<Rating> ratings;
    std::vector<User> users;

   public:
    Manager();

    void addMovie(int id, const std::string& title, const std::string& genre,
                  int year);
    void addUser(int id, const std::string& name, const std::string& email);
    void addRating(int userId, int movieId, double score);

    // id 기반 객체 찾기
    Movie* findMovieById(int id);
    User* findUserById(int id);
    Rating* findRatingById(int id);

    // 제목으로 영화 찾기
    Movie* findMovieByTitle(const std::string& title);
    
    // 정렬된 영화 리스트 반환하기
    std::vector <Movie> getSortedMovies() const;
    

    void printMovieList() const;
    void printMovieList(const std::vector<Movie>& sorted) const;
    void printMoviesByRating() const;
    void printUserList() const;
    void printRatingByMovie() const;
};
