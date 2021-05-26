/****

LAED1 - Projeto - Detecção de faixa de pedestres em uma imagem

Alunos(as): Arthur Severo de Souza

Data: 26/03/2021 

****/

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

    if (fullText.empty())
    {
        cout << "Arquivo vazio.";
        putchar('\n');
        return 0;
    }
    int i = 0;

    // pega o numero de elementos do vetor apresentado pelo arquivo e o converte em um numero inteiro
    string nStr = "";
    do
    {
        nStr.push_back(fullText[i]);
        i++;
    } while (fullText[i] != '\n');
    // int n = stoi(nStr);
    int n = atoi(nStr.c_str());

    // pega o numero de perfis apresentado pelo arquivo e o converte em um numero inteiro
    string lStr = "";
    do
    {
        lStr.push_back(fullText[i]);
        i++;
    } while (fullText[i] != '\n');
    // int l = stoi(lStr);
    int l = atoi(lStr.c_str());

    if (n <= 0 || l <= 0)
    {
        cout << "Resultado: Padrao de faixa de pedestres nao encontrado." << endl;
        return 0;
    }

    // pega os numeros do vetor e os converte em inteiros, registrado um em cada posicao de um vetor
    int *numbers = (int *)malloc(n * sizeof(int));

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

    // calcula quantas "quebras" tem no vetor e faz um novo vetor com os valores de cada segmento
    int breaks = 0;
    int *values = (int *)malloc(breaks * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        if (numbers[i] != numbers[i + 1])
        {
            breaks++;

            values = (int *)realloc(values, breaks * sizeof(int));

            switch (numbers[i])
            {
            case 0:
                values[breaks - 1] = 1;
                break;
            case 128:
                values[breaks - 1] = 2;
                break;
            case 255:
                values[breaks - 1] = 3;
                break;
            default:
                break;
            }
        }
    }

    free(numbers);

    // // recebe a sequencia a ser buscada
    // int patternSize;
    // cout << "Digite a quantidade de numeros presentes na sequencia: ";
    // cin >> patternSize;
    // if (n < patternSize)
    // {
    //     cout << "Padrao nao encontrado" << endl;
    //     return 0;
    // }
    // int pattern[patternSize];
    // cout << "Digite os " << patternSize << " numeros em sequencia: ";
    // for (int i = 0; i < patternSize; i++)
    // {
    //     cin >> pattern[i];
    // }

    int patternSize = 13;
    if (n < patternSize)
    {
        cout << "Resultado: Padrao de faixa de pedestres nao encontrado." << endl;
        return 0;
    }
    int pattern[patternSize];
    pattern[0] = 1;
    pattern[1] = 3;
    pattern[2] = 1;
    pattern[3] = 3;
    pattern[4] = 1;
    pattern[5] = 3;
    pattern[6] = 1;
    pattern[7] = 3;
    pattern[8] = 1;
    pattern[9] = 3;
    pattern[10] = 1;
    pattern[11] = 3;
    pattern[12] = 1;

    // percorre o vetor
    int patternCounter = 0;
    for (int i = 0; i < n; i++)
    {
        // se o numero [i] for igual ao primeiro numero do padrao (patternCounter = 0)
        if (values[i] == pattern[patternCounter])
        {
            // aumente em um o contador do padrao
            patternCounter++;
            // analize os proximos 'patternSize' numeros
            for (int j = (i + 1); j < (i + patternSize); j++)
            {
                // a cada proximo consecutivo que for igual, aumente o contador de padrao
                if (pattern[patternCounter] == values[j])
                {
                    patternCounter++;
                    // se em algum momento o contador for do mesmo tamanho do padrao, retorne verdadeiro
                    if (patternCounter == patternSize)
                    {
                        cout << "Resultado: Padrao de faixa de pedestres encontrado." << endl;
                        return 0;
                    }
                }
                // se nao, zere o contador
                else
                {
                    patternCounter = 0;
                    break;
                }
            }
        }
    }
    // ao final, se o contador nunca for igual ao tamanho do padrao, retorne falso
    cout << "Resultado: Padrao de faixa de pedestres nao encontrado." << endl;

    free(values);

    return 0;
}