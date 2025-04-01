#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <locale.h>
#include "aluno.h"
#include "disciplinas.h"
#include "planejaMatricula.h"

// Carga Horária Mínima: 3747h
// Carga Horária Máxima por Período Letivo: 540h
// 2.952 horas de disciplina geral divido em:
// 2.376 horas de disciplinas obrigatórias e 576 horas em (8) eletivas
// 180 de TCC
// 240 de Atividades Complementares
// 375 de Atividades de Extensão

int main()
{
    setlocale(LC_ALL, "Portuguese_Brazil");

    Aluno aluno;
    printf("Nº do último período cursado: ");
    scanf("%d", &aluno.periodoAtual);
    aluno.periodoAtual++; // o planejamento eh para o proximo periodo do discente

    limparBuffer();

    int numPeriodosFaltantes = 10 - aluno.periodoAtual + 1;
    Periodo periodo[numPeriodosFaltantes];

    aluno.horasCumpridasObrigatorias = 0, aluno.horasCumpridasEletivas = 0, aluno.horasCumpridasExtensao = 0, aluno.horasCumpridasComplementares = 0;
    aluno.numCursadas = entrada(aluno.cursadas, 0, &aluno);

    planejarSemestre(&aluno, periodo, aluno.periodoAtual, true);
    imprimirSemestre(&aluno, periodo, 0, 1);

    printf("\nCom o encerramento do semestre, a situação do discente será a seguinte:\n");
    imprimirHoras("DISCIPLINAS OBRIGATÓRIAS", aluno.horasCumpridasObrigatorias, TOTAL_OBRIGATORIAS);
    imprimirHoras("DISCIPLINAS ELETIVAS", aluno.horasCumpridasEletivas, TOTAL_ELETIVAS);
    // imprimirHoras("EXTENSÃO", aluno.horasCumpridasExtensao, TOTAL_EXTENSAO);
    imprimirHoras("HORAS COMPLEMENTARES", aluno.horasCumpridasComplementares, TOTAL_COMPLEMENTARES);

    printf("\n----------------------------------------------------------\n");

    char continuar;
    printf("\nDeseja visualizar o planejamento para os próximos semestres? (S/N) ");
    scanf("%c", &continuar);

    if (continuar == 'S' || continuar == 's')
    {
        planejarSemestre(&aluno, periodo, aluno.periodoAtual, false);
        imprimirSemestre(&aluno, periodo, 1, numPeriodosFaltantes);
        printf("\n----------------------------------------------------------\n");
    }
    else
        printf("Obrigada por utilizar o programa!\n");

    return 0;
}

void imprimirHoras(const char *tipo, int horasCumpridas, int totalHoras)
{
    int faltantes = totalHoras - horasCumpridas;
    if (faltantes < 0) faltantes = 0;
    
    printf("- HORAS PAGAS EM %s: %dh\n- HORAS FALTANTES EM %s: %dh\n", 
           tipo, horasCumpridas, tipo, faltantes);
}

void imprimirSemestre(Aluno *aluno, Periodo *periodo, int semestreInicio, int fim)
{
    for (int j = semestreInicio; j < fim; j++)
    {
        printf("\n----------------------------------------------------------\n");

        printf("\nNúmero de disciplinas planejadas para o %dº semestre: %d\n\nSendo elas:\n", periodo[j].periodo, periodo[j].numPlanejadas);

        for (int i = 0; i < periodo[j].numPlanejadas; i++)
        {
            printf("%s - %s (%s%c%s)\n", periodo[j].planejadas[i].codigo, periodo[j].planejadas[i].nome_dis, periodo[j].planejadas[i].dias, periodo[j].planejadas[i].turno, periodo[j].planejadas[i].horarios);
        }

        separarComplementares(&aluno->horasCumpridasComplementares);
    }
}

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int entrada(Historico *historico, int i, Aluno *aluno)
{
    printf("Codigo: ");
    if (fgets(historico[i].codigo, sizeof(historico[i].codigo), stdin) == NULL)
        return i;

    historico[i].codigo[strcspn(historico[i].codigo, "\n")] = '\0';

    if (strcmp(historico[i].codigo, "-2") == 0)
        return i;

    printf("Nota: ");
    if (scanf("%lf", &historico[i].mediaFinal) == 1) // se ainda houver leitura de nota
    {
        if (historico[i].mediaFinal == -2) // se a nota for -2, encerra
        {
            limparBuffer();
            return i;
        }
        else if (historico[i].mediaFinal == -1) // se a nota for -1 define que esta trancada
        {
            historico[i].trancada = true;
        }
        else // caso nao seja -1, nao esta trancada
        {
            historico[i].trancada = false;
            atualizarHorasCumpridas(aluno, historico[i].codigo, historico[i].mediaFinal);
        }
    }
    else
    {
        limparBuffer();
        return i;
    }

    limparBuffer();

    return entrada(historico, i + 1, aluno);
}

