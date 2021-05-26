#include <iostream>
#include <fstream>

using namespace std;

int main()
{

    // le o nome do arquivo
    string nome;
    cout << "Digite o nome do arquivo: ";
    cin >> nome;

    // abre o arquivo e atribui todo seu conteudo a uma string
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

    // pega o numero de elementos do vetor apresentado pelo arquivo e o converte em um numero inteiro
    string nStr = "";
    int i = 0;
    do
    {
        nStr.push_back(fullText[i]);
        i++;
    } while (fullText[i] != '\n');
    // int n = stoi(nStr);
    int n = atoi(nStr.c_str());

    if (n == 0)
    {
        cout << "Matriz: " << endl;
        cout << "0\n0";
        return 0;
    }

    // pega os numeros do vetor e os converte em inteiros, registrado um em cada posicao de um vetor
    int *numbers = (int *) malloc(n * sizeof(int));

    for (int j = 0; j < n; j++)
    {
        string currentNumber = "";
        do
        {
            currentNumber.push_back(fullText[i]);
            i++;
        } while (fullText[i] != ' ' && fullText[i] != '\n');
        // numbers[j] = stoi(currentNumber);
        numbers[j] = atoi(currentNumber.c_str());
        currentNumber.clear();
    }

    if (n == 1)
    {
        cout << "Matriz: " << endl;
        cout << "1\n"
             << n;
        return 0;
    }

    // copia o vetor de numeros para outro e ordena em ordem crescente
    int *orderedNumbers = (int *) malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        orderedNumbers[i] = numbers[i];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (orderedNumbers[i] > orderedNumbers[j])
                swap(orderedNumbers[i], orderedNumbers[j]);
        }
    }

    // calcula quantos numeros distintos tem no vetor
    int distinctNumbers = 0;
    int *numberValues = (int *) malloc(distinctNumbers * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        if (orderedNumbers[i] != orderedNumbers[i + 1])
        {
            if (distinctNumbers != 0)
            {
                numberValues = (int *)realloc(numberValues, distinctNumbers * sizeof(int));
            }
            numberValues[distinctNumbers] = orderedNumbers[i];
            distinctNumbers++;
        }
    }

    // aloca memorias iniciais para a matriz final e algumas variaveis necessarias
    int k = 1;
    int **finalNumbers = (int **) malloc(2 * sizeof(int*));
    for(int i = 0; i < 2; i++){
    finalNumbers[i] = (int *) malloc(k * sizeof(int));
    }
    int currentSegmentSize = 1;

    for (int j = 0; j < n; j++)
    {
        // conta o tamanho do segmento atual (onde os numeros sao consecutivos e iguais)
        if (numbers[j] == numbers[j + 1])
        {
            currentSegmentSize++;
        }
        else
        {
            // quando termina de contar o segmento, aloca um novo espaco na matriz
            for (int i = 0; i < 2; i++)
            {
                finalNumbers[i] = (int *)realloc(finalNumbers[i], k * sizeof(int));
            }
            // confere o valor do numero presente no segmento e registra em um espaco da matriz
            for (int i = 0; i < distinctNumbers; i++)
            {
                if (numberValues[i] == numbers[j])
                    finalNumbers[0][k - 1] = (i + 1);
            }
            // registra o tamanho do segmento analizado na matriz
            finalNumbers[1][k - 1] = currentSegmentSize;
            // reseta o tamanho do segmento e aumenta a variavel de colunas
            currentSegmentSize = 1;
            k++;
        }
    }

    // printa a matriz
    cout << "Matriz: " << endl;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < (k - 1); j++)
        {
            cout << finalNumbers[i][j] << " ";
        }
        putchar('\n');
    }

    free(numbers);
    free(orderedNumbers);
    free(numberValues);
    free(finalNumbers);

    return 0;
}