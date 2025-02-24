#include "gui.h"

gui::gui(QWidget* parent) : QWidget(parent) {

    readFile();
    QVBoxLayout* layout = new QVBoxLayout();
    movies = new QListWidget();
    input = new QLineEdit();
    searchButton = new QPushButton("Search");
    addButton = new QPushButton("Add");
    nextButton = new QPushButton("next");
    currentMovie = new QLabel("Current Movie");

    layout->addWidget(movies);
    layout->addWidget(input);
    layout->addWidget(currentMovie);
    layout->addWidget(searchButton);
    layout->addWidget(addButton);
    layout->addWidget(nextButton);

    setLayout(layout);

    QObject::connect(searchButton, &QPushButton::clicked, this, [this]() {
        filterByGenre(input->text().toStdString());
    });

}

void gui::readFile()
{
    this->ctrl.readAllFile("movie.txt");
}

void gui::filterByGenre(std::string genre) {

    WatchList ls = this->ctrl.filterMoviesByGenre(genre);

    Movie* m = ls.getCurrentMovie();
    std::string movieText = m->getTitle() + " " + m->getGenre() + " " + std::to_string(m->getYear()) + " " + std::to_string(m->getLikes()) + " " + m->getTrailer();
    currentMovie->setText(QString::fromStdString(movieText));

    QObject::connect(addButton, &QPushButton::clicked, this, [m,ls,this]() {
        addMovieToWatchList(m);
    });

    QObject::connect(nextButton, &QPushButton::clicked, this, [ls,this]() {
        nextMovie(ls);
    });
}

void gui::addMovieToWatchList(Movie* m)
{
    QString carStr = QString::fromStdString(m->toString());
    QListWidgetItem* item = new QListWidgetItem(carStr);
    movies->addItem(item);
}

void gui::nextMovie(WatchList ls)
{
    ls.next();
    Movie* m = ls.getCurrentMovie();
    std::string movieText = m->getTitle() + " " + m->getGenre() + " " + std::to_string(m->getYear()) + " " + std::to_string(m->getLikes()) + " " + m->getTrailer();
    currentMovie->setText(QString::fromStdString(movieText));
    QObject::connect(nextButton, &QPushButton::clicked, this, [ls,this]() {
        nextMovie(ls);
    });
}



