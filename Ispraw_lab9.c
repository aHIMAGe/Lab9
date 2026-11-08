#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double fa(double x);
double fb(double x);
double arccosn(double x, int N);
double arccoseps(double x, double eps);
float ploshad(float r);
void opred(void);
char risunok(int row, int col, int r, char c);

int main()
{
    double x1, y1, y2;
    int punkt1;
    double x2, eps, ystd, yn, yeps;
    int N, i;
    int r, punkt3, row, col;
    float s;
    char c, ch;

    setlocale(LC_ALL, ".UTF8");

    printf("Задание 1:\n");
    printf("Введите x: ");
    scanf("%lf", &x1);

    y1 = fa(x1);
    y2 = fb(x1);
    printf("fa(x)=%.4lf , fb(x)=%.4lf\n", y1, y2);

    do
    {
        printf("\nМеню (1 - произведение, 2 - разность квадратов, 3 - удвоенная сумма, 0 - выход): ");
        scanf("%d", &punkt1);

        switch (punkt1)
        {
        case 1:
            printf("произведение: %.4lf\n", y1 * y2);
            break;
        case 2:
            printf("разность квадратов: %.4lf\n", pow(y1, 2) - pow(y2, 2));
            break;
        case 3:
            printf("удвоенная сумма: %.4lf\n", 2.0 * (y1 + y2));
            break;
        case 0:
            printf("Выход из меню задания 1\n");
            break;
        default:
            printf("Ошибка: неверный пункт меню\n");
            break;
        }
    } while (punkt1 != 0);

    printf("\nЗадание 2 (Вариант 7 - arccos(x)):\n");
    printf("Введите x (|x| < 1): ");
    scanf("%lf", &x2);
    printf("Введите количество членов ряда N (N >= 1): ");
    scanf("%d", &N);
    printf("Введите точность eps (eps > 0, например, 0.0001): ");
    scanf("%lf", &eps);

    if (fabs(x2) >= 1.0 || N < 1 || eps <= 0.0)
    {
        printf("Ошибка: должно выполняться |x| < 1, N >= 1 и eps > 0\n");
    }
    else
    {
        ystd = acos(x2);
        yn = arccosn(x2, N);
        yeps = arccoseps(x2, eps);

        printf("1) Стандартная функция acos(x)    = %.6lf\n", ystd);
        printf("2) Сумма ряда arccosn(x, %d)       = %.6lf\n", N, yn);
        printf("3) С точностью arccoseps(x, eps) = %.6lf\n", yeps);

        printf("\nТаблица сходимости:\n");
        printf("  N |  arccos_N | отклонение\n");
        printf("-----------------------------\n");
        for (i = 1; i <= N; i++)
        {
            yn = arccosn(x2, i);
            printf("%3d | %9.4lf | %+.4e\n", i, yn, ystd - yn);
        }
    }

    printf("\nЗадание 3 (ДЗ - Четырехугольник, вариант 16):\n");
    printf("Введите радиус вписанной окружности r: ");
    scanf("%d", &r);

    if (r <= 0)
    {
        printf("Ошибка: радиус должен быть положительным\n");
        return 0;
    }

    do
    {
        printf("\nМеню операций:\n");
        printf("1 - рассчитать площадь\n");
        printf("2 - вывести определение фигуры\n");
        printf("3 - нарисовать фигуру\n");
        printf("0 - выход из программы\n");
        printf("Выберите операцию: ");
        scanf("%d", &punkt3);

        switch (punkt3)
        {
        case 1:
            s = ploshad((float)r);
            printf("Площадь описанного четырехугольника: %.2f\n", s);
            break;
        case 2:
            opred();
            break;
        case 3:
            printf("Введите символ для рисования: ");
            scanf(" %c", &c);
            for (row = 1; row <= 2 * r + 1; row++)
            {
                for (col = 1; col <= 2 * r + 1; col++)
                {
                    ch = risunok(row, col, r, c);
                    putchar(ch);
                }
                putchar('\n');
            }
            break;
        case 0:
            printf("Завершение работы.\n");
            break;
        default:
            printf("Ошибка: неверный пункт меню\n");
            break;
        }
    } while (punkt3 != 0);

    return 0;
}

double fa(double x)
{
    double y;

    if (x <= 3.0)
    {
        y = pow(x, 2) - 3.0 * x + 9.0;
    }
    else
    {
        y = 1.0 / (pow(x, 3) + 3.0);
    }
    return y;
}

double fb(double x)
{
    double y;

    y = x * exp(sin(pow(x, 2)));
    return y;
}

double arccosn(double x, int N)
{
    int k;
    double sum, t;

    sum = x;
    t = x;
    for (k = 1; k < N; k++)
    {
        t = t * (2.0 * k - 1.0) * (2.0 * k - 1.0) * x * x / ((2.0 * k) * (2.0 * k + 1.0));
        sum += t;
    }
    return (M_PI / 2.0) - sum;
}

double arccoseps(double x, double eps)
{
    int k;
    double sum, t;

    sum = x;
    t = x;
    k = 1;
    while (fabs(t) > eps)
    {
        t = t * (2.0 * k - 1.0) * (2.0 * k - 1.0) * x * x / ((2.0 * k) * (2.0 * k + 1.0));
        sum += t;
        k++;
    }
    return (M_PI / 2.0) - sum;
}

float ploshad(float r)
{
    return 4.0f * r * r;
}

void opred(void)
{
    printf("Описанный четырехугольник - это четырехугольник, все стороны которого касаются одной окружности (вписанной окружности радиуса r).\n");
    printf("Свойство: суммы противоположных сторон описанного четырехугольника равны (AB + CD = BC + AD).\n");
}

char risunok(int row, int col, int r, char c)
{
    int center = r + 1;
    if (abs(row - center) + abs(col - center) == r)
    {
        return c;
    }
    else
    {
        return ' ';
    }
}