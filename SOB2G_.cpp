#pragma once
#include <iostream>
#include "objects.hpp"
#include<math.h>
#include<string>


using namespace sf;
using namespace std;

LinkedList<shapes_<CircleShape>*> circles_;
LinkedList<element<CircleShape>*> bullets;
LinkedList<RectangleShape> obstacles;
LinkedList<Text> texts;

Stack highscore;

RectangleShape aim(Vector2f(15, 15));

Font font;

void make_player(); 
void make_bullet();
void del_bullets(bool);
void spawn_enemy();
void aim_();
void make_obstacles();
void check_collision();
void update_texts();


int main()
{
    make_player();
    show_bullet = true;
    if (!font.loadFromFile("LASER.ttf"))
    {
        cout << "error";
    }

    while (window.isOpen())
    {
        if (life != 0)
        {
                update_texts();
                make_obstacles();
                aim_();
                spawn_enemy();

                if ((Keyboard::isKeyPressed(Keyboard::Escape)) || (sf::Mouse::isButtonPressed(sf::Mouse::Right)))
                {
                    window.close();
                }
        
                window.clear();

                n_cir = circles_.length(circles_.head);
        

                for (int i = 0; i < obstacles.length(obstacles.head); i++)
                {
                    window.draw(obstacles.get_(i));
                }

                for (int i = 0; i < n_cir; i++)
                {
                    circles_.get_(0)->move();
                    if (i != 0)
                    {
                        circles_.get_(i)->move(0);
                    }
                    window.draw(circles_.get_(i)->c1);
                }       // drawing enemies and player
                del_bullets(false);
                if ((Keyboard::isKeyPressed(Keyboard::Space)) || (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
                {
                    if (bullets.length(bullets.head) <= 0)
                    {
                        make_bullet();
                    }
                }
                if (bullets.length(bullets.head) > 0 && show_bullet)
                {
                    check_collision();
                }
                n_bullets = bullets.length(bullets.head);
                for (int i = 0; i <n_bullets; i++)
                {
                    bullets.get_(i)->check_shoot();
                }
                for (int i = 0; i < texts.length(texts.head); i++)
                {
                    window.draw(texts.get_(i));
                    
                }

     
                window.draw(aim);
                //window.clear();
        }
        else
        {
            window.clear();
            Text t;
            t.setFont(font);
            t.setCharacterSize(30);
            t.setString("GAME OVER\nPress 'SPACE' for new game");
            t.setPosition(width / 2 - 100, height / 2);
            t.setFillColor(Color::Red);
            window.draw(t);
            if ((Keyboard::isKeyPressed(Keyboard::Space)))
            {
                for (int i = 1; i < 5; i++)
                    {
                        circles_.delete_(1);
                    }
                life = 1;
                score  = 0;
                level = 2;
            }
        }
        

        window.display();
    }

    return EXIT_SUCCESS;
}

void make_player()
{
    shapes_<CircleShape>* s = new shapes_<CircleShape>(15.0, 0, 255, 0, 255, true);
    circles_.insert(s);
}

void del_bullets(bool del=false)
{
    int i, x, y;
    for (i = 0; i < bullets.length(bullets.head); i++)
    {
        Vector2f position = bullets.get_(i)->c1.getPosition();
        x = position.x;
        y = position.y;
        if ((0 > x ||  x > width || y > height || y < 0) || del)
            bullets.delete_(i);
    }
}

void make_bullet()
{
    if (bullets.length(bullets.head) < 1)
    {
        element<CircleShape>* b = new element<CircleShape>(5.0, 0, 0, 255, 255, circles_.get_(0)->pos(true) + 7.5, circles_.get_(0)->pos(false) + 7.5);
        bullets.insert(b);
    }
    del_bullets(false);
    show_bullet = true;
}

void aim_()
{
    aim.setFillColor(Color::Magenta);
    Vector2i positionm = Mouse::getPosition(window);
    Vector2f position = aim.getPosition();
    float mx = positionm.x, my = positionm.y, x = position.x, y = position.y, mag;
    aim.move(mx - x, my - y);
}

void spawn_enemy()
{
    if (circles_.length(circles_.head) <= level)
    {
        float x = 0, y = float(rand() % (height - 250));
        shapes_<CircleShape>* s = new shapes_<CircleShape>(15.0, 255, 0, 0, 255);
        s->c1.setPosition(x, y+200);
        s->enmy_ready();
        circles_.insert(s);
    }
}

void create_obs(float x, float y, float xp = diff - 15, float yp= diff - 15,int i=0)
{
    RectangleShape a(Vector2f(diff*x + 15, 15 + diff * y));
    a.setPosition(Vector2f(xp, yp-5));
    
    if (i == 1)
    {
        a.setFillColor(Color::Red);
    }
    obstacles.insert(a);
}

void make_obstacles()
{
    if (obstacles.length(obstacles.head) <= 5)
    {
        create_obs(6.2, 0);
        create_obs(0, 2.8);
        create_obs(6.2, 0, diff - 15, diff + diff * 2.8); // upper one
        create_obs(0, 1.2, diff + diff * 6.2 );
        create_obs(0, 1.153, diff + diff * 6.2, diff + diff * 1.5 + 30);
        create_obs(0, 0, g.return_xy(home_i_value, 'x') * div_, g.return_xy(home_i_value, 'y') * div_, 1);
    }
}

void check_collision()
{
    float xb, yb, xe, ye;
    
    for (int i = 1; i < circles_.length(circles_.head); i++)
    {
        Vector2f positionb = bullets.get_(0)->c1.getPosition();
        xb = positionb.x;
        yb = positionb.y;
        Vector2f position = circles_.get_(i)->c1.getPosition();
        xe = position.x;
        ye = position.y;
       

        if (abs(xb - xe) < 10 && abs(yb - ye) < 10)
        {
         /*   printf("\tBullet x: %f, y: %f\n", xb, yb);
            printf("\tEnemy x: %f, y: %f\n", xe, ye);*/
            if (circles_.get_(i)->c1.getFillColor() == Color::Red)
            {
                circles_.get_(i)->c1.setFillColor(Color::Cyan);
                
            }
            else if (circles_.get_(i)->c1.getFillColor() == Color::Cyan)
            {
                circles_.get_(i)->c1.setFillColor(Color::Yellow);
            }
            else if ((circles_.get_(i)->c1.getFillColor() == Color::Yellow))
            {
                circles_.delete_(i);
            }
            
            score++;
            if (score % 10 == 0)
            {
                level++;
            }
            if (score > highscore.top())
            {
                highscore.push(score);
            }

            show_bullet = false;
        }
    }
}

void add_text(string t,int x=0,int y=0, int size=24, int g = 0)
{
    Text text;
    text.setFont(font);
    text.setString(t);
    text.setCharacterSize(size);
    text.setFillColor(Color::Red);
    if (g == 1)
    {
        text.setFillColor(Color::Magenta);
    }
    text.setPosition(x, y);
    texts.insert(text);
}


void update_texts()
{
    if (texts.length(texts.head) < 2)
    {
        add_text("SOBG: Shooting Battlegrounds", width/2 - 200, 0, 25);
        add_text("Hint: The red ball is our enemy and it dies after you shoot it 3 times.\n\tIt turns yellow in its last life.n\n\tGame is over if any one ball reaches the red dot in top left corner of big white box.", 0, 30, 15);
        add_text("High Score :\nScore: \nPress 'Esc' to quit", width - 300, 0, 20, 1);
        add_text("", width - 100, 0, 30);
        return;
    }
    texts.delete_();

    add_text(to_string(highscore.top()) + "\n" + to_string(score), width - 100, 0, 20, 1);
}
