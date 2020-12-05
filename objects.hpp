#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "data_structures.hpp"

using namespace sf;

float vel = 0.5;

int height = 900, width = 1600, n_cir, n_bullets = 0, level = 2, diff = 200, div_ = 50, home_i_value = 18 * 5 + 5, life=1,score=0;
const char* name = "SOB2G";
bool show_bullet;

RenderWindow window(VideoMode(width, height), "SOB2G", Style::Default);

Graph g(width / div_, height / div_);


template <class typeofshape>
class shapes_
{
protected:
    float xp, yp, xvel, yvel, en_v = 0.8;
    const char* dir;
    bool right = false, left = false, up = false, down = false;
    LinkedList<int> path;

public:
    typeofshape c1;
    shapes_(float rad, int r, int b, int g, int alpha, bool a = false)
    {
        if (a)
        {
            this->xp = width / 2; this->yp = height / 2;
            c1.setPosition(xp, yp);
        }
        else
        {
            this->xp = this->yp = 0;
        }

        this->yvel = this->xvel = 0.0;
        c1.setRadius(rad);
        c1.setFillColor(Color::Color(r, b, g, alpha));
    }
    shapes_() {}
    void move() {
        check_key();
        checkbool();
        checkxy();
        c1.move(xvel, yvel);
    }
    void move(int jj)
    {
        if (path.length(path.head) > 0)
        {
            int n = path.get_(0);
            float mx, my, xv, yv, dx, dy, mag, x, y;

            sf::Vector2f position = c1.getPosition();

            mx = g.return_xy(n, 'x') * div_;
            my = g.return_xy(n, 'y') * div_;

            x = position.x;
            y = position.y;
           // printf("\tx: %f : %f, y: %f : %f, n: %d, length: %d\n\n", mx, x, my, y, n, path.length(path.head));

            if ( abs(x - mx) < 3 && abs(y - my) < 3)
            {
                //printf("here");
                path.delete_(0);
                return;
            }

            dx = (mx - x);
            dy = (my - y);

            mag = sqrt(pow(dx, 2) + pow(dy, 2));
            xv = dx / mag;
            yv = dy / mag;

            
            c1.move(xv * vel * en_v * level * (score*0.01 + 1) / 10, yv * vel * en_v * level * (score*0.01 + 1) / 10);
           // printf("\tx: %f, y: %f\n", x, y);
            return;
        }
        else
        {
            life = 0;
        }

    }

    void enmy_ready()
    {
        float x, y;
        sf::Vector2f position = c1.getPosition();
        x = position.x;
        y = position.y;
        g.dijkstra(g.return_i(x/div_, y/div_), home_i_value);
        //printf("here\n");
        int n = g.path.length(g.path.head);
        for (int i = 0; i < n; i++){
            this->path.insert(g.path.get_(i));
        }
        g.clear_path();
    }

    float pos(bool x_pos) {
        if (x_pos)
        {
            return this->xp;
        }
        return this->yp;
    }
    void checkxy() {
        Vector2f position = c1.getPosition();
        xp = position.x;
        yp = position.y;
       // printf("\tx: %f, y: %f\n", xp, yp);
        if (yp < diff)
        {
            yvel = vel;
            yp = diff;
        }
        else if (yp > height- diff)
        {
            yvel = -vel;
            yp = height- diff;
        }
        if (xp < diff)
        {
            xvel = vel;
            xp = diff;
        }
        else if (xp > width- diff)
        {
            xvel = -vel;
            xp = width- diff;
        }
    }
    void checkbool() {
        if (right)
        {
            xvel = vel;
        }
        if (left)
        {
            xvel = -vel;
        }
        if (up)
        {
            yvel = -vel;
        }
        if (down)
        {
            yvel = vel;
        }
        if (!(right || left))
        {
            xvel = 0;
        }
        if (!(up || down))
        {
            yvel = 0;
        }
    }
    void check_key() {
        Vector2i positionm = Mouse::getPosition(window);
        Vector2f position = c1.getPosition();
        float mx = positionm.x, my = positionm.y, x=position.x, y=position.y, diff_m=100;
      //  printf("x: %f, y: %f\n", mx, my);
        if (Keyboard::isKeyPressed(Keyboard::Right) || mx - x > diff_m)
            right = true;
        else
            right = false;
        if (Keyboard::isKeyPressed(Keyboard::Left) || mx - x < -diff_m)
            left = true;
        else
            left = false;
        if (Keyboard::isKeyPressed(Keyboard::Up) || my - y < -diff_m)
            up = true;
        else
            up = false;
        if (Keyboard::isKeyPressed(Keyboard::Down) || my - y > diff_m)
            down = true;
        else
            down = false;
    }
};


template <class typeofshape>
class element :public shapes_<typeofshape>
{
    bool check = false;
    float xv, yv, mag, f, dx, dy;
    bool checked = false;
public:
    element(float rad, int r, int b, int g, int alpha, float xp, float yp)
    {
        f = 10;
        xv = yv = 0;
        this->xp = xp;
        this->yp = yp;
        this->c1.setRadius(rad);
        this->c1.setFillColor(Color::Color(r, b, g, alpha));
        this->c1.setPosition(xp, yp);
    }

    void check_shoot()
    {
        if (show_bullet)
            window.draw(this->c1);

        if (!checked)
        {
            Vector2i positionm = Mouse::getPosition(window);
            Vector2f position = this->c1.getPosition();
            float mx = positionm.x, my = positionm.y, x = position.x, y = position.y, mag;
            dx = (mx - x);
            dy = (my - y);
            mag = sqrt(pow(dx, 2) + pow(dy, 2));
            xv = dx / mag;
            yv = dy / mag;
            checked = true;
        }
       // printf("x: %f, y: %f\n", xv, yv);
        this->c1.move(vel * xv * f, vel * yv * f);
        this->xp += vel * xv;
        this->yp += vel * yv;
    }
};
