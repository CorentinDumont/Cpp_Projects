#ifndef MORPION_H
#define MORPION_H

#include <QMainWindow>
#include <QLineEdit>
#include <QString>
#include <QSignalMapper>
#include <QSpinBox>
#include <QLabel>
#include <QGridLayout>
#include <QDebug>
#include <QPushButton>
#include <QVector>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
using namespace std ;

typedef pair <int , int> couple_int ;
typedef vector< vector< int > > Grille;
typedef vector< vector< couple_int > > ensemble;

// Faut il cela ??
QT_BEGIN_NAMESPACE

class ButtonWidget;

class Morpion : public QMainWindow
{
    Q_OBJECT

public:
    explicit Morpion(QWidget *parent = 0);

    void colorer(int val);

    void placer_joueur(int val);
    void retirer_joueur(int val);   // 4 Traitements selon la nature du joueur et la phase de jeu
    void placer_ordi();
    void retirer_ordi();

    void retirer (int, int);        // Utile pour 'décolorer' une case

    float valeur(int a, unsigned int i);     // Fonction d'évaluation pour l'IA

    bool gagner();      //Vérifie les cas gagnants
    void check();       //Fait les traitements de changements de phase de jeu (ex. Changement de joueur...)

    void montrer_valeurs(int a);    //Pour les tests

    ~Morpion();


public slots :
    //void clic_une_case();
    void spinbox_modified(int);
    void clic_une_case(const int & val);
    void restart();
    void start();
    void stop();

private:
    QRect dims_zone_dessin;
    QVector<ButtonWidget *> tab_pushButtons;
    QPushButton *pushButton_quit;
    QPushButton *pushButton_restart;
    QPushButton *pushButton_start;
    QPushButton *pushButton_pause;

    QSpinBox *spinBox_Nb_joueurs;      //Pour choisir le nombre de joueurs
    int nombre_de_joueurs;

    QLineEdit *lineEdit_instruction;
    QLineEdit *lineEdit_aide_placement; //Pour donner des indications aux joueurs

    ensemble E;     //Toutes les informations sur la position des pions
    ensemble E_precedent;   //Informations sur les 4 états de jeu précédents
    int nb_tour;
    int nb_boucle;      //Pour traiter les boucle -> égalité

    vector<couple_int> lignes_vert;
    vector<couple_int> lignes_horiz;
    vector<couple_int> coins_D1;
    vector<couple_int> coins_D2;
    int nb_lignes;
    int nb_coins;

    QColor couleur_du_joueur;
    int numero_joueur;  //Pour savoir quel joueur est en train de jouer

    couple_int case_a_vider;    //Pour ne pas rejouer à l'endroit d'où l'on vient de bouger
    vector<couple_int> vect_egal;   //Pour traiter les cas d'égalité de la fonction d'évaluation

    bool deplacement_en_cours;      //Pour savoir s'il faut retirer ou placer un pion

    bool victoire;
    bool egalite;
    bool pause;     //Pour gérer les arrêts de partie
};
//--------------------
class ButtonWidget : public QPushButton
{
    Q_OBJECT

public:
    ButtonWidget(int num=0, QWidget *parent = 0, QRect rect=QRect());
    void paintEvent(QPaintEvent *event);
    void setMyGeometry(QRect rect);
    void changercouleur(QColor couleur);
    void victoire(bool b);
signals :
    void clicked(const int &val);

private:
    QSignalMapper *signalMapper;
    int my_number;
    QRect myRect;
    QColor my_color;    //Couleur du bouton
    bool victory;       //Le bouton est-il dans un alignement vainqueur?
};

pair <bool, int> chercher_couple(vector<couple_int>, couple_int);
void afficher(ensemble E);                                                      // 4 fonctions utiles pour le traitement, le test et l'affichage
bool pseudo_egalite_vect(vector<couple_int> vect1, vector<couple_int> vect2);
void delay(int);

#endif // MORPION_H
