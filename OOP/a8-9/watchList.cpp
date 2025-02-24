#include "watchList.h"

WatchList::WatchList()
{
    this->current = 0;
}

void WatchList::add(Movie* mv)
{
    this->movie.push_back(mv);
}

void WatchList::deleteMovie(Movie* mv)
{
    int pos = findMovie(mv);
    if (pos != -1)
    {
        delete this->movie[pos];
        this->movie.erase(movie.begin() + pos);
        //reloadFile();
    }
    else
        std::cout << "Movie not in your WatchList!\n";
}

int WatchList::findMovie(Movie* mv)
{
    for (int i = 0; i < this->movie.size(); i++)
    {
        if (this->movie[i]->getTitle() == mv->getTitle() && this->movie[i]->getGenre() == mv->getGenre() && this->movie[i]->getYear() == mv->getYear())
            return i;
        std::cout<<"\n";
    }
    return -1;
}

Movie* WatchList::findMovieByInformation(std::string title, std::string genre, int year)
{
    for(auto mv: movie)
        if(mv->getTitle() == title && mv->getYear() == year && mv->getGenre() == genre)
            return mv;
    Movie* mv;
}

Movie* WatchList::getCurrentMovie()
{
    return this->movie.at(this->current);
}

void WatchList::play()
{
    if (this->movie.size() == 0)
        return;
    Movie* currentMovie = this->getCurrentMovie();
    //currentMovie->playTrailer();
}

void WatchList::next()
{
    if (this->current + 1 == this->movie.size())
    {
        this->current = 0;
        return;
    }
    this->current++;
}

bool WatchList::isEmpty()
{
    return this->movie.size() == 0;
}

void WatchList::saveToCSV(std::string fileName, Movie* mv)
{
    std::ofstream file;
    file.open(fileName, std::ios_base::app);
    file << mv->getTitle() << ',' << mv->getGenre() << ',' << std::to_string(mv->getYear()) << ',' << std::to_string(mv->getLikes()) << ',' << mv->getTrailer() << '\n';
    file.close();

}

void WatchList::openCSV(std::string filePath)
{
    std::ifstream file(filePath);
    if (file.good())
    {
        file.close();
        std::string command = "start excel \"" + filePath + "\"";
        system(command.c_str());
    } else {
        std::cerr << "File does not exist or could not be opened: " << filePath << std::endl;
    }
}

void WatchList::reloadFile()
{
    std::ofstream file;
    file.open("movie.csv");
    for(auto mv : this->movie)
        file << mv->getTitle() << ',' << mv->getGenre() << ',' << std::to_string(mv->getYear()) << ',' << std::to_string(mv->getLikes()) << ',' << mv->getTrailer() << '\n';
    file.close();
}

