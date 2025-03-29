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
    printf("Qual o preiodo atual: ");
    scanf("%d", &aluno.periodoAtual);

    limparBuffer();

    aluno.numCursadas = entrada(aluno.cursadas, 0);
    aluno.numPlanejadas = 0, aluno.horasCumpridasObrigatorias = 0, aluno.horasCumpridasEletivas = 0, aluno.horasCumpridasExtensao = 0, aluno.horasCumpridasComplementares = 0;

    planejarSemestre(&aluno, obrigatorias, NUM_OBRIGATORIAS);

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
    }
    else
    {
        limparBuffer();
        return i;
    }

    limparBuffer();

    return entrada(historico, i + 1);
}

void planejarSemestre(Aluno *aluno, Disciplina obrigatorias[], int num_obrigatorias)
{
    for (int i = 0; i < num_obrigatorias; i++)
    {
        if (obrigatorias[i].periodo <= aluno->periodoAtual &&
            !disciplinaJaCursada(aluno, obrigatorias[i]) &&
            verificaPreRequisitos(aluno, obrigatorias[i]) &&
            aluno->numPlanejadas < 6)
        {
            // aluno->planejadas[aluno->numPlanejadas] = obrigatorias[i];
            // aluno->horasCumpridasObrigatorias = aluno->horasCumpridasObrigatorias + obrigatorias[i].cargaHoraria;
            // aluno->numPlanejadas++;
            // verificaDiasSemana(aluno);
            // verificaMax3PorDia(aluno);

            Aluno temp = *aluno; // copia temporária para testar a adição
            temp.planejadas[temp.numPlanejadas] = obrigatorias[i];
            temp.numPlanejadas++;

            if (!verificaMax3PorDia(&temp))
                continue; // se exceder o limite, pula para a proxima disciplina

            // se passar no teste, adiciona a disciplina de verdade
            aluno->planejadas[aluno->numPlanejadas] = obrigatorias[i];
            aluno->horasCumpridasObrigatorias += obrigatorias[i].cargaHoraria;
            aluno->numPlanejadas++;
        }
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
                break;
            case 1:
                aluno->horasCumpridasEletivas += disciplina.cargaHoraria;
                break;
            case 2:
                aluno->horasCumpridasExtensao += disciplina.cargaHoraria;
                break;
            }
            return true;
        }
    }
    return false;
}

bool verificaPreRequisitos(Aluno *aluno, Disciplina disciplina)
{
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

// alterei algumas coisas .mainero
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
            case '3': diasPresenca[1] = true; break; // terça
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
        Disciplina d = aluno->planejadas[i];

        // se os turnos forem diferentes nao ha choque
        if (d.turno != turno)
            continue;

        // verificar se ha dias em comum
        bool haDiaEmComum = false;
        for (int j = 0; dias[j] != '\0'; j++)
        {
            if (strchr(d.dias, dias[j])) // se algum dia da nova disciplina estiver nos dias ja planejados
            {
                haDiaEmComum = true;
                break;
            }
        }

        if (!haDiaEmComum)
            continue;

        for (int j = 0; horarios[j] != '\0'; j++)
        {
            if (strchr(d.horarios, horarios[j])) // se algum horario coincidir
                return true;                     // choque encontrado
        }
    }

    return false;
}