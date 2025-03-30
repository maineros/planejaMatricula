#ifndef ALUNO_H
#define ALUNO_H
#include "disciplinas.h"

int TOTAL_OBRIGATORIAS = 2376;
int TOTAL_ELETIVAS = 576;
int TOTAL_EXTENSAO = 240;
int TOTAL_COMPLEMENTARES = 375;
typedef struct
{
    char codigo[8];
    double mediaFinal;
    bool trancada;
} Historico;
typedef struct
{
    int periodoAtual;
    Historico cursadas[100];
    int numCursadas;
    Disciplina planejadas[6];
    int numPlanejadas;
    int horasCumpridasObrigatorias;
    int horasCumpridasEletivas;
    int horasCumpridasExtensao;
    int horasCumpridasComplementares;
} Aluno;

#endif