void atualizarHorasCumpridas(Aluno *aluno, const char *codigo, double mediaFinal)
{
    if (mediaFinal >= 7) // apenas se o aluno foi aprovado
    { 
        for (int j = 0; j < NUM_OBRIGATORIAS; j++)
        {
            if (strcmp(codigo, obrigatorias[j].codigo) == 0) 
            {
                aluno->horasCumpridasObrigatorias += obrigatorias[j].cargaHoraria;
                return;
            }
        }
        
        for (int j = 0; j < NUM_ELETIVAS; j++) 
        {
            if (strcmp(codigo, eletivas[j].codigo) == 0) 
            {
                aluno->horasCumpridasEletivas += eletivas[j].cargaHoraria;
                return;
            }
        }
    }
}

void planejarSemestre(Aluno *aluno, Periodo *periodo, int atual, bool parada)
{
    if (aluno->periodoAtual > 10)
        return;

    int idxPeriodo = aluno->periodoAtual - atual;
    periodo[idxPeriodo].periodo = aluno->periodoAtual;
    periodo[idxPeriodo].numPlanejadas = 0;
    periodo[idxPeriodo].numHoras = 0;

    for (int i = 0; i < NUM_OBRIGATORIAS; i++)
    {
        if (obrigatorias[i].periodo > aluno->periodoAtual &&
            aluno->periodoAtual < 7) // verifica periodo
            continue;

        bool jaAprovado = false;

        for (int j = 0; j < aluno->numCursadas; j++)
        {
            if (strcmp(aluno->cursadas[j].codigo, obrigatorias[i].codigo) == 0)
            {
                if (aluno->cursadas[j].mediaFinal >= 7.0 &&
                    !aluno->cursadas[j].trancada) // verifica se ja cursou e foi aprovado
                {
                    jaAprovado = true;
                    break;
                }
            }
        }

        if (jaAprovado)
            continue;

        if (!verificaPreRequisitos(aluno, obrigatorias[i])) // verifica os pre-requisitos
            continue;

        if (periodo[idxPeriodo].numPlanejadas >= 6) // verifica o limite de disciplinas por semestre
            break;

        if (haChoqueHorario(periodo, idxPeriodo, obrigatorias[i].turno, obrigatorias[i].dias, obrigatorias[i].horarios)) // verifica choque de horario
            continue;

        bool diasDisciplina[5] = {false}; // array para garantir que nao exceda 3 disciplinas por dia
        extrairDiasSemana(obrigatorias[i].dias, diasDisciplina); // marca com true os dias que tem aula

        bool diaLimiteExcedido = false;
        for (int dia = 0; dia < 5; dia++)
        {
            if (diasDisciplina[dia])
            {
                int contagem = 0;

                for (int j = 0; j < periodo[idxPeriodo].numPlanejadas; j++)
                {

                    bool diasPlanejada[5] = {false};
                    extrairDiasSemana(periodo[idxPeriodo].planejadas[j].dias, diasPlanejada);
                    if (diasPlanejada[dia])
                        contagem++; // contagem de disciplina por dia
                }

                if (contagem >= 3)
                {
                    diaLimiteExcedido = true;
                    break;
                }
            }
        }

        if (diaLimiteExcedido)
            continue; // se exceder 3, vai para a proxima disciplina

        if ((periodo[idxPeriodo].numHoras + obrigatorias[i].cargaHoraria) > MAXIMO_HORAS)
            break;

        if (strcmp(obrigatorias[i].codigo, "COMP372")  == 0 || strcmp(obrigatorias[i].codigo, "COMP373") == 0)
        {
            if ((periodo[idxPeriodo].numHoras + obrigatorias[i].cargaHoraria * 2) > MAXIMO_HORAS)
                continue;
        }

        periodo[idxPeriodo].planejadas[periodo[idxPeriodo].numPlanejadas] = obrigatorias[i];

        periodo[idxPeriodo].numPlanejadas++;

        periodo[idxPeriodo].numHoras += obrigatorias[i].cargaHoraria;

        aluno->horasCumpridasObrigatorias += obrigatorias[i].cargaHoraria; // adiciona as horas da obrigatoria

        strcpy(aluno->cursadas[aluno->numCursadas].codigo, obrigatorias[i].codigo);
        aluno->cursadas[aluno->numCursadas].mediaFinal = 7.0;
        aluno->cursadas[aluno->numCursadas].trancada = false;
        aluno->numCursadas++;
    }

    for (int i = 0; i < NUM_ELETIVAS; i++)
    {
        bool jaAprovado = false;
        for (int j = 0; j < aluno->numCursadas; j++)
        {
            if (strcmp(aluno->cursadas[j].codigo, eletivas[i].codigo) == 0)
            {
                if (aluno->cursadas[j].mediaFinal >= 7.0 && 
                    !aluno->cursadas[j].trancada) // talvez de algo
                {
                    jaAprovado = true;
                    break;
                }
            }
        }

        if (jaAprovado)
            continue;

        if (periodo[idxPeriodo].numPlanejadas >= 6)
            break;

        if (haChoqueHorario(periodo, idxPeriodo, eletivas[i].turno, eletivas[i].dias, eletivas[i].horarios))
            continue;

        bool diasDisciplina[5] = {false};
        extrairDiasSemana(eletivas[i].dias, diasDisciplina);

        bool diaLimiteExcedido = false;
        for (int dia = 0; dia < 5; dia++)
        {
            if (diasDisciplina[dia])
            {
                int contagem = 0;
                
                for (int j = 0; j < periodo[idxPeriodo].numPlanejadas; j++)
                {
                    bool diasPlanejada[5] = {false};
                    extrairDiasSemana(periodo[idxPeriodo].planejadas[j].dias, diasPlanejada);
                    if (diasPlanejada[dia])
                        contagem++;
                }

                if (contagem >= 3)
                {
                    diaLimiteExcedido = true;
                    break;
                }
            }
        }

        if (diaLimiteExcedido)
            continue;

        if ((periodo[idxPeriodo].numHoras + obrigatorias[i].cargaHoraria) > MAXIMO_HORAS)
            break;

        bool diasOcupados[5] = {false};
        for (int j = 0; j < periodo[idxPeriodo].numPlanejadas; j++)
        {
            bool diasPlanejada[5] = {false};
            extrairDiasSemana(periodo[idxPeriodo].planejadas[j].dias, diasPlanejada);
            for (int dia = 0; dia < 5; dia++)
            {
                if (diasPlanejada[dia])
                {
                    diasOcupados[dia] = true;
                }
            }
        }

        // verifica se a disciplina preenche algum dia que ainda está vazio
        bool preencheDiaVazio = false;
        for (int dia = 0; dia < 5; dia++)
        {
            if (diasDisciplina[dia] && !diasOcupados[dia])
            {
                preencheDiaVazio = true;
                break;
            }
        }

        // se a disciplina NÃO preenche um dia vazio, continue procurando outra
        if (!preencheDiaVazio)
            continue;

        periodo[idxPeriodo].planejadas[periodo[idxPeriodo].numPlanejadas] = eletivas[i];
        periodo[idxPeriodo].numPlanejadas++;

        periodo[idxPeriodo].numHoras += eletivas[i].cargaHoraria;

        aluno->horasCumpridasEletivas += eletivas[i].cargaHoraria;

        strcpy(aluno->cursadas[aluno->numCursadas].codigo, eletivas[i].codigo);
        aluno->cursadas[aluno->numCursadas].mediaFinal = 7.0;
        aluno->cursadas[aluno->numCursadas].trancada = false;
        aluno->numCursadas++;
    } 

    if (parada)
        return;
    else
        aluno->periodoAtual++;
        
    planejarSemestre(aluno, periodo, atual, parada);
}

