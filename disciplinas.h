#ifndef DISCIPLINAS_H
#define DISCIPLINAS_H
#include <stdbool.h>

typedef struct Disciplina
{
    char codigo[8];
    char nome_dis[100];
    int periodo;
    char preRequisitos[5][8];
    int numPreRequisitos;
    char coRequisitos[5][8];
    int numCoRequisitos;
    char dias[4];
    char turno;
    char horarios[5];
    int numDiasSem;
    int cargaHoraria;
} Disciplina;

Disciplina obrigatorias[] = {
    // 1o periodo
    {"COMP359", "Programa��o 1", 1, {}, 0, {}, 0, "6", 'T', "3456", 1, 72},
    {"COMP360", "L�gica para Computa��o", 1, {}, 0, {}, 0, "24", 'T', "34", 2, 72},
    {"COMP361", "Computa��o, Sociedade e �tica", 1, {}, 0, {}, 0, "24", 'T', "56", 2, 72},
    {"COMP362", "Matem�tica Discreta", 1, {}, 0, {}, 0, "35", 'T', "12", 2, 72},
    {"COMP363", "C�lculo Diferencial e Integral", 1, {}, 0, {}, 0, "35", 'T', "3456", 2, 144},

    // 2o periodo
    {"COMP364", "Estrutura de Dados", 2, {"COMP359"}, 1, {}, 0, "35", 'M', "56", 2, 72},
    {"COMP365", "Banco de Dados", 2, {}, 0, {}, 0, "24", 'T', "12", 2, 72},
    {"COMP366", "Organiza��o e Arquitetura de Computadores", 2, {}, 0, {}, 0, "35", 'M', "34", 2, 72},
    {"COMP367", "Geometria Anal�tica", 2, {}, 0, {}, 0, "24", 'T', "34", 2, 72},

    // 3o periodo
    {"COMP368", "Redes de Computadores", 3, {"COMP359"}, 1, {}, 0, "24", 'T', "34", 2, 72},
    {"COMP369", "Teoria dos Grafos", 3, {"COMP364", "COMP362"}, 2, {}, 0, "25", 'T', "12", 2, 72},
    {"COMP370", "Probabilidade e Estat�stica", 3, {"COMP363"}, 1, {}, 0, "24", 'M', "56", 2, 72},
    {"COMP371", "�lgebra Linear", 3, {"COMP367"}, 1, {}, 0, "24", 'M', "34", 2, 72},

    // 4o periodo
    {"COMP372", "Programa��o 2", 4, {"COMP364", "COMP365", "COMP368"}, 3, {"COMP373"}, 1, "4", 'T', "3456", 1, 72},
    {"COMP373", "Programa��o 3", 4, {"COMP364", "COMP365", "COMP368"}, 3, {"COMP372"}, 1, "35", 'T', "34", 2, 72},
    {"COMP374", "Projeto e An�lise de Algoritmos", 4, {"COMP364", "COMP369"}, 2, {}, 0, "24", 'T', "56", 2, 72},
    {"COMP376", "Teoria da Computa��o", 4, {}, 0, {}, 0, "24", 'T', "12", 2, 72},

    // 5o periodo
    {"COMP378", "Sistemas Operacionais", 5, {"COMP366"}, 1, {}, 0, "24", 'T', "12", 2, 72},
    {"COMP379", "Compiladores", 5, {"COMP364", "COMP376"}, 2, {}, 0, "24", 'T', "34", 2, 72},
    {"COMP380", "Intelig�ncia Artificial", 5, {"COMP360", "COMP374"}, 2, {}, 0, "35", 'T', "34", 2, 72},
    {"COMP381", "Computa��o Gr�fica", 5, {}, 0, {}, 0, "35", 'T', "56", 2, 72},

    // 6o periodo
    {"COMP382", "Projeto e Desenvolvimento de Sistemas", 6, {}, 0, {}, 0, "245", 'M', "3456", 3, 288},

    // 7o periodo
    {"COMP386", "Metodologia de Pesquisa e Trabalho Individual", 7, {}, 0, {}, 0, "35", 'T', "12", 2, 72},
    {"COMP387", "No��es de Direito", 7, {}, 0, {}, 0, "3", 'T', "3456", 1, 72},
};

int NUM_OBRIGATORIAS = sizeof(obrigatorias) / sizeof(Disciplina);

