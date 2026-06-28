#include<string.h>
#include<stdio.h>
#include <time.h>
#include <ctype.h>

int deposito_cadastrado = 0; // variavel que precisa estar no programa do gabriel
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

typedef struct{
    char nome[51];
	char cep[9];
	char endereco[61];
	char telefone[12];
	float capacidade_max;       //em metros cúbicos
    produto produtos[100];
}Deposito;

produto produtos;
Deposito depositos[5];

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
	printf("Informe o CEP do deposito onde o produto será armazenado: ");
	

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
void remover_produto() {
    char cep_busca[9];
    char codigo_busca[13];
    int deposito_encontrado = 0;
    int produto_encontrado = 0;

    printf("Digite o CEP do deposito onde o produto se encontra: ");
    scanf("%s", cep_busca);

    printf("Digite o codigo de barras do produto a ser removido: ");
    scanf("%s", codigo_busca);

    FILE *fp_original = fopen("dados.bin", "rb"); 
    if (fp_original == NULL) {
        printf("Erro ao abrir o arquivo de dados.\n");
        return;
    }

    FILE *fp_temp = fopen("temp.bin", "wb");
    if (fp_temp == NULL) {
        printf("Erro no arquivo!");
        fclose(fp_original);
        return;
    }

    Deposito dep;

    while (fread(&dep, sizeof(Deposito), 1, fp_original) == 1) {
        
        if (strcmp(dep.cep, cep_busca) == 0) {
            deposito_encontrado = 1;
            int i, j;
            
            for (i = 0; i < 100; i++) {

                if (strlen(dep.produtos[i].codigo_barras) > 0 && 
                    strcmp(dep.produtos[i].codigo_barras, codigo_busca) == 0) {
                    
                    produto_encontrado = 1;
                    
                    for (j = i; j < 99; j++) {
                        dep.produtos[j] = dep.produtos[j + 1];
                    }
                    memset(&dep.produtos[99], 0, sizeof(produto));
                    
                    break;
                }
            }
        }
        
       
        fwrite(&dep, sizeof(Deposito), 1, fp_temp);
    }

    fclose(fp_original);
    fclose(fp_temp);

    
    if (!deposito_encontrado) {
        printf("Deposito com o CEP informado nao foi encontrado.\n");
        remove("temp.bin"); 
    } else if (!produto_encontrado) {
        printf("Produto com o codigo de barras informado nao foi encontrado neste deposito.\n");
        remove("temp.bin"); 
    } else {
        
        remove("depositos.bin");
        rename("temp.bin", "depositos.bin");
        printf("Produto removido com sucesso!\n");
    }
}

