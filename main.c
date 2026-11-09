#include <stdio.h>
#include <math.h>
#include <locale.h>

// Прототипы функций Задания 1
double fa(double x);
double fb(double x);
double product(double a, double b);
double diff_squares(double a, double b);
double double_sum(double a, double b);

// Прототипы функций Задания 2
double sin_n(double x, int N);
double sin_eps(double x, double eps);
double exp_neg_n(double x, int N);
double exp_neg_eps(double x, double eps);

int main(void)
{
    setlocale(LC_ALL, "");

    // Задание 1. Значения двух функций
    printf("=== Задание 1 ===\n");
    printf("F1(x) = x^2 - 3x + 9, если x <= 3;  1 / (x^3 + 3), если x > 3\n");
    printf("F2(x) = x * e^(sin(x^2))\n");
    printf("Введите x: ");

    double x;
    if (scanf("%lf", &x) != 1) return 1;

    double f1 = fa(x);
    double f2 = fb(x);

    // п.2 - значения функций
    printf("fa(x) = %lf, fb(x) = %lf\n", f1, f2);

    // п.3 - произведение, разность квадратов, удвоенная сумма
    printf("произведение = %lf, разность квадратов = %lf, удвоенная сумма = %lf\n\n",
        product(f1, f2), diff_squares(f1, f2), double_sum(f1, f2));

    // п.4 - меню
    int choice;
    do
    {
        printf("Меню:\n");
        printf("1 - значение F1(x)\n");
        printf("2 - значение F2(x)\n");
        printf("3 - произведение F1(x) * F2(x)\n");
        printf("4 - разность квадратов F1(x)^2 - F2(x)^2\n");
        printf("5 - удвоенная сумма 2 * (F1(x) + F2(x))\n");
        printf("0 - выход из меню\n");
        printf("Ваш выбор: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = -1;
            continue;
        }

        if (choice >= 1 && choice <= 5)
        {
            printf("Введите x: ");
            if (scanf("%lf", &x) != 1) continue;
            f1 = fa(x);
            f2 = fb(x);
        }

        switch (choice)
        {
        case 1:
            printf("F1(%.4lf) = %lf\n\n", x, f1);
            break;
        case 2:
            printf("F2(%.4lf) = %lf\n\n", x, f2);
            break;
        case 3:
            printf("Произведение = %lf\n", product(f1, f2));
            break;
        case 4:
            printf("Разность квадратов = %lf\n", diff_squares(f1, f2));
            break;
        case 5:
            printf("Удвоенная сумма = %lf\n", double_sum(f1, f2));
            break;
        case 0:
            printf("Выход из меню\n");
            break;
        default:
            printf("Неизвестный пункт меню\n");
            break;
        }
    } while (choice != 0);

    // Задание 2. sin(x) тремя способами
    printf("=== Задание 2. sin(x) ===\n");
    printf("Введите x (в радианах): ");
    if (scanf("%lf", &x) != 1) return 1;

    int N;
    printf("Введите число членов ряда N: ");
    if (scanf("%d", &N) != 1) return 1;

    double eps;
    printf("Введите точность eps: ");
    if (scanf("%lf", &eps) != 1) return 1;

    if (N < 1 || eps <= 0) {
        printf("Ошибка: N должно быть >= 1, eps > 0\n");
    }
    else
    {
        double s_std = sin(x);

        printf("  N |    sin_N     |  отклонение\n");
        printf("----+--------------+--------------\n");
        for (int i = 1; i <= N; i++)
        {
            double s_n = sin_n(x, i);
            printf("%3d | %12.8lf | %+.4e\n", i, s_n, s_n - s_std);
        }

        double s_eps = sin_eps(x, eps);
        printf("\nСтандартная sin(x)  = %.10lf\n", s_std);
        printf("Ряд по N = %d       = %.10lf, отклонение %+.4e\n",
            N, sin_n(x, N), sin_n(x, N) - s_std);
        printf("Ряд по eps = %g = %.10lf, отклонение %+.4e\n\n",
            eps, s_eps, s_eps - s_std);
    }

    // Задание 2 e^(-x) через ряд
    printf("=== Задание 2. Вариант 1: e^(-x) ===\n");
    printf("e^(-x) = 1 - x + x^2/2! - x^3/3! + ...\n");
    printf("Введите x: ");
    if (scanf("%lf", &x) != 1) return 1;
    printf("Введите число членов ряда N: ");
    if (scanf("%d", &N) != 1) return 1;
    printf("Введите точность eps: ");
    if (scanf("%lf", &eps) != 1) return 1;

    if (N < 1 || eps <= 0) {
        printf("Ошибка: N должно быть >= 1, eps > 0\n");
    }
    else
    {
        double e_std = exp(-x);

        printf("  N |   exp_N      |  отклонение\n");
        printf("----+--------------+--------------\n");
        for (int i = 1; i <= N; i++)
        {
            double e_n = exp_neg_n(x, i);
            printf("%3d | %12.8lf | %+.4e\n", i, e_n, e_n - e_std);
        }

        double e_eps = exp_neg_eps(x, eps);
        printf("Стандартная exp(-x) = %.10lf\n", e_std);
        printf("Ряд по N = %d       = %.10lf, отклонение %+.4e\n",
            N, exp_neg_n(x, N), exp_neg_n(x, N) - e_std);
        printf("Ряд по eps = %g = %.10lf, отклонение %+.4e\n",
            eps, e_eps, e_eps - e_std);
    }

    return 0;
}

// F1(x): кусочная функция
double fa(double x)
{
    if (x <= 3)
        return x * x - 3 * x + 9;
    else
        return 1.0 / (x * x * x + 3.0);
}

// F2(x) = x * e^(sin(x^2))
double fb(double x)
{
    return x * exp(sin(x * x));
}

// Произведение значений
double product(double a, double b)
{
    return a * b;
}

// Разность квадратов значений
double diff_squares(double a, double b)
{
    return a * a - b * b;
}

// Удвоенная сумма значений
double double_sum(double a, double b)
{
    return 2.0 * (a + b);
}

// Исправленный ряд Тейлора для sin(x) на N членов
double sin_n(double x, int N)
{
    double sum = x;   // Первый член ряда (при k = 0) равен x
    double term = x;  // Текущий член ряда

    for (int k = 1; k < N; k++) // Итерируемся до N членов (всего N слагаемых)
    {
        term *= -x * x / ((2 * k) * (2 * k + 1));
        sum += term;
    }
    return sum;
}

// Исправленный ряд Тейлора для sin(x) по точности
double sin_eps(double x, double eps)
{
    double sum = x;
    double term = x;
    int k = 1;

    while (fabs(term) >= eps)
    {
        term *= -x * x / ((2 * k) * (2 * k + 1));
        sum += term;
        k++;
    }
    return sum;
}

// Исправленный ряд Тейлора для e^(-x) на N членов
double exp_neg_n(double x, int N)
{
    double sum = 1.0;  // Первый член ряда (при n = 0) равен 1
    double term = 1.0;

    for (int n = 1; n < N; n++) // Итерируемся до N членов
    {
        term *= -x / n;
        sum += term;
    }
    return sum;
}

// Исправленный ряд Тейлора для e^(-x) по точности
double exp_neg_eps(double x, double eps)
{
    double sum = 1.0;
    double term = 1.0;
    int n = 1;

    while (fabs(term) >= eps)
    {
        term *= -x / n;
        sum += term;
        n++;
    }
    return sum;
}
