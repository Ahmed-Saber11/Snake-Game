#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

enum Direction { Stop = 0, UP, Down, Right, Left };
struct Map { int Width, Length; };
struct Fruit { int Fruit_X, Fruit_Y; };
struct Snake { int Head_X, Head_Y, Tail_N, Tail_X[100], Tail_Y[100]; };
struct Score_game { int Score, speed;; bool Game_Over; };

Map map; Snake snake; Score_game S_G; Fruit fruit; Direction Dir;

void Setup() {
map.Length = 19;
map.Width = 40;
S_G.speed = 50;

Dir = Stop;

fruit.Fruit_X = rand() % (map.Width - 2) + 1;
fruit.Fruit_Y = rand() % (map.Length - 2) + 1;

snake.Head_X = map.Width / 2;
snake.Head_Y = map.Length / 2;
snake.Tail_N = 0;

S_G.Score = 0;
S_G.Game_Over = false;
}
void Draw() {
system("cls");
for (int i = 0; i < map.Length; i++) {
  for (int j = 0; j < map.Width; j++) {
   if (i == 0 || i == map.Length - 1)
    cout << "*";
   else if (j == 0 || j == map.Width - 1)
    cout << "*";
   else if (j == snake.Head_X && i == snake.Head_Y)
    cout << char(2);
   else if (j == fruit.Fruit_X && i == fruit.Fruit_Y)
    cout << char(3);
   else
   {
    bool PrintTail = false;
    for (int k = 0; k < snake.Tail_N; k++)
    {
     if (snake.Tail_X[k] == j && snake.Tail_Y[k] == i)
     {
      cout << "o";
      PrintTail = true;
     }
    }
    if (!PrintTail)
     cout << " ";
   }
  }
  cout << endl;
}
cout << "---------------------------------------\n";
cout << " To exit the gym, press X \n";
cout << "---------------------------------------\n";
cout << "Score : " << S_G.Score << endl;
cout << "---------------------------------------\n";

}
void Input(){
if (_kbhit())
{
  switch (_getch())
  {
  case 'a':
   if (Dir != Right)
    Dir = Left;
   break;
  case 'd':
   if (Dir != Left)
    Dir = Right;
   break;
  case 'w':
   if (Dir != Down)
    Dir = UP;
   break;
  case 's':
   if (Dir != UP)
    Dir = Down;
   break;
  case 'x':
   S_G.Game_Over = true;
   break;
  }
}
}
void TAIL() {
snake.Tail_X[0] = snake.Head_X;
snake.Tail_Y[0] = snake.Head_Y;
for (int i = 1; i < snake.Tail_N; i++) {
  swap(snake.Tail_X[0], snake.Tail_X[i]);
  swap(snake.Tail_Y[0], snake.Tail_Y[i]);
}
}
void Logic(){
TAIL();
switch (Dir)
{
case UP:
  snake.Head_Y--;
  break;
case Down:
  snake.Head_Y++;
  break;
case Right:
  snake.Head_X++;
  break;
case Left:
  snake.Head_X--;
  break;
default:
  break;
}
for (int i = 1; i < snake.Tail_N; i++) {
  if (snake.Tail_X[i] == snake.Head_X && snake.Tail_Y[i] == snake.Head_Y)
   S_G.Game_Over = true;
}

if (snake.Head_X <= 0 snake.Head_X >= map.Width snake.Head_Y <= 0 || snake.Head_Y >= map.Length - 1)
  S_G.Game_Over = true;

if (snake.Head_X == fruit.Fruit_X && snake.Head_Y == fruit.Fruit_Y) {
  S_G.Score++;
  snake.Tail_N++;
  fruit.Fruit_X = rand() % (map.Width - 2) + 1;
  fruit.Fruit_Y = rand() % (map.Length - 2) + 1;
  S_G.speed-=2; 
}
}


int main()
{
Setup();
while (!S_G.Game_Over) {
  Draw();
  Input();
  Logic();
  Sleep(S_G.speed);
}
system("pause");
return 0;
}