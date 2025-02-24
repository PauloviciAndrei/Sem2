#include "controller.h"

void Controller::addMovieToRepository(const std::string title, const std::string genre, const int year, const int nbLikes, const std::string trailer)
{
    Movie* m = new Movie(title, genre, year, nbLikes, trailer);
    this->repo.addMovie(m);
    this->repo.saveFile("movie.txt", m);
}

void Controller::deleteMovieToRepository(const std::string title, const std::string genre, const int year)
{
    Movie m = Movie(title, genre, year, 0, "");
    this->repo.deleteMovie(m);
}

void Controller::updateMovieToRepository(const std::string title, const std::string genre, const int year, const int nbLikes, const std::string trailer)
{
    Movie m = Movie(title, genre, year, nbLikes, trailer);
    this->repo.updateMovie(m);
}

void Controller::addMovieToWatchList(std::string fileName, Movie* mv)
{
    this->watchList.add(mv);
    this->watchList.saveToCSV(fileName,mv);
    std::cout << mv->getTitle() << " ";
}

void Controller::deleteMovieFromWatchList(const std::string title, const std::string genre, const int year)
{
    Movie* m = new Movie(title, genre, year, 0, "");
    this->watchList.deleteMovie(m);
}

void Controller::startWatchList()
{
    this->watchList.play();
}

void Controller::nextMovieWatchList()
{
    this->watchList.next();
}

WatchList Controller::filterMoviesByGenre(const std::string genre)
{
    if (genre == "")
        return this->watchList;
    WatchList l;
    Movie* mv;
    for (int i = 0; i < this->repo.getMovies().size(); i++)
    {
        mv = this->repo.getMovies().at(i);
        if (mv->getGenre() == genre)
        {
            l.add(mv);
        }
    }
    return l;
}

void Controller::likeMovie(Movie* mv)
{

}

void Controller::readAllFile(std::string fileName)
{
    this->repo.readFile(fileName);
}

void Controller::openCSV(const std::string filePath)
{
    this->watchList.openCSV(filePath);
}
