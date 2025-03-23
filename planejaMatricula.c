#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "planejaMatricula.h"
#include "disciplinas.h"
#include "letrasValores.h"
#include "aluno.h"

// nao eh permitido que o aluno esteja matriculado em uma disciplina sem ter seu pre-requisito
// nao eh permitido que o aluno esteja matriculado em duas disciplinas com choque de horario
// eh obrigatorio que o aluno esteja matriculado em pelo menos uma disciplina

int main()
{
    char nomeCompleto[] = "daniel araujo albuquerque";
    char nome1[20], nome2[20], nome3[20], nome4[20];
    leNomesComCircularidade(nomeCompleto, nome1, nome2, nome3, nome4);

    // char historico[][7] = {"COMP359", "COMP360", "COMP361", "COMP362", "COMP363"};

    Aluno aluno = {1, {}, 0, {}, 0};
    int num_obrigatorias = sizeof(obrigatorias) / sizeof(obrigatorias[0]);

    // DEBUG 
    int peso1 = calculaPeso(nome1);
    int peso2 = calculaPeso(nome2);
    int peso3 = calculaPeso(nome3);

    printf("pesos = %d %d %d\n", peso1, peso2, peso3);

    printf("%d\n", calculaLimiteDisciplinas(peso1));
    printf("%s\n", calculaTempoConclusao(peso2));
    printf("%s\n", calculaEnfase(peso2));
    printf("%s\n", encontraDisciplinas(peso1));
    
    // DEBUG
    planejarSemestre(&aluno, obrigatorias, num_obrigatorias);
    reservarHorasFlexiveis(&aluno);

    printf("Disciplinas planejadas para o proximo semestre:\n");
    for (int i = 0; i < aluno.num_planejadas; i++)
        printf("%s - %s\n", aluno.planejadas[i].codigo, aluno.planejadas[i].nome_dis);

    return 0;
}

void leNomesComCircularidade(const char *nomeCompleto, char nome1[], char nome2[], char nome3[], char nome4[])
{
    // array para armazenar os nomes
    char nomes[4][20];
    int i = 0;

    // usando strtok para separar o nome completo em partes
    char nomeTemp[100];
    strcpy(nomeTemp, nomeCompleto);  // copia do nome completo para ser usada no strtok
    char *token = strtok(nomeTemp, " ");  // os nomes serao divididos pelo espaco entre eles

    // preencher os nomes com o maximo de 4 partes
    while (token != NULL && i < 4) {
        strcpy(nomes[i], token);
        token = strtok(NULL, " ");
        i++;
    }

    // se tiver menos de 4 nomes, garantir a circularidade
    for (int j = i; j < 4; j++) {
        strcpy(nomes[j], nomes[j - i]);
    }

    // copiando para as variaveis de saida
    strcpy(nome1, nomes[0]);
    strcpy(nome2, nomes[1]);
    strcpy(nome3, nomes[2]);
    strcpy(nome4, nomes[3]);
}

int obtemValorLetra(char letra)
{
    int len = strlen(letras);
    for (int i = 0; i < len; i++)
        if (tolower(letra) == letras[i]) return valores[i]; // retorna o respectivo valor da letra
    
    return 0;
}

int calculaPeso(char *nome)
{
    int soma = 0;

    for (int i = 0; nome[i] != '\0'; i++)
    {
        soma += obtemValorLetra(nome[i]);
    }

    return soma;
}

int calculaLimiteDisciplinas(int peso)
{
    // limite maximo de disciplinas por semestre
    // somar todos os numeros do primeiro nome e dividir por 3; valor do resto:
    // 0 = maximo 10
    // 1 = maximo 8
    // 2 = maximo 6

    return (peso % 3 == 0) ? 10 : (peso % 3 == 1) ? 8 : 6;
}

const char* calculaTempoConclusao(int peso)
{
    // tempo no qual o aluno deseja concluir o curso
    // somar todos os numeros do proximo nome e dividir por 3; valor do resto:
    // 0: no menor tempo possivel
    // 1: no maior tempo possivel
    // 2: tempo medio possivel

    return (peso % 3 == 0) ? "Menor tempo possivel" :
           (peso % 3 == 1) ? "Maior tempo possivel" :
                             "Tempo medio possivel";
}

const char* calculaEnfase(int peso)
{
    // escolha das enfases
    // somar todos os numeros do proximo nome e dividir por 3; valor do resto:
    // 0: enfase desejada pelo aluno
    // 1: enfase que diminui o tempo de conclusao de curso pelo aluno
    // 2: nenhuma enfase

    return (peso % 3 == 0) ? "Enfase desejada pelo aluno" :
           (peso % 3 == 1) ? "Enfase para menor tempo de conclusao" :
                             "Sem Enfase"; 
}

const char* encontraDisciplinas(int peso)
{
    // escolha das disciplinas deve seguir a seguinte orientacao:
    // somar todos os numeros do proximo nome e dividir por 3; valor do resto:
    // 0: as disciplinas devem ocupar o menor numero de dias possiveis
    // 1: as disciplinas devem pertencer a um mesmo turno
    // 2: o aluno nao deve extrapolar o limite de 3 disciplinas por dia, mas deve ir todos os dias a ufal

    return (peso % 3 == 0) ? "Menor numero de dias possivel" :
           (peso % 3 == 1) ? "Mesmo turno" :
                             "Nao extrapolar 3 disciplinas/dia, mas ir todos os dias"; 
}

bool verificaPreRequisitos(Aluno *aluno, Disciplina disciplina)
{
    // bubble sort para verificar, para cada disciplina, se o aluno possui os pre-requisitos dela em suas disciplinas cursadas
    for (int i = 0; i < disciplina.numPreRequisitos; i++) // percorre os pre-requisitos de uma dada disciplina
    {
        bool encontrou = false;
        for (int j = 0; j < aluno->num_cursadas; j++) // verifica, para cada pre-requisito, se o aluno possui essa disciplina p-r cursada
        {
            if (strcmp(disciplina.preRequisitos[i], aluno->cursadas[j].codigo) == 0)
            {
                encontrou = true;
                break;
            }
        }

        if (!encontrou)
            return false;
    }
    return true;
}

void reservarHorasFlexiveis(Aluno *aluno)
{
    printf("Reservando 2 horas por dia para horas flexíveis.\n");
}

void planejarSemestre(Aluno *aluno, Disciplina obrigatorias[], int num_obrigatorias)
{
    // percorre ate o numero de disciplinas obrigatorias
    for (int i = 0; i < num_obrigatorias; i++)
    {
        if (obrigatorias[i].periodo == aluno->periodo_atual && // verifica se o periodo em que a disciplina eh ofertada no fluxo padrao coincide com o periodo atual do aluno
            verificaPreRequisitos(aluno, obrigatorias[i]) && // verifica se o aluno possui todos os pre-requisitos de cada disciplina
            aluno->num_planejadas < 6) // verifica se o numero de materias nao esta extrapolando o max para o aluno
        {    
            aluno->planejadas[aluno->num_planejadas] = obrigatorias[i];
            aluno->num_planejadas++;
        }
    }
}