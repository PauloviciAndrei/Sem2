#ifndef QTTEST5_GUI_H
#define QTTEST5_GUI_H

#include <QLineEdit>
#include <QList>
#include <QListWidget>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QColor>

#include "controller.h"

class gui : public QWidget {
private:
    Controller ctrl;
    QListWidget* movies;
    QLineEdit* input;
    QPushButton* searchButton;
    QPushButton* addButton;
    QPushButton* nextButton;
    QLabel* currentMovie;

public:
    gui(QWidget *parent = Q_NULLPTR);
    void readFile();
    void filterByGenre(std::string genre);
    void addMovieToWatchList(Movie* m);
    void nextMovie(WatchList ls);
};

#endif //QTTEST5_GUI_H
