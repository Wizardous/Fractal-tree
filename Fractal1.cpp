#include<iostream>
#include<graphics.h>
#include<math.h>
#include "./canvas.h"
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

    void frac1(float length, float angle, int itr){
        
        if(itr > 0){
            //this means there is still some hope for new branches
            
            //decide the branch color
            Decide_color(itr);

            //shrink length
            length *= 0.67;

            //taking right branch first
            Point cursor_backup(S.getCursor(0), S.getCursor(1));
            cursor_backup._0 = S.getCursor(2);

            //rotate cursor right
            S.rotate_cursor(-angle);
            S.Line(length);
            frac1(length, angle, itr-1);

            //color decision for second branch
            Decide_color(itr);

            //restore current itr's cursor backup data
            S.set_cursor(cursor_backup.x, cursor_backup.y, cursor_backup._0);
            S.rotate_cursor(angle);
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
    int itr;
    float angle, length;

    cout<<"\n>Length: ";
    cin>>length;

    cout<<">Angle: ";
    cin>>angle;

    int gd=0, gm;
    initgraph(&gd, &gm, NULL);
    getch();
    for(itr=0; itr<11; itr++){
        cleardevice();
        Fractals F;
        F.Tree(length, angle, itr);
        delay(500);
    }
    getch();
    closegraph();
    return 0;
}