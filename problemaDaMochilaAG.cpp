#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

typedef struct item
{
    int W;
    int V;
    int VW;
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
    int i = 0; // Seta o indice no primeiro elemento da string

    string Wbstr;
    do
    {
        Wbstr.push_back(fullText[i]);
        i++;
    } while (fullText[i] != '\n');
    // int Wb = stoi(Wstr);
    int Wb = atoi(Wbstr.c_str());

    string nstr;
    do
    {
        nstr.push_back(fullText[i]);
        i++;
    } while (fullText[i] != '\n');
    // int n = stoi(nstr);
    int n = stoi(nstr.c_str());

    // Pega o W e valores de cada item e atribui a um vetor de items
    i++; // Tira o indice do \n

    item *lista = (item *)calloc(n, sizeof(item));

    for (int j = 0; j < n; j++)
    {
        string currentNumber = "";
        while (fullText[i] != ' ')
        {

            currentNumber.push_back(fullText[i]);
            i++;
        }
        // m[j].W = stoi(currentNumber);
        lista[j].W = stoi(currentNumber.c_str());
        currentNumber.clear();

        while (fullText[i] != '\n')
        {

            currentNumber.push_back(fullText[i]);
            i++;
        }
        // m[j].V = stoi(currentNumber);
        lista[j].V = stoi(currentNumber.c_str());
        currentNumber.clear();
    }

    // Atribui os estados 1 do arquivo para um vetor de tamanho n
    i++; // Tira o indice do \n
    string onUsers;
    int *onUser = (int *)malloc(n * sizeof(int));
    for (int j = 0; j < n; j++)
    {
        onUsers.push_back(fullText[i]);
        //on[j] = stoi(ons);
        onUser[j] = atoi(onUsers.c_str());
        onUsers.clear();
        i += 2;
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

    // Calcula o V/W de cada item e atribui as respectivas variaveis
    for (int i = 0; i < n; i++)
    {
        lista[i].VW = lista[i].V / lista[i].W;
    }

    int *onSystem = (int *)calloc(n, sizeof(int));
    int currentW = 0;
    float currentVW = 0;
    float totalVW = 0;
    int totalW = 0;

    // Roda um laco while ate que algum dos retornos condicionais sejam atingidos
    while (1)
    {
        currentW = 0;
        currentVW = 0;
        // Seta o maior VW em currentVW e seu W em currentW
        for (int i = 0; i < n; i++)
        {
            if (lista[i].VW > currentVW)
            {
                currentVW = lista[i].VW;
                currentW = lista[i].W;
            }
        }

        // Adiciona os valores de currentVW e currentW em totalVW e totalW
        totalVW += currentVW;
        totalW += currentW;

        // Trata da condicao do totalW ultrapassar o peso maximo da mochila
        if (totalW > Wb)
        {
            // Desfaz as somas feitas em totalW e totalVW
            totalVW -= currentVW;
            totalW -= currentW;
            // Seta o valor de VW do item selecionado como 0, marcando-o como item ja visitado
            for (int i = 0; i < n; i++)
            {
                if (lista[i].VW == currentVW)
                {
                    lista[i].VW = 0;
                    break;
                }
            }
        }
        else
        {
            // Caso o totalW nao tenha ultrapassado o peso da mochila, quer dizer que o item selecionado sera posto na mochila
            // Seta (na posicao de indice equivalente a lista) o valor 1 em um vetor que conta quais itens foram escolhidos
            // Seta o VW do item selecionado como 0, marcando-o como ja visitado
            for (int i = 0; i < n; i++)
            {
                if (lista[i].VW == currentVW)
                {
                    onSystem[i] = 1;
                    lista[i].VW = 0;
                    break;
                }
            }
        }

        // Confere se todos os itens ja foram visitados (estao com VW = 0) e, caso seja verdadeiro, quebra o laco while
        int cont = 0;
        for (int i = 0; i < n; i++)
        {
            if (lista[i].VW == 0)
            {
                cont++;
            }
        }
        if (cont == n)
        {
            break;
        }
    }

    // Seta o valor otimo em maxValue usando como referencia de visita o vetor de itens escolhidos pelo sistema
    int maxValue = 0;
    for (int i = 0; i < n; i++)
    {
        if (onSystem[i] == 1)
        {
            maxValue += lista[i].V;
        }
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

    // Libera a memoria usada pelos vetores
    free(lista);
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