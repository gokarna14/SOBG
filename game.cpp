#include <SFML/Graphics.hpp>
#include<iostream>


using namespace std;
using namespace sf;

class moveplayer
{
public:
    float xpos;
    float ypos;
    float xvel;
    float yvel;
    bool carstopright;
    bool carstopup;
    movecar()
    {
        bool carstopright=true;
        bool carstopup=true;
        float xpos=0;
        float ypos=0;
        float xvel=0;
        float yvel=0;
    }
    void update(bool playerup,bool playerdown,bool playerright,bool playerleft)
    {
        if(playerright)
        {
            bool carstopright=true;
            xvel=0.3;
        }
        if(playerleft)
        {
            bool carstopright=false;
            xvel=-0.3;
        }
        if(playerup)
        {
            bool carstopup=true;
            yvel=-0.3;
        }
        if(playerdown)
        {
            bool carstopup=false;
            yvel=0.3;
        }
        if(!(playerright || playerleft))
        {
            xvel=0;
        }
        if(!(playerup || playerdown))
        {
            yvel=0;
        }
        xpos+=xvel;
        ypos+=yvel;
        /*if(xpos>95 || xpos<-95)
        {
            xvel=0;
        }*/
    }
};

int main()
{

    bool playerright,playerleft,playerup,playerdown =false;
    moveplayer p1;
    // Create the main window
    RenderWindow app(VideoMode(width, height), "DSA GAME");

    CircleShape c1(15);
    c1.setFillColor(Color::Red);

    RectangleShape rect(Vector2f(width,height));
    rect.setFillColor(Color::Cyan);

    while (app.isOpen())
    {
        // Process events
        Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == Event::Closed)
                app.close();
        }


        // Clear screen
        app.clear();
         if(Keyboard::isKeyPressed(Keyboard::Right))
            playerright=true;
        if(Keyboard::isKeyPressed(Keyboard::Left))
            playerleft=true;
        if(Keyboard::isKeyPressed(Keyboard::Up))
            playerup=true;
        if(Keyboard::isKeyPressed(Keyboard::Down))
            playerdown=true;
        if(!(Keyboard::isKeyPressed(Keyboard::Down)))
            playerdown=false;
        if(!(Keyboard::isKeyPressed(Keyboard::Up)))
            playerup=false;
        if(!(Keyboard::isKeyPressed(Keyboard::Left)))
            playerleft=false;
        if(!(Keyboard::isKeyPressed(Keyboard::Right)))
            playerright=false;
        p1.update(playerup,playerdown,playerright,playerleft);
        c1.move(Vector2f(p1.xvel,p1.yvel));
        app.draw(rect);
        app.draw(c1);
        app.display();
    }

    return EXIT_SUCCESS;
}