bool verificaPreRequisitos(Aluno *aluno, Disciplina disciplina)
{
    if (disciplina.numPreRequisitos == 0) // se nao tiver pre-requisito ja retorna
        return true;

    for (int i = 0; i < disciplina.numPreRequisitos; i++)
    {
        bool encontrou = false;

        for (int j = 0; j < aluno->numCursadas; j++)
        {
            if (strcmp(disciplina.preRequisitos[i], aluno->cursadas[j].codigo) == 0)
            {
                if (aluno->cursadas[j].mediaFinal >= 7) // alem de ter cursado, tem que ter passado na disciplina
                {
                    encontrou = true;
                    break;
                }
            }
        }

        if (!encontrou)
            return false;
    }

    return true;
}

bool verificaCoRequisitos(Aluno *aluno, Disciplina *disciplina, Periodo *periodo, int idxPeriodo, int indice)
{
    if (disciplina[indice].numCoRequisitos == 0)
    {
        // printf("Nao tem corequisito\n.");
        return true;
    }

    for (int i = 0; i < disciplina[indice].numCoRequisitos; i++)
    {
        bool encontrou = false;

        for (int j = 0; j < aluno->numCursadas; j++)
        {
            if (strcmp(disciplina[indice].coRequisitos[i], aluno->cursadas[j].codigo) == 0)
            {
                if (aluno->cursadas[j].mediaFinal >= 7)
                {
                    // printf("Uma materia ja foi cursada\n.");
                    encontrou = true;
                    break;
                }
            }
        }

        if (!encontrou)
        {
            for (int j = 0; j < periodo[idxPeriodo].numPlanejadas; j++)
            {
                if (strcmp(disciplina[indice].coRequisitos[i], periodo[idxPeriodo].planejadas[j].codigo) == 0)
                {
                    printf("A outra materia esta planejada para esse periodo\n.");
                    encontrou = true;
                    break;
                }
            }
        }

        if (!encontrou)
        {
            return false;
        }
    }

    return true;
}

