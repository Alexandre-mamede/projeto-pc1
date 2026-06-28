#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "struct.h"
#include "produto.h"
int deposito_cadastrado = 0;

char categoria[9][50] = {
	"Eletrônico",
	"Moda e Vestuário",
	"Casa e Decoração",
	"Esporte e Lazer",
	"Livros e Músicas",
	"Automotivo",
	"Saúde e Bem-estar",
	"Briquedos e Jogos",
	"Alimentos e Bebidas"};
	
	
	int deposito_existe(char cep[])
{
    FILE *fp = abrir_arquivo("depositos.bin","rb");

    if(fp == NULL)
        return 0;

    Deposito dep;

    while(fread(&dep,sizeof(Deposito),1,fp))
    {
        if(strcmp(dep.cep,cep) == 0)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}
	

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

char cadastrar_produto(produto produtos, Deposito depositos){
	if(deposito_cadastrado == 0){
		return 0;
	}
	printf("Digite o codigo de barras do produto: ");
	scanf("%s",produtos.codigo_barras);
	
	printf("Digite o nome do produto");
	scanf("%s",produtos.nome_produto);
	
	
	printf("===== Digite o numero do tipo do produto ======");
	printf("1- %s\n",categoria[0]);
	printf("2- %s\n",categoria[1]);	
	printf("3- %s\n",categoria[2]);
	printf("4- %s\n",categoria[3]);
	printf("5- %s\n",categoria[4]);
	printf("6- %s\n",categoria[5]);
	printf("7- %s\n",categoria[6]);
	printf("8- %s\n",categoria[7]);
	printf("9- %s\n",categoria[8]);
	printf("10- %s\n",categoria[9]);
	scanf("%d",produtos.tipo_produto);

	if(produtos.tipo_produto > 10 || produtos.tipo_produto <1 ){
		printf("categoria invalida");
		return -1;
	}
	if(produtos.tipo_produto == 10){
		produtos.perecivel = 1;
	}else {
		produtos.perecivel = 0;
	}

	if(produtos.perecivel == 1){
		printf("Digite a data de fabricação");
		scanf("%s",produtos.data_fabricacao);
		
		printf("\nDigite a data de vencimento do produto:");
		scanf("%s",produtos.data_validade);
	
	int status = verificar_data(produtos);

		if(status == 1){
			printf("Cadastro inválido. Produto vencido!");
			return -1;
		}
		
		printf("\nDigite o volume da unidade:");
		scanf("%f",&produtos.volume_unidade);
		
		printf("\nDigite a quantidade de itens do produto:");
		scanf("%d",&produtos.quantidade_itens);
		
		printf("\nDigite o valor do produto:");
		scanf("%f",&produtos.valor_unitario);

		printf("===== Produto Cadastrado com Sucesso =====");

	}else if(produtos.perecivel == 0){
		
		printf("Digite a data de fabricação");
		scanf("%s",produtos.data_fabricacao);
		
		printf("\nDigite o volume da unidade:");
		scanf("%f",&produtos.volume_unidade);
		
		printf("\nDigite a quantidade de itens do produto:");
		scanf("%d",&produtos.quantidade_itens);
		
		printf("\nDigite o valor do produto:");
		scanf("%f",&produtos.valor_unitario);

		printf("===== Produto Cadastrado com Sucesso =====");
	}
	printf("Informe o CEP onde o produto será armazenado: ");
	//preciso esperar o desenvolvimento desta parte com o Gabriel

	scanf("%s",&depositos.cep);
	int teste_cep = validar_cep(depositos.cep);
	if(teste_cep == 1){

	}else {
		while(teste_cep != 1){
			
			printf("Informe o cep novamente: ");
			scanf("%s",&depositos.cep);
			teste_cep = validar_cep(depositos.cep);
			if(teste_cep == 1){
				printf("verificando capacidade do deposito: ");
				if(//deposito vazio 
			deposito_vazio	){ 
						//adicionar item no deposito
					//guardar no deposito;
				} 
				else { printf("deposito cheio escolha uma das opções abaixo");
					int n;
					do{
					printf("\n1-escolher outro deposito");
					printf("\n2-altera quantidade produto a ser cadastrada:");
					printf("\n3-voltar ao menu produtos");
					scanf("%d",&n);					
					switch (n){
						case 1:

						cadastrar_produto(produtos, depositos);

						break;

						case 2:
						printf("Digite a quantidade de produtos a ser cadastrada:");
						scanf("%d",&produtos.quantidade_itens);
						break;
						
						default:
						printf("opção invalida");
						break;
						}
					}while(3);
				}
			}
		}
	}
}
int consultar_produto(produto produtos, Deposito depositos){
	char codigo_busca[13];
	printf("Digite o codigo de barras do produto para ser consultado:");
	scanf("%s",codigo_busca);
	int i=0;
	FILE *fp;
	fp =  fopen("produtos.bin", "r");
	while(i != 5){
	while (fscanf(fp, " %[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%d;%f\n",
		produtos.codigo_barras,produtos.nome_produto,produtos.tipo_produto,produtos.data_fabricacao,
		produtos.volume_unidade,produtos.quantidade_itens,produtos.valor_unitario,
		produtos.data_validade) != EOF) {
	}
	if(strcmp(produtos.codigo_barras, codigo_busca ) == 0){
		printf("======Produto Encontrado======\n");
		printf("Nome do Depósito: %s\n", depositos.nome);
        printf("CEP do depósito: %s\n", depositos.cep);
        printf("Nome do Produto: %s\n", produtos.nome_produto);
        printf("Código de barras: %s\n", produtos.codigo_barras);
		printf("Categoria de produto: %s\n",categoria);
        printf("Data de Fabricação: %s\n", produtos.data_fabricacao);
        printf("Volume de uma unidade: %s\n", produtos.volume_unidade);
        printf("Quantidade de itens: %d\n", produtos.quantidade_itens);
    	printf("Valor unitário: R$ %.2f\n", produtos.valor_unitario);
		if(produtos.data_validade == 1){
			printf("Data de Validade: %s\n", produtos.data_validade);
		}
		fclose(fp);
	}else {
		printf("======Produto não encontrado======");
		
		return 0;
		}
	} 
}
	void atualiza_produto()
{
    char cep_busca[9];
    char codigo_busca[14];

    produto prod;

    printf("Digite o CEP do deposito: ");
    scanf("%8s", cep_busca);

    if(!deposito_existe(cep_busca))
    {
        printf("Deposito nao encontrado!\n");
        return;
    }

    printf("Digite o codigo de barras do produto: ");
    scanf("%13s", codigo_busca);

    FILE *fp = abrir_arquivo("produtos.bin","rb+");

    if(fp == NULL)
        return;

    int encontrado = 0;

    while(fread(&prod,sizeof(produto),1,fp))
    {
        if(strcmp(prod.codigo_barras,codigo_busca) == 0)
        {
            encontrado = 1;

            int opcao;

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
                    scanf(" %100[^\n]", prod.nome_produto);
                    break;

                case 2:
                    printf("Novo codigo de barras: ");
                    scanf("%13s", prod.codigo_barras);
                    break;

                case 3:
                    printf("Nova categoria (1-9): ");
                    scanf("%d",&prod.tipo_produto);

                    if(prod.tipo_produto < 1 || prod.tipo_produto > 9)
                    {
                        printf("Categoria invalida!\n");
                        fclose(fp);
                        return;
                    }
                    break;

                case 4:
                    printf("Nova data de fabricacao (dd/mm/aaaa): ");
                    scanf("%10s", prod.data_fabricacao);
                    break;

                case 5:
                    printf("Nova data de validade (dd/mm/aaaa): ");
                    scanf("%10s", prod.data_validade);

                    if(verificar_data(prod))
                    {
                        printf("Produto vencido!\n");
                        fclose(fp);
                        return;
                    }
                    break;

                case 6:
                    printf("Novo volume da unidade: ");
                    scanf("%f",&prod.volume_unidade);

                    break;

                case 7:
                    printf("Nova quantidade: ");
                    scanf("%d",&prod.quantidade_itens);
    
                    break;

                case 8:
                    printf("Novo valor unitario: ");
                    scanf("%f",&prod.valor_unitario);
                    break;

                default:
                    printf("Opcao invalida!\n");
                    fclose(fp);
                    return;
            }

            
            fseek(fp,-sizeof(produto),SEEK_CUR);

           
            fwrite(&prod,sizeof(produto),1,fp);

            printf("\nProduto atualizado com sucesso!\n");

            break;
        }
    }

    if(!encontrado)
    {
        printf("Produto nao encontrado!\n");
    }

    fclose(fp);
}
