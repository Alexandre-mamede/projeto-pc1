#include<string.h>
#include<stdio.h>
#include <time.h>
#include <ctype.h>
#include "struct.h"

int deposito_cadastrado = 0; 
typedef struct{
	char codigo_barras[13];
	char nome_produto[101];
	int tipo_produto;
	int perecivel;
	char data_fabricacao[11];
	float volume_unidade;
	int quantidade_itens;
	float valor_unitario;
	char data_validade[11];
}produto;

typedef struct {
    char nome[51];
    char cep[10];               
    char endereco[61];
    char telefone[12];
    float capacidade_Maxima;       
    produto produtos[100];     
    int qtd_produtos;          
    float capacidade_atual;     
} Deposito;

produto produtos;
Deposito depositos[5];

char categoria[10][50] = {
	"Eletrônico",
	"Moda e Vestuário",
	"Casa e Decoração",
	"Esporte e Lazer",
	"Livros e Músicas",
	"Automotivo",
	"Saúde e Bem-estar",
	"Briquedos e Jogos",
	"Alimentos e Bebidas"};
	
    int salvar_produto_deposito(){

    }
int Deposito_Full(Deposito depositos[], int encontrado, float quantidade_x_volume){

    if(depositos[encontrado].capacidade_atual + quantidade_x_volume >= depositos[encontrado].capacidade_Maxima){
        printf("\nNao cabe!!!\n");
        return 0;
    }else{
        return 1;
    }

}
	
	int deposito_existe(char cep_teste[]){
    FILE *fp = abrir_arquivo("dados.bin","rb");

    if(fp == NULL)
        return 0;

    Deposito dep;

    while(fread(&dep,sizeof(Deposito),1,fp))
    {
        if(strcmp(dep.cep,cep_teste) == 0)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}
#include <stdio.h>
#include <string.h>



	

int validar_cep(const char *cep) {
    if (strlen(cep) != 8) return 0;
    
    for (int i = 0; cep[i] != '\0'; i++) {
        if (!isdigit(cep[i])) return 0;
    }
    return 1;
}
 	FILE *abrir_arquivo(const char *nomeArquivo, const char *modo)
{
    FILE *fp = fopen(nomeArquivo, modo);

    if(fp == NULL)
    {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return NULL;
    }

    return fp;
}


int verificar_data(produto prod) {
    int dia_val, mes_val, ano_val;
    int dia_atual, mes_atual, ano_atual;

    time_t agora = time(NULL);
    struct tm data_atual = *localtime(&agora);

    dia_atual = data_atual.tm_mday;
    mes_atual = data_atual.tm_mon + 1;
    ano_atual = data_atual.tm_year + 1900;

    if (sscanf(prod.data_validade, "%d/%d/%d", &dia_val, &mes_val, &ano_val) != 3) {
        return -1; 
	    }

    if (ano_val < ano_atual) {
        return 1;  
    } 
    else if (ano_val > ano_atual) {
        return 0;  
    } 
    else { 
        if (mes_val < mes_atual) {
            return 1;  
        } 
        else if (mes_val > mes_atual) {
            return 0;  
        } 
        else { 
            if (dia_val < dia_atual) {
                return 1; 
            } else {
                return 0; 
            }
        }
    }
}

int alocar_produto_no_deposito_por_indice(produto novo_produto, const char *cep_busca) {
    
    FILE *fp = fopen("dados.bin", "rb+");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo dados.bin ou nenhum deposito cadastrado.\n");
        return 0; 
    }

    Deposito dep;
    int encontrado = 0; 
    int achou_deposito = 0; 
    long posicao_no_arquivo = 0;

    while (fread(&dep, sizeof(Deposito), 1, fp) == 1) {
        
        if (strcmp(cep_busca, dep.cep) == 0) {
            achou_deposito = 1;
            break;
            
        }
        
        encontrado++; 
        
        posicao_no_arquivo = ftell(fp);
    }

    if (achou_deposito == 1) {

    if (dep.qtd_produtos >= 100) {
        printf("Erro: O deposito %s (indice %d) ja esta cheio!\n", dep.nome, encontrado);
        fclose(fp);
        return -1;
    }

    float volume = novo_produto.volume_unidade *
                   novo_produto.quantidade_itens;

    if (dep.capacidade_atual + volume > dep.capacidade_Maxima) {
        printf("Erro: O deposito nao possui capacidade suficiente.\n");
        fclose(fp);
        return -1;
    }


    if(dep.capacidade_atual + volume > dep.capacidade_Maxima){
    fclose(fp);
    return -1;
}
    dep.produtos[dep.qtd_produtos] = novo_produto;

    dep.qtd_produtos++;

    dep.capacidade_atual += volume;

    fseek(fp, posicao_no_arquivo, SEEK_SET);

    fwrite(&dep, sizeof(Deposito), 1, fp);

        printf("Sucesso: Produto alocado no deposito '%s' que estava na posicao [%d] do arquivo!\n", dep.nome, encontrado);
    } else {
        printf("Erro: Deposito com o CEP %s nao foi encontrado.\n", cep_busca);
    }

    fclose(fp);
    return achou_deposito;
}


