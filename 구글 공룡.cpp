#include<stdio.h>
#include<windows.h>
#include<conio.h>
#define DINO_BOTTOM_Y 12
#define CAC_BOTTOM_Y 20
#define CAC_BOTTOM_X 45
 
//콘솔 창의 크기와 제목을 지정하는 함수
void SetConsoleView()
{
    system("mode con:cols=100 lines=25");
    system("title Google Dinosaurs.");
}
 
//커서의 위치를 x, y로 이동하는 함수
void GotoXY(int x, int y)
{
    COORD Pos;
    Pos.X = 2 * x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
 
//키보드의 입력을 받고, 입력된 키의 값을 반환하는 함수
int GetKeyDown()
{
    if (_kbhit() != 0)
    {
        return _getch();
    }
    return 0;
}

//공룡을 표현하는 함수
void DrawDino(int dinoY)
{
    GotoXY(0, dinoY);
    static bool legFlag = true;
    printf("        $$$$$$$ \n");
    printf("       $$ $$$$$$\n");
    printf("       $$$$$$$$$\n");
    printf("$      $$$      \n");
    printf("$$     $$$$$$$  \n"); 
    printf("$$$   $$$$$     \n");
    printf(" $$  $$$$$$$$$$ \n");
    printf(" $$$$$$$$$$$    \n");
    printf("  $$$$$$$$$$    \n");
    printf("    $$$$$$$$    \n");
    printf("     $$$$$$     \n");
    if (legFlag)
    {
        printf("     $    $$$    \n");
        printf("     $$          ");
        legFlag = false;
    }
    else
    {
        printf("     $$$  $     \n");
        printf("          $$    ");
        legFlag = true;
    }
}
 
//선인장을 표현하는 함수
void DrawCactus(int cacX)
{
	GotoXY(cacX, CAC_BOTTOM_Y - 1);
    printf("   $$ ");
    GotoXY(cacX, CAC_BOTTOM_Y);
    printf(" $ $$ ");
    GotoXY(cacX, CAC_BOTTOM_Y + 1);
    printf(" $$$$ ");
    GotoXY(cacX, CAC_BOTTOM_Y + 2);
    printf("   $$  $ ");
    GotoXY(cacX, CAC_BOTTOM_Y + 3);
    printf("   $$$$$ ");
    GotoXY(cacX, CAC_BOTTOM_Y + 4);
    printf("   $$ ");
}
 
//충돌발생 시 게임오버 
void DrawGameOver(const int gameover)
{
    system("pause");
}
 
//충돌 표현 
bool Collision(const int cacX, const int dinoY)
{
    if (cacX <= 8 && cacX >= 4 &&
        dinoY > 8)
    {
        return true;
    }
    return false;
}
 
int main()
{
    SetConsoleView();
 
    while (true)
    {
        bool jumping = false;
        bool bottom = true;
        const int height = 3;
        
        int dinoY = DINO_BOTTOM_Y;
        int cacX = CAC_BOTTOM_X;
        
        int gameover = 0;

        while (true)
        {
            //충돌의 x, y값 
            if(Collision(cacX, dinoY))
                break;
 
            //점프키 지정 
            if (GetKeyDown() == ' ' && bottom)
            {
                jumping = true;
                bottom = false;
            }
 
            //점프 표현 
            if (jumping)
            {
                dinoY -= height;
            }
            else
            {
                dinoY += height;
            }
 
            //바닥 지정 
            if (dinoY >= DINO_BOTTOM_Y)
            {
                dinoY = DINO_BOTTOM_Y;
                bottom = true;
            }
 
            //선인장이 다가오는 속도 지정 
            cacX -= 2;
            if (cacX <= 0)
            {
                cacX = CAC_BOTTOM_X;
            }
 
            //점프의 높이 지정
            if (dinoY <= 3)
            {
                jumping = false;
            }
 
            DrawDino(dinoY);
            DrawCactus(cacX);

            Sleep(60);
            system("cls");
        }
        DrawGameOver(gameover);
    }
    return 0;
}
