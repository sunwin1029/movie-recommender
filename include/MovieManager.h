#pragma once
#include <map>
#include <string>
#include <vector>

#include "BaseManager.h"
#include "Movie.h"

class MovieManager : public BaseManager {
   private:
    std::vector<Movie> movies;

   public:
    MovieManager();

    void addMovie(int id, const std::string& title, const std::string& genre,
                  int year);

    Movie* findMovieById(int id);
    Movie* findMovieByTitle(const std::string& title);

    std::vector<Movie> getSortedMovies() const;
    std::vector<Movie> getTopMovies(int count) const;
    std::map<std::string, double> getAverageRatingByGenre() const;
    double getAverageRating() const;
    const std::vector<Movie>& getMovies() const;

    void printMovieList() const;
    void printMovieList(const std::vector<Movie>& movieList) const;

    void loadFromFile(const std::string& filename) override;
    void saveToFile(const std::string& filename) const override;
    int size() const override;
};