void transferir_produto() {
    char cep_origem[9], cep_destino[9], codigo_busca[13];
    int qtd_mover;
    
    printf("=== TRANSFERENCIA DE PRODUTO ===\n");
    printf("Digite o CEP do deposito de ORIGEM: ");
    scanf("%8s", cep_origem);
    printf("Digite o codigo de barras do produto: ");
    scanf("%12s", codigo_busca);
    printf("Digite a quantidade de itens a ser movida: ");
    scanf("%d", &qtd_mover);
    printf("Digite o CEP do deposito de DESTINO: ");
    scanf("%8s", cep_destino);

    FILE *fp = fopen("depositos.bin", "rb+");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo de depositos.\n");
        return;
    }

    Deposito dep;
    int idx_origem = -1, idx_destino = -1;
    long pos_origem = -1, pos_destino = -1;
    int prod_idx_origem = -1;

    long pos_atual = ftell(fp);
    while (fread(&dep, sizeof(Deposito), 1, fp) == 1) {
        if (strcmp(dep.cep, cep_origem) == 0) {
            pos_origem = pos_atual;
            for (int i = 0; i < 100; i++) {
                if (strlen(dep.produtos[i].codigo_barras) > 0 && 
                    strcmp(dep.produtos[i].codigo_barras, codigo_busca) == 0) {
                    prod_idx_origem = i;
                    break;
                }
            }
        }
        if (strcmp(dep.cep, cep_destino) == 0) {
            pos_destino = pos_atual;
        }
        pos_atual = ftell(fp);
    }

    if (pos_origem == -1) {
        printf("Erro: Deposito de origem nao encontrado.\n");
        fclose(fp);
        return;
    }
    if (pos_destino == -1) {
        printf("Erro: Deposito de destino nao encontrado.\n");
        fclose(fp);
        return;
    }

    fseek(fp, pos_origem, SEEK_SET);
    Deposito dep_origem;
    fread(&dep_origem, sizeof(Deposito), 1, fp);

    if (prod_idx_origem == -1 || dep_origem.produtos[prod_idx_origem].quantidade_itens < qtd_mover) {
        printf("Erro: Produto nao encontrado ou quantidade insuficiente na origem.\n");
        fclose(fp);
        return;
    }

    fseek(fp, pos_destino, SEEK_SET);
    Deposito dep_destino;
    fread(&dep_destino, sizeof(Deposito), 1, fp);

    produto prod_transferido = dep_origem.produtos[prod_idx_origem];
    int sucesso = 0;

    while (!sucesso) {
        float volume_ocupado_destino = 0;
        for (int i = 0; i < 100; i++) {
            if (strlen(dep_destino.produtos[i].codigo_barras) > 0) {
volume_ocupado_destino += (dep_destino.produtos[i].quantidade_itens * dep_destino.produtos[i].volume_unidade);
            }
        }

        float volume_necessario = qtd_mover * prod_transferido.volume_unidade;

        if (volume_ocupado_destino + volume_necessario <= dep_destino.capacidade_max) {
            sucesso = 1; 
        } else {
            int opcao;
            printf("\n Espaco insuficiente no deposito de destino!\n");
            printf("1. Alterar quantidade de itens\n");
            printf("2. Cancelar transferencia\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);

            if (opcao == 1) {
                printf("Digite a nova quantidade a ser movida: ");
                
                scanf("%d", &qtd_mover);
                if (qtd_mover <= 0) {
                
                    printf("Quantidade invalida. Operacao cancelada.\n");
                    fclose(fp);
                    return;
                }
                if (dep_origem.produtos[prod_idx_origem].quantidade_itens < qtd_mover) {
                
                    printf("Erro: Nova quantidade excede o estoque da origem.\n");
                    fclose(fp);
                    return;
                }
            } else {
                
                printf("Transferencia cancelada pelo usuario.\n");
                fclose(fp);
                return;
            }
        }
    }
    dep_origem.produtos[prod_idx_origem].quantidade_itens -= qtd_mover;

    if (dep_origem.produtos[prod_idx_origem].quantidade_itens == 0) {
        for (int j = prod_idx_origem; j < 99; j++) {
            dep_origem.produtos[j] = dep_origem.produtos[j + 1];
        }
        memset(&dep_origem.produtos[99], 0, sizeof(produto));
    }

    int prod_idx_destino = -1;
    for (int i = 0; i < 100; i++) {
        if (strcmp(dep_destino.produtos[i].codigo_barras, codigo_busca) == 0) {
            prod_idx_destino = i;
            break;
        }
    }

    if (prod_idx_destino != -1) {

        dep_destino.produtos[prod_idx_destino].quantidade_itens += qtd_mover;

    } else {
        int espaco_vazio = -1;
        for (int i = 0; i < 100; i++) {
            if (strlen(dep_destino.produtos[i].codigo_barras) == 0) {
                espaco_vazio = i;
                break;
            }
        }

        if (espaco_vazio == -1) {
            printf("Erro: O deposito de destino nao possui slots livres para novos produtos (Limite de 100 atingido).\n");
            fclose(fp);
            return;
        }

        dep_destino.produtos[espaco_vazio] = prod_transferido;
        dep_destino.produtos[espaco_vazio].quantidade_itens = qtd_mover; 
    }
    
    fseek(fp, pos_origem, SEEK_SET);
    fwrite(&dep_origem, sizeof(Deposito), 1, fp);

    fseek(fp, pos_destino, SEEK_SET);
    fwrite(&dep_destino, sizeof(Deposito), 1, fp);

    fclose(fp);
    printf("\nTransferencia de %d itens realizada com sucesso!\n", qtd_mover);
}
