#ifndef PLANEJAMATRICULA_H
#define PLANEJAMATRICULA_H

// le o nome do aluno de maneira circular para garantir a efetividade do calculo
void leNomesComCircularidade(const char *nomeCompleto, char nome1[], char nome2[], char nome3[], char nome4[]);

// atribui a cada letra do nome do aluno o seu respectivo valor tabelado
int obtemValorLetra(char letra);

// efetua um somatorio para encontrar o peso/valor de cada nome do aluno
int calculaPeso(char *nome);

// calcula em quantas disciplinas o aluno pode se matricular no semestre
int calculaLimiteDisciplinas(int peso);

// calcula em quanto tempo o aluno devera finalizar a graduacao
const char* calculaTempoConclusao(int peso);

// decide a enfase que o aluno deve fazer
const char* calculaEnfase(int peso);

// decide quantas disciplinas/dia o aluno deve ter e quantos dias/semana o aluno deve comparecer
const char* encontraDisciplinas(int peso);

// verifica se o aluno tem os pre-requisitos para se matricular em uma disciplina
int verificaPreRequisitos(char *codigo, char historico[][10], int numDisciplinas);

#endif