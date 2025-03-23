#ifndef DISCIPLINAS_H
#define DISCIPLINAS_H
#include <stdbool.h> 
typedef struct {
    char codigo[10];
    char nome_dis[100];
    int periodo;
    char preRequisitos[5][10];
    int numPreRequisitos;
    char coRequisitos[5][10];
    int numCoRequisitos;
    char horario[10];
    int numHorarios;
    int cargaHoraria;
    bool enfase;
    bool eletiva;
    int tipo;
} Disciplina;

Disciplina obrigatorias[] = {
    {"COMP359", "Programacao 1", 1, {}, 0, {}, 0, "6T3456", 1, 72, false, false, 1},
    {"COMP360", "Logica para Computacao", 1, {}, 0, {}, 0, "24T34", 2, 72, false, false, 1},
    {"COMP361", "Computacao, Sociedade e Etica", 1, {}, 0, {}, 0, "24T56", 2, 72, false, false, 1},
    {"COMP362", "Matematica Discreta", 1, {}, 0, {}, 0, "35T12", 2, 72, false, false, 1},
    {"COMP363", "Calculo Diferencial e Integral", 1, {}, 0, {}, 0, "35T3456", 2, 144, false, false, 1},

    {"COMP364", "Estrutura de Dados", 2, {"COMP359"}, 1, {}, 0, "35M56", 2, 72, false, false, 1},
    {"COMP365", "Banco de Dados", 2, {}, 0, {}, 0, "24T12", 2, 72, false, false, 1},
    {"COMP366", "Organizacao e Arquitetura de Computadores", 2, {}, 0, {}, 0, "35M34", 2, 72, false, false, 1},
    {"COMP367", "Geometria Analitica", 2, {}, 0, {}, 0, "24T34", 2, 72, false, false, 1},

    {"COMP368", "Redes de Computadores", 3, {"COMP359"}, 1, {}, 0, "24T34", 2, 72, false, false, 1},
    {"COMP369", "Teoria dos Grafos", 3, {"COMP364", "COMP362"}, 2, {}, 0, "25T12", 2, 72, false, false, 1},
    {"COMP370", "Probabilidade e Estatística", 3, {"COMP363"}, 1, {}, 0, "24M56", 2, 72, false, false, 1},
    {"COMP371", "Álgebra Linear", 3, {"COMP367"}, 1, {}, 0, "24M34", 2, 72, false, false, 1},

    {"COMP372", "Programação 2", 4, {"COMP364", "COMP365", "COMP368"}, 3, {"COMP373"}, 1, "4T3456", 1, 72, false, false, 1},
    {"COMP373", "Programação 3", 4, {"COMP364", "COMP365", "COMP368"}, 3, {"COMP372"}, 1, "35T34", 2, 72, false, false, 1},
    {"COMP374", "Projeto e Análise de Algoritmos", 4, {"COMP364", "COMP369"}, 2, {}, 0, "24T56", 2, 72, false, false, 1},
    {"COMP376", "Teoria da Computação", 4, {}, 0, {}, 0, "24T12", 2, 72, false, false, 1},

    {"COMP378", "Sistemas Operacionais", 5, {"COMP366"}, 1, {}, 0, "24T12", 2, 72, false, false, 1},
    {"COMP379", "Compiladores", 5, {"COMP364", "COMP376"}, 2, {}, 0, "24T34", 2, 72, false, false, 1},
    {"COMP380", "Inteligência Artificial", 5, {"COMP360", "COMP374"}, 2, {}, 0, "35T34", 2, 72, false, false, 1},
    {"COMP381", "Computação Gráfica", 5, {}, 0, {}, 0, "35T56", 2, 72, false, false, 1},

    {"COMP382", "Projeto e Desenvolvimento de Sistemas", 6, {}, 0, {}, 0, "245M3456", 3, 288, false, false, 1},

    {"COMP386", "Metodologia de Pesquisa e Trabalho Individual", 7, {}, 0, {}, 0, "35T12", 2, 72, false, false, 1},
    {"COMP387", "Noções de Direito", 7, {}, 0, {}, 0, "3T3456", 1, 72, false, false, 1},
};

// Disciplina enfase[]
// {

// }

#endif