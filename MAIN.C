#include <stdio.h>
#include "struct.h"
#include "deposito.h"
#include "produto.h"
#include "persistencia.h"

int main()
{
    Deposito depositos[5];
    int totalDepositos = carregarDados(depositos);

    int opcao;
    int opDeposito;
    int opProduto;

    char cep[10];
    char codigo[13];

    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1 - Deposito\n");
        printf("2 - Produto\n");
        printf("3 - Salvar e Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

        // ===================== DEPÓSITO =====================
        case 1:

            do {
                printf("\n===== MENU DEPOSITO =====\n");
                printf("1 - Cadastrar\n");
                printf("2 - Consultar\n");
                printf("3 - Consultar Todos\n");
                printf("4 - Atualizar\n");
                printf("5 - Remover\n");
                printf("6 - Voltar\n");
                printf("Opcao: ");
                scanf("%d", &opDeposito);

                switch (opDeposito) {

                case 1:
                    Cadastrar_Novo_Deposito(depositos, &totalDepositos);
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

                case 5:
                    Remover_Deposito(depositos, &totalDepositos);
                    break;
                }

            } while (opDeposito != 6);

            break;

        // ===================== PRODUTO =====================
        case 2:

            do {
                printf("\n===== MENU PRODUTO =====\n");
                printf("1 - Cadastrar\n");
                printf("2 - Consultar\n");
                printf("3 - Atualizar\n");
                printf("4 - Remover\n");
                printf("5 - Transferir\n");
                printf("6 - Voltar\n");
                printf("Opcao: ");
                scanf("%d", &opProduto);

                switch (opProduto) {

                case 1:
                    cadastrar_produto(depositos, totalDepositos);
                    break;

                case 2:
                    printf("Codigo do produto: ");
                    scanf("%12s", codigo);
                    consultar_produto(depositos, codigo, totalDepositos);
                    break;

                case 3:
                    printf("CEP: ");
                    scanf("%9s", cep);
                    printf("Codigo: ");
                    scanf("%12s", codigo);
                    atualiza_produto(cep, codigo, depositos, totalDepositos);
                    break;

                case 4:
                    printf("CEP: ");
                    scanf("%9s", cep);
                    printf("Codigo: ");
                    scanf("%12s", codigo);
                    remover_produto(cep, codigo, depositos, totalDepositos);
                    break;

                case 5:
                    printf("Funcao transferencia ainda depende da tua implementacao final.\n");
                    break;
                }

            } while (opProduto != 6);

            break;

        // ===================== SAIR =====================
        case 3:
            salvarDados(depositos, totalDepositos);
            printf("\nDados salvos com sucesso!\n");
            printf("Encerrando...\n");
            break;

        default:
            printf("\nOpcao invalida!\n");
        }

    } while (opcao != 3);

    return 0;
}
