/****

LAED1 - Projeto - Detecção de faixa de pedestres em uma imagem

Alunos(as): Arthur Severo de Souza

Data: 26/03/2021 

****/

#include <iostream>
#include <fstream>

using namespace std;

#define ITERATOR 1
#define MAX_SIZE 1000

typedef struct
{
    int key;
} item;

typedef struct
{
    item Item[MAX_SIZE];
    int begin, end;
} array;

void clear(array *array)
{
    array->begin = ITERATOR;
    array->end = array->begin;
}

int isEmpty(array array)
{
    return (array.begin == array.end);
}

void insert(item x, array *array)
{
    if (array->end > MAX_SIZE)
        printf("Lista esta cheia\n");
    else
    {
        array->Item[array->end - 1] = x;
        array->end++;
    }
}

void remove(int p, array *array, item *Item)
{
    int aux;

    if (isEmpty(*array) || p >= array->end)
    {
        printf(" Erro   Posicao nao existe\n");
        return;
    }
    *Item = array->Item[p - 1];
    array->end--;
    for (aux = p; aux < array->end; aux++)
        array->Item[aux - 1] = array->Item[aux];
}

void printAll(array array)
{
    int aux;

    for (aux = array.begin - 1; aux <= (array.end - 2); aux++)
        printf("%d\n", array.Item[aux].key);
}

int main()
{

    // le o nome do arquivo
    string name;
    cout << "Digite o nome do arquivo: ";
    cin >> name;

    // abre o arquivo e atribui todo seu conteudo a uma string
    ifstream file(name);

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

    // registra o padrao a ser procurado
    int patternSize = 11;
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

    // pega o numero de perfis apresentado pelo arquivo e o converte em um numero inteiro
    int charCounter = 0;
    string lStr = "";
    do
    {
        lStr.push_back(fullText[charCounter]);
        charCounter++;
    } while (fullText[charCounter] != '\n');
    int l = atoi(lStr.c_str());

    if (l <= 0)
    {
        cout << "Resultado:  Pista sem faixa de pedestres" << endl;
        return 0;
    }

    item currentItem;
    array numbers;
    clear(&numbers);

    // loop que roda para cada perfil
    for (int i = 0; i < l; i++)
    {
        // pega o numero de elementos do perfil atual apresentado pelo arquivo e o converte em um numero inteiro
        string nStr = "";
        do
        {
            nStr.push_back(fullText[charCounter]);
            charCounter++;
        } while (fullText[charCounter] != '\n');
        int n = atoi(nStr.c_str());

        // pega os numeros do vetor e os converte em inteiros, registrando um em cada posicao de um vetor
        for (int j = 0; j < n; j++)
        {
            string currentNumber = "";
            do
            {
                currentNumber.push_back(fullText[charCounter]);
                charCounter++;
            } while (fullText[charCounter] != ' ' && fullText[charCounter] != '\n');
            currentItem.key = atoi(currentNumber.c_str());
            currentNumber.clear();
            insert(currentItem, &numbers);
        }

        // faz um novo vetor com os valores de cada segmento
        array values;
        clear(&values);
        for (int i = 0; i < n; i++)
        {
            if (numbers.Item[i].key != numbers.Item[i + 1].key)
            {
                switch (numbers.Item[i].key)
                {
                case 0:
                    currentItem.key = 1;
                    insert(currentItem, &values);
                    break;
                case 128:
                    currentItem.key = 2;
                    insert(currentItem, &values);
                    break;
                case 255:
                    currentItem.key = 3;
                    insert(currentItem, &values);
                    break;
                default:
                    break;
                }
            }
        }

        // percorre os valores do perfil atual
        int patternCounter = 0;
        for (int i = 0; i < values.end; i++)
        {
            // se o valor [i] for igual ao primeiro numero do padrao (patternCounter = 0)
            if (values.Item[i].key == pattern[patternCounter])
            {
                // aumente em um o contador do padrao
                patternCounter++;
                // analize os proximos 'patternSize' numeros
                for (int j = (i + 1); j < (i + patternSize); j++)
                {
                    // a cada proximo consecutivo que for igual, aumente o contador de padrao
                    if (pattern[patternCounter] == values.Item[j].key)
                    {
                        patternCounter++;
                        if (patternCounter > values.end)
                        {
                            cout << "Resultado: Pista sem faixa de pedestres" << endl;
                            return 0;
                        }
                        // se em algum momento o contador for do mesmo tamanho do padrao, retorne verdadeiro
                        if (patternCounter == patternSize)
                        {
                            cout << "Resultado: Pista com faixa de pedestres" << endl;
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
        clear(&numbers);
        clear(&values);
    }

    // ao final, se o contador nunca for igual ao tamanho do padrao, retorne falso
    cout << "Resultado: Pista sem faixa de pedestres" << endl;

    return 0;
}