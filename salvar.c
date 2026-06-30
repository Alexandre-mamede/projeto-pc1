#include <stdio.h>
#include "persistencia.h"

#define ARQUIVO_BINARIO "dados.bin"
#define MAX_DEPOSITOS 5

int carregarDados(Deposito depositos[]) {
    FILE *fp = fopen(ARQUIVO_BINARIO, "rb");

    if (fp == NULL) {
        printf("\n[Aviso] Arquivo '%s' nao encontrado. O sistema iniciara vazio.\n", ARQUIVO_BINARIO);
        return 0;
    }

    int lidos = 0;

    lidos = fread(depositos, sizeof(Deposito), MAX_DEPOSITOS, fp);

    fclose(fp);
    printf("\n[Sucesso] %d deposito(s) carregado(s) com sucesso de '%s'.\n", lidos, ARQUIVO_BINARIO);

    return lidos;
}

int salvarDados(Deposito depositos[], int total_depositos) {
    if (total_depositos < 0) {
        total_depositos = 0;
    }

    FILE *fp = fopen(ARQUIVO_BINARIO, "wb");

    if (fp == NULL) {
        printf("\n[Erro] Nao foi possivel abrir o arquivo '%s' para escrita.\n", ARQUIVO_BINARIO);
        return 0;
    }
    int gravados = fwrite(depositos, sizeof(Deposito), total_depositos, fp);

    fclose(fp);

    if (gravados == total_depositos) {
        printf("\n[Sucesso] %d deposito(s) gravado(s) com sucesso em '%s'.\n", gravados, ARQUIVO_BINARIO);
        return 1;
    } else {
        printf("\n[Erro] Falha parcial na gravacao dos dados.\n");
        return 0;
    }
}
