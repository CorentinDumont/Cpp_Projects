#include "monbouton.h"

MonBouton::MonBouton(QString c,int i):QPushButton(c)
{
    Id=i;
}
void MonBouton::selection ()
{
    this->monId(Id);
    this->setEnabled(false);
}