int validar_codigo(char codigo[])
{
    if(strlen(codigo) != 12)
        return 0;

    for(int i = 0; i < 12; i++)
    {
        if(!isdigit(codigo[i]))
            return 0;
    }

    return 1;
}

char cadastrar_produto(produto produtos, Deposito depositos){
    if(deposito_cadastrado == 0){
        printf("Nenhum deposito cadastrado no sistema!\n");
        return 0;
    }
    do
{
    printf("Digite o codigo de barras do produto (12 digitos): ");
    scanf("%12s", produtos.codigo_barras);

    if(!validar_codigo(produtos.codigo_barras))
    {
        printf("Codigo de barras invalido!\n");
    }

} while(!validar_codigo(produtos.codigo_barras));
    
    printf("Digite o nome do produto: ");
    scanf(" %[^\n]", produtos.nome_produto); 
    
    printf("===== Digite o numero do tipo do produto ======\n");
    printf("1- %s\n", categoria[0]);
    printf("2- %s\n", categoria[1]); 
    printf("3- %s\n", categoria[2]);
    printf("4- %s\n", categoria[3]);
    printf("5- %s\n", categoria[4]);
    printf("6- %s\n", categoria[5]);
    printf("7- %s\n", categoria[6]);
    printf("8- %s\n", categoria[7]);
    printf("9- %s\n", categoria[8]);
    printf("10- %s\n", categoria[9]);
    scanf("%d", &produtos.tipo_produto);

    if(produtos.tipo_produto > 10 || produtos.tipo_produto < 1){
        printf("categoria invalida\n");
        return -1;
    }
    if(produtos.tipo_produto == 10){
        produtos.perecivel = 1;
    }else {
        produtos.perecivel = 0;
    }

    if(produtos.perecivel == 1){
        printf("Digite a data de fabricação: ");
        scanf("%s", produtos.data_fabricacao);
        
        printf("\nDigite a data de vencimento do produto: ");
        scanf("%s", produtos.data_validade);
    
        int status = verificar_data(produtos);
        if(status == 1){
            printf("Cadastro inválido. Produto vencido!\n");
            return -1;
        }
    }else if(produtos.perecivel == 0){
        printf("Digite a data de fabricação: ");
        scanf("%s", produtos.data_fabricacao);
        strcpy(produtos.data_validade, "N/A"); 
    }

    printf("\nDigite o volume da unidade: ");
    scanf("%f", &produtos.volume_unidade);
    
    printf("\nDigite a quantidade de itens do produto: ");
    scanf("%d", &produtos.quantidade_itens);
    
    printf("\nDigite o valor do produto: ");
    scanf("%f", &produtos.valor_unitario);

    char cep_busca[10];
    int teste_cep = 0;

    do {
        printf("\nInforme o CEP do deposito onde o produto será armazenado: ");
        scanf("%s", cep_busca); 
        
        teste_cep = validar_cep(cep_busca);
        if (teste_cep != 1) {
            printf("Cep inválido! Digite no formato correto.\n");
            continue;
        }


        int status_alocacao = alocar_produto_no_deposito_por_indice(produtos, cep_busca);

        if (status_alocacao == 1) {
            printf("\n===== Produto Cadastrado com Sucesso =====\n");
            return 1;         } 
        else if (status_alocacao == -1) {
            printf("\nDeposito cheio! Escolha uma das opções abaixo:\n");
            int n;
            printf("1 - Escolher outro deposito (digitar outro CEP)\n");
            printf("2 - Alterar quantidade do produto a ser cadastrada\n");
            printf("3 - Voltar ao menu principal\n");
            scanf("%d", &n);

            if (n == 2) {
                printf("Digite a nova quantidade de itens do produto: ");
                scanf("%d", &produtos.quantidade_itens);
            } 
            else if (n == 3) {
                return 0; 
            }
        } 
        else {
            
            printf("Esse deposito nao existe no sistema. Tente outro CEP.\n");
        }

    } while (1);
}