bool verificaDiasSemana(Periodo *teste, int atual)
{
    bool diasSemana[5] = {false};
    int totalDias = 0;

    for (int i = 0; i < teste[atual].numPlanejadas; i++)
    {
        bool diasPresenca[5] = {false};
        extrairDiasSemana(teste[atual].planejadas[i].dias, diasPresenca);

        for (int j = 0; j < 5; j++)
        {
            if (diasPresenca[j] && !diasSemana[j])
            {
                diasSemana[j] = true;
                totalDias++;

                if (totalDias == 5) // se todos os dias ja foram cobertos, retorna true imediatamente
                    return true;
            }
        }
    }

    return false;
}

bool verificaMax3PorDia(Periodo *teste, int atual)
{
    int contagem[5] = {0};

    for (int i = 0; i < teste[atual].numPlanejadas; i++)
    {
        bool diasPresenca[5] = {false};
        extrairDiasSemana(teste[atual].planejadas[i].dias, diasPresenca);

        for (int j = 0; j < 5; j++)
        {
            if (diasPresenca[j])
                contagem[j]++;
        }
    }

    for (int i = 0; i < 5; i++)
    {
        if (contagem[i] > 3)
        {
            return false;
        }
    }

    return true;
}

void extrairDiasSemana(char dias[], bool diasPresenca[5])
{
    // resetando os dias
    for (int i = 0; i < 5; i++)
        diasPresenca[i] = false;

    for (int i = 0; dias[i] != '\0'; i++)
    {
        switch (dias[i])
        {
        case '2': diasPresenca[0] = true; break; // segunda
        case '3': diasPresenca[1] = true; break; // terca
        case '4': diasPresenca[2] = true; break; // quarta
        case '5': diasPresenca[3] = true; break; // quinta
        case '6': diasPresenca[4] = true; break; // sexta
        }
    }
}

bool haChoqueHorario(Periodo *teste, int atual, char turno, char dias[5], char horarios[6])
{
    for (int i = 0; i < teste[atual].numPlanejadas; i++)
    {
        bool diaComum = false;
        for (int j = 0; dias[j] != '\0'; j++)
        {
            if (strchr(teste[atual].planejadas[i].dias, dias[j])) // verifica se ha dias em comum
            {
                diaComum = true;
                break;
            }
        }

        if (!diaComum) // se nao tiver, proximo
            continue;

        if (turno != teste[atual].planejadas[i].turno) // verifica se eh do mesmo turno
            continue;

        for (int j = 0; horarios[j] != '\0'; j++)
        {
            if (strchr(teste[atual].planejadas[i].horarios, horarios[j])) // verifica se ha choque de horario
            {
                return true;
            }
        }
    }

    return false;
}

void separarComplementares(int *horasComplementaresPagas)
{
    int complementaresPeriodo = TOTAL_COMPLEMENTARES / MAX_PERIODOS;
    printf("\nSeparadas %d horas complementares para esse semestre.\n", complementaresPeriodo);
    *horasComplementaresPagas += complementaresPeriodo;

    return;
}