#include <iostream>

using namespace std;

void dec2bin(int dec)
{

    if (dec == 1)
    {
        cout << "1";
    }
    else if (dec == 0)
    {
        cout << "0";
    }
    else
    {
        dec2bin(dec / 2);
        cout << dec % 2;
    }
}

int main()
{

    int dec;
    cout << "Digite um numero inteiro: ";
    cin >> dec;
    cout << "Resultado: ";
    dec2bin(dec);

    putchar('\n');
    return 0;
}