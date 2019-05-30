#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

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
    } else if (arvoreCPF->info->cpf > no->info->cpf) { //se o CPF do no for menor insere na esquerda
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
    if (arvore != NULL) {
        if (arvore->info->cpf > CPF) {
            arvore = searchByCPF(arvore->esquerda, CPF);
        } else if (arvore->info->cpf < CPF) {
            arvore = searchByCPF(arvore->direita, CPF);
        } else {
            return arvore;
        }
    }
}

void printTree(No * arvore) {
    if (arvore == NULL)
        return;
    printf("%-15s  %20d  %-15s\n", arvore->info->nome, arvore->info->cpf, arvore->info->profissao);
    printTree(arvore->esquerda);
    printTree(arvore->direita);
}

No * remove_No(No * no) {
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

No * removeByCPF(No *arvore, int CPF) {
    if (arvore == NULL) {
        return arvore;
    }

    No *ant = NULL;
    No *atual = arvore;

    while (atual != NULL) {
        if (CPF == atual->info->cpf) {
            if (atual == arvore) {
                arvore = remove_No(atual);
            } else {
                if (ant->direita == atual) {
                    ant->direita = remove_No(atual);
                } else {
                    ant->esquerda = remove_No(atual);
                }
            }
            return arvore;
        }
        ant = atual;
        if (CPF > atual->info->cpf) {
            atual = atual->direita;
        } else {
            atual = atual->esquerda;
        }
    }
    return arvore;
}

No * removeByName(No *arvore, char nome[]) {
    if (arvore == NULL) {
        return arvore;
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
            return arvore;
        }
        ant = atual;
        if (strncmp(atual->info->nome, nome, 50) > 0) {
            atual = atual->direita;
        } else {
            atual = atual->esquerda;
        }
    }
    return arvore;
}

/*
 * 
 */
