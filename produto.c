#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "struct.h"

#define MAX_DEP 5

Deposito depositos[MAX_DEP];
int total_depositos = 0;

// ===================== VALIDAÇÕES =====================

int validar_codigo(char c[]) {
    if (strlen(c) != 12) return 0;
    for (int i = 0; i < 12; i++)
        if (!isdigit(c[i])) return 0;
    return 1;
}

int validar_cep(char cep[]) {
    if (strlen(cep) != 8) return 0;
    for (int i = 0; i < 8; i++)
        if (!isdigit(cep[i])) return 0;
    return 1;
}

// ===================== DEPÓSITO =====================

int buscar_deposito(char cep[]) {
    for (int i = 0; i < total_depositos; i++)
        if (strcmp(depositos[i].cep, cep) == 0)
            return i;
    return -1;
}

// ===================== DATA =====================

int produto_vencido(produto p) {
    int d, m, a;
    int dd, mm, aa;

    time_t t = time(NULL);
    struct tm now = *localtime(&t);

    dd = now.tm_mday;
    mm = now.tm_mon + 1;
    aa = now.tm_year + 1900;

    if (sscanf(p.data_validade, "%d/%d/%d", &d, &m, &a) != 3)
        return 1;

    if (a < aa) return 1;
    if (a > aa) return 0;
    if (m < mm) return 1;
    if (m > mm) return 0;
    if (d < dd) return 1;

    return 0;
}

// ===================== CADASTRAR PRODUTO =====================

void cadastrar_produto() {

    if (total_depositos == 0) {
        printf("Nenhum deposito cadastrado.\n");
        return;
    }

    produto p;

    do {
        printf("Codigo de barras (12 digitos): ");
        scanf("%12s", p.codigo_barras);
    } while (!validar_codigo(p.codigo_barras));

    printf("Nome produto: ");
    scanf(" %[^\n]", p.nome_produto);

    printf("Tipo produto (1-10): ");
    scanf("%d", &p.tipo_produto);

    printf("Perecivel (1 sim / 0 nao): ");
    scanf("%d", &p.perecivel);

    printf("Data fabricacao (DD/MM/AAAA): ");
    scanf("%10s", p.data_fabricacao);

    if (p.perecivel == 1) {
        printf("Data validade (DD/MM/AAAA): ");
        scanf("%10s", p.data_validade);

        if (produto_vencido(p)) {
            printf("Produto vencido. Cadastro negado.\n");
            return;
        }
    } else {
        strcpy(p.data_validade, "N/A");
    }

    printf("Volume unidade: ");
    scanf("%f", &p.volume_unidade);

    printf("Quantidade: ");
    scanf("%d", &p.quantidade_itens);

    printf("Valor unitario: ");
    scanf("%f", &p.valor_unitario);

    char cep[9];

    while (1) {

        printf("CEP deposito: ");
        scanf("%8s", cep);

        if (!validar_cep(cep)) continue;

        int idx = buscar_deposito(cep);

        if (idx == -1) {
            printf("Deposito nao encontrado.\n");
            continue;
        }

        Deposito *d = &depositos[idx];

        if (d->qtd_produtos >= 100) {
            printf("Deposito cheio (100 produtos).\n");
            return;
        }

        float volume = p.volume_unidade * p.quantidade_itens;

        if (d->capacidade_atual + volume > d->capacidade_Maxima) {
            printf("Sem capacidade no deposito.\n");
            return;
        }

        d->produtos[d->qtd_produtos] = p;
        d->qtd_produtos++;
        d->capacidade_atual += volume;

        printf("Produto cadastrado.\n");
        return;
    }
}

// ===================== CONSULTA =====================

void consultar_produto() {

    char codigo[13];
    int achou = 0;

    printf("Codigo de barras: ");
    scanf("%12s", codigo);

    for (int d = 0; d < total_depositos; d++) {
        for (int i = 0; i < depositos[d].qtd_produtos; i++) {

            if (strcmp(depositos[d].produtos[i].codigo_barras, codigo) == 0) {

                printf("\nDeposito: %s | CEP: %s\n",
                       depositos[d].nome,
                       depositos[d].cep);

                printf("Produto: %s\n",
                       depositos[d].produtos[i].nome_produto);

                printf("Tipo: %d\n",
                       depositos[d].produtos[i].tipo_produto);

                printf("Qtd: %d\n",
                       depositos[d].produtos[i].quantidade_itens);

                achou = 1;
            }
        }
    }

    if (!achou)
        printf("Produto nao encontrado.\n");
}

// ===================== REMOVER =====================

void remover_produto() {

    char cep[9], codigo[13];
    int qtd;

    printf("CEP: ");
    scanf("%8s", cep);

    printf("Codigo: ");
    scanf("%12s", codigo);

    int idx = buscar_deposito(cep);
    if (idx == -1) return;

    Deposito *d = &depositos[idx];

    for (int i = 0; i < d->qtd_produtos; i++) {

        if (strcmp(d->produtos[i].codigo_barras, codigo) == 0) {

            printf("Quantidade atual: %d\n",
                   d->produtos[i].quantidade_itens);

            printf("Remover: ");
            scanf("%d", &qtd);

            if (qtd > d->produtos[i].quantidade_itens)
                return;

            d->produtos[i].quantidade_itens -= qtd;
            d->capacidade_atual -= qtd * d->produtos[i].volume_unidade;

            if (d->produtos[i].quantidade_itens == 0) {
                for (int j = i; j < d->qtd_produtos - 1; j++)
                    d->produtos[j] = d->produtos[j + 1];

                d->qtd_produtos--;
            }

            return;
        }
    }
}

// ===================== TRANSFERÊNCIA =====================

void transferir_produto() {

    char cep_o[9], cep_d[9], codigo[13];
    int qtd;

    printf("Origem CEP: ");
    scanf("%8s", cep_o);

    printf("Destino CEP: ");
    scanf("%8s", cep_d);

    printf("Codigo: ");
    scanf("%12s", codigo);

    printf("Quantidade: ");
    scanf("%d", &qtd);

    int o = buscar_deposito(cep_o);
    int d = buscar_deposito(cep_d);

    if (o == -1 || d == -1) return;

    Deposito *orig = &depositos[o];
    Deposito *dest = &depositos[d];

    for (int i = 0; i < orig->qtd_produtos; i++) {

        if (strcmp(orig->produtos[i].codigo_barras, codigo) == 0) {

            float vol = qtd * orig->produtos[i].volume_unidade;

            if (dest->capacidade_atual + vol > dest->capacidade_Maxima) {
                printf("Sem espaco no destino.\n");
                return;
            }

            orig->produtos[i].quantidade_itens -= qtd;
            dest->produtos[dest->qtd_produtos] = orig->produtos[i];
            dest->produtos[dest->qtd_produtos].quantidade_itens = qtd;

            orig->capacidade_atual -= vol;
            dest->capacidade_atual += vol;

            dest->qtd_produtos++;

            if (orig->produtos[i].quantidade_itens == 0) {
                for (int j = i; j < orig->qtd_produtos - 1; j++)
                    orig->produtos[j] = orig->produtos[j + 1];

                orig->qtd_produtos--;
            }

            return;
        }
    }
}
