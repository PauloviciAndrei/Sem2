#pragma once
#include <vector>
#include <fstream>
#include "movie.h"
#include <cstdlib>

class WatchList
{
private:
    std::vector<Movie*> movie;
    int current;

public:
    WatchList();

    int getSize() const { return this->movie.size(); }

    void add(Movie* mv);
    void deleteMovie(Movie* mv);

    Movie* getCurrentMovie();
    Movie*
    findMovieByInformation(std::string title, std::string genre, int year);

    void play();

    void next();

    bool isEmpty();

    void saveToCSV(std::string fileName, Movie* mv);

    void openCSV(std::string fileName);


private:
    int findMovie(Movie* mv);
    void reloadFile();
};