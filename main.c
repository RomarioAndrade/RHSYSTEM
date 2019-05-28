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
    if (arvore == NULL || strcmp(arvore->info->nome, nome) == 0)
        return arvore;
    if (strcmp(arvore->info->nome, nome) > 0)
        return searchByName(arvore->esquerda, nome);
    else if (strcmp(arvore->info->nome, nome) < 0) {
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

void printTree(No* tree) {
    if (tree == NULL)
        return;
    printf("Nó atual: %p | esquerda: %p | info: %s | direita %p \n", tree, tree->esquerda,
            tree->info->nome, tree->direita);
    printTree(tree->esquerda);
    printTree(tree->direita);
}

void remove_(No **arvore, Info *info, int nameOrCPF) {

}

No *search_(No **arvore, Info *info, int nameOrCPF) {
    return *arvore;
}

/*
 * 
 */
int main(int argc, char** argv) {
    No *arvore = NULL;

    char nome1[50] = "teste 1";
    char profissao1[30] = "teste prof";
    Info *i1 = factoryInfo(111111, nome1, profissao1);
    //printf("%s", i1->profissao);


    char nome2[50] = "teste 2";
    char profissao2[30] = "teste prof";
    Info *i2 = factoryInfo(222222, nome2, profissao2);

    char nome3[50] = "teste 3";
    char profissao3[30] = "teste prof";
    Info *i3 = factoryInfo(333333, nome3, profissao3);

    char nome4[50] = "teste 0";
    char profissao4[30] = "teste prof";
    Info *i4 = factoryInfo(100001, nome4, profissao4);

    No *n1 = factoryNo(i1);
    No *n2 = factoryNo(i2);
    No *n3 = factoryNo(i3);
    No *n4 = factoryNo(i4);

    //printf("%d", n1->info->cpf);

    insert_TreeByName(&arvore, n1);
    insert_TreeByName(&arvore, n2);
    insert_TreeByName(&arvore, n3);
    insert_TreeByName(&arvore, n4);

    printTree(arvore);

    return (EXIT_SUCCESS);
}

