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
    {"COMP359", "Programação 1", 1, {}, 0, {}, 0, "6", 'T', "3456", 1, 72},
    {"COMP360", "Lógica para Computação", 1, {}, 0, {}, 0, "24", 'T', "34", 2, 72},
    {"COMP361", "Computação, Sociedade e Ética", 1, {}, 0, {}, 0, "24", 'T', "56", 2, 72},
    {"COMP362", "Matemática Discreta", 1, {}, 0, {}, 0, "35", 'T', "12", 2, 72},
    {"COMP363", "Cálculo Diferencial e Integral", 1, {}, 0, {}, 0, "35", 'T', "3456", 2, 144},

    // 2o periodo
    {"COMP364", "Estrutura de Dados", 2, {"COMP359"}, 1, {}, 0, "35", 'M', "56", 2, 72},
    {"COMP365", "Banco de Dados", 2, {}, 0, {}, 0, "24", 'T', "12", 2, 72},
    {"COMP366", "Organização e Arquitetura de Computadores", 2, {}, 0, {}, 0, "35", 'M', "34", 2, 72},
    {"COMP367", "Geometria Analítica", 2, {}, 0, {}, 0, "24", 'T', "34", 2, 72},

    // 3o periodo
    {"COMP368", "Redes de Computadores", 3, {"COMP359"}, 1, {}, 0, "24", 'T', "34", 2, 72},
    {"COMP369", "Teoria dos Grafos", 3, {"COMP364", "COMP362"}, 2, {}, 0, "25", 'T', "12", 2, 72},
    {"COMP370", "Probabilidade e Estatística", 3, {"COMP363"}, 1, {}, 0, "24", 'M', "56", 2, 72},
    {"COMP371", "Álgebra Linear", 3, {"COMP367"}, 1, {}, 0, "24", 'M', "34", 2, 72},

    // 4o periodo
    {"COMP372", "Programação 2", 4, {"COMP364", "COMP365", "COMP368"}, 3, {"COMP373"}, 1, "4", 'T', "3456", 1, 72},
    {"COMP373", "Programação 3", 4, {"COMP364", "COMP365", "COMP368"}, 3, {"COMP372"}, 1, "35", 'T', "34", 2, 72},
    {"COMP374", "Projeto e Análise de Algoritmos", 4, {"COMP364", "COMP369"}, 2, {}, 0, "24", 'T', "56", 2, 72},
    {"COMP376", "Teoria da Computação", 4, {}, 0, {}, 0, "24", 'T', "12", 2, 72},

    // 5o periodo
    {"COMP378", "Sistemas Operacionais", 5, {"COMP366"}, 1, {}, 0, "24", 'T', "12", 2, 72},
    {"COMP379", "Compiladores", 5, {"COMP364", "COMP376"}, 2, {}, 0, "24", 'T', "34", 2, 72},
    {"COMP380", "Inteligência Artificial", 5, {"COMP360", "COMP374"}, 2, {}, 0, "35", 'T', "34", 2, 72},
    {"COMP381", "Computação Gráfica", 5, {}, 0, {}, 0, "35", 'T', "56", 2, 72},

    // 6o periodo
    {"COMP382", "Projeto e Desenvolvimento de Sistemas", 6, {}, 0, {}, 0, "245", 'M', "3456", 3, 288},

    // 7o periodo
    {"COMP386", "Metodologia de Pesquisa e Trabalho Individual", 7, {}, 0, {}, 0, "35", 'T', "12", 2, 72},
    {"COMP387", "Noções de Direito", 7, {}, 0, {}, 0, "3", 'T', "3456", 1, 72},
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
    {"COMP389", "Conceitos de Linguagem de Programação", 0, {}, 0, {}, 0, "35", 'T', "34", 2, 72},
    {"COMP390", "Aprendizagem de Máquina", 0, {"COMP404"}, 1, {}, 0, "24", 'T', "56", 2, 72},
    {"COMP391", "Sistemas Digitais", 0, {"COMP404"}, 1, {}, 0, "56", 'M', "34", 2, 72},
    {"COMP392", "Sistemas Distribuídos", 0, {}, 0, {}, 0, "6", 'T', "1234", 1, 72},
    {"COMP393", "Redes Neurais e Aprendizado Profundo", 0, {}, 0, {}, 0, "35", 'T', "34", 2, 72},
    {"COMP394", "FPGA", 0, {}, 0, {}, 0, "25", 'M', "56", 2, 72},
    {"COMP395", "Interação Homem-Máquina", 0, {"COMP373"}, 1, {}, 0, "24", 'T', "34", 2, 72},
    {"COMP396", "Processamento Digital de Imagens", 0, {"COMP381"}, 1, {}, 0, "35", 'T', "12", 2, 72},
    {"COMP397", "Computação Evolucionária", 0, {}, 0, {}, 0, "24", 'T', "12", 2, 72},
    {"COMP398", "Sistemas Embarcados", 0, {}, 0, {}, 0, "35", 'T', "56", 2, 72},
    {"COMP399", "Gerência de Projeto", 0, {"COMP382"}, 0, {}, 0, "35", 'T', "56", 2, 72},
    {"COMP400", "Visão Computacional", 0, {}, 0, {}, 0, "25", 'M', "56", 2, 72},
    {"COMP401", "Ciência de Dados", 0, {"COMP370"}, 1, {}, 0, "24", 'M', "34", 2, 72},
    {"COMP402", "Microcoontroladores e Aplicações", 0, {}, 0, {}, 0, "24", 'M', "56", 2, 72},
    {"COMP403", "Segurança de Sistemas Computacionais", 0, {"COMP368"}, 1, {}, 0, "46", 'M', "34", 2, 72},
    {"COMP404", "Cálculo 3", 0, {"COMP363"}, 1, {}, 0, "36", 'M', "12", 2, 72},

    // demais eletivas
    {"COMP405", "Tópicos em Ciência da Computação 1", 0, {}, 0, {}, 0, "26", 'T', "34", 2, 72},
    {"COMP406", "Tópicos em Ciência da Computação 2", 0, {}, 0, {}, 0, "34", 'M', "12", 2, 72},
    {"COMP407", "Tópicos em Ciência da Computação 3", 0, {}, 0, {}, 0, "5", 'M', "56", 2, 72},
    {"COMP409", "Tópicos em Matemática para Comp. 1", 0, {}, 0, {}, 0, "2", 'T', "456", 3, 72},
    {"COMP410", "Tópicos em Matemática para Comp. 2", 0, {}, 0, {}, 0, "45", 'M', "23", 2, 72},
    {"COMP411", "Tópicos em Matemática para Comp. 3", 0, {}, 0, {}, 0, "6", 'T', "123", 3, 72},
    {"COMP412", "Tópicos em Física para Computação 1", 0, {}, 0, {}, 0, "3", 'T', "234", 3, 72},
    {"COMP413", "Tópicos em Física para Computação 2", 0, {}, 0, {}, 0, "4", 'M', "12", 2, 72},
    {"COMP414", "Tópicos em Física para Computação 3", 0, {}, 0, {}, 0, "56", 'T', "34", 2, 72},
    {"CC1941", "Cálculo 4", 0, {}, 0, {}, 0, "35", 'T', "12", 2, 72},
    {"CC1942", "Cálculo Numérico", 0, {}, 0, {}, 0, "24", 'M', "34", 2, 72},
    {"CC1943", "Circuitos Digitais", 0, {}, 0, {}, 0, "4", 'T', "1234", 4, 72},
    {"CC1944", "Circuitos Impressos", 0, {}, 0, {}, 0, "56", 'M', "12", 2, 72},
    {"CC1945", "Fundamentos de Libras", 0, {}, 0, {}, 0, "3", 'T', "56", 2, 72},
    {"CC1946", "Geometria Computacional", 0, {}, 0, {}, 0, "25", 'M', "45", 2, 72},
    {"CC1947", "Pesquisa Operacional", 0, {}, 0, {}, 0, "6", 'T', "123", 3, 72},
    {"CC1948", "Programação para Sistemas Embarcados", 0, {}, 0, {}, 0, "34", 'M', "23", 2, 72},
    {"CC1949", "Projeto de Sistemas Embarcados", 0, {}, 0, {}, 0, "5", 'T', "3456", 4, 72},
    {"CC1950", "Tópicos em Arquitetura de Comp.", 0, {}, 0, {}, 0, "26", 'T', "12", 2, 72},
    {"CC1951", "Tópicos em Banco de Dados", 0, {}, 0, {}, 0, "3", 'M', "123", 3, 72},
    {"CC1952", "Tópicos em Computação Científica", 0, {}, 0, {}, 0, "45", 'T', "34", 2, 72},
    {"CC1953", "Tópicos em Computação Paralela", 0, {}, 0, {}, 0, "24", 'T', "56", 2, 72},
    {"CC1954", "Tópicos em Computação Visual", 0, {}, 0, {}, 0, "5", 'M', "234", 3, 72},
    {"CC1955", "Tópicos em Comunicação de Dados", 0, {}, 0, {}, 0, "6", 'M', "56", 2, 72},
    {"CC1956", "Tópicos em Desenvolvimento de Sist.", 0, {}, 0, {}, 0, "35", 'M', "12", 2, 72},
    {"CC1957", "Tópicos em Engenharia de Software", 0, {}, 0, {}, 0, "4", 'T', "56", 2, 72},
    {"CC1958", "Tópicos em Humanidades", 0, {}, 0, {}, 0, "2", 'T', "123", 3, 72},
    {"CC1959", "Tópicos em Informática na Educação", 0, {}, 0, {}, 0, "3", 'M', "45", 2, 72},
    {"CC1960", "Tópicos em Inteligência Artificial", 0, {}, 0, {}, 0, "46", 'T', "12", 2, 72},
    {"CC1961", "Tópicos em Linguagens de Programação", 0, {}, 0, {}, 0, "5", 'T', "123", 3, 72},
    {"CC1962", "Tópicos em Programação", 0, {}, 0, {}, 0, "6", 'M', "34", 2, 72},
    {"CC1963", "Tópicos em Redes de Computadores", 0, {}, 0, {}, 0, "24", 'M', "56", 2, 72},
    {"CC1964", "Tópicos em Sistemas de Computação", 0, {}, 0, {}, 0, "35", 'T', "34", 2, 72},
    {"CC1965", "Tópicos em Sistemas de Informação", 0, {}, 0, {}, 0, "6", 'T', "234", 3, 72},
    {"CC1966", "Tópicos em Sistemas Distribuídos", 0, {}, 0, {}, 0, "3", 'M', "1234", 4, 72},
    {"CC1967", "Tópicos em Sistemas Inteligentes", 0, {}, 0, {}, 0, "5", 'T', "12", 2, 72},
    {"CC1968", "Tópicos em Software Básico", 0, {}, 0, {}, 0, "4", 'M', "345", 3, 72}
};

int NUM_ELETIVAS = sizeof(eletivas) / sizeof(Disciplina);

#endif