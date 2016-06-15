#include "plateau.h"

Plateau::Plateau(QWidget *parent) :
    QWidget(parent)
{
    NbManque=0;
    string sc1="score= ";
    string sc2="score= ";
    sc.push_back(sc1);
    sc.push_back(sc2);
    scint.push_back(0);
    scint.push_back(0);
    nbjoue.push_back(0);
    nbjoue.push_back(0);
    nbjoue.push_back(0);
    nbjoue.push_back(0);

    // Letters buttons (keyboard)
    int i;
    int j;
    for (i=0;i<=25;i++)
    {
         boutons.push_back(new MonBouton(QString('A'+i),i));
         connect(boutons[i], SIGNAL(clicked()), boutons[i], SLOT(selection()));
         connect(boutons[i],SIGNAL(monId(int)),this,SLOT(traitement(int)));
    }
    for (i=0;i<=25;i++){boutons[i]->setEnabled(false);}

    // Player buttons
    boutons.push_back(new MonBouton(QString("Sacha"),-1));
    boutons.push_back(new MonBouton(QString("Régis"),-1));

    zoneDessin = new ZoneDessin;

    // System buttons
    // Quit
    QPushButton *quitButton = new QPushButton("Quitter");
    // End game
    QPushButton *endButton = new QPushButton("Fin de partie");
    // Restart
    QPushButton *reButton = new QPushButton("Recommencer");

    // Defines Layout
    QHBoxLayout *layoutfin = new QHBoxLayout;
    layoutfin->addWidget(endButton);
    layoutfin->addWidget(reButton);
    layoutfin->addWidget(quitButton);
    QHBoxLayout *layout0 = new QHBoxLayout;
    layout0->addWidget(boutons[26]);
    layout0->addWidget(boutons[27]);
    QLabel* score1 =  new QLabel("score = 0");
    QLabel* score2 =  new QLabel("score = 0");
    score.push_back(score1);
    score.push_back(score2);
    joueur = new QLabel("Jeu du pendu Pokemon");
    QHBoxLayout *layoutscore = new QHBoxLayout;
    layoutscore->addWidget(score1);
    layoutscore->addWidget(score2);
    joue.push_back(new QLabel("manche(s) jouée(s) = 0, dont perdue(s) = 0"));
    joue.push_back(new QLabel("manche(s) jouée(s) = 0, dont perdue(s) = 0"));
    QHBoxLayout *layoutjoue = new QHBoxLayout;
    layoutjoue->addWidget(joue[0]);
    layoutjoue->addWidget(joue[1]);
    QVBoxLayout *layout1 = new QVBoxLayout;
    layout1->addLayout(layoutfin);
    layout1->addWidget(joueur);
    QVBoxLayout *layout2 = new QVBoxLayout;
    layout2->addLayout(layout0);
    layout2->addLayout(layoutscore);
    layout2->addLayout(layoutjoue);
    layout2->addLayout(layout1);
    QHBoxLayout *layoutdessin = new QHBoxLayout;
    layoutdessin->addWidget(zoneDessin->getlabel());
    layout2->addLayout(layoutdessin);
    lmot =  new QLabel("Choisissez un dresseur");
    layout2->addWidget(lmot);
    setLayout(layout2);
    QGridLayout *l = new QGridLayout;
    for (i=0;i<=2;i++)
    {
        for (j=0;j<=6;j++)
        l->addWidget(boutons[7*i+j],i,j);
    }
    for (i=0;i<=4;i++)
    {
        l->addWidget(boutons[21+i],3,i+1);
    }
    layout2->addLayout(l);

    // Connnect the players and system buttons to their callbacks
    connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(endButton, SIGNAL(clicked()), this, SLOT(finpartie()));
    connect(reButton, SIGNAL(clicked()), this, SLOT(recommencer()));
    connect(boutons[26], SIGNAL(clicked()), this, SLOT(setplayer1()));
    connect(boutons[27], SIGNAL(clicked()), this, SLOT(setplayer2()));

    // Load the words that can be used by the game (pokemon's names)
    this->chargeMots();
    srand(time(NULL));
}

// Callbacks of keyboard's buttons
void Plateau::traitement(int j)
{
    char c='A'+j;
    vector<int> cpt;

    // check if the letter is in the word
    for (int i = 0; i<mot.size(); i++)
    {
        if (mot[i] == c)
        cpt.push_back(i);
    }
    if (cpt.size()==0)
    {
        NbManque++;
        if (NbManque==9) // Decide whether the turn of the player is finished
        {
            this->endGame(false);
        }
        else // Update the image
        zoneDessin->incCpt();
    }
    else
    {
        for (unsigned int i = 0; i<cpt.size(); i++)
        {motAffiche[cpt[i]]=c;}
        lmot->setText("Nom du Pokemon : "+motAffiche);
        if (mot==motAffiche){this->endGame(true);}
    }
}

