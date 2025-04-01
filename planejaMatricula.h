#ifndef PLANEJAMATRICULA_H
#define PLANEJAMATRICULA_H
#include <stdbool.h>
#include "aluno.h"
#include "disciplinas.h"

// Limpa o buffer de entrada para que não sejam recebidos caracteres de outras entradas anteriores.
void limparBuffer();

// Recebe os dados básicos de histórico do discente.
int entrada(Historico *historico, int i, Aluno *aluno);

// Verifica se o discente possui as disciplinas pre-réquisito de uma outra disciplina cursadas com nota suficiente.
bool verificaPreRequisitos(Aluno *aluno, Disciplina disciplina);

// Verifica se o discente está com no máximo 3 disciplinas/dia. 
bool verificaMax3PorDia(Periodo *teste, int Atual);

// Verifica se uma disciplina já foi cursada com nota suficiente pelo discente.
bool disciplinaJaCursada(Aluno *aluno, Disciplina disciplina);

// Planeja o semestre do discente.
void planejarSemestre(Aluno *aluno, Periodo *periodo, int atual, bool parada);

// Verifica para quais dias da semana o discente possui aulas planejadas.
void extrairDiasSemana(char horario[], bool dias[5]);

// Verifica se o discente possui disciplinas em todos os dias da semana.
bool verificaDiasSemana(Periodo *teste, int Atual);

// Verifica se uma disciplina a ser adicionada possui choque de horário com alguma disciplina previamente planejada.
bool haChoqueHorario(Periodo *teste, int Atual, char turno, char dias[5], char horarios[6]);

// Separa a quantidade de horas complementares que o discente irá pagar no semestre;
void separarComplementares(int *horasComplementaresPagas);

bool verificaCoRequisitos(Aluno *aluno, Disciplina *disciplina, Periodo *periodo, int indicePeriodo, int indice);

void imprimirSemestre(Aluno *aluno, Periodo *periodo, int semestreInicio, int fim);

void atualizarHorasCumpridas(Aluno *aluno, const char *codigo, double mediaFinal);

void imprimirHoras(const char *tipo, int horasCumpridas, int totalHoras);

#endif