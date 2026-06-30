#ifndef PRODUTO_H
#define PRODUTO_H

// forward declaration (evita dependência circular)
struct Deposito;

typedef struct {
    char codigo_barras[13];
    char nome_produto[101];
    int tipo_produto;
    int perecivel;
    char data_fabricacao[11];
    float volume_unidade;
    int quantidade_itens;
    float valor_unitario;
    char data_validade[11];
} produto;

char cadastrar_produto(produto *p, struct Deposito depositos);

int consultar_produto(void);
void atualiza_produto(void);
void remover_produto(void);
void transferir_produto(void);

int validar_codigo(char codigo[]);
int validar_cep(const char *cep);
int verificar_data(produto prod);

int alocar_produto_no_deposito_por_indice(produto novo_produto, const char *cep_busca);

#endif
