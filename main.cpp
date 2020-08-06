#include <iostream>
#include <stdlib.h>

#ifdef __WIN32
#include<conio.h>
#include<windows.h>
#endif


#ifdef __linux
#include "func.hpp"
#endif

using namespace std;
bool gameover;
const int width =50;
const int height =20;
int x, y, fx, fy;
int score;
int ntail;
int tailX[100], tailY[100];
enum Direction {STOP=0, LEFT, RIGHT, UP, DOWN};
Direction dir;
void setup(){
    #ifdef __WIN32
    system("cls");
    #endif
    #ifdef __linux
    system("clear");
    #endif
    gameover = false;
    dir = STOP;
    x = width/2;
    y = height/2;
    fx = rand()%width;
    fy = rand()%height;
    score =0;
}
void draw(){
    printf("\033[0;0H");
    // cout<<"\n\n\n\n\n\n\n";
    for(int i=0; i<=width; i++)
        cout<<"H";
    cout<<endl;
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            if(j==0 || j==width-1)
                cout<<"H";
            if(i == y && j==x)
                cout<<"O";
            else if(i == fy && j == fx)
                cout<<"F";
            else{
                    bool flag = false;
                for(int k=0; k<ntail; k++){
                    if(tailX[k] == j && tailY[k] == i){
                        cout<<"o";
                        flag = true;
                    }
                }
                    if(!flag)
                        cout<<" ";
            }

        }
        cout<<endl;
    }
    for(int i=0; i<=width; i++)
        cout<<"H";
    cout<<"\n\n\n\nSCORE :   "<<score<<endl<<"LENGTH:   "<<ntail<< endl;
}
void input(){
    if(_kbhit()){
        switch(_getch()){
            case 'a' : dir = LEFT;
                    break;
            case 'l' : dir = RIGHT;
                    break;
            case 't' : dir = UP;
                    break;
            case 'b' : dir = DOWN;
                    break;
            case 'x' : gameover = true;
                    break;
        }
    }
}
void logic(){
    tailX[0] = x;
    tailY[0] = y;
    for(int i=1; i<ntail; i++){
        swap(tailX[i-1], tailX[i]);
        swap(tailY[i-1], tailY[i]);
    }
    switch(dir){
    case LEFT :
        x--;
        break;
    case RIGHT :
        x++;
        break;
    case UP :
        y--;
        break;
    case DOWN :
        y++;
        break;
    default :
        break;
    }
    if(x >width || x<0 || y>height || y<0)
        gameover = true;

    if(x >= width)
        x=0;
    else if(x<=0)
        x = width-1;
    if(y >= height)
        y = 0;
    else if(y<=0)
        y  = height-1;
    for(int i=0; i<ntail; i++)
        if(tailX[i] == x && tailY[i] == y)
        gameover = true;
    if(x == fx && y== fy){
        score +=10;
        fx = rand()%width;
        fy = rand()%height;
        ntail++;
    }
}
int main(){
    setup();
    while(!gameover){
        draw();
        input();
        logic();

        #ifdef __WIN32
        Sleep(100);
        #endif
        #ifdef __linux
        usleep(100000);
        #endif
    }
}
