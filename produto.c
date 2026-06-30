#include <string.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include "struct.h"

#define MAX_DEP 5

int deposito_cadastrado = 0;
int total_depositos = 0;

Deposito depositos[MAX_DEP];

char categoria[10][50] = {
    "Eletrônico",
    "Moda e Vestuário",
    "Casa e Decoração",
    "Esporte e Lazer",
    "Livros e Músicas",
    "Automotivo",
    "Saúde e Bem-estar",
    "Briquedos e Jogos",
    "Alimentos e Bebidas"
};

// ===================== UTIL =====================

int validar_codigo(char codigo[]) {
    if (strlen(codigo) != 12) return 0;

    for (int i = 0; i < 12; i++)
        if (!isdigit(codigo[i])) return 0;

    return 1;
}

int validar_cep(const char *cep) {
    if (strlen(cep) != 8) return 0;

    for (int i = 0; cep[i] != '\0'; i++)
        if (!isdigit(cep[i])) return 0;

    return 1;
}

// ===================== DEPÓSITO =====================

int deposito_existe(char cep[]) {
    for (int i = 0; i < total_depositos; i++)
        if (strcmp(depositos[i].cep, cep) == 0)
            return i;

    return -1;
}

int Deposito_Full(int idx, float volume) {
    if (depositos[idx].capacidade_atual + volume >= depositos[idx].capacidade_Maxima) {
        printf("\nNao cabe!!!\n");
        return 0;
    }
    return 1;
}

// ===================== DATA =====================

int verificar_data(produto prod) {
    int d, m, a;
    int da, ma, aa;

    time_t t = time(NULL);
    struct tm now = *localtime(&t);

    da = now.tm_mday;
    ma = now.tm_mon + 1;
    aa = now.tm_year + 1900;

    if (sscanf(prod.data_validade, "%d/%d/%d", &d, &m, &a) != 3)
        return -1;

    if (a < aa) return 1;
    if (a > aa) return 0;

    if (m < ma) return 1;
    if (m > ma) return 0;

    if (d < da) return 1;

    return 0;
}

// ===================== PRODUTO EM DEPÓSITO =====================

int alocar_produto_no_deposito(produto novo, const char *cep) {

    int idx = deposito_existe((char*)cep);

    if (idx == -1) {
        printf("Deposito nao encontrado.\n");
        return 0;
    }

    Deposito *dep = &depositos[idx];

    if (dep->qtd_produtos >= 100) {
        printf("Deposito cheio de produtos.\n");
        return -1;
    }

    float volume = novo.volume_unidade * novo.quantidade_itens;

    if (!Deposito_Full(idx, volume))
        return -1;

    dep->produtos[dep->qtd_produtos] = novo;
    dep->qtd_produtos++;
    dep->capacidade_atual += volume;

    return 1;
}

// ===================== CADASTRO =====================

int cadastrar_produto(produto *p) {

    if (deposito_cadastrado == 0) {
        printf("Nenhum deposito cadastrado.\n");
        return 0;
    }

    do {
        printf("Codigo barras (12 digitos): ");
        scanf("%12s", p->codigo_barras);

        if (!validar_codigo(p->codigo_barras))
            printf("Codigo invalido.\n");

    } while (!validar_codigo(p->codigo_barras));

    printf("Nome: ");
    scanf(" %[^\n]", p->nome_produto);

    printf("Tipo (1-10): ");
    scanf("%d", &p->tipo_produto);

    if (p->tipo_produto < 1 || p->tipo_produto > 10)
        return -1;

    p->perecivel = (p->tipo_produto == 10);

    printf("Data fabricacao: ");
    scanf("%10s", p->data_fabricacao);

    if (p->perecivel) {
        printf("Data validade: ");
        scanf("%10s", p->data_validade);

        if (verificar_data(*p) == 1) {
            printf("Produto vencido.\n");
            return -1;
        }
    } else {
        strcpy(p->data_validade, "N/A");
    }

    printf("Volume unidade: ");
    scanf("%f", &p->volume_unidade);

    printf("Quantidade: ");
    scanf("%d", &p->quantidade_itens);

    printf("Valor: ");
    scanf("%f", &p->valor_unitario);

    char cep[10];

    printf("CEP deposito: ");
    scanf("%8s", cep);

    return alocar_produto_no_deposito(*p, cep);
}

// ===================== CONSULTA =====================

int consultar_produto(char codigo[]) {

    for (int d = 0; d < total_depositos; d++) {
        for (int i = 0; i < depositos[d].qtd_produtos; i++) {

            if (strcmp(depositos[d].produtos[i].codigo_barras, codigo) == 0) {

                printf("\nProduto encontrado\n");
                printf("Deposito: %s\n", depositos[d].nome);
                printf("CEP: %s\n", depositos[d].cep);
                printf("Nome: %s\n", depositos[d].produtos[i].nome_produto);
                printf("Codigo: %s\n", depositos[d].produtos[i].codigo_barras);

                return 1;
            }
        }
    }

    printf("Nao encontrado.\n");
    return 0;
}

// ===================== ATUALIZA =====================

int atualiza_produto(char cep[], char codigo[]) {

    int idx = deposito_existe(cep);
    if (idx == -1) return 0;

    Deposito *dep = &depositos[idx];

    for (int i = 0; i < dep->qtd_produtos; i++) {

        if (strcmp(dep->produtos[i].codigo_barras, codigo) == 0) {

            printf("Novo nome: ");
            scanf(" %[^\n]", dep->produtos[i].nome_produto);

            return 1;
        }
    }

    return 0;
}

// ===================== REMOVER =====================

int remover_produto(char cep[], char codigo[]) {

    int idx = deposito_existe(cep);
    if (idx == -1) return 0;

    Deposito *dep = &depositos[idx];

    for (int i = 0; i < dep->qtd_produtos; i++) {

        if (strcmp(dep->produtos[i].codigo_barras, codigo) == 0) {

            for (int j = i; j < dep->qtd_produtos - 1; j++)
                dep->produtos[j] = dep->produtos[j + 1];

            dep->qtd_produtos--;

            return 1;
        }
    }

    return 0;
}