void Plateau::newGame()
{
    int i;
    mot = this->nouveauMot();
    motAffiche=mot;
    for(i=0;i<mot.size();i++){motAffiche[i]='*';}
    lmot->setText("Nom du Pokemon : "+motAffiche);
    NbManque=0;
    zoneDessin->initCpt();
    for (i=0;i<=25;i++){boutons[i]->setEnabled(true);}

}

// Check if the turn of a player is finished
void Plateau::endGame(bool b)
{
    string s;
    string s2;
    string s3;
    char buf [10];
    char buf2 [10];
    char buf3 [10];
    int i;
    for (i=0;i<=25;i++){boutons[i]->setEnabled(false);}
    if (b==true)
    {
        lmot->setText("Nom du Pokemon : "+motAffiche+" - Bravo! Vous avez gagné!");

    }
    else
    {
        lmot->setText("Perdu! Le Pokemon était : "+mot);
        zoneDessin->incCpt();
    }
    scint[player-1]+=NbManque;
    if(NbManque==9){nbjoue[player+1]+=1;}
    itoa(NbManque,buf,10);
    sc[player-1]=sc[player-1]+buf+"+";
    s=sc[player-1];
    itoa(nbjoue[player-1],buf2,10);
    itoa(nbjoue[player+1],buf3,10);
    score[player-1]->setText(QString(s.c_str()));
    s2="manche(s) jouée(s) = ";
    s3=", dont perdue(s) = ";
    joue[player-1]->setText(QString((s2+buf2+s3+buf3).c_str()));
    boutons[26]->setEnabled(true);
    boutons[27]->setEnabled(true);
}

// Load all the words from a txt file
void Plateau::chargeMots()
{
    nbmot=0;
    ifstream f("ressources/pokemon_names.txt");
    if(f)
    {
        string s;
        while (f)
        {
        getline(f,s);
        mots.push_back(QString(s.c_str()).toUpper());
        nbmot++;
        }
        f.close();
    }
    else
    {
        cout<<"Le fichier n'a pas ete ouvert"<<endl;
        string s0="MissingNo";
        for (int i=0; i<=(nbmot-1); i++)
        {mots.push_back(QString(s0.c_str()).toUpper());}
    }
}

// Randomly load a new word
QString Plateau::nouveauMot()
{
    int x;
    for (int i=0;i<5;i++)
    {
    x = rand() % nbmot;
    }
    return mots[x];
}

void Plateau::setplayer1()
{
    nbjoue[0]+=1;
    player=1;
    joueur->setText("Tour de Sacha");
    boutons[26]->setEnabled(false);
    boutons[27]->setEnabled(false);
    this->newGame();
}

void Plateau::setplayer2()
{
    nbjoue[1]+=1;
    player=2;
    joueur->setText("Tour de Régis");
    boutons[26]->setEnabled(false);
    boutons[27]->setEnabled(false);
    this->newGame();
}

// End game, calculate the scores and display the winner's name
void Plateau::finpartie()
{
    zoneDessin->cptfin();
    joueur->setText("Partie terminée");
    for (int i=0;i<=27;i++){boutons[i]->setEnabled(false);}
    char buf [2];
    if (nbjoue[0]==0)
    {
        if (nbjoue[1]>0)
        {
            itoa(scint[1],buf,2);
            sc[1]=buf;
            score[1]->setText("score = "+QString(sc[1].c_str()));
        }
    }
    else
    {
        if (nbjoue[1]==0)
        {
            itoa(scint[0],buf,10);
            sc[0]=buf;
            score[0]->setText("score = "+QString(sc[0].c_str()));
        }
        else
        {
            itoa(scint[1],buf,10);
            sc[1]=buf;
            score[1]->setText("score = "+QString(sc[1].c_str()));
            itoa(scint[0],buf,10);
            sc[0]=buf;
            score[0]->setText("score = "+QString(sc[0].c_str()));
            if (scint[0]==scint[1])lmot->setText("Egalité entre Sacha et Régis");
            else
            {
                if (scint[0]<scint[1]){lmot->setText("Sacha a gagné");}
                else {lmot->setText("Régis a gagné");}

            }
        }
    }
    nbjoue[0]=0;
    nbjoue[1]=0;
    nbjoue[2]=0;
    nbjoue[3]=0;
    sc[0]="score = ";
    sc[1]="score = ";
}

// Restart
void Plateau::recommencer()
{
    string s="manche(s) jouée(s) = 0, dont perdue(s) = 0";
    joueur->setText("Jeu du pendu Pokemon");
    string sc1="score = 0";
    string sc2="score = 0";
    score[0]->setText(QString(sc1.c_str()));
    score[1]->setText(QString(sc2.c_str()));
    joue[0]->setText(QString(s.c_str()));
    joue[1]->setText(QString(s.c_str()));
    scint[0]=0;
    scint[1]=0;
    lmot->setText("Choisissez un dresseur");
    for (int i=0;i<=25;i++){boutons[i]->setEnabled(false);}
    for (int i=26;i<=27;i++){boutons[i]->setEnabled(true);}
    zoneDessin->recommencerzd();
}
