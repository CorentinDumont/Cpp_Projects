#ifndef ZONEDESSIN_H
#define ZONEDESSIN_H

#include <iostream>

#include <QWidget>
#include <QLabel>

using namespace std;

// Class used to display images (corresponding the the number of misses of the player
class ZoneDessin : public QWidget
{
    Q_OBJECT
private:
    int cpt;
    vector<string> formes;
    QLabel* label;
public:
    explicit ZoneDessin(QWidget *parent = 0);
    int getcpt();
    void ajoutforme(string);
    QLabel* getlabel();
    void recommencerzd();
    void cptfin();
signals:
public slots:
    void incCpt ();
    void initCpt ();
};

#endif // ZONEDESSIN_H
