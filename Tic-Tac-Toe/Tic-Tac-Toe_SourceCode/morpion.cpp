#include "morpion.h"
#include <QPainter>
#include <QDebug>
#include <QPainter>
#include <QObject>
#include <QSignalMapper>
#include <QTime>
#include <QProcess>
#include <QCoreApplication>


//---------------------------------------------// Constructeur et SLOTs de Morpion
Morpion::Morpion(QWidget *parent) :
    QMainWindow(parent)
{
    spinBox_Nb_joueurs = new QSpinBox(this);
    spinBox_Nb_joueurs->setObjectName(QString::fromUtf8("spinBox_Nb_joueurs"));
    spinBox_Nb_joueurs->setGeometry(QRect(500, 50, 90, 30));
    QObject::connect(spinBox_Nb_joueurs , SIGNAL(valueChanged(int)), this, SLOT(spinbox_modified(int)));
    spinBox_Nb_joueurs -> setMinimum(0);
    spinBox_Nb_joueurs -> setMaximum(2);
    spinBox_Nb_joueurs -> setValue(1);
    spinBox_Nb_joueurs -> setSuffix("  humain(s)");

    lineEdit_instruction = new QLineEdit(this);
    lineEdit_instruction->setObjectName(QString::fromUtf8("lineEdit_instruction"));
    lineEdit_instruction->setGeometry(QRect(50, 50, 350, 30));
    lineEdit_instruction->setReadOnly(true);
    lineEdit_instruction->setText("Choisissez le nombre de joueurs puis cliquez sur commencer");

    lineEdit_aide_placement = new QLineEdit(this);
    lineEdit_aide_placement->setObjectName(QString::fromUtf8("lineEdit_aide_placement"));
    lineEdit_aide_placement->setGeometry(QRect(50, 85, 350, 30));
    lineEdit_aide_placement->setReadOnly(true);
    lineEdit_aide_placement->setText("");


    victoire=false;
    egalite=false;
    pause=false;
    nombre_de_joueurs=1;
    case_a_vider.first=-1;
    case_a_vider.second=-1;
    deplacement_en_cours=false;
    srand(time(NULL));
    numero_joueur=rand()%2+1;
    if(numero_joueur==1)couleur_du_joueur=Qt::red;
    else couleur_du_joueur=Qt::blue;
    vector<couple_int> VV;
    for (int i=1;i<4;i++)
    {
        for (int j=1;j<4;j++)
        {
            VV.push_back(make_pair(i,j));
        }
    }
    vector<couple_int> VN;
    vector<couple_int> VB;
    E.push_back(VV);
    E.push_back(VN);
    E.push_back(VB);
    for(int i=0;i<8;i++)E_precedent.push_back(VN);
    nb_boucle=0;
    nb_tour=-1;

    for(int i=1;i<4;i++)
    {
        lignes_vert.push_back(make_pair(i,2));
        lignes_horiz.push_back(make_pair(2,i));
        coins_D1.push_back(make_pair(i,i));
        coins_D2.push_back(make_pair(i,4-i));
    }
    nb_lignes=0;
    nb_coins=0;

    resize(771, 611);

    ButtonWidget * temp;
    for (int i=0;i<9;i++){
        QRect rect = QRect(180+90*(i%3),120+(i/3)*90,90,91);

        temp = new ButtonWidget(i+1, this, rect);
        temp-> setGeometry(rect);
        temp-> setMyGeometry(rect);
        //        temp-> setText(QString()); On ne donne pas de nom aux boutons
        //QObject::connect(temp, SIGNAL(clicked()), this, SLOT(clic_une_case()));
        tab_pushButtons.push_back(temp);
        temp->show();
    }
    for (int i=0;i<9;i++)tab_pushButtons[i]->setEnabled(false);

    pushButton_start = new QPushButton(this);
    pushButton_start->setObjectName(QString::fromUtf8("pushButton_start"));
    pushButton_start->setGeometry(QRect(280, 440, 90, 23));
    pushButton_start->setText("Commencer");
    QObject::connect(pushButton_start, SIGNAL(clicked()), this, SLOT(start()));

    pushButton_quit = new QPushButton(this);
    pushButton_quit->setObjectName(QString::fromUtf8("pushButton_quit"));
    pushButton_quit->setGeometry(QRect(280, 500, 90, 23));
    pushButton_quit->setText("Quitter");
    QObject::connect(pushButton_quit, SIGNAL(clicked()), this, SLOT(close()));

    pushButton_restart = new QPushButton(this);
    pushButton_restart->setObjectName(QString::fromUtf8("pushButton_restart"));
    pushButton_restart->setGeometry(QRect(280, 470, 90, 23));
    pushButton_restart->setText("Recommencer");
    QObject::connect(pushButton_restart, SIGNAL(clicked()), this, SLOT(restart()));

    pushButton_pause = new QPushButton(this);
    pushButton_pause->setObjectName(QString::fromUtf8("pushButton_pause"));
    pushButton_pause->setGeometry(QRect(380, 470, 30, 23));
    pushButton_pause->setText("||");
    QObject::connect(pushButton_pause, SIGNAL(clicked()), this, SLOT(stop()));
    pushButton_pause->setEnabled(false);

    QMetaObject::connectSlotsByName(this);

    setWindowTitle("MORPION");
    show();
}