int main() {
    No *arvoreCPF = NULL;
    No *arvoreNAME = NULL;
    No *node_1 = NULL;
    No *node_2 = NULL;
    Info *info1 = NULL;
    Info *info2 = NULL;

    char nome[50];
    char profissao[30];
    char messagens[50] = "";
    int CPF, option;

    do {
        system("clear");
        printf("Sistema de RH versão 0.01\n");
        printf("=========================\n\n");
        printf("< 1 > Inserir:\n");
        printf("< 2 > Remover por nome:\n");
        printf("< 3 > Remover por CPF:\n");
        printf("< 4 > Buscar por nome:\n");
        printf("< 5 > Buscar por CPF:\n");
        printf("< 6 > Listar:\n");
        printf("< 0 > Para sair\n\n");
        printf("Status: %s\n\n", messagens);
        printf("> ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                system("clear");
                strcpy(messagens, "");
                printf("Sistema de RH versão 0.01\n");
                printf("=========================\n\n");
                printf("%-10s%2s", "Nome", "> ");
                scanf("%s", &nome);
                printf("%-10s%2s", "Cpf", "> ");
                scanf("%d", &CPF);
                printf("%-10s%3s", "Profissão", "> ");
                scanf("%s", &profissao);

                info1 = factoryInfo(CPF, nome, profissao);
                info2 = factoryInfo(CPF, nome, profissao);

                node_1 = factoryNo(info1);
                node_2 = factoryNo(info2);

                if (searchByCPF(arvoreCPF, info1->cpf) != NULL || searchByName(arvoreNAME, info2->nome) != NULL) {
                    system("clear");
                    printf("Sistema de RH versão 0.01\n");
                    printf("=========================\n\n");
                    printf("O Nome ou o CPF já foi cadastrado\n");
                    printf("\n");
                    printf("Digite 1 para voltar ao menu:");
                    scanf("%d", &option);
                } else {
                    arvoreCPF = insert_TreeByCPF(arvoreCPF, node_1);
                    arvoreNAME = insert_TreeByName(arvoreNAME, node_2);
                    strcpy(messagens, "Funcionario cadastrado com sucesso");
                }
                break;

            case 2:
                system("clear");
                strcpy(messagens, "");
                printf("Sistema de RH versão 0.01\n");
                printf("=========================\n\n");
                printf("Insira o nome do funcionário a ser removido\n");
                printf("%-10s%2s", "Nome", "> ");
                scanf("%s", &nome);

                if (searchByName(arvoreNAME, nome) == NULL) {
                    system("clear");
                    printf("Sistema de RH versão 0.01\n");
                    printf("=========================\n\n");
                    printf("O funcionario não esta cadastrado\n");
                    printf("\n");
                    printf("Digite 1 para voltar ao menu:");
                    scanf("%d", &option);
                } else {
                    arvoreCPF = removeByName(arvoreNAME, nome);
                    arvoreNAME = removeByName(arvoreCPF, nome);
                    strcpy(messagens, "Funcionario removido com sucesso");
                }


                break;

            case 3:
                system("clear");
                printf("Sistema de RH versão 0.01\n");
                printf("=========================\n\n");
                printf("Insira o CPF do funcionário a ser removido\n");
                printf("%-10s%2s", "CPF", "> ");
                scanf("%d", &CPF);

                if (searchByCPF(arvoreCPF, CPF) == NULL) {
                    system("clear");
                    printf("Sistema de RH versão 0.01\n");
                    printf("=========================\n\n");
                    printf("O CPF não esta cadastrado\n");
                    printf("\n");
                    printf("Digite 1 para voltar ao menu:");
                    scanf("%d", &option);
                } else {
                    arvoreCPF = removeByCPF(arvoreCPF, CPF);
                    arvoreNAME = removeByCPF(arvoreNAME, CPF);
                    strcpy(messagens, "Funcionario removido com sucesso");
                }
                break;

            case 4:
                system("clear");
                printf("Sistema de RH versão 0.01\n");
                printf("=========================\n\n");
                printf("Insira o nome do funcionário a ser procurado\n");
                printf("%-10s%2s", "Nome", "> ");
                scanf("%s", &nome);

                No *tmp = searchByName(arvoreNAME, nome);

                system("clear");
                printf("Sistema de RH versão 0.01\n");
                printf("=========================\n\n");
                printf("%-15s  %-20s  %-15s\n", "Nome", "CPF", "Profissão");
                printf("===============  ===================== ===============\n");
                if (tmp == NULL) {
                    printf("Não encontrado\n");
                } else {
                    printf("%-15s  %-20d  %-15s\n", tmp->info->nome, tmp->info->cpf, tmp->info->profissao);
                }

                printf("\n");
                printf("Digite 1 para voltar ao menu:");
                scanf("%d", &option);

                break;

            case 5:
                system("clear");
                printf("Sistema de RH versão 0.01\n");
                printf("=========================\n\n");
                printf("Insira o CPF do funcionário a ser procurado\n");
                printf("%-10s%2s", "CPF", "> ");
                scanf("%d", &CPF);

                No *no = searchByCPF(arvoreCPF, CPF);

                system("clear");
                printf("Sistema de RH versão 0.01\n");
                printf("=========================\n\n");
                printf("%-15s  %-20s  %-15s\n", "Nome", "CPF", "Profissão");
                printf("===============  ====================  ===============\n");
                if (no == NULL) {
                    printf("Não encontrado\n");
                } else {
                    printf("%-15s  %-20d  %-15s\n", no->info->nome, no->info->cpf, no->info->profissao);
                }

                printf("\n");
                printf("Digite 1 para voltar ao menu:");
                scanf("%d", &option);

                break;

            case 6:
                system("clear");
                printf("Sistema de RH versão 0.01\n");
                printf("=========================\n\n");
                printf("%-15s  %-20s  %-15s\n", "Nome", "CPF", "Profissão");
                printf("===============  ====================  ===============\n");

                if (arvoreNAME == NULL) {
                    printf("Arvore vazia\n");
                } else {
                    printTree(arvoreNAME);
                }
                printf("\n");
                printf("Digite 1 para voltar ao menu:");
                scanf("%d", &option);
                break;
        }
    } while (option);
    return 0;
}

