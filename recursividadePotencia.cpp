#include <iostream>

using namespace std;

int mult(int base, int exp);

int main()
{
    int base, exp;
    cout << "Digite a base e o expoente inteiros: ";
    cin >> base >> exp;
    cout << "Resultado: " << mult(base, exp);

    putchar('\n');
    return 0;
}

int mult(int base, int exp)
{
    if (exp == 0)
    {
        return 1;
    }
    else
    {
        base = base * mult(base, exp - 1);
    }
    return base;
}
