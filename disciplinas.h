#ifndef DISCIPLINAS_H
#define DISCIPLINAS_H

typedef struct 
{
    char codigo[10];
    char nome[100];
    int periodo;
    char preRequisitos[5][10];
    int numPreRequisitos;
    char horario[10];
    int numHorarios;
    int cargaHoraria;
} Disciplina;

// TODO: tem apenas as disciplinas do primeiro e segundo periodos
Disciplina obrigatorias[] = {
    {"COMP359", "Programação 1", 1, {}, 0, "6T3456", 1, 72},
    {"COMP360", "Lógica para Computação", 1, {}, 0, "24T34", 2, 72},
    {"COMP361", "Computação, Sociedade e Ética", 1, {}, 0, "24T56", 2, 72},
    {"COMP362", "Matemática Discreta", 1, {}, 0, "35T12", 2, 72},
    {"COMP363", "Cálculo Diferencial e Integral", 1, {}, 0, "35T3456", 2, 72},
    {"COMP364", "Estrutura de Dados", 2, {"COMP359"}, 1, "35T12", 2, 72},
    {"COMP365", "Banco de Dados", 2, {}, 0, "24T12", 2, 72},
    {"COMP366", "Organização e Arquitetura de Computadores", 2, {}, 0, "35T34", 2, 72},
    {"COMP367", "Geometria Analítica", 2, {}, 0, "24M34", 2, 72}
};

// TODO: todas as disciplinas eletivas
// Disciplina *eletivas = {};

#endif