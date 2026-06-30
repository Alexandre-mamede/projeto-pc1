#include <string.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include "struct.h"

#define MAX_PRODUTOS 100

// ===================== UTIL =====================

int validar_codigo(char codigo[]) {
    if (strlen(codigo) != 12) return 0;

    for (int i = 0; i < 12; i++)
        if (!isdigit((unsigned char)codigo[i])) return 0;

    return 1;
}

// MESMO PADRÃO DO deposito.c: XXXXX-XXX
int validar_cep(const char *cep) {
    if (strlen(cep) != 9) return 0;

    for (int i = 0; i < 9; i++) {
        if (i == 5) {
            if (cep[i] != '-') return 0;
        } else {
            if (!isdigit((unsigned char)cep[i])) return 0;
        }
    }

    return 1;
}

// ===================== DEPÓSITO =====================

int deposito_existe(Deposito depositos[], const char cep[], int total) {
    for (int i = 0; i < total; i++) {
        if (strcmp(depositos[i].cep, cep) == 0)
            return i;
    }
    return -1;
}

int Deposito_Full(int idx, float volume, Deposito depositos[]) {
    if (depositos[idx].capacidade_atual + volume > depositos[idx].capacidade_Maxima) {
        printf("\nDeposito sem capacidade suficiente.\n");
        return 0;
    }
    return 1;
}

// ===================== DATA =====================

int verificar_data(produto prod) {
    int d, m, a;
    int dd, mm, aa;

    time_t t = time(NULL);
    struct tm now = *localtime(&t);

    dd = now.tm_mday;
    mm = now.tm_mon + 1;
    aa = now.tm_year + 1900;

    if (sscanf(prod.data_validade, "%d/%d/%d", &d, &m, &a) != 3)
        return -1;

    if (a < aa) return 1;
    if (a > aa) return 0;

    if (m < mm) return 1;
    if (m > mm) return 0;

    if (d < dd) return 1;

    return 0;
}

// ===================== ALOCAR =====================

int alocar_produto_no_deposito(produto novo, const char *cep,
                                Deposito depositos[], int total) {

    int idx = deposito_existe(depositos, cep, total);
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

    if (!Deposito_Full(idx, volume, depositos))
        return -1;

    dep->produtos[dep->qtd_produtos] = novo;
    dep->qtd_produtos++;
    dep->capacidade_atual += volume;

    return 1;
}

// ===================== CADASTRO =====================

int cadastrar_produto(produto *p, int total_depositos, Deposito depositos[]) {

    if (total_depositos == 0) {
        printf("Nenhum deposito cadastrado.\n");
        return 0;
    }

    do {
        printf("Codigo (12 digitos): ");
        scanf("%12s", p->codigo_barras);

        if (!validar_codigo(p->codigo_barras))
            printf("Codigo invalido.\n");

    } while (!validar_codigo(p->codigo_barras));

    printf("Nome: ");
    scanf(" %[^\n]", p->nome_produto);

    printf("Categoria (1-10): ");
    scanf("%d", &p->tipo_produto);

    if (p->tipo_produto < 1 || p->tipo_produto > 10) {
        printf("Categoria invalida.\n");
        return -1;
    }

    printf("Perecivel (1 sim / 0 nao): ");
    scanf("%d", &p->perecivel);

    printf("Data fabricacao: ");
    scanf("%10s", p->data_fabricacao);

    if (p->perecivel == 1) {

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

    printf("Valor unitario: ");
    scanf("%f", &p->valor_unitario);

    char cep[10];

    printf("CEP (XXXXX-XXX): ");
    scanf("%9s", cep);

    if (!validar_cep(cep)) {
        printf("CEP invalido.\n");
        return -1;
    }

    return alocar_produto_no_deposito(*p, cep, depositos, total_depositos);
}

// ===================== CONSULTA =====================

int consultar_produto(Deposito depositos[], char codigo[], int total) {

    for (int d = 0; d < total; d++) {
        for (int i = 0; i < depositos[d].qtd_produtos; i++) {

            if (strcmp(depositos[d].produtos[i].codigo_barras, codigo) == 0) {

                printf("\nProduto encontrado\n");
                printf("Deposito: %s\n", depositos[d].nome);
                printf("CEP: %s\n", depositos[d].cep);
                printf("Produto: %s\n", depositos[d].produtos[i].nome_produto);
                printf("Codigo: %s\n", depositos[d].produtos[i].codigo_barras);
                printf("Quantidade: %d\n", depositos[d].produtos[i].quantidade_itens);

                return 1;
            }
        }
    }

    printf("Nao encontrado.\n");
    return 0;
}

// ===================== ATUALIZA =====================

int atualiza_produto(char cep[], char codigo[],
                      Deposito depositos[], int total) {

    int idx = deposito_existe(depositos, cep, total);
    if (idx == -1) return 0;

    Deposito *dep = &depositos[idx];

    for (int i = 0; i < dep->qtd_produtos; i++) {

        if (strcmp(dep->produtos[i].codigo_barras, codigo) == 0) {

            printf("Novo nome: ");
            scanf(" %[^\n]", dep->produtos[i].nome_produto);

            printf("Nova quantidade: ");
            scanf("%d", &dep->produtos[i].quantidade_itens);

            printf("Novo valor: ");
            scanf("%f", &dep->produtos[i].valor_unitario);

            return 1;
        }
    }

    return 0;
}

// ===================== REMOVER =====================

int remover_produto(char cep[], char codigo[],
                    Deposito depositos[], int total) {

    int idx = deposito_existe(depositos, cep, total);
    if (idx == -1) return 0;

    Deposito *dep = &depositos[idx];

    for (int i = 0; i < dep->qtd_produtos; i++) {

        if (strcmp(dep->produtos[i].codigo_barras, codigo) == 0) {

            float volume = dep->produtos[i].volume_unidade *
                           dep->produtos[i].quantidade_itens;

            dep->capacidade_atual -= volume;

            for (int j = i; j < dep->qtd_produtos - 1; j++)
                dep->produtos[j] = dep->produtos[j + 1];

            dep->qtd_produtos--;

            return 1;
        }
    }

    return 0;
}
