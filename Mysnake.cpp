#include <iostream>
#include <conio.h>
#include <windows.h>
#include <queue>
#include <ctime>
#include<algorithm>
using namespace std;
void gotoxy(int x, int y);
void color(int n);
struct point
{
int x,y;
};
void ramka(point a)
{
       color(66);
  for(int i=0;i<=40;i++) {a.y=i;a.x=0;gotoxy(a.y,a.x); cout<<" ";a.y=i;a.x=20;gotoxy(a.y,a.x); cout<<" ";}
  for(int i=0;i<=20;i++) {a.y=0;a.x=i;gotoxy(a.y,a.x); cout<<" ";a.y=40;a.x=i;gotoxy(a.y,a.x); cout<<" ";}
}
bool chdead(queue<point> k)
{
  int n=k.size();
  if(k.size()>2)
    {
  if(k.back().x==20||k.back().x==0||k.back().y==0||k.back().y==40) return 1;//proverqva dali zmiqta se buta v stenata
        {
    for(int i=0;i<n-1;i++)
            {
      if(k.front().x==k.back().x&&k.front().y==k.back().y) return 1; //proverqva dali zmiqta se samoizqjda
      k.pop();
            }
        }
    }
  return 0;
}
bool dali(queue<point>k,int r1,int r2)
{
  while(!k.empty())
  {
      if(k.front().x==r1&&k.front().y==r2) return 1;
      else k.pop();
  }
  return 0;
}
void move(point &a,point f,queue<point> &k,char ch,int size,char z1,char &ch1,int &score)
{

 if((ch!=119&&ch!=115&&ch!=97&&ch!=100)||(ch1==115&&ch==119)||(ch1==97&&ch==100)||(ch1==119&&ch==115)||(ch1==100&&ch==97)) ch=ch1; //ne pozvolqva drugi klavishi da vliqqt na zmiqta
 if(ch==119){a.x=k.back().x-1;a.y=k.back().y;ch1=ch;}//moveup
 if(ch==115){a.x=k.back().x+1;a.y=k.back().y;ch1=ch;}//movedown
 if(ch==97){a.x=k.back().x;a.y=k.back().y-1;ch1=ch;}//moveleft
 if(ch==100){a.x=k.back().x;a.y=k.back().y+1;ch1=ch;}//moveright

k.push(a);if(!chdead(k))
  { gotoxy(k.front().y,k.front().x);
color(0);
if(k.front().x!=0)cout<<" ";
gotoxy(a.y,a.x);
color(160);
cout<<" ";
int r1=k.front().x;
int r2=k.front().y;
if((k.back().x!=f.x||k.back().y!=f.y)&&k.size()>size)//ako ne qde i ne se sintezira
k.pop();
if(k.back().x==f.x&&k.back().y==f.y)score+=1000; //uvelichava skora pri qdene
if(z1=='1') Sleep(140);//burzina
if(z1=='2') Sleep(88);
if(z1=='3') Sleep(55);
  }
else k.pop();
}
point qbuka(point &f,queue<point> k)
{
      bool z=0;
 int r1,r2;
 bool dq=1;
 r1=rand()%19+1;//x na qbuka
 r2=rand()%39+1;//y na qbuka

while(!z)
{
  if(dali(k,r1,r2))
    {
    r1=rand()%19+1;
    r2=rand()%39+1;
    }
 else z=1;

}

 f.x=r1;
 f.y=r2;
 return f;
}
void newap(queue<point> k,point &f)
{
if(k.back().x==f.x&&k.back().y==f.y)//nova qbulka
  {
      f=qbuka(f,k);
      gotoxy(f.y,f.x);
      color(176);
      cout<<" ";
      color(32);
  }
}
void delsnake(queue<point> &k)
{
  while(!k.empty())
      k.pop();
}
void start(point &a,queue<point> &k,point &f,char&ch,char &ch1,int &lives,int &size,int &score) //vizualizira startoviq ekran
      {
      gotoxy(50,1);color(10);cout<<"W,S,D,A to move";
      ch=115;ch1=115;// buton nadolu
      if(lives!=0&&!k.empty()) size=k.size();
      else {lives=5; size=5;score=0;}
      delsnake(k);
      a.x=0;a.y=20;//nachalni koordinati na zmiqta
      k.push(a);
      ramka(a);
      f=qbuka(f,k);//randomizira qbuka
  gotoxy(f.y,f.x);
color(176);
cout<<" ";}
int main()
{
 srand(time(0));
point a;//Oxy
point f;//qbulka
char ch=115,ch1=115;//buton S
char renew; //getch za y/n
int size=5;//nachalna golemina na zmiqta
int score;
int lives;//jivoti
bool quit;
bool dead;
queue<point> k;//zmiq
char z;
  do
  {   color(10);
      system("cls");
      cout<<"\n\n\t\tSnake Game v1.70 //Free version\n\n";
      cout<<"\n\n\t\t1. Start game";
      cout<<"\n\n\t\t2. Exit";
      z=getch();
      system("cls");
      switch (z)
      {
      case '1':
          char z1;
              system("cls");
      cout<<"\n\n\t\tChoose level:\n";
      cout<<"\n\n\t\t1. Easy(boring)";
      cout<<"\n\n\t\t2. Normal(recommended)";
      cout<<"\n\n\t\t3. Very hard";
      z1=getch();
      system("cls");
quit=0;dead=0;
delsnake(k);
start(a,k,f,ch,ch1,lives,size,score);
while(quit==0)
  {
          while((!kbhit())&&!dead)
          {
              move(a,f,k,ch,size,z1,ch1,score);//premestvane na zmiqta
              newap(k,f);//nova qbuka
              if(score>0) score-=10;

                  color(14);gotoxy(45,3);cout<<"Length:"<<k.size();
                  gotoxy(45,4);cout<<"Lives:"<<lives;
                  if(chdead(k))
                  {ramka(a);dead=1;lives--;}
                  color(14);
                  gotoxy(45,4);cout<<"Lives:"<<lives;
                  gotoxy(45,5);cout<<"Score:";
                  gotoxy(51,5);cout<<"     ";gotoxy(51,5);cout<<score;

          }



     if(!dead) ch=getch();
if(dead)
  { gotoxy(41,0);color(14);
if(lives==0) cout<<"You lose!Your score is:"<<score<<" , wanna try again?(y/n)";
else cout<<lives<<" lives...do you continue?(y/n)";

renew=getch();

if(renew=='y')
  {
  dead=0;
color(0);system("cls");
start(a,k,f,ch,ch1,lives,size,score);
}
else if(renew=='n') {quit=1;color(10);system("cls");}
}
  }
          break;
      case '2':
          color(10);system("cls");
          break;
      }
      system("pause");
  }
  while (z!='2');
  color(10);

return 0;
}

void gotoxy(int x, int y)
{
static HANDLE hStdout = NULL;
COORD coord;

coord.X = x;
coord.Y = y;

if (!hStdout)
{
   hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
}

SetConsoleCursorPosition(hStdout,coord);
}
void clrscr(int x,int y)
{
static HANDLE hStdout = NULL;
static CONSOLE_SCREEN_BUFFER_INFO csbi;
const COORD startCoords = {x,y};
DWORD dummy;

if (!hStdout)
{
   hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
   GetConsoleScreenBufferInfo(hStdout,&csbi);
}

FillConsoleOutputCharacter(hStdout,
                          ' ',
                          csbi.dwSize.X * csbi.dwSize.Y,
                          startCoords,
                          &dummy);
gotoxy(0,0);
}

void color(int n)
{
HANDLE hConsole;

hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

SetConsoleTextAttribute(hConsole, n);
}