Disciplina extensao[] = {
    {"COMP377", "ACE 1: Projeto 1", 4, {}, 0, {}, 0, "6", 'T', "12", 1, 57},
    {"COMP383", "ACE 2: Continuidade do projeto 1", 5, {}, 0, {}, 0, "6", 'T', "34", 1, 57},
    {"COMP384", "ACE 3: Projeto 2", 6, {}, 0, {}, 0, "5", 'T', "12", 1, 57},
    {"COMP383", "ACE 4: Continuidade do projeto 2", 7, {}, 0, {}, 0, "5", 'T', "345", 1, 47},
    {"COMP385", "ACE 5: Evento", 8, {}, 0, {}, 0, "5", 'T', "56", 1, 57}
};

int NUM_EXTENSAO = sizeof(extensao) / sizeof(Disciplina);

Disciplina eletivas[] = {
    // eletivas de enfase
    {"COMP389", "Conceitos de Linguagem de Programa��o", 0, {}, 0, {}, 0, "35", 'T', "34", 2, 72},
    {"COMP390", "Aprendizagem de M�quina", 0, {"COMP404"}, 1, {}, 0, "24", 'T', "56", 2, 72},
    {"COMP391", "Sistemas Digitais", 0, {"COMP404"}, 1, {}, 0, "56", 'M', "34", 2, 72},
    {"COMP392", "Sistemas Distribu�dos", 0, {}, 0, {}, 0, "6", 'T', "1234", 1, 72},
    {"COMP393", "Redes Neurais e Aprendizado Profundo", 0, {}, 0, {}, 0, "35", 'T', "34", 2, 72},
    {"COMP394", "FPGA", 0, {}, 0, {}, 0, "25", 'M', "56", 2, 72},
    {"COMP395", "Intera��o Homem-M�quina", 0, {"COMP373"}, 1, {}, 0, "24", 'T', "34", 2, 72},
    {"COMP396", "Processamento Digital de Imagens", 0, {"COMP381"}, 1, {}, 0, "35", 'T', "12", 2, 72},
    {"COMP397", "Computa��o Evolucion�ria", 0, {}, 0, {}, 0, "24", 'T', "12", 2, 72},
    {"COMP398", "Sistemas Embarcados", 0, {}, 0, {}, 0, "35", 'T', "56", 2, 72},
    {"COMP399", "Ger�ncia de Projeto", 0, {"COMP382"}, 0, {}, 0, "35", 'T', "56", 2, 72},
    {"COMP400", "Vis�o Computacional", 0, {}, 0, {}, 0, "25", 'M', "56", 2, 72},
    {"COMP401", "Ci�ncia de Dados", 0, {"COMP370"}, 1, {}, 0, "24", 'M', "34", 2, 72},
    {"COMP402", "Microcoontroladores e Aplica��es", 0, {}, 0, {}, 0, "24", 'M', "56", 2, 72},
    {"COMP403", "Seguran�a de Sistemas Computacionais", 0, {"COMP368"}, 1, {}, 0, "46", 'M', "34", 2, 72},
    {"COMP404", "C�lculo 3", 0, {"COMP363"}, 1, {}, 0, "36", 'M', "12", 2, 72},

    // demais eletivas
    {"COMP405", "T�picos em Ci�ncia da Computa��o 1", 0, {}, 0, {}, 0, "26", 'T', "34", 2, 72},
    {"COMP406", "T�picos em Ci�ncia da Computa��o 2", 0, {}, 0, {}, 0, "34", 'M', "12", 2, 72},
    {"COMP407", "T�picos em Ci�ncia da Computa��o 3", 0, {}, 0, {}, 0, "5", 'M', "56", 2, 72},
    {"COMP409", "T�picos em Matem�tica para Comp. 1", 0, {}, 0, {}, 0, "2", 'T', "456", 3, 72},
    {"COMP410", "T�picos em Matem�tica para Comp. 2", 0, {}, 0, {}, 0, "45", 'M', "23", 2, 72},
    {"COMP411", "T�picos em Matem�tica para Comp. 3", 0, {}, 0, {}, 0, "6", 'T', "123", 3, 72},
    {"COMP412", "T�picos em F�sica para Computa��o 1", 0, {}, 0, {}, 0, "3", 'T', "234", 3, 72},
    {"COMP413", "T�picos em F�sica para Computa��o 2", 0, {}, 0, {}, 0, "4", 'M', "12", 2, 72},
    {"COMP414", "T�picos em F�sica para Computa��o 3", 0, {}, 0, {}, 0, "56", 'T', "34", 2, 72},
    {"CC1941", "C�lculo 4", 0, {}, 0, {}, 0, "35", 'T', "12", 2, 72},
    {"CC1942", "C�lculo Num�rico", 0, {}, 0, {}, 0, "24", 'M', "34", 2, 72},
    {"CC1943", "Circuitos Digitais", 0, {}, 0, {}, 0, "4", 'T', "1234", 4, 72},
    {"CC1944", "Circuitos Impressos", 0, {}, 0, {}, 0, "56", 'M', "12", 2, 72},
    {"CC1945", "Fundamentos de Libras", 0, {}, 0, {}, 0, "3", 'T', "56", 2, 72},
    {"CC1946", "Geometria Computacional", 0, {}, 0, {}, 0, "25", 'M', "45", 2, 72},
    {"CC1947", "Pesquisa Operacional", 0, {}, 0, {}, 0, "6", 'T', "123", 3, 72},
    {"CC1948", "Programa��o para Sistemas Embarcados", 0, {}, 0, {}, 0, "34", 'M', "23", 2, 72},
    {"CC1949", "Projeto de Sistemas Embarcados", 0, {}, 0, {}, 0, "5", 'T', "3456", 4, 72},
    {"CC1950", "T�picos em Arquitetura de Comp.", 0, {}, 0, {}, 0, "26", 'T', "12", 2, 72},
    {"CC1951", "T�picos em Banco de Dados", 0, {}, 0, {}, 0, "3", 'M', "123", 3, 72},
    {"CC1952", "T�picos em Computa��o Cient�fica", 0, {}, 0, {}, 0, "45", 'T', "34", 2, 72},
    {"CC1953", "T�picos em Computa��o Paralela", 0, {}, 0, {}, 0, "24", 'T', "56", 2, 72},
    {"CC1954", "T�picos em Computa��o Visual", 0, {}, 0, {}, 0, "5", 'M', "234", 3, 72},
    {"CC1955", "T�picos em Comunica��o de Dados", 0, {}, 0, {}, 0, "6", 'M', "56", 2, 72},
    {"CC1956", "T�picos em Desenvolvimento de Sist.", 0, {}, 0, {}, 0, "35", 'M', "12", 2, 72},
    {"CC1957", "T�picos em Engenharia de Software", 0, {}, 0, {}, 0, "4", 'T', "56", 2, 72},
    {"CC1958", "T�picos em Humanidades", 0, {}, 0, {}, 0, "2", 'T', "123", 3, 72},
    {"CC1959", "T�picos em Inform�tica na Educa��o", 0, {}, 0, {}, 0, "3", 'M', "45", 2, 72},
    {"CC1960", "T�picos em Intelig�ncia Artificial", 0, {}, 0, {}, 0, "46", 'T', "12", 2, 72},
    {"CC1961", "T�picos em Linguagens de Programa��o", 0, {}, 0, {}, 0, "5", 'T', "123", 3, 72},
    {"CC1962", "T�picos em Programa��o", 0, {}, 0, {}, 0, "6", 'M', "34", 2, 72},
    {"CC1963", "T�picos em Redes de Computadores", 0, {}, 0, {}, 0, "24", 'M', "56", 2, 72},
    {"CC1964", "T�picos em Sistemas de Computa��o", 0, {}, 0, {}, 0, "35", 'T', "34", 2, 72},
    {"CC1965", "T�picos em Sistemas de Informa��o", 0, {}, 0, {}, 0, "6", 'T', "234", 3, 72},
    {"CC1966", "T�picos em Sistemas Distribu�dos", 0, {}, 0, {}, 0, "3", 'M', "1234", 4, 72},
    {"CC1967", "T�picos em Sistemas Inteligentes", 0, {}, 0, {}, 0, "5", 'T', "12", 2, 72},
    {"CC1968", "T�picos em Software B�sico", 0, {}, 0, {}, 0, "4", 'M', "345", 3, 72}
};

int NUM_ELETIVAS = sizeof(eletivas) / sizeof(Disciplina);

#endif