#ifndef ALUNO_H
#define ALUNO_H
#include "disciplinas.h"

typedef struct {
    int periodo_atual;
    Disciplina cursadas[100];
    int num_cursadas;
    Disciplina planejadas[6];
    int num_planejadas;
} Aluno;

#endif