#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define ROW 9
#define COL 9

int pifagor(int row, int col);
int chisla(int row, int col);
int chetn(int n);
char figura(int row, int col, int r, char c);

int main()
{
    int row, col, val;
    int n, res;
    char yn;
    int r, cont;
    char c, ch;

    setlocale(LC_ALL, ".UTF8");

    //задание 1.1
    for (row = 1; row <= ROW; row++)
    {
        for (col = 1; col <= COL; col++)
        {
            val = pifagor(row, col);
            printf("%5d", val);
        }
        printf("\n");
    }

    //задание 1.2
    for (row = 1; row <= ROW; row++)
    {
        for (col = 1; col <= row; col++)
        {
            val = pifagor(row, col);
            printf("%5d", val);
        }
        printf("\n");
    }

    //задание 1.3(16 вариант)
    for (row = 1; row <= 9; row++)
    {
        for (col = 1; col <= 9; col++)
        {
            printf("%d x %d = %-3d  ", row, col, row * col);
        }
        printf("\n");
    }

    //Задание 2
    do
    {
        printf("Введите число: ");
        scanf("%d", &n);

        res = chetn(n);
        printf("Количество четных цифр: %d\n", res);

        printf("Продолжить? (Да - y, нет - n): ");
        scanf(" %c", &yn);
    } while (yn != 'n');

    //ДЗ
    do
    {
        printf("Введите символ из которого будет строиться фигура: ");
        scanf(" %c", &c);
        printf("Введите радиус r: ");
        scanf("%d", &r);

        if (r <= 0)
        {
            printf("Ошибка: радиус должен быть положительным\n");
        }
        else
        {
            printf("Четырехугольник (контур):\n\n");
            for (row = 1; row <= 2 * r + 1; row++)
            {
                for (col = 1; col <= 2 * r + 1; col++)
                {
                    ch = figura(row, col, r, c);
                    putchar(ch);
                }
                putchar('\n');
            }
        }

        printf("\nПродолжить? (Да - введите любое число, Нет - введите 0): ");
        scanf("%d", &cont);
    } while (cont != 0);
    return 0;
}

int pifagor(int row, int col)
{
    return row * col;
}

int chisla(int row, int col)
{
    return row * 10 + col;
}

int chetn(int n)
{
    int k, d;

    k = 0;
    n = abs(n);

    if (n == 0)
    {
        return 1;
    }

    while (n > 0)
    {
        d = n % 10;
        if (d % 2 == 0)
        {
            k++;
        }
        n = n / 10;
    }
    return k;
}

char figura(int row, int col, int r, char c)
{
    int center = r + 1;
    if (abs(row - center) + abs(col - center) == r)
        return c;
    else
        return ' ';
}