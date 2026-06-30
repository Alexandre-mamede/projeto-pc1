#ifndef PRODUTO_H
#define PRODUTO_H

char cadastrar_produto(produto *p, struct Deposito depositos);

int consultar_produto(void);
void atualiza_produto(void);
void remover_produto(void);
void transferir_produto(void);

int validar_codigo(char codigo[]);
int VALIDAR_cep(const char *cep);
int verificar_data(produto prod);

int alocar_produto_no_deposito_por_indice(produto novo_produto, const char *cep_busca);

#endif
