#ifndef MONBOUTON_H
#define MONBOUTON_H

#include <QPushButton>

// myButton class, to be able to pass an int when the user click on a button
class MonBouton : public QPushButton
{
    Q_OBJECT
private:
    int Id;

public:
    MonBouton(QString,int);

signals:
    void monId (int);

public slots:
    void selection ();

};

#endif // MONBOUTON_H
