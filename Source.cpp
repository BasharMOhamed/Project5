#include<iostream>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
int score = 0;
using namespace std;
using namespace sf;
struct Ghosts
{
    bool PacCollision;
    bool hasFreeChoice;
    bool OccupiedSquares[4] = { true,true,true,true };

}G1, G2, G3, G4;
Ghosts GhostStorage[] = { G1,G2,G3,G4 };
Sprite Ghost[4];
Sprite pacman;
Sprite point;
Sound EatingSound;
string rec[22] = {
        " ################### ",
        " #........#........# ",
        " #.##.###.#.###.##.# ",
        " #.................# ",
        " #.##.#.#####.#.##.# ",
        " #....#...#...#....# ",
        " ####.###.#.###.#### ",
        "    #.#...a...#.#    ",
        "    #.#.##=##.#.#    ",
        "    #...#bcd#...#    ",
        "    #.#.#####.#.#    ",
        "    #.#.......#.#    ",
        " ####.#.#####.#.#### ",
        " #........#........# ",
        " #.##.###.#.###.##.# ",
        " #..#.....P.....#..# ",
        " ##.#.#.#####.#.#.## ",
        " #....#...#...#....# ",
        " #.######.#.######.# ",
        " #.................# ",
        " ################### ",
        "                     "
};
//Array = {Right,Left,Up,Down}
int tilesize = 32;
float movespeed = 64 / tilesize;
bool walking;
int OppositeMovement[4] = {};



//Checks for squares arround the ghosts
void CheckSquares()
{
    for (int l = 0; l < 4; l++)
    {


        for (int k = 0; k < 4; k++)
        {
            if (k == 0)
            {
                int j = (Ghost[l].getPosition().x + 32) / 32, i = Ghost[l].getPosition().y / 32;

                if (rec[i][j] != '#')
                {
                    GhostStorage[l].OccupiedSquares[k] = false;
                    continue;
                }

            }
            if (k == 1)
            {
                int j = (Ghost[l].getPosition().x - 32) / 32, i = Ghost[l].getPosition().y / 32;

                if (rec[i][j] != '#')
                {
                    GhostStorage[l].OccupiedSquares[k] = false;
                    continue;
                }
            }
            if (k == 2)
            {
                int j = Ghost[l].getPosition().x / 32, i = (Ghost[l].getPosition().y - 32) / 32;
                if (rec[i][j] != '#')
                {
                    GhostStorage[l].OccupiedSquares[k] = false;
                    continue;
                }
            }
            if (k == 3)
            {
                int j = Ghost[l].getPosition().x / 32, i = (Ghost[l].getPosition().y + 32) / 32;
                if (rec[i][j] != '#')
                {
                    GhostStorage[l].OccupiedSquares[k] = false;
                    continue;
                }
            }


        }
    }
}
void eatingpoints() {
    int j = pacman.getPosition().x / 32, i = (pacman.getPosition().y) / 32;
    if (rec[i][j] == '.')
    {
        rec[i][j] = ' ';
        score++;
    }
}

bool gameover() {
    bool PacmanDead = false;
    for (int Ggg = 0; Ggg < 4; Ggg++) {
        if (pacman.getPosition().x == Ghost[Ggg].getPosition().x && pacman.getPosition().y == Ghost[Ggg].getPosition().y) {
            PacmanDead = true;
        }
    }
    return PacmanDead;
}







//pacman wins sound function

//pacman dying sound function

