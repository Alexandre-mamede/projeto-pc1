#include <stdio.h>
#include "struct.h"
#include "deposito.h"
#include "produto.h"
#include "persistencia.h"

void salvar_produto(produto produtos[], int total) {

    FILE *fp = fopen("dados.bin", "wb");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fwrite(produtos, sizeof(produto), total, fp);

    fclose(fp);

    printf("Produtos salvos com sucesso!\n");
}

void carregar_produto(produto produtos[], int *total) {

    FILE *fp = fopen("dados.bin", "rb");

    if (fp == NULL) {
        *total = 0;
        return;
    }

    *total = fread(produtos, sizeof(produto), 100, fp);

    fclose(fp);
}

int main() {

    produto produtos[100];
  

    int totalProdutos = 0;
    int totalDepositos = 0;

    int opcao;
    int opDeposito;
    int opProduto;

    carregar_produto(produtos, &totalProdutos);

    do {

        printf("\n=== MENU ===\n");
        printf("1. Deposito\n");
        printf("2. Produtos\n");
        printf("3. Salvar e Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

        case 1:

            do {

                printf("\n=== MENU DEPOSITO ===\n");
                printf("1 - Cadastrar\n");
                printf("2 - Consultar\n");
                printf("3 - Consultar Todos\n");
                printf("4 - Atualizar\n");
                printf("5 - Voltar\n");
                scanf("%d", &opDeposito);

                switch (opDeposito) {

                case 1:
                    totalDepositos++;
                    Cadastrar_Novo_Deposito(depositos, totalDepositos);
                    break;

                case 2:
                    Consultar_Inf_Depositos(depositos, totalDepositos);
                    break;

                case 3:
                    Consultar_Todas_Inf_Depositos(depositos, totalDepositos);
                    break;

                case 4:
                    Atualizar_Dados_Deposito(depositos, totalDepositos);
                    break;
                }

            } while (opDeposito != 5);

            break;

        case 2:

            do {

                printf("\n=== MENU PRODUTO ===\n");
                printf("1 - Cadastrar\n");
                printf("2 - Consultar\n");
                printf("3 - Atualizar\n");
                printf("4 - Voltar\n");
                scanf("%d", &opProduto);

                switch (opProduto) {

                case 1:
                    cadastrar_produto(&produtos[totalProdutos], &depositos[0]);
                    totalProdutos++;
                    break;

                case 2:
                    consultar_produto(produtos, totalProdutos);
                    break;

                case 3:
                    atualiza_produto(produtos, totalProdutos);
                    break;
                }

            } while (opProduto != 4);

            break;

        case 3:

            salvar_produto(produtos, totalProdutos);
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida!\n");
        }

    } while (opcao != 3);

    return 0;
}
