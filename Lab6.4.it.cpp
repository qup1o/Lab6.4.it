// Lab 6.4 (iterative)
#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

void Create(double* a, const int size, const double Low, const double High);
void Print(const double* a, const int size);
int IndexOfMin(const double* a, const int size);
int FindNegative(const double* a, const int size, const int start);
double SumRange(const double* a, const int from, const int to);
bool SumBetweenFirstTwoNegatives(const double* a, const int size,
    double& sum);
bool IsSmall(const double x);
void ShiftRight(double* a, const int from, const int to);
void MoveSmallFirst(double* a, const int size);

int main()
{
    srand((unsigned)time(NULL));  // ініціалізація генератора випадкових чисел

    int n;
    cout << "n = "; cin >> n;
    if (n <= 0)
    {
        cout << "n must be positive" << endl;
        return 1;
    }

    double* a = new double[n];     // динамічний масив

    Create(a, n, -5.0, 5.0);
    cout << "Array:" << endl;
    Print(a, n);

    cout << "Index of min element = " << IndexOfMin(a, n) << endl;

    double s;
    if (SumBetweenFirstTwoNegatives(a, n, s))
        cout << "Sum between 1st and 2nd negative = " << s << endl;
    else
        cout << "There are fewer than two negative elements" << endl;

    MoveSmallFirst(a, n);
    cout << "Modified array:" << endl;
    Print(a, n);

    delete[] a;                    // знищення динамічного масиву
    return 0;
}

// формування масиву випадковими числами з [Low; High]
void Create(double* a, const int size, const double Low, const double High)
{
    for (int i = 0; i < size; i++)
        a[i] = Low + (High - Low) * rand() / RAND_MAX;
}

// виведення масиву в рядок
void Print(const double* a, const int size)
{
    cout << fixed << setprecision(2);
    for (int i = 0; i < size; i++)
        cout << setw(8) << a[i];
    cout << endl;
}

// індекс (номер) першого мінімального елемента
int IndexOfMin(const double* a, const int size)
{
    int imin = 0;                  // перший елемент вважаємо мінімальним
    for (int i = 1; i < size; i++)
        if (a[i] < a[imin])
            imin = i;
    return imin;
}

// індекс першого від'ємного елемента, починаючи з позиції start
// (або -1, якщо такого немає)
int FindNegative(const double* a, const int size, const int start)
{
    for (int i = start; i < size; i++)
        if (a[i] < 0)
            return i;
    return -1;
}

// сума елементів з індексами від from до to-1
double SumRange(const double* a, const int from, const int to)
{
    double s = 0;
    for (int i = from; i < to; i++)
        s += a[i];
    return s;
}

// сума елементів між першим і другим від'ємними елементами;
// повертає false, якщо від'ємних елементів менше двох
bool SumBetweenFirstTwoNegatives(const double* a, const int size,
    double& sum)
{
    int first = FindNegative(a, size, 0);
    if (first == -1)
        return false;

    int second = FindNegative(a, size, first + 1);
    if (second == -1)
        return false;

    sum = SumRange(a, first + 1, second);
    return true;
}

// критерій: модуль елемента не перевищує одиниці
bool IsSmall(const double x)
{
    return fabs(x) <= 1;
}

// зсув елементів a[from..to-1] на одну позицію праворуч
void ShiftRight(double* a, const int from, const int to)
{
    for (int j = to; j > from; j--)
        a[j] = a[j - 1];
}

// спочатку - елементи, модуль яких не перевищує 1, потім - усі інші;
// відносний порядок елементів зберігається
void MoveSmallFirst(double* a, const int size)
{
    int k = 0;                     // кількість вже розміщених "малих"
    for (int i = 0; i < size; i++)
        if (IsSmall(a[i]))
        {
            double t = a[i];
            ShiftRight(a, k, i);
            a[k] = t;
            k++;
        }
}