void Morpion::stop()
{
    if(pause==false)
    {
        pause=true;
    }                       // Pour pouvoir mettre en pause en mode Ordinateur vs. Ordinateur
    else
    {
        pause=false;
        placer_ordi();
    }
}

void Morpion::start()
{
    spinBox_Nb_joueurs->setEnabled(false);
    pushButton_start->setEnabled(false);
    lineEdit_aide_placement->setText("Placer un pion");
    if(nombre_de_joueurs==0 || (numero_joueur==2 && nombre_de_joueurs==1))
    {
        QString q="Tour de l'ordi ";
        if(couleur_du_joueur==Qt::blue)q=q+"bleu";
        else q=q+"rouge";
        lineEdit_instruction->setText(q);
        if(nombre_de_joueurs==0)pushButton_pause->setEnabled(true);
        placer_ordi();
    }
    else
    {
        QString q="Tour du joueur ";
        if(couleur_du_joueur==Qt::blue)q=q+"bleu";
        else q=q+"rouge";
        lineEdit_instruction->setText(q);
        for (int i=0;i<9;i++)tab_pushButtons[i]->setEnabled(true);
    }
}

//------------------// Un peu le même rôle que le constructeur, remise à zéro des variables.
void Morpion::restart()
{
    pushButton_pause->setEnabled(false);
    lineEdit_instruction->setText("Choisissez le nombre de joueurs puis cliquez sur commencer");
    lineEdit_aide_placement->setText("");
    victoire=false;
    egalite=false;
    pause=false;
    nombre_de_joueurs=1;
    case_a_vider.first=-1;
    case_a_vider.second=-1;
    deplacement_en_cours=false;
    srand(time(NULL));
    numero_joueur=rand()%2+1;
    if(numero_joueur==1)couleur_du_joueur=Qt::red;
    else couleur_du_joueur=Qt::blue;
    vector<couple_int> VV;
    for (int i=1;i<4;i++)
    {
        for (int j=1;j<4;j++)
        {
            VV.push_back(make_pair(i,j));
        }
    }
    vector<couple_int> VN;
    vector<couple_int> VB;
    E.pop_back();
    E.pop_back();
    E.pop_back();
    E.push_back(VV);
    E.push_back(VN);
    E.push_back(VB);
    for(int i=0;i<8;i++)E_precedent.pop_back();
    for(int i=0;i<8;i++)E_precedent.push_back(VN);
    nb_boucle=0;
    nb_tour=-1;
    nb_lignes=0;
    nb_coins=0;
    spinBox_Nb_joueurs->setEnabled(true);
    spinBox_Nb_joueurs -> setValue(1);
    for(int i=0; i<9; i++)
    {
        tab_pushButtons[i]->changercouleur(Qt::gray);
        tab_pushButtons[i]->setEnabled(false);
        tab_pushButtons[i]->victoire(false);
    }
    pushButton_start->setEnabled(true);
}

//----------------------------------------// Pour faire choisir le nombre de joueurs à l'utilisateur
void Morpion::spinbox_modified(int val)
{
    nombre_de_joueurs=val;
}

//-----------------------------------------------------// Ce qui se passe quand on clique sur une case
void Morpion::clic_une_case(const int & val)
{
    if(deplacement_en_cours==false)
    {
        placer_joueur(val);
    }
    else retirer_joueur(val);
}

