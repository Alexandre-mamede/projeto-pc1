#include<string.h>
#include<stdio.h>
#include <time.h>

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
//variavel temporaria ate a criação do typedef stuct referente aos depositos
char cep;
int validar_cep(const char *cep) {
    if (strlen(cep) != 8) return 0;
    
    for (int i = 0; cep[i] != '\0'; i++) {
        if (!isdigit(cep[i])) return 0;
    }
    return 1;
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
char categoria[10][50] = {"Eletrônico","Moda e Vestuário","Casa e Decoração",
	"Esporte e Lazer","Livros e Músicas","Automotivo","Saúde e Bem-estar",
	"Briquedos e Jogos","Alimentos e Bebidas"};

char cadastrar_produto(produto produtos){
	if(deposito_cadastrado == 0){
		return 0;
	}
	printf("Digite o codigo de barras do produto: ");
	scanf("%s",produtos.codigo_barras);
	
	printf("Digite o nome do produto");
	scanf("%s",produtos.nome_produto);
	
	
	printf("===== Digite o tipo do produto ======");
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
	scanf("%d",&produtos.tipo_produto);
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
	
		int status = verificar_produto(produtos);
		
		if(status == 1){
			printf("Cadastro inválido. Produto vencido!");
			return -1;
		}
		
		printf("\nDigite o volume da unidade:");
		scanf("%f",&produtos.volume_unidade);
		
		printf("\nDigite a quantidade de itens do produto:");
		scanf("%d",&produtos.quantidade_itens);
		
		printf("\nDigite o valor do produto:");
		scanf("%f",produtos.valor_unitario);

		printf("===== Produto Cadastrado com Sucesso =====");

	}else if(produtos.perecivel == 0){
		
		printf("Digite a data de fabricação");
		scanf("%s",produtos.data_fabricacao);
		
		printf("\nDigite o volume da unidade:");
		scanf("%f",&produtos.volume_unidade);
		
		printf("\nDigite a quantidade de itens do produto:");
		scanf("%d",&produtos.quantidade_itens);
		
		printf("\nDigite o valor do produto:");
		scanf("%f",produtos.valor_unitario);

		printf("===== Produto Cadastrado com Sucesso =====");
	}
	printf("Informe o CEP onde o produto será armazenado: ");
	//preciso esperar o desenvolvimento desta parte com o Gabriel
	scanf("%s",&cep);
	int teste_cep = validar_cep(cep);
	if(teste_cep == 1){

	}else {
		while(teste_cep != 1){
			
			printf("Informe o cep novamente: ");
			scanf("%s",&cep);
			teste_cep = validar_cep(cep);
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
						cadastrar_produto(produtos);
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
int consultar_produto(produto produtos){
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
		printf("Nome do Depósito: %s\n", deposito.nome_deposito);
        printf("CEP do depósito: %s\n", deposito.cep_deposito);
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
