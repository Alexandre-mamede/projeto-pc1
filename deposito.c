#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUTOS 100

int validar_cep(char cep[]){
    if (strlen(cep) != 9)
        return 0;

    for (int i = 0; i < 9; i++){
        if (i == 5){
            if (cep[i] != '-')
                return 0;
        }
        else{
            if (!isdigit((unsigned char)cep[i]))
                return 0;
        }
    }

    return 1;
}

void Cadastrar_Novo_Deposito(Deposito depositos[],int *contador){ //completa
    int c;
    if(*contador >= 5){ 
        printf("\nJa possui a quantidade maxima de depositos\n");
        return;
    }

    printf("\nDigite o nome do deposito: ");
    if(scanf("%50[^\n]s", depositos[*contador].nome) != 1){
        printf("\nNome invalido\n");
        while((c = getchar()) != '\n' && c != EOF);
        return;   
    }while((c = getchar()) != '\n' && c != EOF);


    printf("\nDigite o CEP do depoisito: ");
    if(scanf("%9s", depositos[*contador].cep) != 1){
        printf("\nCEP invalido\n");
        while((c = getchar()) != '\n' && c != EOF);
        return;   
    }while((c = getchar()) != '\n' && c != EOF);
    
    printf("\nDigite o endereço do deposito: ");
    if(scanf("%[^\n]s", depositos[*contador].endereco) != 1){
        printf("\nEndereco invalido\n");
        while((c = getchar()) != '\n' && c != EOF);
        return;   
    }while((c = getchar()) != '\n' && c != EOF);
    
    printf("\nDigite o telefone: ");
    if(scanf("%11s", depositos[*contador].telefone) != 1){
        printf("\nTelefone invalido\n");
        while((c = getchar()) != '\n' && c != EOF);
        return;   
    }while((c = getchar()) != '\n' && c != EOF);

    printf("\nDigite a capacidade máxima em metros cubicos: ");
    if(scanf("%f", &depositos[*contador].capacidade_Maxima) != 1){
        printf("\nValor invalido\n");
        while((c = getchar()) != '\n' && c != EOF);
        return;
    }while((c = getchar()) != '\n' && c != EOF);

    (*contador)++;
}

void Consultar_Inf_Depositos(Deposito depositos[],int contador){  //completa
    int c;
    
    if(contador == 0){
        printf("\nNenhum deposito cadastrado para procurar\n");
        return;
    }

    char temp[10];
    int encontrado = -1,valido;
    do{
        printf("\nDigite o CEP do deposito que deseja consultar: ");
        
        scanf("%9s", temp);
        while ((c = getchar()) != '\n' && c != EOF);

        valido = validar_cep(temp);

        if(!valido){
            printf("\nFormato invalido, deve ser 'XXXXX-XXX'\n");
        }

    }while(!valido);

    for(int i=0; i < contador; i++){
        if(strcmp(depositos[i].cep,temp) == 0){
            encontrado = i;
            break;
        }
    }

    if(encontrado != -1){
        printf("\nNome: %s",depositos[encontrado].nome);

        printf("\nCEP: %s",depositos[encontrado].cep);

        printf("\nEndereco: %s",depositos[encontrado].endereco);

        printf("\nTelefone: %s",depositos[encontrado].telefone);

        printf("\nQuantidade: %.2f / %.2f m3",depositos[encontrado].capacidade_atual,depositos[encontrado].capacidade_Maxima);
       
        printf("\nProdutos do deposito:\n");

        if(depositos[encontrado].qtd_produtos == 0){
            printf("\nNao possui nenhum produto\n");
        }else{
        for(int i=0; i<depositos[encontrado].qtd_produtos; i++){            
            printf("\n%d - %s\n", depositos[encontrado].produtos[i].quantidade_itens, depositos[encontrado].produtos[i].nome_produto);

        }
    }

    }else{
        printf("\nDeposito inexistente\n");
        return;
    }
}

void Consultar_Todas_Inf_Depositos(Deposito depositos[],int contador){  //completa
    if(contador == 0){
        printf("\nNenhum deposito cadastrado");
        return;
    }
    for(int i=0; i<contador; i++){
        printf("\n-----------------------------\n");

        printf("\nNome: %s",depositos[i].nome);

        printf("\nCEP: %s",depositos[i].cep);

        printf("\nEndereco: %s",depositos[i].endereco);

        printf("\nTelefone: %s",depositos[i].telefone);

        printf("\nCapacidade: %.2f / %.2f m3\n",depositos[i].capacidade_atual,depositos[i].capacidade_Maxima);

        printf("\nProdutos do deposito:\n");

        if(depositos[i].qtd_produtos == 0){
            printf("\nNao possui nenhum produto\n");

        }
        else{
            for(int j=0; j<depositos[i].qtd_produtos; j++){            
                printf("\n%d - %s\n", depositos[i].produtos[j].quantidade_itens, depositos[i].produtos[j].nome_produto);

        }printf("\n");
    }
    }
}