//--------------------------------------------// Destructeur de Morpion
Morpion::~Morpion()
{
    //   a completer
    delete(spinBox_Nb_joueurs);
    delete(lineEdit_instruction);
    delete(pushButton_quit);
    delete(pushButton_restart);
    delete(pushButton_start);
    for(int i=0; i<tab_pushButtons.size(); i++)delete(tab_pushButtons[i]);
}

//----------------
/*
void Morpion::clic_une_case()
{
    qDebug () <<  "Morpion:: clic_une_case : Une case cliquee ";
    QPushButton *bouton_cliked = (QPushButton *) QObject::sender ();// ptr valide seulement dans ce slot
    if (bouton_cliked){
        qDebug () <<  "Morpion:: clic_une_case : La case cliquee " ;
    }
}
*/
//--------------------------------------------------//
//---------------------------------

ButtonWidget::ButtonWidget(int num, QWidget *parent,  QRect rect)
//: QWidget(parent)  Voir setparent
{
    // TRACE : qDebug() << "Creation de bouton "<< rect;
    setParent(parent);
    victory=false;
    my_number=num;
    my_color=Qt::gray;
    signalMapper = new QSignalMapper(this);

    setGeometry(rect);
    connect(this, SIGNAL(clicked()), signalMapper, SLOT(map()));
    signalMapper->setMapping(this, num);


    connect(signalMapper, SIGNAL(mapped(const int &)), this, SIGNAL(clicked(const int &)));

    // IMPORTANT  Et je connecte au SLOT clic_une_case de la forme principale
    connect(this, SIGNAL(clicked(const int &)), parent, SLOT(clic_une_case(const int &)));
    show();

}
//---------------------------------------

void ButtonWidget::paintEvent(QPaintEvent *e)
{
    /* Initialisation du QPainter pour faire un rectangle rouge (pour l'exemple)*/
    QPainter p(this);
    p.setPen(QColor(255, 0, 0)); //DÃ©finition de la couleur du tracÃ©

    // ZZZ : dessiner le rectangle qui simule le bouton (car le bouton n'a pas de nom !) se positionne p/r  au bouton lui mm

    QRect tmp_rect=QRect(5,2,width() - 6, height() -5);
    QLinearGradient gradient(tmp_rect.topLeft(), tmp_rect.bottomRight());
    gradient.setColorAt(0, Qt::white);

    //QString s;
    //s = s.number(my_number);
    //p.drawText(10,15,s);
    if(victory)
    {
        p.setPen(Qt::green);
        gradient.setColorAt(1, Qt::green);
    }
    else
    {
        p.setPen(my_color);
        gradient.setColorAt(1, my_color);
    }
    p.fillRect(tmp_rect, gradient);         //On marque les cases jouées par des dégradés de couleur
    p.drawRect(tmp_rect);

    update();
}

//---------

void ButtonWidget::setMyGeometry(QRect rect)
{
    myRect=rect;
}


//-----------------------------------------------------------// Fonction pour appliquer des changements aux boutons depuis des fonctions de Morpion
void ButtonWidget::changercouleur(QColor couleur)
{
    my_color=couleur;
}

void ButtonWidget::victoire(bool b)
{
    victory=b;
}


//------------------------------------------------// Les fonctions qui gèrent les phases de jeu en fonction de la nature du joueur (humain ou ordinateur).
void Morpion::placer_joueur(int val)
{
    int x=(val-1)/3+1;
    int y=val-3*((val-1)/3);
    if(chercher_couple(E[0],make_pair(x,y)).first)
    {
        if(case_a_vider.first!=-1)      //-----------// Si il y avait une case à vider (si on déplace) on la vide
        {
            E[0].push_back(make_pair(case_a_vider.first, case_a_vider.second));
            case_a_vider.first=-1;
            case_a_vider.second=-1;
        }
        colorer(val);
        E[numero_joueur].push_back(make_pair(x,y));
        retirer(0, chercher_couple(E[0],make_pair(x,y)).second);
        check();
        if(deplacement_en_cours)lineEdit_aide_placement->setText("Retirez un pion");
        else lineEdit_aide_placement->setText("Placer un pion");
        //afficher(E);
        if(nombre_de_joueurs==1 && victoire==false)     // Y a-t-il victoire, égalité, le joueur suivant est-il un ordinateur?, un joueur?
        {
            QString q="Tour de l'ordi ";
            if(couleur_du_joueur==Qt::blue)q=q+"bleu";
            else q=q+"rouge";
            lineEdit_instruction->setText(q);
            for (int i=0;i<9;i++)tab_pushButtons[i]->setEnabled(false);
            placer_ordi();
        }
        else
        {
            if(victoire)
            {
                QString q="Victoire du joueur ";
                if(couleur_du_joueur==Qt::blue)q=q+"rouge";
                else q=q+"bleu";
                lineEdit_instruction->setText(q);
                lineEdit_aide_placement->setText("");
            }
            else
            {
                if(egalite)
                {
                    lineEdit_instruction->setText("Egalité");
                    lineEdit_aide_placement->setText("");
                }
                else
                {
                    QString q="Tour du joueur ";
                    if(couleur_du_joueur==Qt::blue)q=q+"bleu";
                    else q=q+"rouge";
                    lineEdit_instruction->setText(q);
                }
            }
        }
    }
}

