#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>

using namespace std;

int main()
{

    // Le o nome do arquivo
    string nome;
    cout << "Digite o nome do arquivo de entrada: ";
    cin >> nome;

    // Abre o arquivo e atribui todo seu conteudo a uma string
    ifstream file(nome);

    if (!file)
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

    if (fullText == "")
    {
        cout << "Arquivo vazio.";
        putchar('\n');
        return 0;
    }

    // Pega o numero de linhas da "escada" apresentado pelo arquivo e o converte em um numero inteiro
    string rowsStr = "";
    int i = 0;
    do
    {
        rowsStr.push_back(fullText[i]);
        i++;
    } while (fullText[i] != '\n');
    int rowsInt = stoi(rowsStr);
    // int rowsInt = atoi(rowsStr.c_str());
    if (rowsInt == 1)
    {
        cout << "Resposta: fileira 1, caixa 1.";
        putchar('\n');
        return 0;
    }
    else if (rowsInt == 0)
    {
        cout << "Resposta: fileira 0, caixa 0.";
        putchar('\n');
        return 0;
    }

    // Pega os numeros seguintes e coloca um em cada posicao de um vetor de inteiros
    int *n = (int *)calloc(800, sizeof(int));
    int k = 0;
    int fullTextLength = fullText.length();
    string currentNumber = "";
    for (int j = i + 1; j < fullTextLength; j++)
    {
        if (fullText[j] != ' ' && fullText[j] != '\n')
        {
            currentNumber.push_back(fullText[j]);
        }
        else
        {
            n[k] = stoi(currentNumber);
            // n[k] = atoi(currentNumber.c_str());
            k++;
            currentNumber.erase();
            currentNumber.shrink_to_fit();
        }
    }

    // Cria uma matriz de tamanho rowsInt x rowsInt preenchida com 0's
    int **m = (int **)calloc(rowsInt, sizeof(int *));
    for (int i = 0; i < rowsInt; i++)
    {
        m[i] = (int *)calloc(rowsInt, sizeof(int));
    }

    // Preenche a matriz com os numeros do vetor n de forma que componham uma "escada"
    int j = 0;
    int it = 1;
    int l = 0;
    for (int i = 0; i < rowsInt; i++)
    {
        for (j = 0; j < it; j++)
        {
            m[i][j] = n[l];
            l++;
        }
        it++;
    }

    // Define as variaveis necessarias para armazenar a posicao e valor do ganhador
    it = 1;
    j = 0;
    i = 0;
    int currentValue = 0;
    int rowValue = 0;
    int winnerValue = 0;
    int winnerRow = 0;
    int winnerBox = 0;

    // Trata a excecao da posicao [0][0] ser a ganhadora
    winnerValue = m[i][j];
    winnerRow = 1;
    winnerBox = 1;

    // Visita cada posicao relevante da matriz, somando todas as anteriores, e entao remove o valor das outras posicoes da mesma linha
    for (i = 1; i < rowsInt; i++)
    {
        it++;
        for (j = 0; j < it; j++)
        {
            rowValue = rowValue + m[i][j];
            currentValue = currentValue + m[i][j];

            // Compara o valor final da posicao analisada com o atual ganhador
            if ((currentValue + m[i][j] - rowValue + m[0][0]) > winnerValue)
            {
                winnerValue = currentValue - rowValue + m[i][j] + m[0][0];
                winnerRow = i + 1;
                winnerBox = j + 1;
            }
        }
        rowValue = 0;
    }

    free(m);
    // cout << "Valor: " << winnerValue << endl;
    cout << "Resposta: fileira " << winnerRow << ", caixa " << winnerBox << ".";
    putchar('\n');

    return 0;
}
