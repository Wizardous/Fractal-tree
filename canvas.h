#include<iostream>
#include<graphics.h>
#include<math.h>
using namespace std;
#define PI 3.14159265

struct Point{
    public:
        float x, y, r, _0;
        //_0 is in radians

        Point(){
            this->x = 0;
            this->y = 0;
            this->r = this->_0 = 0;
        }

        Point(float x, float y){
            this->x = x;
            this->y = y;

            this->r = sqrtf(powf(x, 2) + powf(y, 2));
            this->_0 = atan2(y, x);
        }



        void Display(){
            cout<<"\n  >X: "<<x;
            cout<<"\n  >Y: "<<y;
            cout<<"\n  >R: "<<r;
            cout<<"\n  >_0: "<<_0 * 180 / PI;       //o/p in degree
        }

        void Plot(){
            putpixel(x, y, WHITE);
        }
    
};

class SVG{
    float Xo, Yo;
    float cursorX, cursorY;
    float cursorAngle;      //stored in radian format


    Point draw_line(float length){
        Point P_new(length, 0);             //new img line of length given is created at (0,0)G
        float xb=P_new.x,
            yb=P_new.y;

        P_new.x = cursorX + (xb * cos(cursorAngle)) - (yb * sin(cursorAngle));
        P_new.y = cursorY - (xb * sin(cursorAngle)) + (yb * cos(cursorAngle));
            
        return P_new;
    }

    void draw_Axis(){
        setcolor(CYAN);
        line(Xo, 0, Xo, Yo);
        line(0, Yo, 2*Xo, Yo);
        setcolor(WHITE);
    }

    public:
        SVG(){
            cout<<"\nInitiating SVG!";
            Xo = getmaxx() / 2;
            Yo = getmaxy();

            //initializing cursor to the asumed origin of current svg
            cursorAngle = 0;
            cursorX = Xo;
            cursorY = Yo;
        }

        /*
        Move Cursor to desired location on the graph
        */
        void move_cursor(float x, float y){
            cursorX = Xo + x;
            cursorY = Yo - y;
        }

        void set_cursor(float x, float y, float _0){
            cursorX = x;
            cursorY = y;
            cursorAngle = _0;
        }

        /*
        Returns the x or y co-ordinates of cursor or angle
        */
        float getCursor(int c){        //for c={0, 1, 2} return cursor.{x, y, _0}
            switch (c){
                case 0:return cursorX;
                case 1:return cursorY;
                case 2:return cursorAngle;
            }
        }

        /*
        Rotate cursor direction in Anti-clockwise direction
        */
        void rotate_cursor(float angle){        //angles in degrees in ANTI-CLOCKWISE direction
            angle *= PI/180;                    //now angle in radian format
            cursorAngle += angle;
        }

        /*
        Draw a vector on the graph of given length
        */
        void Line(float length){
            Point P_new = draw_line(length);
            
            line(cursorX, cursorY, P_new.x, P_new.y);
            
            //move cursor to new end of line 
            cursorX = P_new.x;
            cursorY = P_new.y;

            // cout<<"\ncX: "<<cursorX - Xo;
            // cout<<"\ncY: "<<-(cursorY - Yo);
            // cout<<"\nAngle: "<<(cursorAngle*180/PI);
        }

        //Must switch off the lights before leaving...!
        ~SVG(){
            cout<<"\n\nClosing SVG!\n";
        }
};