void Morpion::retirer_joueur(int val)
{
    int x=(val-1)/3+1;
    int y=val-3*((val-1)/3);
    if(chercher_couple(E[numero_joueur],make_pair(x,y)).first)
    {
        colorer(val);
        retirer(numero_joueur, chercher_couple(E[numero_joueur],make_pair(x,y)).second);
        case_a_vider.first=x;       // On ne vide pas la case tout de suite pour empêcher de rejouer au même endroit (ça ne serait pas un déplacement)
        case_a_vider.second=y;
        deplacement_en_cours=false;
        lineEdit_aide_placement->setText("Placer un pion");
    }
    //afficher(E);
}

void Morpion::placer_ordi()
{
    if(this->isVisible()==false || egalite || pause)
    {
        if(egalite)
        {
            lineEdit_instruction->setText("Egalité");
            lineEdit_aide_placement->setText("");
        }
    }
    else
    {
        pushButton_restart->setEnabled(false);
        if(deplacement_en_cours)retirer_ordi();
        else
        {
            //montrer_valeurs(0);
            delay(1);
            vector<couple_int> vect_vide;
            vect_egal=vect_vide;
            vect_egal.push_back(E[0][0]);
            float valeur_indice_vide=valeur(0, 0);
            float valeur_buff;
            for(unsigned int i=1; i<E[0].size(); i++)
            {
                valeur_buff=valeur(0, i);
                if(valeur_buff>valeur_indice_vide)      //--------// Choisi intelligemment la case à remplir
                {
                    vect_egal=vect_vide;
                    vect_egal.push_back(E[0][i]);
                    valeur_indice_vide=valeur_buff;
                }
                else
                {
                    if(valeur_buff==valeur_indice_vide)vect_egal.push_back(E[0][i]);
                }
            }
            int indice_vide;
            int x;
            int y;
            if(chercher_couple(vect_egal, make_pair(2,2)).first)        //--------------// En cas d'égalité dans la fonction d'évaluation, critères suplémentaires : on joue de préférence au milieu ou dans les coins
            {
                indice_vide=chercher_couple(vect_egal, make_pair(2,2)).second;
                x=2;
                y=2;
            }
            else
            {
                vector<couple_int> v;
                v.push_back(make_pair(1,1));
                v.push_back(make_pair(1,3));
                v.push_back(make_pair(3,1));
                v.push_back(make_pair(3,3));
                srand(time(NULL));
                int i=rand()%4;
                bool trouve=false;
                for(int j=0;j<4;j++)
                {
                    if(trouve==false)
                    {
                        if(chercher_couple(vect_egal, v[i]).first)
                        {
                            indice_vide=chercher_couple(vect_egal, v[i]).second;
                            x=v[i].first;
                            y=v[i].second;
                            trouve=true;
                        }
                        if(i<3)i++;
                        else i=0;
                    }
                }
                if(trouve==false)
                {
                    srand(time(NULL));
                    indice_vide=rand()%vect_egal.size();
                    x=vect_egal[indice_vide].first;
                    y=vect_egal[indice_vide].second;
                }
            }
            int val=3*(x-1)+y;
            if(case_a_vider.first!=-1)          // Si il y avait une case à vider depuis retirer_ordi, on la vide
            {
                E[0].push_back(make_pair(case_a_vider.first, case_a_vider.second));
                case_a_vider.first=-1;
                case_a_vider.second=-1;
            }
            colorer(val);
            E[numero_joueur].push_back(vect_egal[indice_vide]);
            retirer(0, chercher_couple(E[0], vect_egal[indice_vide]).second);
            check();
            if(deplacement_en_cours)lineEdit_aide_placement->setText("Retirez un pion");
            else lineEdit_aide_placement->setText("Placer un pion");
            //afficher(E);
            if(nombre_de_joueurs==0 && victoire==false)     //----------// Y a-t-il victoire, égalité, tour du suivant (humain, ordinateur?) ? On appelle les fonctions en conséquence.
            {
                QString q="Tour de l'ordi ";
                if(couleur_du_joueur==Qt::blue)q=q+"bleu";
                else q=q+"rouge";
                lineEdit_instruction->setText(q);
                placer_ordi();
            }
            else
            {
                if(victoire)
                {
                    QString q="Victoire de l'ordi ";
                    if(couleur_du_joueur==Qt::blue)q=q+"rouge";
                    else q=q+"bleu";
                    lineEdit_instruction->setText(q);
                    lineEdit_aide_placement->setText("");
                }
                else
                {
                    QString q="Tour du joueur ";
                    if(couleur_du_joueur==Qt::blue)q=q+"bleu";
                    else q=q+"rouge";
                    lineEdit_instruction->setText(q);
                }
            }
        }
        for (int i=0;i<9;i++)tab_pushButtons[i]->setEnabled(true);      //On re-permet au joueur humain de jouer
        pushButton_restart->setEnabled(true);
    }
}

