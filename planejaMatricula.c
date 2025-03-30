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
    printf("Período atual: ");
    scanf("%d", &aluno.periodoAtual);
    aluno.periodoAtual++; // o planejamento eh para o proximo periodo do discente

    limparBuffer();

    if (aluno.periodoAtual < 2) // tratamento de erro para calouro
    {
        printf("O planejamento de matrícula só ocorre a partir do segundo semestre. Calouros são automaticamente cadastrados.\n");

        return 0;
    }

    aluno.numCursadas = entrada(aluno.cursadas, 0);
    aluno.numPlanejadas = 0, aluno.horasCumpridasObrigatorias = 0, aluno.horasCumpridasEletivas = 0, aluno.horasCumpridasExtensao = 0, aluno.horasCumpridasComplementares = 0;

    planejarSemestre(&aluno, obrigatorias, NUM_OBRIGATORIAS, NUM_ELETIVAS);

    printf("\nDisciplinas planejadas para o próximo semestre: ");
    printf("%d\n\n", aluno.numPlanejadas);

    for (int i = 0; i < aluno.numPlanejadas; i++)
        printf("%s - %s (%s%c%s)\n", aluno.planejadas[i].codigo, aluno.planejadas[i].nome_dis, aluno.planejadas[i].dias, aluno.planejadas[i].turno, aluno.planejadas[i].horarios);

    separarComplementares(&aluno.horasCumpridasComplementares);

    printf("\nCom o encerramento do semestre, a situação do discente será a seguinte:\n");
    printf("- HORAS PAGAS EM DISCIPLINAS OBRIGATÓRIAS: %dh\n- HORAS FALTANTES EM DISCIPLINAS OBRIGATÓRIAS: %dh\n", aluno.horasCumpridasObrigatorias, TOTAL_OBRIGATORIAS - aluno.horasCumpridasObrigatorias);
    printf("- HORAS PAGAS EM DISCIPLINAS ELETIVAS: %dh\n- HORAS FALTANTES EM DISCIPLINAS ELETIVAS: %dh\n", aluno.horasCumpridasEletivas, TOTAL_ELETIVAS - aluno.horasCumpridasEletivas);
    printf("- HORAS PAGAS EM EXTENSÃO: %dh\n- HORAS FALTANTES EM EXTENSÃO: %dh\n", aluno.horasCumpridasExtensao, TOTAL_EXTENSAO - aluno.horasCumpridasExtensao);
    printf("- HORAS COMPLEMENTARES PAGAS: %dh\n- HORAS COMPLEMENTARES FALTANTES: %dh\n", aluno.horasCumpridasComplementares, TOTAL_COMPLEMENTARES - aluno.horasCumpridasComplementares);

    if (!verificaDiasSemana(&aluno))
        printf("Atenção: O aluno não está indo todos os dias da semana.\n");

    if (!verificaMax3PorDia(&aluno))
        printf("Atenção: O aluno está excedendo o limite de três disciplinas por dia.\n");

    return 0;
}

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int entrada(Historico *historico, int i)
{
    printf("Codigo: ");
    if (fgets(historico[i].codigo, sizeof(historico[i].codigo), stdin) == NULL)
    {
        return i;
    }

    historico[i].codigo[strcspn(historico[i].codigo, "\n")] = '\0';

    if (strcmp(historico[i].codigo, "-2") == 0)
    {
        return i;
    }

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
        }
    }
    else
    {
        limparBuffer();
        return i;
    }

    limparBuffer();

    return entrada(historico, i + 1);
}

