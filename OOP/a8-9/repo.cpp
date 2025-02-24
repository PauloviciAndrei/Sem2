#include "repo.h"

void Repository::addMovie( Movie* mv)
{
    this->movie.push_back(mv);
}

std::vector<Movie*> Repository::getMovies()
{
    return this->movie;
}

void Repository::deleteMovie(const Movie mv)
{
    int pos = findMovie(mv.getTitle(), mv.getGenre(), mv.getYear());
    if (pos != -1)
    {
        delete this->movie[pos];
        this->movie.erase(movie.begin() + pos);
    }
    else
        std::cout << "No such movie\n";
}

void Repository::updateMovie(const Movie mv)
{
    int pos = findMovie(mv.getTitle(), mv.getGenre(), mv.getYear());
    if (pos != -1)
        this->movies.updateItem(pos, mv);
    else
        std::cout << "No such movie\n";
}

int Repository::findMovie(const std::string title, const std::string genre, const int year)
{

    for (int i = 0; i < this->movie.size(); i++)
    {

        if (this->movie[i]->getTitle() == title && this->movie[i]->getGenre() == genre && this->movie[i]->getYear() == year)
            return i;
        std::cout<< movie[i]->getTitle() << title << "\n";
        std::cout<< movie[i]->getGenre() << genre << "\n";
        std::cout<< movie[i]->getYear() << year << "\n";
        std::cout<<"\n";
    }
    return -1;
}

void Repository::readFile(std::string fileName)
{

    std::string title;
    std::string genre;
    std::string year;
    std::string nbLikes;
    std::string trailer;
    Movie* mv;
    std::ifstream file(fileName);

    if(file.is_open())
        while(getline(file,title, ','))
        {
            getline(file,genre,',');
            getline(file,year,',');
            getline(file,nbLikes,',');
            getline(file, trailer,'\n');
            mv = new Movie(title, genre, stoi(year), stoi(nbLikes), trailer);
            this->movie.push_back(mv);
        }

}

void Repository::saveFile(const std::string fileName, Movie* mv)
{
    std::ofstream file(fileName, std::ios_base::app);
    if(file.is_open())
    {
        file << mv->getTitle() << ',' << mv->getGenre() << ',' << std::to_string(mv->getYear()) << ',' << std::to_string(mv->getLikes()) << ',' << mv->getTrailer() << '\n';
    }
}

void Repository::saveCSVFIle(const std::string fileName)
{
    std::ofstream file;
    file.open(fileName);
}


