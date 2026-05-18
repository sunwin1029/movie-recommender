#pragma once

#include <string>

#include "Manager.h"

void program(Manager& m);
void execute(int menu, Manager& m);
void printMenu();

void addMovie(Manager& m);
void findMovieByTitle(Manager& m);
void printAllMovies(Manager& m);
void printSortedMovies(Manager& m);
void addUser(Manager& m);
void printUsers(Manager& m);
void addRating(Manager& m);
void printRatingsOfMovie(Manager& m);
int getInteger(const std::string& warningMessage,
               const std::string& stringRequireMessage);