void Morpion::retirer_ordi()
{
    //montrer_valeurs(numero_joueur);
    delay(1);
    vector<couple_int> vect_vide;
    vect_egal=vect_vide;
    vect_egal.push_back(E[numero_joueur][0]);

    float valeur_indice_couleur=valeur(numero_joueur, 0);
    float valeur_buff;
    for(unsigned int i=1; i<E[numero_joueur].size(); i++)
    {
        valeur_buff=valeur(numero_joueur, i);
        if(valeur_buff<valeur_indice_couleur)       //--------// On choisit la case la moins importante (fonction d'évaluation minimale), pour l'enlever (pour le déplacement)
        {
            vect_egal=vect_vide;
            vect_egal.push_back(E[numero_joueur][i]);
            valeur_indice_couleur=valeur_buff;
        }
        else
        {
            if(valeur_buff==valeur_indice_couleur)vect_egal.push_back(E[numero_joueur][i]);
        }
    }
    srand(time(NULL));
    int indice_couleur=rand()%vect_egal.size();
    int x=vect_egal[indice_couleur].first;
    int y=vect_egal[indice_couleur].second;
    int val=3*(x-1)+y;
    colorer(val);
    retirer(numero_joueur, chercher_couple(E[numero_joueur], vect_egal[indice_couleur]).second);
    case_a_vider.first=x;           //-------------// On ne vide pas la case tout de suite, ainsi, on ne risque pas de rejouer au même endroit lorsqu'on déplace le pion.
    case_a_vider.second=y;
    deplacement_en_cours=false;
    lineEdit_aide_placement->setText("Placer un pion");
    placer_ordi();
    //afficher(E);
}


//-----------------------------------------------// La fonction d'évaluation
float Morpion::valeur(int a, unsigned int i)
{
    int L1=0,L2=0,C1=0,C2=0,D1=0,D2=0;
    int x=E[a][i].first;
    int y=E[a][i].second;
    //-------------------------------// Calcul des variables :
    if (E[1].size()==0){}
    else
    {
        for(unsigned int j=0; j<E[1].size(); j++)
        {
            if(a!=1 || j!=i)
            {
                if(E[1][j].first==x)L1++;
                if(E[1][j].second==y)C1++;
                if((x==1 && y==2) || (x==2 && y==1) || (x==2 && y==3) || (x==3 && y==2)){}
                else {if((abs(E[1][j].first-x)==1 && abs(E[1][j].second-y)==1) || (abs(E[1][j].first-x)==2 && abs(E[1][j].second-y)==2))D1++;}
            }
        }
    }
    if (E[2].size()==0){}
    else
    {
        for(unsigned int j=0; j<E[2].size(); j++)
        {
            if(a!=2 || j!=i)
            {
                if(E[2][j].first==x)L2++;
                if(E[2][j].second==y)C2++;
                if((x==1 && y==2) || (x==2 && y==1) || (x==2 && y==3) || (x==3 && y==2)){}
                else {if((abs(E[2][j].first-x)==1 && abs(E[2][j].second-y)==1) || (abs(E[2][j].first-x)==2 && abs(E[2][j].second-y)==2))D2++;}
            }
        }
    }
    float result=((L1-L2)*(L1-L2)+(C1-C2)*(C1-C2)+(D1-D2)*(D1-D2));

    //-----------------------------------------------------------------------// Pour favoriser le fait de gagner plutôt que de faire perdre l'autre (la fonction étant symétrique)
    if(numero_joueur==1 && (L1==2 || C1==2 || D1==2))
    {
        if(a==0)return result+0.5;
        else return result-0.5;
    }
    if(numero_joueur==2 && (L2==2 || C2==2 || D2==2))
    {
        if(a==0)return result+0.5;
        else return result-0.5;
    }
    return result;
}


