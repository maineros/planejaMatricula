#ifndef ALUNO_H
#define ALUNO_H
#include "disciplinas.h"

#define TOTAL_OBRIGATORIAS 2016
#define TOTAL_ELETIVAS 936 // 576 de eletivas 'comuns' + 360 de eletivas de enfase, pois ainda nao estamos diferenciando
#define TOTAL_EXTENSAO 375
#define TOTAL_COMPLEMENTARES 240

#define TOTAL_DISCIPLINAS 60 // total de disciplinas durante toda a graduacao
#define DISCIPLINAS_POR_PERIODO 6
#define MAX_PERIODOS 10

#define MAXIMO_HORAS 540 // maximo de carga horaria por semestre

typedef struct Historico
{
    char codigo[8];
    double mediaFinal;
    bool trancada;
} Historico;
typedef struct Aluno
{
    int periodoAtual;
    Historico cursadas[100];
    int numCursadas;
    int horasCumpridasObrigatorias;
    int horasCumpridasEletivas;
    int horasCumpridasExtensao;
    int horasCumpridasComplementares;
} Aluno;
typedef struct Periodo
{
    int periodo;
    Disciplina planejadas[6];
    int numPlanejadas;
    int numHoras;
    bool dias[5];
} Periodo;

#endif