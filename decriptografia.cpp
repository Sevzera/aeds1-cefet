#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <math.h>

using namespace std;

int main()
{

    // Le o nome do arquivo
    string name;
    cout << "Digite o nome do arquivo: ";
    cin >> name;

    // Abre o arquivo e atribui todo seu conteudo a uma string
    ifstream file(name);

    if (!file)
    {
        cout << "Arquivo inexistente.";
        putchar('\n');
        return 0;
    }

    string fullText;
    int lines = 0;
    for (string line; getline(file, line);)
    {
        fullText += line;
        if (lines > 1)
        {
            fullText.push_back('\n');
        }
        lines++;
    }

    if (fullText == "")
    {
        cout << "Arquivo vazio.";
        putchar('\n');
        return 0;
    }

    // Printa a mensagem codificada

    putchar('\n');
    cout << "--------------------" << endl;
    cout << "Mensagem codificada:" << endl;
    cout << "--------------------" << endl;
    cout << fullText << endl;

    // Adiciona # no final da string, caso seu tamanho seja impar

    int size = fullText.size();

    if (size % 2 != 0)
    {

        fullText.push_back('#');
    }

    // cout << "Passo 0: " << fullText << endl;

    // Percorre a string desfazendo as permutacoes

    char aux;
    int cont = 0;
    int div;
    if ((size / 2) % 2 == 0)
    {
        div = 1;
    }
    else
    {
        div = 0;
    }
    for (int i = 0; i <= (size / 2 - div); i += 4)
    {

        aux = fullText[i];
        fullText[i] = fullText[(size - 1) - (cont + 1)];
        fullText[(size - 1) - (cont + 1)] = aux;

        aux = fullText[i + 1];
        fullText[i + 1] = fullText[(size - 1) - cont];
        fullText[(size - 1) - cont] = aux;

        cont = cont + 4;
    }

    // cout << "Passo 1: " << fullText << endl;

    // Percorre a string desfazendo as reflexoes em duplas

    for (int i = 0; i <= size; i += 2)
    {

        aux = fullText[i];
        fullText[i] = fullText[i + 1];
        fullText[i + 1] = aux;
    }

    // cout << "Passo 2: " << fullText << endl;

    // Substitui os caracteres

    for (int i = 0; i <= size; i++)
    {

        if ((fullText[i] >= 70 && fullText[i] <= 90) || (fullText[i] >= 102 && fullText[i] <= 122))
        {
            fullText[i] = fullText[i] - 5;
        }
        else
        {
            switch (fullText[i])
            {
            case '#':
                fullText[i] = ' ';
                break;
            case 'A':
                fullText[i] = 'V';
                break;
            case 'B':
                fullText[i] = 'W';
                break;
            case 'C':
                fullText[i] = 'X';
                break;
            case 'D':
                fullText[i] = 'Y';
                break;
            case 'E':
                fullText[i] = 'Z';
                break;
            case 'a':
                fullText[i] = 'v';
                break;
            case 'b':
                fullText[i] = 'w';
                break;
            case 'c':
                fullText[i] = 'x';
                break;
            case 'd':
                fullText[i] = 'y';
                break;
            case 'e':
                fullText[i] = 'z';
                break;
            default:
                break;
            }
        }
    }

    // cout << "Passo 3: " << fullText << endl;

    // Printa a mensagem decodificada

    putchar('\n');
    cout << "----------------------" << endl;
    cout << "Mensagem decodificada:" << endl;
    cout << "----------------------" << endl;
    cout << fullText;

    return 0;
}