//----------------------------------------// Les fonctions pour voir les victoires, faire les changements de phase de jeu...
bool Morpion::gagner()
{
    if(E[numero_joueur].size()==3)
    {
        if((E[numero_joueur][0].first==E[numero_joueur][1].first && E[numero_joueur][0].first==E[numero_joueur][2].first) || (E[numero_joueur][0].second==E[numero_joueur][1].second && E[numero_joueur][0].second==E[numero_joueur][2].second) || (chercher_couple(E[numero_joueur], make_pair(1,1)).first && chercher_couple(E[numero_joueur], make_pair(2,2)).first && chercher_couple(E[numero_joueur], make_pair(3,3)).first) || (chercher_couple(E[numero_joueur], make_pair(1,3)).first && chercher_couple(E[numero_joueur], make_pair(2,2)).first && chercher_couple(E[numero_joueur], make_pair(3,1)).first))
        {
            victoire=true;
            return true;
        }
        else return false;
    }
    else return false;
}

void Morpion::check()
{
    // On teste d'abord si il y a égalité :
    //      Pour cela, soit les joueurs tourne en rond (on sauvegarde les 4 états précedents et on teste si on repasse par ces états) : c'est le travail de E_precedent et nb_boucle
    //                 soit le nombre de tours a dépassé un seuil : c'est le travail de nb_tour
    //                 soit on est passé plusieurs fois par des situations remarquables (les cases vides forment une diagonale ou une ligne passant par le centre) : c'est le travail de lignes_vert, lignes_horiz, coins_D1, coins_D2, nb_lignes et nb_coins.
    nb_tour++;
    if(pseudo_egalite_vect(E[1],E_precedent[2*(nb_tour%4)]) && pseudo_egalite_vect(E[2],E_precedent[2*(nb_tour%4)+1]))nb_boucle++;
    else nb_boucle=0;
    E_precedent[2*(nb_tour%4)]=E[1];
    E_precedent[2*(nb_tour%4)+1]=E[2];
    if(pseudo_egalite_vect(E[0],lignes_vert) || pseudo_egalite_vect(E[0],lignes_horiz))nb_lignes++;
    if(pseudo_egalite_vect(E[0],coins_D1) || pseudo_egalite_vect(E[0],coins_D2))nb_coins++;
    if(nb_boucle>4 || nb_tour>100 || nb_lignes>2 || nb_coins>2)
    {
        for (int i=1; i<10; i++)
        {
            egalite=true;
            tab_pushButtons[i-1]->setEnabled(false);
            if(chercher_couple(E[0],make_pair((i-1)/3+1, i-3*((i-1)/3))).first==false)tab_pushButtons[i-1]->changercouleur(Qt::black);
        }
    }

    // Puis on teste si il y a victoire d'un joueur
    if(gagner())
    {
        for (int i=0; i<9; i++)
        {
            tab_pushButtons[i]->setEnabled(false);
        }
        for (unsigned int j=0; j<E[numero_joueur].size(); j++)
        {
            tab_pushButtons[3*(E[numero_joueur][j].first-1)+E[numero_joueur][j].second-1]->victoire(true);
        }
    }
    // Enfin, on change de joueur
    if(numero_joueur==1)
    {
        numero_joueur=2;
        couleur_du_joueur=Qt::blue;
    }
    else
    {
        numero_joueur=1;
        couleur_du_joueur=Qt::red;
    }

    // Et si un joueur a 3 pions, on indique qu'il doit d'abord en retirer un avant de jouer.
    if(E[numero_joueur].size()==3)deplacement_en_cours=true;
}

void Morpion::colorer(int val)
{
    if(deplacement_en_cours)tab_pushButtons[val-1]->changercouleur(Qt::gray);
    else tab_pushButtons[val-1]->changercouleur(couleur_du_joueur);
}


