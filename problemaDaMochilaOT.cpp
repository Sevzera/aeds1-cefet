#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

typedef struct item
{
    int W;
    int V;
    float VW;
} item;

int main()
{

    // Declara, le o arquivo para uma string e trata possiveis erros
    string name;
    cout << "Digite o nome do arquivo: ";
    cin >> name;

    ifstream file(name);

    if (file.fail())
    {
        cout << "Arquivo inexistente.";
        putchar('\n');
        return 0;
    }

    string fullText;
    for (string line; getline(file, line);)
    {
        fullText += line;
        fullText += '\n';
    }

    if (fullText.empty())
    {
        cout << "Arquivo vazio.";
        putchar('\n');
        return 0;
    }

    // Pega os valores de W e n da string e transforma em variaveis inteiras
    int index = 0; // Seta o indice no primeiro elemento da string

    string Wbstr;
    do
    {
        Wbstr.push_back(fullText[index]);
        index++;
    } while (fullText[index] != '\n');
    // int Wb = stoi(Wstr);
    int Wb = atoi(Wbstr.c_str());

    string nstr;
    do
    {
        nstr.push_back(fullText[index]);
        index++;
    } while (fullText[index] != '\n');
    // int n = stoi(nstr);
    int n = stoi(nstr.c_str());

    // Pega o W e valores de cada item e atribui a um vetor de items
    index++; // Tira o indice do \n

    item *lista = (item *)calloc(n, sizeof(item));

    for (int j = 0; j < n; j++)
    {
        string currentNumber = "";
        while (fullText[index] != ' ')
        {

            currentNumber.push_back(fullText[index]);
            index++;
        }
        // m[j].W = stoi(currentNumber);
        lista[j].W = stoi(currentNumber.c_str());
        currentNumber.clear();

        while (fullText[index] != '\n')
        {

            currentNumber.push_back(fullText[index]);
            index++;
        }
        // m[j].V = stoi(currentNumber);
        lista[j].V = stoi(currentNumber.c_str());
        currentNumber.clear();
    }

    // Atribui os estados 1 do arquivo para um vetor de tamanho n
    index++; // Tira o indice do \n
    string onUsers;
    int *onUser = (int *)malloc(n * sizeof(int));
    for (int j = 0; j < n; j++)
    {
        onUsers.push_back(fullText[index]);
        //on[j] = stoi(ons);
        onUser[j] = atoi(onUsers.c_str());
        onUsers.clear();
        index += 2;
    }

    // Trata dos casos onde n = 1 ou 0
    if (n == 1 && lista[0].W <= Wb && onUser[0] == 1)
    {
        cout << "Solucao otima.";
        return 0;
    }
    else if (n == 1 && lista[0].W <= Wb && onUser[0] == 0)
    {
        cout << "Solucao viavel mas nao otima.";
        return 0;
    }
    else if (n == 1 && lista[0].W > Wb && onUser[0] == 1)
    {
        cout << "Solucao inviavel.";
        return 0;
    }
    else if (n == 1 && lista[0].W > Wb && onUser[0] == 0)
    {
        cout << "Solucao otima.";
        return 0;
    }
    else if (n == 0)
    {
        cout << "Solucao otima.";
        return 0;
    }

    // Seta o valor e o peso somado pelo usuario em userValue e userW usando como referencia de visita o vetor de itens escolhidos pelo usuario
    int userValue = 0;
    for (int i = 0; i < n; i++)
    {
        if (onUser[i] == 1)
        {
            userValue += lista[i].V;
        }
    }

    int userW = 0;
    for (int i = 0; i < n; i++)
    {
        if (onUser[i] == 1)
        {
            userW += lista[i].W;
        }
    }

    // Cria uma matriz [n + 1][Wb + 1] com 0s
    int **m = (int **)calloc(n + 1, sizeof(int *));
    for (int i = 0; i < n + 1; i++)
    {
        m[i] = (int *)calloc(Wb + 1, sizeof(int));
    }

    // Encontra o valor maximo por meio da aplicacao e analise da matriz
    // Segue-se um mesmo processo para "descobrir" cada elemento da matriz
    // O valor maximo sera o ultimo elemento descoberto, m[n + 1][Wb + 1]
    int maxValue = 0;
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < Wb + 1; j++)
        {
            if (lista[i - 1].W < j + 1)
            {
                int currentCol = j - lista[i - 1].W;
                int currentValue = lista[i - 1].V + m[i - 1][currentCol];
                if (m[i - 1][j] < currentValue)
                {
                    m[i][j] = lista[i - 1].V + m[i - 1][currentCol];
                }
                else if (m[i - 1][j] > currentValue)
                {
                    m[i][j] = m[i - 1][j];
                }
            }
            else
            {
                m[i][j] = m[i - 1][j];
            }
            // for (int i = 0; i < n + 1; i++)
            // {
            //     for (int j = 0; j < Wb + 1; j++)
            //     {
            //         cout << m[i][j] << ' ';
            //     }
            //     putchar('\n');
            // }
            // putchar('\n');
            // puts("-----------------------------------");
            // putchar('\n');
            maxValue = m[i][j];
        }
    }

    // Libera a memoria usada pelos vetores/matriz
    free(lista);
    free(m);
    free(onUser);

    //Caso otimo: Confere se o valor do sistema (otimo) equivale ao valor dos itens do usuario e printa a mensagem correspondente
    if (maxValue == userValue && userW <= Wb)
    {
        cout << "Solucao otima." << endl;
        return 0;
    }
    //Caso nao otimo: Confere se o peso dos itens escolhidos pelo usuario nao ultrapassa o peso maximo da mochila e printa a mensagem correspondente
    else if (userValue < maxValue && userW <= Wb)
    {
        cout << "Solucao viavel mas nao otima." << endl;
        return 0;
    }
    // Caso inviavel: Caso os casos anteriores sejam falsos, o caso e inviavel e printa a mensagem correspondente
    else if (userW > Wb)
    {
        cout << "Solucao inviavel." << endl;
        return 0;
    }
}