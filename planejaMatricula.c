#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <locale.h>
#include "aluno.h"
#include "disciplinas.h"
#include "planejaMatricula.h"

// Carga Hor�ria M�nima: 3747h
// Carga Hor�ria M�xima por Per�odo Letivo: 540h
// 2.952 horas de disciplina geral divido em:
    // 2.376 horas de disciplinas obrigat�rias e 576 horas em (8) eletivas
    // 180 de TCC
    // 240 de Atividades Complementares
    // 375 de Atividades de Extens�o

int main()
{
    setlocale(LC_ALL, "Portuguese_Brazil");

    Aluno aluno;
    printf("Qual o preiodo atual: ");
    scanf("%d", &aluno.periodoAtual);

    limparBuffer();

    aluno.numCursadas = entrada(aluno.cursadas, 0);
    aluno.numPlanejadas = 0, aluno.horasCumpridasObrigatorias = 0, aluno.horasCumpridasEletivas = 0, aluno.horasCumpridasExtensao = 0, aluno.horasCumpridasComplementares = 0;

    planejarSemestre(&aluno, obrigatorias, NUM_OBRIGATORIAS, NUM_ELETIVAS);

    printf("\nDisciplinas planejadas para o próximo semestre: ");
    printf("%d\n", aluno.numPlanejadas);

    for (int i = 0; i < aluno.numPlanejadas; i++)
        printf("%s - %s (%s%c%s)\n", aluno.planejadas[i].codigo, aluno.planejadas[i].nome_dis, aluno.planejadas[i].dias, aluno.planejadas[i].turno, aluno.planejadas[i].horarios);

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

    if (scanf("%lf", &historico[i].mediaFinal) == 1)
    {
        if (historico[i].mediaFinal == -2)
        {
            limparBuffer();
            return i;
        }
        else if (historico[i].mediaFinal == -1)
        {
            historico[i].trancada = true;
        }
        else
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
        // 1. verifica periodo
        if (obrigatorias[i].periodo > aluno->periodoAtual)
        {
            continue;
        }

        // 2. Verifica se ja cursou e foi aprovado
        bool jaAprovado = false;
        for (int j = 0; j < aluno->numCursadas; j++)
        {
            if (strcmp(aluno->cursadas[j].codigo, obrigatorias[i].codigo) == 0)
            {
                if (aluno->cursadas[j].mediaFinal >= 7.0 &&       
                    !aluno->cursadas[j].trancada)
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

        // 3. Verifica pre-requisitos
        if (!verificaPreRequisitos(aluno, obrigatorias[i]))
        {
            continue;
        }

        // 4. Limite de disciplinas
        if (aluno->numPlanejadas >= 6)
        {
            break;
        }

        // 5. Choque de horario
        if (haChoqueHorario(aluno, obrigatorias[i].turno, obrigatorias[i].dias, obrigatorias[i].horarios))
        {
            continue;
        }

        // 6. Limite de 3 disciplinas por dia
        bool diasDisciplina[5] = {false};
        extrairDiasSemana(obrigatorias[i].dias, diasDisciplina);

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

        // Se passou em todas as verificacoes, adiciona
        aluno->planejadas[aluno->numPlanejadas] = obrigatorias[i];
        aluno->numPlanejadas++;

        if (obrigatorias[i].tipo == 0)
        {
            aluno->horasCumpridasObrigatorias += obrigatorias[i].cargaHoraria;
        }
    }

    // Para eletivas (mesma logica, sem verificacao de periodo)
    for (int i = 0; i < numEletivas; i++)
    {
        // Verifica se ja cursou e foi aprovado
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

        // Verificacao de limite por dia
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

        // Se passou em todas as verificacoes, adiciona
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
            if (strcmp(disciplina.preRequisitos[i], aluno->cursadas[j].codigo) == 0)
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
            case '2': diasPresenca[0] = true; break; // segunda
            case '3': diasPresenca[1] = true; break; // ter�a
            case '4': diasPresenca[2] = true; break; // quarta
            case '5': diasPresenca[3] = true; break; // quinta
            case '6': diasPresenca[4] = true; break; // sexta
        }
    }
}

bool haChoqueHorario(Aluno *aluno, char turno, char dias[5], char horarios[6]) // ainda nao testada
{
    for (int i = 0; i < aluno->numPlanejadas; i++)
    {
        // Verifica se ha dias em comum
        bool diaComum = false;
        for (int j = 0; dias[j] != '\0'; j++)
        {
            if (strchr(aluno->planejadas[i].dias, dias[j]))
            {
                diaComum = true;
                break;
            }
        }

        if (!diaComum)
            continue;

        // Verifica mesmo turno
        if (turno != aluno->planejadas[i].turno)
            continue;

        // Verifica horarios sobrepostos
        for (int j = 0; horarios[j] != '\0'; j++)
        {
            if (strchr(aluno->planejadas[i].horarios, horarios[j]))
            {
                return true;
            }
        }
    }

    return false;
}