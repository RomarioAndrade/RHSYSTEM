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

No *insert_TreeByCPF(No *arvoreCPF, No *no) {
    if (arvoreCPF == NULL) {
        return no;
    } else if (arvoreCPF->info->cpf > no->info->cpf) {
        arvoreCPF->esquerda = insert_TreeByCPF(arvoreCPF->esquerda, no);
    } else {
        arvoreCPF->direita = insert_TreeByCPF(arvoreCPF->direita, no);
    }
    return arvoreCPF;
}

No *insert_TreeByName(No *arvoreNome, No *no) {
    if (arvoreNome == NULL) {
        return no;
    } else if (strcmp(arvoreNome->info->nome, no->info->nome) < 0) {
        arvoreNome->esquerda = insert_TreeByName(arvoreNome->esquerda, no);
    } else if (strcmp(arvoreNome->info->nome, no->info->nome) > 0) {
        arvoreNome->direita = insert_TreeByName(arvoreNome->direita, no);
    }
    return arvoreNome;
}

No *searchByName(No *arvore, char nome[]) {
    if (arvore != NULL) {
        if (strncmp(arvore->info->nome, nome, 50) < 0) {
            arvore = searchByName(arvore->esquerda, nome);
        } else if (strncmp(arvore->info->nome, nome, 50) > 0) {
            arvore = searchByName(arvore->direita, nome);
        } else {
            return arvore;
        }
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

No *remove_No(No *no) {
    No *no1, *no2;
    if (no->esquerda == NULL) {
        no2 = no->direita;
        free(no);
        return no2;
    }
    no1 = no;
    no2 = no->esquerda;
    while (no2->direita != NULL) {
        no1 = no2;
        no2 = no2->direita;
    }

    if (no1 != no) {
        no1->direita = no2->esquerda;
        no2->esquerda = no->esquerda;
    }
    no2->direita = no->direita;
    free(no);
    return no2;
}

int removeByCPF(No *arvore, int CPF) {
    if (arvore == NULL) {
        return 0;
    }

    No *ant = NULL;
    No *atual = arvore;

    while (atual != NULL) {
        if (CPF == atual->info->cpf) {
            if (atual == arvore) {
                atual = remove_No(atual);
            } else {
                if (ant->direita == atual) {
                    ant->direita = remove_No(atual);
                } else {
                    ant->esquerda = remove_No(atual);
                }
            }
            return 1;
        }
        ant = atual;
        if (CPF > atual->info->cpf) {
            atual = atual->direita;
        } else {
            atual = atual->esquerda;
        }
    }
    return 0;
}

int removeByName(No *arvore, char nome[]) {
    if (arvore == NULL) {
        return 0;
    }

    No *ant = NULL;
    No *atual = arvore;

    while (atual != NULL) {
        if (strncmp(atual->info->nome, nome, 50) == 0) {
            if (atual == arvore) {
                arvore = remove_No(atual);
            } else {
                if (ant->direita == atual) {
                    ant->direita = remove_No(atual);
                } else {
                    ant->esquerda = remove_No(atual);
                }
            }
            return 1;
        }
        ant = atual;
        if (strncmp(atual->info->nome, nome, 50) > 0) {
            atual = atual->direita;
        } else {
            atual = atual->esquerda;
        }
    }
    return 0;
}

/*
 * 
 */
int main() {
    No *arvoreCPF = NULL;
    No *arvoreNAME = NULL;

    char nome1[50] = "Maria";
    char profissao1[30] = "teste prof";
    Info *i1 = factoryInfo(111111, nome1, profissao1);


    char nome2[50] = "Lucas";
    char profissao2[30] = "teste prof";
    Info *i2 = factoryInfo(222222, nome2, profissao2);

    char nome3[50] = "José";
    char profissao3[30] = "teste prof";
    Info *i3 = factoryInfo(333333, nome3, profissao3);

    char nome4[50] = "Romário";
    char profissao4[30] = "teste prof";
    Info *i4 = factoryInfo(000100, nome4, profissao4);

    char nome5[50] = "teste";
    char profissao5[30] = "teste prof";
    Info *i5 = factoryInfo(444444, nome5, profissao5);

    char nome6[50] = "andre";
    char profissao6[30] = "teste prof";
    Info *i6 = factoryInfo(333330, nome6, profissao6);

    No *n1 = factoryNo(i1);
    No *n2 = factoryNo(i2);
    No *n3 = factoryNo(i3);
    No *n4 = factoryNo(i4);
    No *n5 = factoryNo(i5);
    No *n6 = factoryNo(i6);

    //printf("%d", n1->info->cpf);
    
    No *n11 = factoryNo(i1);
    No *n22 = factoryNo(i2);
    No *n33 = factoryNo(i3);
    No *n44 = factoryNo(i4);
    No *n55 = factoryNo(i5);
    No *n66 = factoryNo(i6);
    

    
    arvoreCPF = insert_TreeByCPF(arvoreCPF, n11);
    arvoreCPF = insert_TreeByCPF(arvoreCPF, n22);
    arvoreCPF = insert_TreeByCPF(arvoreCPF, n33);
    arvoreCPF = insert_TreeByCPF(arvoreCPF, n44);
    arvoreCPF = insert_TreeByCPF(arvoreCPF, n55);
    arvoreCPF = insert_TreeByCPF(arvoreCPF, n66);

    arvoreNAME = insert_TreeByName(arvoreNAME, n1);
    arvoreNAME = insert_TreeByName(arvoreNAME, n2);
    arvoreNAME = insert_TreeByName(arvoreNAME, n3);
    arvoreNAME = insert_TreeByName(arvoreNAME, n4);
    arvoreNAME = insert_TreeByName(arvoreNAME, n5);
    arvoreNAME = insert_TreeByName(arvoreNAME, n6);

    printTree(arvoreCPF);
    printf("\n");
    printTree(arvoreNAME);
    
    char nome7[50] = "andre";

    removeByName(arvoreNAME, nome7);
    removeByCPF(arvoreCPF,000100);
    
    printf("\n");
    printTree(arvoreCPF);
    printf("\n");
    printTree(arvoreNAME);

    return 0;
}

