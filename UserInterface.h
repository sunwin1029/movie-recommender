#pragma once

#include "Movie.h"
#include "Rating.h"
#include "User.h"
#include "Manager.h"

using namespace std;

void program(Manager& m);
void execute(int menu, Manager &m);
void printMenu();

void addMovie(Manager& m);
void findMovieByTitle(Manager& m);
void printAllMovies(Manager& m);
void printSortedMovies(Manager& m);
void addUser(Manager& m);
void printUsers(Manager& m);
void addRating(Manager& m);
void getRatingsofMovie(Manager& m);