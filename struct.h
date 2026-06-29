#ifndef STRUCT_H
#define STRUCT_H

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
   char endereco[51];
   char telefone[20];
   float capacidade_Maxima;
   float estoque_Atual;
   produto produtos[100];
   int total_Produtos;
   int qtd_produtos;
   float capacidade_atual; 
} Deposito;
#endif
