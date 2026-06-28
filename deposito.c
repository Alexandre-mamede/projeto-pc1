#include <stdio.h>
#include <string.h>
#include "struct.h"
#include "deposito.h"

typedef struct{
    char nome[51];
    char cep[9];
    char endereco[61];
    char telefone[12];
    float capacidade_max;       //em metros cúbicos
}Deposito;
Deposito depositos[5];

void Cadastrar_Novo_Deposito(Deposito Deposito[],int contador){
    if(contador >= 5){ 
        printf("\nJa possui a quantidade maxima de depositos\n");
        return;
    }

    printf("\nDigite o nome do deposito: ");
    scanf("%s", Deposito[contador].nome);
    getchar();
        
    printf("\nDigite o CEP do depoisito: ");
    scanf("%s", Deposito[contador].cep);
    getchar();    
    
    printf("\nDigite o endereço do deposito: ");
    scanf("%s", Deposito[contador].endereco);
    getchar();
    
    printf("\nDigite o telefone: ");
    scanf("%s", Deposito[contador].telefone);
    getchar();

    printf("\nDigite a capacidade máxima em metros cubicos: ");
    scanf("%f", &Deposito[contador].capacidade_max);
    getchar();
}

void Consultar_Inf_Depositos(Deposito Deposito[],int contador){
    if(contador == -1){
        printf("\nNenhum deposito cadastrado para procurar\n");
        return;
    }
    char temp[9];
    int true = 0, encontrado;
    printf("\nDigite o CEP do deposito que deseja consultar: ");
    scanf("%s", temp);
    for(int i=0; i <= contador; i++){
        if(strcmp(Deposito[i].cep,temp) == 0){
            true = 1;
            encontrado = i;
        }
    }

    if(true == 1){
        printf("\n%s",Deposito[encontrado].nome);

        printf("\n%s",Deposito[encontrado].cep);

        printf("\n%s",Deposito[encontrado].endereco);

        printf("\n%s",Deposito[encontrado].telefone);

        printf("\n%f",Deposito[encontrado].capacidade_max); //tenho que alterar no futuro, atualmente vai estar errado
    }else{
        printf("\nDeposito inexistente\n");
        return;
    }
}

void Consultar_Todas_Inf_Depositos(Deposito Deposito[],int contador){
    if(contador == -1){
        printf("\nNenhum deposito cadastrado");
    }
    for(int i=0; i<=contador; i++){
        printf("\n%s",Deposito[i].nome);

        printf("\n%s",Deposito[i].cep);

        printf("\n%s",Deposito[i].endereco);

        printf("\n%s",Deposito[i].telefone);

        printf("\n%f\n",Deposito[i].capacidade_max);
    }
}

void Atualizar_Dados_Deposito(Deposito Deposito[],int contador){
    if(contador == -1){
        printf("\nNenhum deposito cadastrado para procurar\n");
        return;
    }

    char temp[9];
    int true = 0, encontrado, n;
    
    printf("\nDigite o CEP do deposito que deseja consultar: ");
    scanf("%s", temp);
    
    for(int i=0; i <= contador; i++){
        if(strcmp(Deposito[i].cep,temp) == 0){
            true = 1;
            encontrado = i;
        }
    }

    if(true == 1){
        do{
            printf("\nDigite a opção que deseja atualizar:\n");
            printf("\n1. Nome do Depósito;\n");
            printf("2. CEP;\n");
            printf("3. Ebdereço;\n");
            printf("4. Telefone;\n");
            printf("5. Capacidade máxima;\n");
            printf("6. Voltar ao menu Depósito;\n");

            scanf("%d", &n);

            switch(n){
                case 1:
                    char temp_nome[51];
                    printf("\nDigite o novo nome: ");
                    scanf("%[^\n]s",temp);
                    strcpy(Deposito[encontrado].nome,temp);
                    printf("\nNome do Depósito alterado!\n");
                    break;

                case 2:
                    char temp_cep[9];
                    printf("\nDigite o novo CEP: ");
                    scanf("%[^\n]s", Deposito[encontrado].cep);
                    strcpy(Deposito[encontrado].cep,temp_cep);
                    printf("\nCEP do Depósito alterado!\n");
                    break;

                case 3:
                    char temp_endereco[61];
                    printf("\nDigite o novo endereco: ");
                    scanf("%[^\n]s", Deposito[encontrado].endereco);
                    strcpy(Deposito[encontrado].endereco,temp_endereco);
                    printf("\nEndereco do Depóstio alterado!\n");
                    break;

                case 4:
                    char temp_telefone[12];
                    printf("\nDigite o novo telefone: ");
                    scanf("%[^\n]s", temp_telefone);
                    strcpy(Deposito[encontrado].telefone, temp_telefone);
                    printf("\nTelefone do Depósito alterado!\n");
                    break;

                case 5:
                    float temp_capacidade_max;
                    printf("\nDigite a nova capacidade máxima: ");
                    scanf("%f", &temp_capacidade_max);
                    Deposito[encontrado].capacidade_max = temp_capacidade_max;
                    break;

                case 6:
                    printf("\nRetornando ao menu. . .\n");
                    break;

                default:
                printf("\nOpcão inválida, favor escolher outra!\n");
                break;
            }}while(n!=6);
        }



    }
/*
    void Menu_Deposito(){
        int n;
        do{
            printf("\n1. Cadastrar novo depósito;\n");
            printf("2. Cadastrar novo depósito;\n");
            printf("3. Cadastrar novo depósito;\n");
            printf("4. Cadastrar novo depósito;\n");
            printf("5. Cadastrar novo depósito;\n");
            printf("6. Cadastrar novo depósito;\n");

            printf("Digite a opção que deseja escolher: ");
            scanf("%d", &n);

            switch(n){
                case 1:
                    Cadastrar_Novo_Deposito();
                    break;

                case 2:
                    break;

                case 3:
                    break;

                case 4:
                    break;

                case 5:
                    break;

                case 6:
                    break;

            }



        }while(n!=6);



}*/
