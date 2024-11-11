#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct Acao {
    char texto[50];
} Acao;

typedef struct Pilha {
    Acao acoes[MAX];
    int topo;
} Pilha;


void inicializar_pilha(Pilha *p) {
    p->topo = -1;
}

int pilha_vazia(Pilha *p) {
    return p->topo == -1;
}

int pilha_cheia(Pilha *p) {
    return p->topo == MAX - 1;
}

void empilhar(Pilha *p, Acao acao) {
    if (!pilha_cheia(p)) {
        p->acoes[++(p->topo)] = acao;
    }
}

Acao desempilhar(Pilha *p) {
    if (!pilha_vazia(p)) {
        return p->acoes[(p->topo)--];
    }
    Acao acao_vazia = {" "};
    return acao_vazia;
}


Pilha pilha_acao, pilha_refazer;

void realizar_acao(char *texto) {
    Acao nova_acao;
    strcpy(nova_acao.texto, texto);
    empilhar(&pilha_acao, nova_acao);

    
    inicializar_pilha(&pilha_refazer);
    printf("Ação realizada: %s\n", texto);
}

void desfazer() {
    if (!pilha_vazia(&pilha_acao)) {
        Acao acao = desempilhar(&pilha_acao);
        empilhar(&pilha_refazer, acao);
        printf("Desfez: %s\n", acao.texto);
    } else {
        printf("Nada a desfazer.\n");
    }
}

void refazer() {
    if (!pilha_vazia(&pilha_refazer)) {
        Acao acao = desempilhar(&pilha_refazer);
        empilhar(&pilha_acao, acao);
        printf("Refazendo: %s\n", acao.texto);
    } else {
        printf("Nada a refazer.\n");
    }
}


void exibir_estado() {
    printf("Estado atual do editor de texto:\n");
    for (int i = 0; i <= pilha_acao.topo; i++) {
        printf("%s ", pilha_acao.acoes[i].texto);
    }
    printf("\n");
}

int main() {
    
    inicializar_pilha(&pilha_acao);
    inicializar_pilha(&pilha_refazer);

    
    realizar_acao("Escreveu: Olá");
    realizar_acao("Escreveu: Mundo");
    desfazer();
    realizar_acao("Escreveu: Pessoal");
    desfazer();
    refazer();

    
    exibir_estado();

    return 0;
}