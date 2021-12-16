#include<stdio.h>
#include<windows.h>
#include<conio.h>
#define DINO_BOTTOM_Y 12
#define CAC_BOTTOM_Y 20
#define CAC_BOTTOM_X 45
 
//�ܼ� â�� ũ��� ������ �����ϴ� �Լ�
void SetConsoleView()
{
    system("mode con:cols=100 lines=25");
    system("title Google Dinosaurs.");
}
 
//Ŀ���� ��ġ�� x, y�� �̵��ϴ� �Լ�
void GotoXY(int x, int y)
{
    COORD Pos;
    Pos.X = 2 * x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
 
//Ű������ �Է��� �ް�, �Էµ� Ű�� ���� ��ȯ�ϴ� �Լ�
int GetKeyDown()
{
    if (_kbhit() != 0)
    {
        return _getch();
    }
    return 0;
}

//������ ǥ���ϴ� �Լ�
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
 
//�������� ǥ���ϴ� �Լ�
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
 
//�浹�߻� �� ���ӿ��� 
void DrawGameOver(const int gameover)
{
    system("pause");
}
 
//�浹 ǥ�� 
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
            //�浹�� x, y�� 
            if(Collision(cacX, dinoY))
                break;
 
            //����Ű ���� 
            if (GetKeyDown() == ' ' && bottom)
            {
                jumping = true;
                bottom = false;
            }
 
            //���� ǥ�� 
            if (jumping)
            {
                dinoY -= height;
            }
            else
            {
                dinoY += height;
            }
 
            //�ٴ� ���� 
            if (dinoY >= DINO_BOTTOM_Y)
            {
                dinoY = DINO_BOTTOM_Y;
                bottom = true;
            }
 
            //�������� �ٰ����� �ӵ� ���� 
            cacX -= 2;
            if (cacX <= 0)
            {
                cacX = CAC_BOTTOM_X;
            }
 
            //������ ���� ����
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
