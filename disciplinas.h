#ifndef DISCIPLINAS_H
#define DISCIPLINAS_H
#include <stdbool.h>

typedef struct
{
    char codigo[8];
    char nome_dis[100];
    int periodo;
    char preRequisitos[5][10];
    int numPreRequisitos;
    char coRequisitos[5][10];
    int numCoRequisitos;
    char dias[4];
    char turno;
    char horarios[5];
    int numDiasSem;
    int cargaHoraria;
    int tipo; // tipo 0 - obrigatoria; tipo 1 - eletiva; tipo 2 - extensao
} Disciplina;

Disciplina obrigatorias[] = {
    // 1o periodo
    {"COMP359", "Programa��o 1", 1, {}, 0, {}, 0, "6", 'T', "3456", 1, 72, 0},
    {"COMP360", "L�gica para Computa��o", 1, {}, 0, {}, 0, "24", 'T', "34", 2, 72, 0},
    {"COMP361", "Computa��o, Sociedade e �tica", 1, {}, 0, {}, 0, "24", 'T', "56", 2, 72, 0},
    {"COMP362", "Matem�tica Discreta", 1, {}, 0, {}, 0, "35", 'T', "12", 2, 72, 0},
    {"COMP363", "C�lculo Diferencial e Integral", 1, {}, 0, {}, 0, "35", 'T', "3456", 2, 144, 0},

    // 2o periodo
    {"COMP364", "Estrutura de Dados", 2, {"COMP359"}, 1, {}, 0, "35", 'M', "56", 2, 72, 0},
    {"COMP365", "Banco de Dados", 2, {}, 0, {}, 0, "24", 'T', "12", 2, 72, 0},
    {"COMP366", "Organiza��o e Arquitetura de Computadores", 2, {}, 0, {}, 0, "35", 'M', "34", 2, 72, 0},
    {"COMP367", "Geometria Anal�tica", 2, {}, 0, {}, 0, "24", 'T', "34", 2, 72, 0},

    // 3o periodo
    {"COMP368", "Redes de Computadores", 3, {"COMP359"}, 1, {}, 0, "24", 'T', "34", 2, 72, 0},
    {"COMP369", "Teoria dos Grafos", 3, {"COMP364", "COMP362"}, 2, {}, 0, "25", 'T', "12", 2, 72, 0},
    {"COMP370", "Probabilidade e Estat�stica", 3, {"COMP363"}, 1, {}, 0, "24", 'M', "56", 2, 72, 0},
    {"COMP371", "�lgebra Linear", 3, {"COMP367"}, 1, {}, 0, "24", 'M', "34", 2, 72, 0},

    // 4o periodo
    {"COMP372", "Programa��o 2", 4, {"COMP364", "COMP365", "COMP368"}, 3, {"COMP373"}, 1, "4", 'T', "3456", 1, 72, 0},
    {"COMP373", "Programa��o 3", 4, {"COMP364", "COMP365", "COMP368"}, 3, {"COMP372"}, 1, "35", 'T', "34", 2, 72, 0},
    {"COMP374", "Projeto e An�lise de Algoritmos", 4, {"COMP364", "COMP369"}, 2, {}, 0, "24", 'T', "56", 2, 72, 0},
    {"COMP376", "Teoria da Computa��o", 4, {}, 0, {}, 0, "24", 'T', "12", 2, 72, 0},

    // 5o periodo
    {"COMP378", "Sistemas Operacionais", 5, {"COMP366"}, 1, {}, 0, "24", 'T', "12", 2, 72, 0},
    {"COMP379", "Compiladores", 5, {"COMP364", "COMP376"}, 2, {}, 0, "24", 'T', "34", 2, 72, 0},
    {"COMP380", "Intelig�ncia Artificial", 5, {"COMP360", "COMP374"}, 2, {}, 0, "35", 'T', "34", 2, 72, 0},
    {"COMP381", "Computa��o Gr�fica", 5, {}, 0, {}, 0, "35", 'T', "56", 2, 72, 0},

    // 6o periodo
    {"COMP382", "Projeto e Desenvolvimento de Sistemas", 6, {}, 0, {}, 0, "245", 'M', "3456", 3, 288, 0},

    // 7o periodo
    {"COMP386", "Metodologia de Pesquisa e Trabalho Individual", 7, {}, 0, {}, 0, "35", 'T', "12", 2, 72, 0},
    {"COMP387", "No��es de Direito", 7, {}, 0, {}, 0, "3", 'T', "3456", 1, 72, 0},
};

