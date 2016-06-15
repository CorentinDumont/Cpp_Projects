#include "plateau.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Plateau plateau;
    plateau.setGeometry(300, 100, 50, 50);
    plateau.setWindowTitle("Le Jeu du Pendu Version Pokemon");
    plateau.show();
    return app.exec();
}
