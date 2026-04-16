#pragma once
#include <vector>

#include "Movie.h"
#include "Rating.h"
#include "User.h"

class Manager {
   private:
    std::vector<Movie> movies;
    std::vector<Rating> ratings;
    std::vector<User> users;

   public:
    void addMovie(int id, const std::string& title, const std::string& genre,
                  int year);
    void addUser();
    void addRating();

    Movie* findMovieByTitle();

    void printMovieList() const;
    void printMoviesByRating() const;
    void printUserList() const;
    void printRatingByMovie() const;
};
