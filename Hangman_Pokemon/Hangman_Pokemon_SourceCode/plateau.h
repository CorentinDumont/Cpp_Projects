#ifndef PLATEAU_H
#define PLATEAU_H

#include "zonedessin.h"
#include "monbouton.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <ctime>

#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>

// Has the role of the MainWindow of the game, handles the events (clics), and defines the position of elements
class Plateau : public QWidget
{
    Q_OBJECT
private :
    ZoneDessin *zoneDessin;
    vector<MonBouton*> boutons;
    QLabel* lmot;
    vector<QLabel*> score;
    vector<string> sc;
    vector<string> jm;
    vector<int> scint;
    vector<int> nbjoue;
    QLabel* joueur;
    vector<QLabel*> joue;
    QString mot;
    QString motAffiche;
    vector<QString> mots;
    int NbManque;
    int player;
    int nbmot;
public:
    explicit Plateau(QWidget *parent = 0);
    void endGame(bool);
    void chargeMots();
    QString nouveauMot();
public slots:
    void traitement (int);
    void newGame();
    void setplayer1();
    void setplayer2();
    void finpartie();
    void recommencer();
};

#endif // PLATEAU_H