void planejarSemestre(Aluno *aluno, Disciplina obrigatorias[], int numObrigatorias, int numEletivas)
{
    for (int i = 0; i < numObrigatorias; i++)
    {
        if (obrigatorias[i].periodo > aluno->periodoAtual) // verifica periodo
        {
            continue;
        }

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
        {
            continue;
        }

        if (!verificaPreRequisitos(aluno, obrigatorias[i])) // verifica os pre-requisitos
        {
            continue;
        }

        if (aluno->numPlanejadas >= 6) // verifica o limite de disciplinas por semestre
        {
            break;
        }

        if (haChoqueHorario(aluno, obrigatorias[i].turno, obrigatorias[i].dias, obrigatorias[i].horarios)) // verifica choque de horario
        {
            continue;
        }

        bool diasDisciplina[5] = {false}; // array para garantir que nao exceda 3 disciplinas por dia
        extrairDiasSemana(obrigatorias[i].dias, diasDisciplina); // marca com true os dias que tem aula

        bool diaLimiteExcedido = false;
        for (int dia = 0; dia < 5; dia++)
        {
            if (diasDisciplina[dia])
            {
                int contagem = 0;
                for (int j = 0; j < aluno->numPlanejadas; j++)
                {
                    bool diasPlanejada[5] = {false};
                    extrairDiasSemana(aluno->planejadas[j].dias, diasPlanejada);
                    if (diasPlanejada[dia])
                        contagem++; // contagem de disciplina/dia
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

        // se passou em todas as verificacoes, adiciona a disciplina
        aluno->planejadas[aluno->numPlanejadas] = obrigatorias[i];
        aluno->numPlanejadas++;

        if (obrigatorias[i].tipo == 0)
        {
            aluno->horasCumpridasObrigatorias += obrigatorias[i].cargaHoraria; // adiciona as horas da obrigatoria
        }
    }

    // para eletivas, a mesma logica (da pra adaptar e fazer junto com as obrigatorias)
    for (int i = 0; i < numEletivas; i++)
    {
        bool jaAprovado = false;
        for (int j = 0; j < aluno->numCursadas; j++)
        {
            if (strcmp(aluno->cursadas[j].codigo, eletivas[i].codigo) == 0)
            {
                if (aluno->cursadas[j].mediaFinal >= 7.0 && !aluno->cursadas[j].trancada)
                {
                    jaAprovado = true;
                    break;
                }
            }
        }

        if (jaAprovado)
        {
            continue;
        }

        if (aluno->numPlanejadas >= 6)
        {
            break;
        }

        if (haChoqueHorario(aluno, eletivas[i].turno, eletivas[i].dias, eletivas[i].horarios))
        {
            continue;
        }

        bool diasDisciplina[5] = {false};
        extrairDiasSemana(eletivas[i].dias, diasDisciplina);

        bool diaLimiteExcedido = false;
        for (int dia = 0; dia < 5; dia++)
        {
            if (diasDisciplina[dia])
            {
                int contagem = 0;
                for (int j = 0; j < aluno->numPlanejadas; j++)
                {
                    bool diasPlanejada[5] = {false};
                    extrairDiasSemana(aluno->planejadas[j].dias, diasPlanejada);
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

        aluno->planejadas[aluno->numPlanejadas] = eletivas[i];
        aluno->numPlanejadas++;
        aluno->horasCumpridasEletivas += eletivas[i].cargaHoraria;
    }
}

bool disciplinaJaCursada(Aluno *aluno, Disciplina disciplina)
{
    for (int i = 0; i < aluno->numCursadas; i++)
    {
        if ((strcmp(aluno->cursadas[i].codigo, disciplina.codigo) == 0) &&
            aluno->cursadas[i].mediaFinal >= 7 &&
            aluno->cursadas[i].trancada == false)
        {
            switch (disciplina.tipo)
            {
            case 0:
                aluno->horasCumpridasObrigatorias += disciplina.cargaHoraria;
                printf("Horas obrigat�rias atualizadas: %d\n", aluno->horasCumpridasObrigatorias);
                break;
            case 1:
                aluno->horasCumpridasEletivas += disciplina.cargaHoraria;
                printf("Horas eletivas atualizadas: %d\n", aluno->horasCumpridasEletivas);
                break;
            case 2:
                aluno->horasCumpridasExtensao += disciplina.cargaHoraria;
                printf("Horas de extens�o atualizadas: %d\n", aluno->horasCumpridasExtensao);
                break;
            }

            return true;
        }
    }

    return false;
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
            if (strcmp(disciplina.preRequisitos[i], aluno->cursadas[j].codigo) == 0 &&
                aluno->cursadas[j].mediaFinal >= 7)
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

bool verificaDiasSemana(Aluno *aluno)
{
    bool diasSemana[5] = {false};
    int totalDias = 0;

    for (int i = 0; i < aluno->numPlanejadas; i++)
    {
        bool diasPresenca[5] = {false};
        extrairDiasSemana(aluno->planejadas[i].dias, diasPresenca);

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

bool verificaMax3PorDia(Aluno *aluno)
{
    int contagem[5] = {0};

    for (int i = 0; i < aluno->numPlanejadas; i++)
    {
        bool diasPresenca[5] = {false};
        extrairDiasSemana(aluno->planejadas[i].dias, diasPresenca);

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
        case '2':
            diasPresenca[0] = true;
            break; // segunda
        case '3':
            diasPresenca[1] = true;
            break; // terca
        case '4':
            diasPresenca[2] = true;
            break; // quarta
        case '5':
            diasPresenca[3] = true;
            break; // quinta
        case '6':
            diasPresenca[4] = true;
            break; // sexta
        }
    }
}

bool haChoqueHorario(Aluno *aluno, char turno, char dias[5], char horarios[6]) // ainda nao testada
{
    for (int i = 0; i < aluno->numPlanejadas; i++)
    {
        bool diaComum = false;
        for (int j = 0; dias[j] != '\0'; j++)
        {
            if (strchr(aluno->planejadas[i].dias, dias[j])) // verifica se ha dias em comum
            {
                diaComum = true;
                break;
            }
        }

        if (!diaComum) // se nao tiver, proximo
            continue;

        if (turno != aluno->planejadas[i].turno) // verifica se eh do mesmo turno
            continue;

        for (int j = 0; horarios[j] != '\0'; j++)
        {
            if (strchr(aluno->planejadas[i].horarios, horarios[j])) // verifica se ha choque de horario
            {
                return true;
            }
        }
    }

    return false;
}

void separarComplementares(double *horasComplementaresPagas)
{
    int complementaresPeriodo = TOTAL_COMPLEMENTARES / MAX_SEMESTRES;
    printf("Separadas %d horas complementares para esse semestre.\n", complementaresPeriodo);
    *horasComplementaresPagas += complementaresPeriodo;

    return;
}