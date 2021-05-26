#include <iostream>

using namespace std;

int Digitos(int N)
{
    int i = 1;
    if (N >= 10)
    {
        N = N / 10;
        i = i + Digitos(N);
    }
    return i;
}

int main()
{

    int N;
    cout << "Digite um numero inteiro: ";
    cin >> N;
    cout << "Resultado: " << Digitos(N) << "\n";

    return 0;
}