//-------------------------------------------------------------------------------------// Des fonctions utiles pour le traitement des données
void Morpion::retirer (int couleur, int i)
{
    E[couleur][i]=E[couleur][E[couleur].size()-1];
    E[couleur].pop_back();                              //Retirer un élément d'un vecteur
}

pair <bool, int> chercher_couple(vector<couple_int> Vect, couple_int cple)
{
    for (unsigned int i=0 ; i< Vect.size() ; i++)
    {
        if (Vect[i].first == cple.first && Vect[i].second == cple.second)
        return make_pair(true,i) ;
    }
return make_pair(false,-1) ;        //Renvoie si l'élément est présent et où
}

bool pseudo_egalite_vect(vector<couple_int> vect1, vector<couple_int> vect2)
{
    bool b=(vect1.size()==vect2.size());
    if(b)
    {
        for (unsigned int i=0;i<vect1.size();i++)
        {
            if(chercher_couple(vect2, vect1[i]).first==false)b=false;
        }
    }
    return b;       //---------------// Les vecteurs sont pseudo-égaux si ils contiennent les mêmes éléments (mais pas forcéments dan le même ordre.
}


//----------------------------------------// Un délai pour ralentir (et voir) le jeu de l'ordinateur
void delay(int n)
{
    QTime dieTime = QTime::currentTime().addSecs(n);
    while(QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

//----------------------------------------// Pour les tests, on utilise des fonctions pour afficher ce qui se passe:
void afficher(ensemble E)
{
    if(E[0].size()>0)
    {
        for(unsigned int i=0; i<E[0].size(); i++)qDebug()<<E[0][i].first<<" "<<E[0][i].second;
    }
    qDebug()<<" ";
    if(E[1].size()>0)
    {
        for(unsigned int i=0; i<E[1].size(); i++)qDebug()<<E[1][i].first<<" "<<E[1][i].second;
    }
    qDebug()<<" ";
    if(E[2].size()>0)
    {
        for(unsigned int i=0; i<E[2].size(); i++)qDebug()<<E[2][i].first<<" "<<E[2][i].second;
    }
    qDebug()<<" ";
    qDebug()<<"--------";
    qDebug()<<" ";
}

void Morpion::montrer_valeurs(int a)
{
    vector<float> l(3,-1);
    vector< vector<float> > v(3,l);
    for(unsigned int i=0; i<E[a].size(); i++)
    {
    int L1=0,L2=0,C1=0,C2=0,D1=0,D2=0;
    int x=E[a][i].first;
    int y=E[a][i].second;
    if (E[1].size()==0){}
    else
    {
        for(unsigned int j=0; j<E[1].size(); j++)
        {
            if(a!=1 || j!=i)
            {
                if(E[1][j].first==x)L1++;
                if(E[1][j].second==y)C1++;
                if((x==1 && y==2) || (x==2 && y==1) || (x==2 && y==3) || (x==3 && y==2)){}
                else {if((abs(E[1][j].first-x)==1 && abs(E[1][j].second-y)==1) || (abs(E[1][j].first-x)==2 && abs(E[1][j].second-y)==2))D1++;}
            }
        }
    }
    if (E[2].size()==0){}
    else
    {
        for(unsigned int j=0; j<E[2].size(); j++)
        {
            if(a!=2 || j!=i)
            {
                if(E[2][j].first==x)L2++;
                if(E[2][j].second==y)C2++;
                if((x==1 && y==2) || (x==2 && y==1) || (x==2 && y==3) || (x==3 && y==2)){}
                else {if((abs(E[2][j].first-x)==1 && abs(E[2][j].second-y)==1) || (abs(E[2][j].first-x)==2 && abs(E[2][j].second-y)==2))D2++;}
            }
        }
    }
    float result=((L1-L2)*(L1-L2)+(C1-C2)*(C1-C2)+(D1-D2)*(D1-D2));
    if(numero_joueur==1 && (L1==2 || C1==2 || D1==2))result+=0.5;
    if(numero_joueur==2 && (L2==2 || C2==2 || D2==2))result+=0.5;
    v[x-1][y-1]=result;
    }
    for(int i=0;i<3;i++)
    {
        qDebug()<<v[i][0]<<" "<<v[i][1]<<" "<<v[i][2];
        qDebug()<<" ";
    }
    qDebug()<<" ";
    qDebug()<<"-----------------";
    qDebug()<<" ";
}