void Atualizar_Dados_Deposito(Deposito depositos[],int contador){  //completa
    if(contador == 0){
        printf("\nNenhum deposito cadastrado para procurar\n");
        return;
    }

    char temp[10];
    int  encontrado = -1,repetido = 0, n,c,validado;
    
    printf("\nDigite o CEP do deposito que deseja consultar: ");
    scanf("%9s", temp);
    while ((c = getchar()) != '\n' && c != EOF);
    validado = validar_cep(temp);        
    if(!validado){
       printf("\nFormato invalido, deve ser 'XXXXX-XXX'\n");
       return;
    }

    
    for(int i=0; i < contador; i++){
        if(strcmp(depositos[i].cep,temp) == 0){
            encontrado = i;
            break;
        }
    }

    if(encontrado != -1){
        do{
            printf("\nDigite a opção que deseja atualizar:\n");
            printf("\n1. Nome do Depósito;\n");
            printf("2. CEP;\n");
            printf("3. Endereço;\n");
            printf("4. Telefone;\n");
            printf("5. Capacidade máxima;\n");
            printf("6. Voltar ao menu Depósito;\n");

            scanf("%d", &n);
            while ((c = getchar()) != '\n' && c != EOF);
            

            switch(n){
                case 1:
                    char temp_nome[51];
                    
                    printf("\nDigite o novo nome: ");
                    scanf("%50[^\n]",temp_nome);
                    while ((c = getchar()) != '\n' && c != EOF);
                    
                    strcpy(depositos[encontrado].nome,temp_nome);
                    printf("\nNome do Depósito alterado!\n");
                    break;

                case 2:
                    char temp_cep[10];
                    
                    printf("\nDigite o novo CEP: ");
                    scanf("%9[^\n]s", temp_cep);
                    while ((c = getchar()) != '\n' && c != EOF);
                    
                    validado = validar_cep(temp_cep);
                    
                    if(!validado){
                        printf("\nFormato de CEP invalido\n");
                    }else{
                        repetido = 0;

                        for(int j=0; j<contador; j++){
                            if(j != encontrado && strcmp(temp_cep,depositos[j].cep) == 0){
                                repetido = 1;
                                break;
                            }
                        }
                        if(repetido){
                            printf("\nEsse CEP já existe\n");
                        }else{
                            strcpy(depositos[encontrado].cep,temp_cep);
                            printf("\nCEP do Depósito alterado!\n");
                        }
                    }

                    break;

                case 3:
                    char temp_endereco[61];
                    
                    printf("\nDigite o novo endereco: ");
                    scanf("%60[^\n]s", temp_endereco);
                    while ((c = getchar()) != '\n' && c != EOF);
                            
                    strcpy(depositos[encontrado].endereco,temp_endereco);
                    printf("\nEndereco do Depóstio alterado!\n");
                    break;

                case 4:
                    char temp_telefone[12];
                    
                    printf("\nDigite o novo telefone: ");
                    scanf("%11[^\n]s", temp_telefone);
                    while ((c = getchar()) != '\n' && c != EOF);    

                    strcpy(depositos[encontrado].telefone, temp_telefone);
                    printf("\nTelefone do Depósito alterado!\n");
                    break;

                case 5:
                    float temp_capacidade_Max;

                    printf("\nDigite a nova capacidade máxima: ");
                    scanf("%f", &temp_capacidade_Max);
                    while ((c = getchar()) != '\n' && c != EOF);        
                    if(depositos[encontrado].capacidade_atual > temp_capacidade_Max){
                        printf("\nTamanho invalido\n");
                    }else{
                        depositos[encontrado].capacidade_Maxima = temp_capacidade_Max;
                    }
                    break;

                case 6:
                    printf("\nRetornando ao menu. . .\n");
                    break;

                default:
                    printf("\nOpcão inválida, favor escolher outra!\n");
                    break;

            }}while(n!=6);
        }else{
            printf("\nDeposito inexistente\n");
        }
    }

void Remover_Deposito(Deposito depositos[], int *contador){  //completa
    int c,validado,encontrado = -1;
    char temp[10];

    if(*contador == 0){
        printf("\nNenhum deposito esta cadastrado para ser removido\n");
        return;
    }

    printf("\nDigite o CEP do deposito que deseja excluir\n");
    scanf("%9[^\n]s", temp);
    while ((c = getchar()) != '\n' && c != EOF);

    validado = validar_cep(temp);

    if(!validado){
        printf("\nCEP invalido\n");
        return;
    }else{
        for(int i = 0; i < *contador; i++){
            if(strcmp(temp,depositos[i].cep) == 0){
                encontrado = i;
                break;
            }
        }

        if(encontrado != -1){
            if(depositos[encontrado].qtd_produtos > 0){
                printf("\nO deposito nao esta vazio\n");
                return;
            }else{
                for(int j = encontrado; j < *contador - 1; j++){
                    depositos[j] = depositos[j+1];
                }
               
               
                (*contador)--;

                printf("\nDeposito removido com sucesso\n");
            }

        }else{
            printf("\nDeposito nao encontrado\n");
            return;
        }
    }

}


