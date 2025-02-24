#pragma once
#include "repo.h"
#include "watchList.h"


class Controller
{
private:
    Repository repo;
    WatchList watchList;

public:


    Repository getRepo() const { return repo; }

    void addMovieToRepository(const std::string title, const std::string genre, const int year, const int nbLikes, const std::string trailer);
    void deleteMovieToRepository(const std::string title, const std::string genre, const int year);
    void updateMovieToRepository(const std::string title, const std::string genre, const int year, const int nbLikes, const std::string trailer);
    std::vector<Movie*> getAllMovies()  { return this->repo.getMovies(); }

    WatchList getWatchList() const { return watchList;  }
    void addMovieToWatchList(std::string fileName, Movie* mv);
    void deleteMovieFromWatchList(const std::string title, const std::string genre, const int year);

    void startWatchList();
    void nextMovieWatchList();
    WatchList filterMoviesByGenre(const std::string genre);
    void likeMovie(Movie* mv);
    void saveAllFile(std::string fileName);
    void readAllFile(std::string fileName);

    void openCSV(const std::string filePath);
};