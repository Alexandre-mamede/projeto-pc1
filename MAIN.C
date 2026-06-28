#include <stdio.h>
#include "struct.h"
#include "deposito.h"
#include "produto.h"

void salvar_produto(produto produtos[], int total){
    
    FILE *fp = fopen("produtos_salvos.txt","w");
    
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo para salvar.\n");
    return;
    }
    
    for(int i = 0; i < total; i++){
       fprintf(fp,"%s;%d;%.2f\n",
        produtos[i].nome,
        produtos[i].quantidade_itens,
        produtos[i].valor_unitario);
    }
    
    fclose(fp);
    printf("Arquivo salvo com sucesso!!!\n");
}

int main(){

produto produtos[100];
int total = 0;
int opcao;

    printf("\n=== MENU ===\n\n");
    printf("1. Deposito\n");
    printf("2. Produtos\n");
    printf("3. salvar e sair\n");
    scanf("%d",&opcao);
    
    switch (opcao){
        
       case 1:

    int opDeposito;

    do{

        printf("\n=== MENU DEPOSITO ===\n");
        printf("1-Cadastrar\n");
        printf("2-Consultar\n");
        printf("3-Consultar todos\n");
        printf("4-Atualizar\n");
        printf("5-Voltar\n");

        scanf("%d",&opDeposito);

        switch(opDeposito){

            case 1:

                totalDepositos++;
                Cadastrar_Novo_Deposito(depositos,totalDepositos);
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

        }

    }while(opDeposito!=5);

    break;
       case 2:

    int opProduto;

    do{

        printf("\n=== MENU PRODUTO ===\n");
        printf("1-Cadastrar\n");
        printf("2-Consultar\n");
        printf("3-Atualizar\n");
        printf("4-Voltar\n");

        scanf("%d",&opProduto);

        switch(opProduto){

            case 1:

                cadastrar_produto(produtos[totalProdutos],depositos[0]);
                totalProdutos++;
                break;

            case 2:

                consultar_produto(produtos[0],depositos[0]);
                break;

            case 3:

                atualiza_produto();
                break;

        }

    }while(opProduto!=4);

    break;
       case 3:
            salvar_produto(produtos,total);
            printf("saindo......");
            break;
    }
    return 0;
}
