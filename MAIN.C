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

    do
    {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1 - Deposito\n");
        printf("2 - Produto\n");
        printf("3 - Salvar e Sair\n");
        printf("Opcao: ");
        scanf("%d",&opcao);

        switch(opcao)
        {

        case 1:

            do
            {
                printf("\n===== MENU DEPOSITO =====\n");
                printf("1 - Cadastrar\n");
                printf("2 - Consultar\n");
                printf("3 - Consultar Todos\n");
                printf("4 - Atualizar\n");
                printf("5 - Remover\n");
                printf("6 - Voltar\n");
                scanf("%d",&opDeposito);

                switch(opDeposito)
                {

                case 1:
                    Cadastrar_Novo_Deposito(depositos,&totalDepositos);
                    break;

                case 2:
                    Consultar_Inf_Depositos(depositos,totalDepositos);
                    break;

                case 3:
                    Consultar_Todas_Inf_Depositos(depositos,totalDepositos);
                    break;

                case 4:
                    Atualizar_Dados_Deposito(depositos,totalDepositos);
                    break;

                case 5:
                    Remover_Deposito(depositos,&totalDepositos);
                    break;
                }

            }while(opDeposito != 6);

            break;

        case 2:

            do
            {
                printf("\n===== MENU PRODUTO =====\n");
                printf("1 - Cadastrar\n");
                printf("2 - Consultar\n");
                printf("3 - Atualizar\n");
                printf("4 - Remover\n");
                printf("5 - Transferir\n");
                printf("6 - Voltar\n");
                scanf("%d",&opProduto);

                switch(opProduto)
                {

                case 1:
                    cadastrar_produto(produtos,depositos[0]);
                    break;

                case 2:
                    consultar_produto();
                    break;

                case 3:
                    atualiza_produto();
                    break;

                case 4:
                    remover_produto();
                    break;

                case 5:
                    transferir_produto();
                    break;
                }

            }while(opProduto != 6);

            break;

        case 3:

            salvarDados(depositos,totalDepositos);

            printf("\nDados salvos com sucesso!\n");
            printf("Encerrando...\n");
            break;

        default:
            printf("\nOpcao invalida!\n");

        }

    }while(opcao != 3);

    return 0;
}
