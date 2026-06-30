#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUTOS 100
#define MAX_DEPOSITOS 5

// valida CEP no formato XXXXX-XXX
int validar_cep(char cep[]){
    if (strlen(cep) != 9)
        return 0;

    for (int i = 0; i < 9; i++){
        if (i == 5){
            if (cep[i] != '-')
                return 0;
        } else {
            if (!isdigit((unsigned char)cep[i]))
                return 0;
        }
    }

    return 1;
}

// ===================== CADASTRO DEPÓSITO =====================
void Cadastrar_Novo_Deposito(Deposito depositos[], int *contador){

    int c;

    if (*contador >= MAX_DEPOSITOS){
        printf("\nJa possui a quantidade maxima de depositos\n");
        return;
    }

    depositos[*contador].capacidade_atual = 0;
    depositos[*contador].qtd_produtos = 0;

    printf("\nDigite o nome do deposito: ");
    if (scanf(" %50[^\n]", depositos[*contador].nome) != 1){
        printf("\nNome invalido\n");
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }
    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nDigite o CEP do deposito: ");
    if (scanf(" %9s", depositos[*contador].cep) != 1){
        printf("\nCEP invalido\n");
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }
    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nDigite o endereco do deposito: ");
    if (scanf(" %60[^\n]", depositos[*contador].endereco) != 1){
        printf("\nEndereco invalido\n");
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }
    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nDigite o telefone: ");
    if (scanf(" %11s", depositos[*contador].telefone) != 1){
        printf("\nTelefone invalido\n");
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }
    while ((c = getchar()) != '\n' && c != EOF);

    printf("\nDigite a capacidade maxima: ");
    if (scanf("%f", &depositos[*contador].capacidade_Maxima) != 1){
        printf("\nValor invalido\n");
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }
    while ((c = getchar()) != '\n' && c != EOF);

    (*contador)++;
}

// ===================== CONSULTA UM =====================
void Consultar_Inf_Depositos(Deposito depositos[], int contador){

    int c;

    if (contador == 0){
        printf("\nNenhum deposito cadastrado\n");
        return;
    }

    char temp[10];
    int encontrado = -1;
    int valido;

    do {
        printf("\nDigite o CEP: ");
        scanf("%9s", temp);

        while ((c = getchar()) != '\n' && c != EOF);

        valido = validar_cep(temp);

        if (!valido)
            printf("\nFormato invalido (XXXXX-XXX)\n");

    } while (!valido);

    for (int i = 0; i < contador; i++){
        if (strcmp(depositos[i].cep, temp) == 0){
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1){
        printf("\nDeposito inexistente\n");
        return;
    }

    printf("\nNome: %s", depositos[encontrado].nome);
    printf("\nCEP: %s", depositos[encontrado].cep);
    printf("\nEndereco: %s", depositos[encontrado].endereco);
    printf("\nTelefone: %s", depositos[encontrado].telefone);
    printf("\nCapacidade: %.2f / %.2f m3",
           depositos[encontrado].capacidade_atual,
           depositos[encontrado].capacidade_Maxima);

    printf("\nProdutos:\n");

    if (depositos[encontrado].qtd_produtos == 0){
        printf("Nenhum produto\n");
    } else {
        for (int i = 0; i < depositos[encontrado].qtd_produtos; i++){
            printf("%d - %s\n",
                   depositos[encontrado].produtos[i].quantidade_itens,
                   depositos[encontrado].produtos[i].nome_produto);
        }
    }
}

// ===================== CONSULTA TODOS =====================
void Consultar_Todas_Inf_Depositos(Deposito depositos[], int contador){

    if (contador == 0){
        printf("\nNenhum deposito cadastrado\n");
        return;
    }

    for (int i = 0; i < contador; i++){
        printf("\n-----------------------------\n");
        printf("\nNome: %s", depositos[i].nome);
        printf("\nCEP: %s", depositos[i].cep);
        printf("\nEndereco: %s", depositos[i].endereco);
        printf("\nTelefone: %s", depositos[i].telefone);
        printf("\nCapacidade: %.2f / %.2f m3",
               depositos[i].capacidade_atual,
               depositos[i].capacidade_Maxima);

        printf("\nProdutos:\n");

        if (depositos[i].qtd_produtos == 0){
            printf("Nenhum produto\n");
        } else {
            for (int j = 0; j < depositos[i].qtd_produtos; j++){
                printf("%d - %s\n",
                       depositos[i].produtos[j].quantidade_itens,
                       depositos[i].produtos[j].nome_produto);
            }
        }
    }
}

// ===================== ATUALIZAR =====================
void Atualizar_Dados_Deposito(Deposito depositos[], int contador){

    if (contador == 0){
        printf("\nNenhum deposito cadastrado\n");
        return;
    }

    char temp[10];
    int encontrado = -1;
    int n, c;
    int validado;

    printf("\nDigite o CEP: ");
    scanf("%9s", temp);
    while ((c = getchar()) != '\n' && c != EOF);

    validado = validar_cep(temp);
    if (!validado){
        printf("\nCEP invalido\n");
        return;
    }

    for (int i = 0; i < contador; i++){
        if (strcmp(depositos[i].cep, temp) == 0){
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1){
        printf("\nDeposito inexistente\n");
        return;
    }

    do {
        printf("\n1 Nome\n2 CEP\n3 Endereco\n4 Telefone\n5 Capacidade\n6 Sair\n");
        scanf("%d", &n);
        while ((c = getchar()) != '\n' && c != EOF);

        switch (n){

        case 1:
            printf("\nNovo nome: ");
            scanf(" %50[^\n]", depositos[encontrado].nome);
            break;

        case 2:
            printf("\nNovo CEP: ");
            scanf("%9s", depositos[encontrado].cep);
            break;

        case 3:
            printf("\nNovo endereco: ");
            scanf(" %60[^\n]", depositos[encontrado].endereco);
            break;

        case 4:
            printf("\nNovo telefone: ");
            scanf("%11s", depositos[encontrado].telefone);
            break;

        case 5: {
            float nova;

            printf("\nNova capacidade: ");
            scanf("%f", &nova);

            if (depositos[encontrado].capacidade_atual > nova){
                printf("\nValor invalido\n");
            } else {
                depositos[encontrado].capacidade_Maxima = nova;
            }
            break;
        }

        case 6:
            return;
        }

    } while (n != 6);
}

// ===================== REMOVER =====================
void Remover_Deposito(Deposito depositos[], int *contador){

    int c, encontrado = -1;
    char temp[10];

    if (*contador == 0){
        printf("\nNenhum deposito\n");
        return;
    }

    printf("\nCEP: ");
    scanf("%9s", temp);
    while ((c = getchar()) != '\n' && c != EOF);

    if (!validar_cep(temp)){
        printf("\nCEP invalido\n");
        return;
    }

    for (int i = 0; i < *contador; i++){
        if (strcmp(depositos[i].cep, temp) == 0){
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1){
        printf("\nNao encontrado\n");
        return;
    }

    if (depositos[encontrado].qtd_produtos > 0){
        printf("\nDeposito nao esta vazio\n");
        return;
    }

    for (int i = encontrado; i < *contador - 1; i++){
        depositos[i] = depositos[i + 1];
    }

    (*contador)--;

    printf("\nRemovido com sucesso\n");
}