int NUM_OBRIGATORIAS = sizeof(obrigatorias) / sizeof(Disciplina);

Disciplina extensao[] = {
    {"COMP377", "ACE 1: Projeto 1", 4, {}, 0, {}, 0, "6", 'T', "12", 1, 57, 2},
    {"COMP383", "ACE 2: Continuidade do projeto 1", 5, {}, 0, {}, 0, "6", 'T', "34", 1, 57, 2},
    {"COMP384", "ACE 3: Projeto 2", 6, {}, 0, {}, 0, "5", 'T', "12", 1, 57, 2},
    {"COMP383", "ACE 4: Continuidade do projeto 2", 7, {}, 0, {}, 0, "5", 'T', "345", 1, 47, 2},
    {"COMP385", "ACE 5: Evento", 8, {}, 0, {}, 0, "5", 'T', "56", 1, 57, 2}
};

int NUM_EXTENSAO = sizeof(extensao) / sizeof(Disciplina);

Disciplina eletivas[] = {
    {"COMP389", "Conceitos de Linguagem de Programação", 0, {}, 0, {}, 0, "35", 'T', "34", 2, 72, 1},
    {"COMP390", "Aprendizagem de Máquina", 0, {"COMP404"}, 1, {}, 0, "24", 'T', "56", 2, 72, 1},
    {"COMP391", "Sistemas Digitais", 0, {"COMP404"}, 1, {}, 0, "56", 'M', "34", 2, 72, 1},
    {"COMP392", "Sistemas Distribuídos", 0, {}, 0, {}, 0, "6", 'T', "1234", 1, 72, 1},
    {"COMP393", "Redes Neurais e Aprendizado Profundo", 0, {}, 0, {}, 0, "35", 'T', "34", 2, 72, 1}, // por algum motivo fpga e redes neurais possuem o mesmo codigo de disciplina no ppc
    {"COMP394", "FPGA", 0, {}, 0, {}, 0, "25", 'M', "56", 2, 72, 1},  //mudei o cod para 394 pra nao ter conflito HORARIO INVENTADO
    {"COMP395", "Interação Homem-Máquina", 0, {"COMP373"}, 1, {}, 0, "24", 'T', "34", 2, 72, 1},
    {"COMP396", "Processamento Digital de Imagens", 0, {"COMP381"}, 1, {}, 0, "35", 'T', "12", 2, 72, 1},
    {"COMP397", "Computação Evolucionária", 0, {}, 0, {}, 0, "24", 'T', "12", 2, 72, 1},
    {"COMP398", "Sistemas Embarcados", 0, {}, 0, {}, 0, "35", 'T', "56", 2, 72, 1},
    {"COMP399", "Gerência de Projeto", 0, {"COMP382"}, 1, {}, 0, "35", 'T', "56", 2, 72, 1},
    {"COMP400", "Visão Computacional", 0, {}, 0, {}, 0, "25", 'M', "56", 2, 72, 1},
    {"COMP401", "Ciência de Dados", 0, {"COMP370"}, 1, {}, 0, "24", 'M', "34", 2, 72, 1},
    {"COMP402", "Microcoontroladores e Aplicações", 0, {}, 0, {}, 0, "24", 'M', "56", 2, 72, 1},
    {"COMP403", "Segurança de Sistemas Computacionais", 0, {"COMP368"}, 1, {}, 0, "46", 'M', "34", 2, 72, 1},
    {"COMP404", "Cálculo 3", 0, {"COMP363"}, 1, {}, 0, "36", 'M', "12", 2, 72, 1}
};

int NUM_ELETIVAS = sizeof(eletivas) / sizeof(Disciplina);

#endif