int consultar_produto()
{
    char codigo_busca[13];
    int encontrado = 0;

    printf("Digite o codigo de barras do produto: ");
    scanf("%12s", codigo_busca);

    FILE *fp = fopen("dados.bin", "rb");

    if(fp == NULL)
    {
        printf("Nenhum deposito cadastrado.\n");
        return 0;
    }

    Deposito dep;

    while(fread(&dep, sizeof(Deposito), 1, fp) == 1)
    {
        for(int i = 0; i < dep.qtd_produtos; i++)
        {
            if(strcmp(dep.produtos[i].codigo_barras, codigo_busca) == 0){
                encontrado = 1;

                printf("\n========== PRODUTO ENCONTRADO ==========\n");
                printf("Nome do deposito: %s\n", dep.nome);
                printf("CEP: %s\n", dep.cep);

                printf("Nome do produto: %s\n",dep.produtos[i].nome_produto);

                printf("Codigo de barras: %s\n",dep.produtos[i].codigo_barras);

                printf("Categoria: %s\n", categoria[dep.produtos[i].tipo_produto - 1]);

                printf("Data de fabricacao: %s\n", dep.produtos[i].data_fabricacao);

                if(dep.produtos[i].perecivel)
                {
                    printf("Data de validade: %s\n",dep.produtos[i].data_validade);
                }

                printf("Volume da unidade: %.2f m3\n",dep.produtos[i].volume_unidade);

                printf("Quantidade de itens: %d\n",dep.produtos[i].quantidade_itens);

                printf("Valor unitario: R$ %.2f\n",dep.produtos[i].valor_unitario);

               
            }
        }
    }

    fclose(fp);

    if(!encontrado)
    {
        printf("\nProduto nao encontrado.\n");
        return 0;
    }

    return 1;
}
void atualiza_produto()
{
    char cep_busca[10];
    char codigo_busca[13];

    printf("Digite o CEP do deposito: ");
    scanf("%9s", cep_busca);

    if(deposito_existe(cep_busca) == 0)
    {
        printf("Deposito nao encontrado!\n");
        return;
    }

    printf("Digite o codigo de barras do produto: ");
    scanf("%12s", codigo_busca);

    FILE *fp = abrir_arquivo("dados.bin","rb+");

    if(fp == NULL)
        return;

    Deposito dep;
    int encontrado = 0;
    long posicao;

    while(1)
    {
        posicao = ftell(fp);

        if(fread(&dep,sizeof(Deposito),1,fp) != 1)
            break;

        if(strcmp(dep.cep,cep_busca) == 0)
        {
            for(int i=0;i<dep.qtd_produtos;i++)
            {
                if(strcmp(dep.produtos[i].codigo_barras,codigo_busca)==0)
                {
                    encontrado = 1;

                    int opcao;
                    float volume_antigo;

                    printf("\nDigite a opcao a ser atualizada:\n");
                    printf("1. Nome do Produto\n");
                    printf("2. Codigo de barras\n");
                    printf("3. Categoria de produto\n");
                    printf("4. Data de Fabricacao\n");
                    printf("5. Data de Validade\n");
                    printf("6. Volume de uma unidade\n");
                    printf("7. Quantidade de itens\n");
                    printf("8. Valor unitario\n");

                    scanf("%d",&opcao);

                    switch(opcao)
                    {

                    case 1:

                        printf("Novo nome: ");
                        scanf(" %100[^\n]",dep.produtos[i].nome_produto);

                        break;

                    case 2:

                        do
                        {
                            printf("Novo codigo de barras: ");
                            scanf("%12s",dep.produtos[i].codigo_barras);

                            if(!validar_codigo(dep.produtos[i].codigo_barras))
                                printf("Codigo invalido!\n");

                        }while(!validar_codigo(dep.produtos[i].codigo_barras));

                        break;

                    case 3:

                        printf("Nova categoria (1-10): ");
                        scanf("%d",&dep.produtos[i].tipo_produto);

                        if(dep.produtos[i].tipo_produto <1 ||
                           dep.produtos[i].tipo_produto >10)
                        {
                            printf("Categoria invalida!\n");
                            fclose(fp);
                            return;
                        }

                        dep.produtos[i].perecivel =
                        (dep.produtos[i].tipo_produto==10);

                        break;

                    case 4:

                        printf("Nova data de fabricacao: ");
                        scanf("%10s",dep.produtos[i].data_fabricacao);

                        break;

                    case 5:

                        if(dep.produtos[i].perecivel==0)
                        {
                            printf("Produto nao perecivel.\n");
                            break;
                        }

                        printf("Nova data de validade: ");
                        scanf("%10s",dep.produtos[i].data_validade);

                        if(verificar_data(dep.produtos[i]))
                        {
                            printf("Produto vencido!\n");
                            fclose(fp);
                            return;
                        }

                        break;

                    case 6:

                        volume_antigo =
                        dep.produtos[i].volume_unidade *
                        dep.produtos[i].quantidade_itens;

                        printf("Novo volume: ");
                        scanf("%f",&dep.produtos[i].volume_unidade);

                        if(dep.capacidade_atual
                           - volume_antigo
                           + dep.produtos[i].volume_unidade *
                           dep.produtos[i].quantidade_itens
                           > dep.capacidade_Maxima)
                        {
                            printf("Capacidade excedida!\n");
                            fclose(fp);
                            return;
                        }

                        dep.capacidade_atual =
                        dep.capacidade_atual
                        - volume_antigo
                        + dep.produtos[i].volume_unidade *
                        dep.produtos[i].quantidade_itens;

                        break;

                    case 7:

                        volume_antigo =
                        dep.produtos[i].volume_unidade *
                        dep.produtos[i].quantidade_itens;

                        printf("Nova quantidade: ");
                        scanf("%d",&dep.produtos[i].quantidade_itens);

                        if(dep.capacidade_atual
                           - volume_antigo
                           + dep.produtos[i].volume_unidade *
                           dep.produtos[i].quantidade_itens
                           > dep.capacidade_Maxima)
                        {
                            printf("Capacidade excedida!\n");
                            fclose(fp);
                            return;
                        }

                        dep.capacidade_atual =
                        dep.capacidade_atual
                        - volume_antigo
                        + dep.produtos[i].volume_unidade *
                        dep.produtos[i].quantidade_itens;

                        break;

                    case 8:

                        printf("Novo valor unitario: ");
                        scanf("%f",&dep.produtos[i].valor_unitario);

                        break;

                    default:

                        printf("Opcao invalida!\n");
                        fclose(fp);
                        return;
                    }

                    fseek(fp,posicao,SEEK_SET);

                    fwrite(&dep,sizeof(Deposito),1,fp);

                    printf("\nProduto atualizado com sucesso!\n");

                    fclose(fp);
                    return;
                }
            }

            printf("Produto nao encontrado neste deposito.\n");
            fclose(fp);
            return;
        }
    }

    if(!encontrado)
        printf("Produto nao encontrado.\n");

    fclose(fp);
}
void remover_produto(){
    char cep_busca[10];
    char codigo_busca[13];
    int deposito_encontrado = 0;
    int produto_encontrado = 0;

    printf("Digite o CEP do deposito onde o produto se encontra: ");
    scanf("%9s", cep_busca);

    printf("Digite o codigo de barras do produto a ser removido: ");
    scanf("%12s", codigo_busca);

    FILE *fp_original = fopen("dados.bin", "rb");

    if(fp_original == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    FILE *fp_temp = fopen("temp.bin", "wb");

    if(fp_temp == NULL)
    {
        printf("Erro ao criar arquivo temporario.\n");
        fclose(fp_original);
        return;
    }

    Deposito dep;

    while(fread(&dep, sizeof(Deposito), 1, fp_original) == 1)
    {
        if(strcmp(dep.cep, cep_busca) == 0)
        {
            deposito_encontrado = 1;

            for(int i = 0; i < dep.qtd_produtos; i++)
            {
                if(strcmp(dep.produtos[i].codigo_barras, codigo_busca) == 0)
                {
                    produto_encontrado = 1;

                    printf("\nProduto encontrado:\n");
                    printf("Nome: %s\n", dep.produtos[i].nome_produto);
                    printf("Quantidade: %d\n",
                           dep.produtos[i].quantidade_itens);

                    int qtd_remover;

                    printf("Quantidade a remover: ");
                    scanf("%d", &qtd_remover);

                    if(qtd_remover <= 0)
                    {
                        printf("Quantidade invalida.\n");
                        fclose(fp_original);
                        fclose(fp_temp);
                        remove("temp.bin");
                        return;
                    }

                    if(qtd_remover > dep.produtos[i].quantidade_itens)
                    {
                        printf("Quantidade maior que a existente.\n");
                        fclose(fp_original);
                        fclose(fp_temp);
                        remove("temp.bin");
                        return;
                    }
                    dep.capacidade_atual -=
                    qtd_remover *
                    dep.produtos[i].volume_unidade;
                    dep.produtos[i].quantidade_itens -= qtd_remover;
                    if(dep.produtos[i].quantidade_itens == 0)
                    {
                        for(int j = i;
                            j < dep.qtd_produtos - 1;
                            j++)
                        {
                            dep.produtos[j] =
                            dep.produtos[j + 1];
                        }

                        memset(&dep.produtos[dep.qtd_produtos - 1],
                               0,
                               sizeof(produto));

                        dep.qtd_produtos--;
                    }

                    break;
                }
            }
        }

        fwrite(&dep, sizeof(Deposito), 1, fp_temp);
    }

    fclose(fp_original);
    fclose(fp_temp);

    if(!deposito_encontrado)
    {
        printf("Deposito nao encontrado.\n");
        remove("temp.bin");
        return;
    }

    if(!produto_encontrado)
    {
        printf("Produto nao encontrado neste deposito.\n");
        remove("temp.bin");
        return;
    }

    remove("dados.bin");
    rename("temp.bin", "dados.bin");

    printf("\nProduto removido com sucesso!\n");
}

void transferir_produto()
{
    char cep_origem[9], cep_destino[9];
    char codigo_busca[13];
    int qtd_mover;

    printf("\n===== TRANSFERENCIA DE PRODUTO =====\n");

    printf("CEP do deposito de origem: ");
    scanf("%8s", cep_origem);

    printf("Codigo de barras do produto: ");
    scanf("%12s", codigo_busca);

    printf("Quantidade a transferir: ");
    scanf("%d", &qtd_mover);

    printf("CEP do deposito de destino: ");
    scanf("%8s", cep_destino);

    FILE *fp = fopen("dados.bin", "rb+");

    if(fp == NULL)
    {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    Deposito origem, destino;
    produto prod_transferido;

    long pos_origem = -1;
    long pos_destino = -1;

    int indice_produto = -1;

    while(1)
    {
        long pos = ftell(fp);

        if(fread(&origem, sizeof(Deposito), 1, fp) != 1)
            break;

        if(strcmp(origem.cep, cep_origem) == 0)
        {
            pos_origem = pos;

            for(int i = 0; i < origem.qtd_produtos; i++)
            {
                if(strcmp(origem.produtos[i].codigo_barras,
                          codigo_busca) == 0)
                {
                    indice_produto = i;
                    break;
                }
            }
        }

        if(strcmp(origem.cep, cep_destino) == 0)
        {
            pos_destino = pos;
        }
    }

    if(pos_origem == -1)
    {
        printf("Deposito de origem nao encontrado.\n");
        fclose(fp);
        return;
    }

    if(pos_destino == -1)
    {
        printf("Deposito de destino nao encontrado.\n");
        fclose(fp);
        return;
    }

    fseek(fp, pos_origem, SEEK_SET);
    fread(&origem, sizeof(Deposito), 1, fp);

    if(indice_produto == -1)
    {
        printf("Produto nao encontrado.\n");
        fclose(fp);
        return;
    }

    if(qtd_mover <= 0 ||
       qtd_mover > origem.produtos[indice_produto].quantidade_itens)
    {
        printf("Quantidade invalida.\n");
        fclose(fp);
        return;
    }

    prod_transferido = origem.produtos[indice_produto];

    fseek(fp, pos_destino, SEEK_SET);
    fread(&destino, sizeof(Deposito), 1, fp);

    float volume =
        qtd_mover * prod_transferido.volume_unidade;

    while(destino.capacidade_atual + volume >
          destino.capacidade_Maxima)
    {
        int op;

        printf("\nDeposito de destino sem capacidade.\n");
        printf("1 - Informar nova quantidade\n");
        printf("2 - Cancelar transferencia\n");
        scanf("%d", &op);

        if(op == 2)
        {
            fclose(fp);
            return;
        }

        printf("Nova quantidade: ");
        scanf("%d", &qtd_mover);

        if(qtd_mover <= 0 ||
           qtd_mover > origem.produtos[indice_produto].quantidade_itens)
        {
            printf("Quantidade invalida.\n");
            fclose(fp);
            return;
        }

        volume = qtd_mover * prod_transferido.volume_unidade;
    }

    origem.produtos[indice_produto].quantidade_itens -= qtd_mover;
    origem.capacidade_atual -= volume;

    if(origem.produtos[indice_produto].quantidade_itens == 0)
    {
        for(int j = indice_produto;
            j < origem.qtd_produtos - 1;
            j++)
        {
            origem.produtos[j] = origem.produtos[j + 1];
        }

        memset(&origem.produtos[origem.qtd_produtos - 1],
               0,
               sizeof(produto));

        origem.qtd_produtos--;
    }

    int indice_destino = -1;

    for(int i = 0; i < destino.qtd_produtos; i++)
    {
        if(strcmp(destino.produtos[i].codigo_barras,
                  codigo_busca) == 0)
        {
            indice_destino = i;
            break;
        }
    }

    if(indice_destino != -1)
    {
        destino.produtos[indice_destino].quantidade_itens += qtd_mover;
    }
    else
    {
        destino.produtos[destino.qtd_produtos] = prod_transferido;
        destino.produtos[destino.qtd_produtos].quantidade_itens = qtd_mover;
        destino.qtd_produtos++;
    }

    destino.capacidade_atual += volume;

    fseek(fp, pos_origem, SEEK_SET);
    fwrite(&origem, sizeof(Deposito), 1, fp);

    fseek(fp, pos_destino, SEEK_SET);
    fwrite(&destino, sizeof(Deposito), 1, fp);

    fclose(fp);

    printf("\nTransferencia realizada com sucesso!\n");
}
