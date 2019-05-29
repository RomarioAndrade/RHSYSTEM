#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct info {
    int cpf;
    char nome[50];
    char profissao[30];
};
typedef struct info Info;

struct t_no {
    Info *info;
    struct t_no *esquerda;
    struct t_no *direita;
};
typedef struct t_no No;

No *factoryNo(Info *info) {
    No *no = malloc(sizeof (No));
    no->info = info;
    no->direita = NULL;
    no->esquerda = NULL;
    return no;
}

Info *factoryInfo(int CPF, char nome[], char profissao[]) {
    Info *info = malloc(sizeof (Info));
    info->cpf = CPF;
    strncpy(info->nome, nome, 50);
    strncpy(info->profissao, profissao, 30);
    return info;
}

void insert_TreeByCPF(No **arvoreCPF, No *no) {
    if (*arvoreCPF == NULL) {
        *arvoreCPF = no;
    } else if ((*arvoreCPF)->info->cpf > no->info->cpf) {
        insert_TreeByCPF(&(*arvoreCPF)->esquerda, no);
    } else {
        insert_TreeByCPF(&(*arvoreCPF)->direita, no);
    }
}

void insert_TreeByName(No **arvoreNome, No *no) {
    if (*arvoreNome == NULL) {
        *arvoreNome = no;
    } else if (strcmp((*arvoreNome)->info->nome, no->info->nome) > 0) {
        insert_TreeByName(&(*arvoreNome)->esquerda, no);
    } else if (strcmp((*arvoreNome)->info->nome, no->info->nome) < 0) {
        insert_TreeByName(&(*arvoreNome)->direita, no);
    }
}

No *searchByName(No *arvore, char nome[]) {
    printf("Nó atual: %p | esquerda: %p | info: %s | direita %p \n", arvore, arvore->esquerda,
            arvore->info->nome, arvore->direita);


    if (arvore == NULL || strncmp(arvore->info->nome, nome, 50) == 0) {
        return arvore;
    }
    if (strncmp(arvore->info->nome, nome, 50) < 0) {
        return searchByName(arvore->esquerda, nome);
    } else if (strncmp(arvore->info->nome, nome, 50) > 0) {
        return searchByName(arvore->direita, nome);
    }
}

No *searchByCPF(No *arvore, int CPF) {
    if (arvore == NULL || arvore->info->cpf == CPF)
        return arvore;
    if (arvore->info->cpf > CPF)
        return searchByCPF(arvore->esquerda, CPF);
    else
        return searchByCPF(arvore->direita, CPF);
}

void printTree(No *arvore) {
    if (arvore == NULL)
        return;
    printf("Nó atual: %p | esquerda: %p | info: %s | direita %p \n", arvore, arvore->esquerda,
            arvore->info->nome, arvore->direita);
    printTree(arvore->esquerda);
    printTree(arvore->direita);
}

void removeByCPF(No **arvore, int CPF) {

    if (*arvore == NULL) {
        return;
    }

    if ((*arvore)->info->cpf < CPF) {
        removeByCPF(&(*arvore)->esquerda, CPF);
    } else if ((*arvore)->info->cpf > CPF) {
        printf("Maior");
        removeByCPF(&(*arvore)->direita, CPF);
    } else {
        printf("%d  %s \n", (*arvore)->info->cpf, (*arvore)->info->nome);
    }
}

/*
 * 
 */
int main() {
    No *arvoreCPF = NULL;
    No *arvoreNAME = NULL;

    char nome1[50] = "teste 1";
    char profissao1[30] = "teste prof";
    Info *i1 = factoryInfo(111111, nome1, profissao1);


    char nome2[50] = "romario 2";
    char profissao2[30] = "teste prof";
    Info *i2 = factoryInfo(222222, nome2, profissao2);

    char nome3[50] = "teste 3";
    char profissao3[30] = "teste prof";
    Info *i3 = factoryInfo(333333, nome3, profissao3);

    char nome4[50] = "teste 0";
    char profissao4[30] = "teste prof";
    Info *i4 = factoryInfo(000100, nome4, profissao4);

    char nome5[50] = "teste 4";
    char profissao5[30] = "teste prof";
    Info *i5 = factoryInfo(444444, nome5, profissao5);

    char nome6[50] = "joao 5";
    char profissao6[30] = "teste prof";
    Info *i6 = factoryInfo(333330, nome6, profissao6);

    No *n1 = factoryNo(i1);
    No *n2 = factoryNo(i2);
    No *n3 = factoryNo(i3);
    No *n4 = factoryNo(i4);
    No *n5 = factoryNo(i5);
    No *n6 = factoryNo(i6);

    //printf("%d", n1->info->cpf);

    insert_TreeByCPF(&arvoreCPF, n1);
    insert_TreeByCPF(&arvoreCPF, n2);
    insert_TreeByCPF(&arvoreCPF, n3);
    insert_TreeByCPF(&arvoreCPF, n4);
    insert_TreeByCPF(&arvoreCPF, n5);
    insert_TreeByCPF(&arvoreCPF, n6);
    
    insert_TreeByName(&arvoreNAME, n1);
    insert_TreeByName(&arvoreNAME, n2);
    insert_TreeByName(&arvoreNAME, n3);
    insert_TreeByName(&arvoreNAME, n4);
    insert_TreeByName(&arvoreNAME, n5);
    insert_TreeByName(&arvoreNAME, n6);

    printTree(arvoreCPF);
    printf("\n");
    printTree(arvoreNAME);
    //No *node = searchByName(arvoreCPF, nome2);
    //if (node == NULL) {
    //    printf("È null");
    //}


    //
    //removeByCPF(&arvore, 333333);

    return 0;
}

