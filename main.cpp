/*!
 * \file main.cpp
 * \brief Programme principal
 * \author Omer
 * \date 9 août 2017
 */

#define VAR_GLOBALES
#include "import.h"

#include "class/Vecteur.h"
#include "class/Physique.h"
#include "class/Animation.h"
#include "class/Camera.h"
#include "class/Personnage.h"
#include "class/Platform.h"
#include "class/Grid.h"
#include "class/Level.h"

void deplacementPersonnage(Personnage *, Level *);
void gestionClavier(Personnage *, Level *);

int main()
{
    cout << "=========================================================================" << endl;
    BLOCK = 32;
    WIDTH = 2000;
    screenHEIGHT = 600;
    screenWIDTH = 800;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Collision");
    window.setFramerateLimit(60);
    window.setPosition(sf::Vector2i(192, 0));
    //import des textures
    texture[0].loadFromFile("image/platform/png/Tiles/0.png");
    texture[1].loadFromFile("image/platform/png/Tiles/1.png");
    texture[2].loadFromFile("image/platform/png/Tiles/2.png");
    texture[3].loadFromFile("image/platform/png/Tiles/3.png");
    texture[4].loadFromFile("image/platform/png/Tiles/4.png");
    texture[5].loadFromFile("image/platform/png/Tiles/5.png");
    texture[6].loadFromFile("image/platform/png/Tiles/6.png");
    texture[7].loadFromFile("image/platform/png/Tiles/7.png");
    texture[8].loadFromFile("image/platform/png/Tiles/8.png");
    texture[9].loadFromFile("image/platform/png/Tiles/9.png");
    texture[10].loadFromFile("image/platform/png/Tiles/10.png");
    texture[11].loadFromFile("image/platform/png/Tiles/11.png");
    texture[12].loadFromFile("image/platform/png/Tiles/12.png");
    texture[13].loadFromFile("image/platform/png/Tiles/13.png");
    texture[14].loadFromFile("image/platform/png/Tiles/14.png");
    texture[15].loadFromFile("image/platform/png/Tiles/15.png");
    texture[16].loadFromFile("image/platform/png/Tiles/16.png");
    texture[17].loadFromFile("image/platform/png/Tiles/17.png");
    for(int i = 0; i < 18; i++)
        texture[i].setSmooth(true);

        //Lancement du niveau
    Level lvl;
    lvl.init();

    //Création du personnage
    Personnage a(8*BLOCK, 3*BLOCK, "image/sprite/perso1.png");
    Personnage b(9*BLOCK, 4*BLOCK, "image/sprite/perso2.png");

    //Ajout d'une gravité au personnage
    Vecteur gravity(0, 2);
    a.physique.add(gravity);
    b.physique.add(gravity);

    window.clear();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            //fermeture de la fenetre
            if (event.type == sf::Event::Closed)
                window.close();
            }
        //Positionnement de la camera
        window.setView(a.Cam());
        //positionnement du decor
        lvl.updateBackground(a.X(), a.Y());

        

        deplacementPersonnage(&a, &lvl);
        deplacementPersonnage(&b, &lvl);

        gestionClavier(&a, &lvl);
        gestionClavier(&b, &lvl);



        /*AFFICHAGE*/
        window.clear();
        window.draw(lvl.Background());
        for(int i = 0; i < lvl.NbPlatform(); i++){
           for(int j = 0; j < lvl.platform[i].n; j++)
               window.draw(lvl.platform[i].Sprite(j));
        }
        window.draw(b.Form());
        window.draw(a.Form());
        window.display();
    }

    return 0;
}

void deplacementPersonnage(Personnage * pers, Level * lvl){
    /*  DEPLACEMENT */
    Vecteur deplacement;
    deplacement = pers->physique.update();
    int dpX = deplacement.X();
    int dpY = deplacement.Y();
    while(lvl->test(pers->X()+dpX, pers->Y()+dpY) == true){
        if(dpX > 0){
            dpX--;
        }else if(dpX < 0){
            dpX++;
        }
        if(dpY > 0){
            dpY--;

        }else if(dpY < 0){
            dpY++;
        }
    }     
    pers->move(dpX, dpY);
    if(lvl->test(pers->X(), pers->Y() + 1) == true){
        pers->setVitesseY(0);
        pers->setVitesseX(0);
    }
}

void gestionClavier(Personnage * pers, Level * lvl){
    /*GESTION CLAVIER*/
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){//JUMP
        if(lvl->test(pers->X(), pers->Y() + 1) == true){
            pers->setVitesseY(-50);
        }
    }if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
        if(lvl->test(pers->X() - 5, pers->Y()) == false){
            pers->Left(5);
        }

    }if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        if(lvl->test(pers->X() + 5, pers->Y()) == false){
            pers->Right(5);
            
        }
    }
}