void main()
{

    //window
    RenderWindow window(VideoMode(672, 704), "PAC MAN");
    window.setFramerateLimit(30);

    //Sound
    SoundBuffer beginning;
    beginning.loadFromFile("C:/Users/lenovo/Downloads/pacman-beginning/pacman_beginning.wav");
    Sound Beginning;
    Beginning.setBuffer(beginning);

    SoundBuffer eatingSound;
    eatingSound.loadFromFile("C:/Users/lenovo/Downloads/pacman_chomp.wav");
    Sound EatingSound;
    EatingSound.setBuffer(eatingSound);

    SoundBuffer winsound;
    winsound.loadFromFile("C:/Users/lenovo/Documents/win.wav");
    Sound winningsound;
    winningsound.setBuffer(winsound);

    SoundBuffer lose;
    lose.loadFromFile("C:/Users/lenovo/Desktop/pacman_death.wav");
    Sound gamelose;
    gamelose.setBuffer(lose);

    









    //rectangles size
    RectangleShape Rect;
    Rect.setSize(Vector2f(32, 32));

    //textures
    Texture pac;
    Texture ghost;
    Texture menu;
    Texture Point;
    Texture win;
    win.loadFromFile("C:/Users/lenovo/Desktop/winning.jpeg");
    menu.loadFromFile("C:/Users/lenovo/Desktop/Menu1.jpg");
    pac.loadFromFile("C:/Users/lenovo/Desktop/realpac.png");
    ghost.loadFromFile("C:/Users/lenovo/Desktop/sprites.jpg");
    Point.loadFromFile("C:/Users/lenovo/Desktop/point.jpg");
    int counter = 0;


    //FONT

    Font font;
    font.loadFromFile("C:/Users/lenovo/Downloads/amatic/AmaticSC-Regular.ttf");
    Text text;
    text.setFont(font);

    text.setCharacterSize(24);

    //Sprites

    for (int i = 0; i < 4; i++) {
        Ghost[i].setTexture(ghost);
    }
    
    Ghost[0].setPosition(2 * 10 * 16, 2 * 7 * 16);
    
    Ghost[1].setPosition(2 * 9 * 16, 2 * 9 * 16);
    
    Ghost[2].setPosition(2 * 10 * 16, 2 * 9 * 16);
    
    Ghost[3].setPosition(2 * 11 * 16, 2 * 9 * 16);
    pacman.setTexture(pac);
    
    pacman.setPosition(2 * 10 * 16, 2 * 15 * 16);
    text.setPosition(32, 672);
    Rect.setFillColor(Color::Blue);
    Sprite winning;
    winning.setTexture(win);
    Sprite Menu;
    Menu.setTexture(menu);
    Sprite point;

    point.setTexture(Point);


    //Scales
    Menu.setScale(1.68, 2.346);
    winning.setScale(1.493333333333333, 2.270967741935484);
    pacman.setScale(1.5, 1.5);
    point.setScale(0.75, 0.75);
    for (int i = 0; i < 4; i++)
    {
        Ghost[i].setScale(1.523809523809524, 1.560975609756098);
    }
    bool intialmovement = true;

    //animation
    pacman.setTextureRect(IntRect(4, 6, 12, 12));
    Ghost[0].setTextureRect(IntRect(0, 0, 64, 64));
    Ghost[1].setTextureRect(IntRect(0, 20.5, 21, 20.5));
    Ghost[2].setTextureRect(IntRect(0, 41, 21, 20.5));
    Ghost[3].setTextureRect(IntRect(0, 61.5, 21, 20.5));
    int pacanimation = 0;
    int pacy = 0;
    int ghostanmi = 0;


    //Music Playing
    Beginning.play();


    //Collision
    FloatRect nextPos;


    //Gameloop
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();


            CheckSquares();
            //CheckSquares Function Beta Test
            /* for (int v = 0; v < 4; v++)
             {


                 for (int n = 0; n < 4; n++)
                 {
                     if (GhostStorage[v].OccupiedSquares[n] == true)
                     {
                         cout << 't';
                     }
                     else
                     {
                         cout << 'f';
                     }
                 }
                 cout << v << endl;
             }*/
            walking = false;


            int xcurr, leftnext, rightnext, ycurr, upnext, downnext;
            bool canMoveUp = true, canMoveDown = true, canMoveRight = true, canMoveLeft = true;
            leftnext = (pacman.getPosition().x - 32) / 32;
            xcurr = (pacman.getPosition().x) / 32;
            rightnext = (pacman.getPosition().x + 32) / 32;
            upnext = (pacman.getPosition().y - 32) / 32;
            ycurr = (pacman.getPosition().y) / 32;
            downnext = (pacman.getPosition().y + 32) / 32;
            if (rec[ycurr][leftnext] == '#')
            {
                canMoveLeft = false;
            }
            if (rec[ycurr][rightnext] == '#')
            {
                canMoveRight = false;
            }
            if (rec[upnext][xcurr] == '#')
            {
                canMoveUp = false;
            }
            if (rec[downnext][xcurr] == '#')
            {
                canMoveDown = false;
            }
            //cout << "Left Pos " << leftnext << endl << "Right Pos" << rightnext << endl << "Up Pos" << upnext << endl << "Down Pos " << downnext << endl;
            //cout << "Left " << canMoveLeft << endl << "Right " << canMoveRight << endl << "Up " << canMoveUp << endl << "Down " << canMoveDown << endl <<"endddddd\n";
            if ((Keyboard::isKeyPressed(Keyboard::A)) && canMoveLeft == true) {


                pacman.move(-16, 0);


                pacanimation++;
                pacy = 0;
                ghostanmi = 5;

            }

            else if ((Keyboard::isKeyPressed(Keyboard::D)) && canMoveRight == true) {


                pacman.move(16, 0);


                pacman.setOrigin(0, 0);

                pacanimation++;
                ghostanmi = 7;
                pacy = 1;

            }
            else  if ((Keyboard::isKeyPressed(Keyboard::W)) && canMoveUp == true) {

                pacman.move(0, -16);


                pacanimation++;
                ghostanmi = 1;
                pacy = 2;
            }
            else  if ((Keyboard::isKeyPressed(Keyboard::S)) && canMoveDown == true) {

                pacman.move(0, 16);


                pacanimation++;
                ghostanmi = 3;
                pacy = 3;
            }



        }

        int xpos = pacman.getPosition().x;
        int ypos = pacman.getPosition().y;
        int remx = xpos % 32;
        int remy = ypos % 32;
        if (remx != 0 || remy != 0)
            pacman.setPosition(xpos - remx, ypos - remy);

        //Pacman Death
        if (gameover() == true)
        {
            counter = 2;
            gamelose.play();

        }
        //Ghost Movement
        CheckSquares();
        int GhostEmptySpace[4];
        int emptycounter = 0;
        for (int ghos = 0; ghos < 4; ghos++)
        {


            for (int Sqr = 0; Sqr < 4; Sqr++)
            {
                if (GhostStorage[ghos].OccupiedSquares[Sqr] == false)
                {
                    emptycounter++;
                }

            }
            GhostEmptySpace[ghos] = emptycounter;
        }
        int intialPosX = pacman.getPosition().x;
        int intialPosY = pacman.getPosition().y;

        if ((intialPosX == 288 || intialPosX == 352) && intialPosY == 480 && intialmovement == true)
        {
            for (int ds = 0; ds < 3; ds++)
            {
                Ghost[0].move(-32, 0);

            }

            Ghost[1].move(32, 0);
            Ghost[1].move(0, -32);
            Ghost[1].move(0, -32);
            for (int ds = 0; ds < 2; ds++)
            {
                Ghost[1].move(-32, 0);

            }

            for (int ds = 0; ds < 2; ds++)
            {
                Ghost[2].move(0, -32);
            }
            for (int ds = 0; ds < 3; ds++)
            {
                Ghost[2].move(32, 0);

            }

            Ghost[3].move(-32, 0);
            for (int ds = 0; ds < 2; ds++)
            {
                Ghost[3].move(0, -32);
            }
            for (int ds = 0; ds < 2; ds++)
            {
                Ghost[3].move(32, 0);

            }

            intialmovement = false;
            OppositeMovement[0] = 0;
            OppositeMovement[1] = 0;
            OppositeMovement[2] = 1;
            OppositeMovement[3] = 1;
        }
        CheckSquares();

        if (intialmovement == false)
        {

            rec[8][10] = '#';
            for (int G = 0; G < 4; G++)
            {
                if (emptycounter > 2)
                {
                    int Const = 0;
                    Const = 1 + rand() % 4;
                    switch (Const)
                    {
                    case 1:
                        if (GhostStorage[G].OccupiedSquares[0] == false && (0 != OppositeMovement[G]))
                        {
                            Ghost[G].move(32, 0);

                            OppositeMovement[G] = 1;
                        }
                        else
                        {
                            Const = 1 + rand() % 4;
                            continue;
                        }
                        //cout << '1' << endl;
                        break;
                    case 2:
                        if (GhostStorage[G].OccupiedSquares[1] == false && (1 != OppositeMovement[G]))
                        {
                            Ghost[G].move(-32, 0);

                            OppositeMovement[G] = 0;
                        }
                        else
                        {
                            Const = 1 + rand() % 4;
                            continue;
                        }
                        //cout << '2' << endl;
                        break;
                    case 3:
                        if (GhostStorage[G].OccupiedSquares[2] == false && (2 != OppositeMovement[G]))
                        {
                            Ghost[G].move(0, -32);

                            OppositeMovement[G] = 3;
                        }
                        else
                        {
                            Const = 1 + rand() % 4;
                            continue;
                        }
                        //cout << '3' << endl;
                        break;
                    case 4:
                        if (GhostStorage[G].OccupiedSquares[3] == false && (3 != OppositeMovement[G]))
                        {
                            Ghost[G].move(0, 32);

                            OppositeMovement[G] = 2;
                        }
                        else
                        {
                            Const = 1 + rand() % 4;
                            continue;
                        }
                        //cout << '4' << endl;
                        break;
                    default:
                        break;
                    }


                }


            }
        }




        /*for (int d = 0; d < 4; d++)
        {
            cout << GhostEmptySpace[d] << ' ' << endl;
        }*/




        //for menu:Start & Quit    WITH MOUSE
        if (Mouse::isButtonPressed(Mouse::Left)) {
            Vector2i mouseposition = Mouse::getPosition(window);
            if (mouseposition.x > 354.48 && mouseposition.x < 589.68 && mouseposition.y>192.372 && mouseposition.y < 506.736) {
                window.close();
            }
            else if (mouseposition.x > 84 && mouseposition.x < 322.56 && mouseposition.y>192.372 && mouseposition.y < 506.736) {
                counter = 1;
            }
        }
        //game over
        //gameover();

        //for eating sound && points invisible

        text.setString("SCORE: " + to_string(score));
        eatingpoints();
        if (score == 174) {
            winningsound.play();
        }
        else if (score == 175) {

            counter = 3;

        }


        //for animation
        pacman.setTextureRect(IntRect(pacanimation * 21.3, pacy * 21.5, 21.3, 21.5));
        Ghost[0].setTextureRect(IntRect(ghostanmi * 21, 0, 21, 20.5));
        Ghost[1].setTextureRect(IntRect(ghostanmi * 21, 20.5, 21, 20.5));
        Ghost[2].setTextureRect(IntRect(ghostanmi * 21, 41, 21, 20.5));
        Ghost[3].setTextureRect(IntRect(ghostanmi * 21, 61.5, 21, 20.5));

        pacanimation %= 3;
        //


        window.clear();
        if (counter == 0) {
            window.draw(Menu);

        }
        else if (counter == 1) {
            Beginning.pause();
            //drawing rectangles
            for (int i = 0; i < 21; i++)
            {
                for (int j = 0; j < 21; j++)
                {
                    if (rec[i][j] == '#')
                    {
                        window.draw(Rect);
                        Rect.setPosition(j * 32, i * 32);
                    }
                    else if (rec[i][j] == 'P')
                    {
                        window.draw(pacman);

                    }
                    else if (rec[i][j] == 'a')
                    {
                        window.draw(Ghost[0]);
                    }
                    else if (rec[i][j] == 'b')
                    {
                        window.draw(Ghost[1]);
                    }
                    else if (rec[i][j] == 'c')
                    {
                        window.draw(Ghost[2]);
                    }
                    else if (rec[i][j] == 'd')
                    {
                        window.draw(Ghost[3]);
                    }
                    else if (rec[i][j] == '.')
                    {
                        window.draw(point);
                        point.setPosition(2 * j * 16.5, 2 * i * 16.5);
                    }
                    window.draw(text);
                }
            }

        }
        else if (counter == 2)
        {
            Texture gameover;
            gameover.loadFromFile("C:/Users/lenovo/Desktop/Gameover.jpg");
            Sprite Gameover;
            Gameover.setTexture(gameover);
            Gameover.setScale(0.6227988878591288, 1.066666666666667);
            
            window.draw(Gameover);
        }
        else if (counter == 3) {
            gamelose.pause();
            window.draw(winning);
        }
        for (int Gg = 0; Gg < 4; Gg++)
        {
            GhostStorage[Gg].OccupiedSquares[0] = true;
            GhostStorage[Gg].OccupiedSquares[1] = true;
            GhostStorage[Gg].OccupiedSquares[2] = true;
            GhostStorage[Gg].OccupiedSquares[3] = true;
        }
        window.display();

    }


}