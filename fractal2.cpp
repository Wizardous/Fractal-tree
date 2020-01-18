//trial to create random fractals
#include<iostream>
#include<graphics.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include"./canvas.h"
using namespace std;
#define PI 3.14159265

//Fractal Class
class Fractals{
    SVG S;
    void Decide_color(int itr){
        switch (itr){
            case 1:
                setcolor(YELLOW);
                break;
            case 2:
                setcolor(LIGHTGREEN);
                break;
            case 3:
                setcolor(GREEN);
                break;
            case 4:
                setcolor(LIGHTRED);
                break;
            default:
                setcolor(BROWN);
                break;
        }
    }

    int randomizer(){
        srand(time(NULL) + rand());
        if((rand()*rand())%3 == 0){
            return rand()%20 + 1;
        }
        return -rand()%20 + 1;
    }

    void frac1(float length, float angle, int itr){

        if(itr > 0){
            int rand_val;
            
            //decide the branch color
            Decide_color(itr);

            //shrink length
            length *= 0.67;

            //taking right branch first
            Point cursor_backup(S.getCursor(0), S.getCursor(1));
            cursor_backup._0 = S.getCursor(2);

            //rotate cursor right
            rand_val = randomizer();
            S.rotate_cursor(-angle + rand_val);
            S.Line(length);
            frac1(length, angle, itr-1);

            //color decision for second branch
            Decide_color(itr);

            //restore current itr's cursor backup data
            S.set_cursor(cursor_backup.x, cursor_backup.y, cursor_backup._0);

            rand_val = randomizer();
            S.rotate_cursor(angle + rand_val);
            S.Line(length);
            frac1(length, angle, itr-1);
        }
        return;
    }

    public:

        void Tree(float length, float angle, int itr){
            //draw the root explicitly!
            setcolor(BROWN);
            S.rotate_cursor(90);
            S.Line(length);
            //following point will work as a seed...
            Point P(S.getCursor(0), S.getCursor(1));
            cout<<"\nFractals initialized!";
            frac1(length,  angle, itr);
            cout<<"\nFractals Complete!";
        }
};

int main(){
    int itr = 10, gd=0, gm=0;
    float angle=30, length;

    cout<<"\n>Length: ";
    cin>>length;

    cout<<"\n>>Branch angle set to 30 degrees!\n";

    initgraph(&gd, &gm, NULL);
    getch();    
    Fractals F;
    F.Tree(length, angle, itr);

    getch();

    closegraph();
    return 0;
}