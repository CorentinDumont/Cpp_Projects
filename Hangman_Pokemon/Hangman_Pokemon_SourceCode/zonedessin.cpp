#include "zonedessin.h"

ZoneDessin::ZoneDessin(QWidget *parent) :
    QWidget(parent)
{
    cpt=9;
    setPalette(QPalette(QColor(250, 250, 250)));
    setAutoFillBackground(true);
    setFixedSize(300,300);
    // Load all images
    formes.push_back("ressources/pendupokemon0.png");
    formes.push_back("ressources/pendupokemon1.png");
    formes.push_back("ressources/pendupokemon2.png");
    formes.push_back("ressources/pendupokemon3.png");
    formes.push_back("ressources/pendupokemon4.png");
    formes.push_back("ressources/pendupokemon5.png");
    formes.push_back("ressources/pendupokemon6.png");
    formes.push_back("ressources/pendupokemon7.png");
    formes.push_back("ressources/pendupokemon8.png");
    formes.push_back("ressources/pendupokemon9.png");
    formes.push_back("ressources/pendupokemon.png");
    label= new QLabel(this);
    label->setPixmap(QPixmap(QString(formes[10].c_str())));
}

// Get index of current image (state of the game, number of misses)
int ZoneDessin::getcpt()
{
    return cpt;
}

// Load the image corresponding to the number of misses of the player
void ZoneDessin::incCpt()
{
    if (cpt<=8)cpt++;
    label->setPixmap(QPixmap(QString(formes[cpt].c_str())));
}

// Load the first image of the game (title)
void ZoneDessin::initCpt()
{
    cpt=0;
    label->setPixmap(QPixmap(QString(formes[cpt].c_str())));
}

// Load the last image of the game (end game)
void ZoneDessin::cptfin()
{
    cpt=10;
    label->setPixmap(QPixmap(QString(formes[cpt].c_str())));
}

QLabel* ZoneDessin::getlabel()
{
    return label;
}

// restart
void ZoneDessin::recommencerzd()
{
    label->setPixmap(QPixmap(QString(formes[10].c_str())));
}
