#ifndef PRODUTO_H
#define PRODUTO_H

#include "struct.h"

// ===================== PRODUTO =====================

int cadastrar_produto(produto *p, int deposito_cadastrado, Deposito depositos[]);

int consultar_produto(Deposito depositos[], char codigo[], int total_depositos);

int atualiza_produto(char cep[], char codigo[], Deposito depositos[], int total_depositos);

int remover_produto(char cep[], char codigo[], Deposito depositos[], int total_depositos);

// ===================== UTIL =====================

int validar_codigo(char codigo[]);
int validar_cep(const char *cep);
int verificar_data(produto prod);

int alocar_produto_no_deposito(produto novo, const char *cep, Deposito depositos[], int total_depositos);

#endif
