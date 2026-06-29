#ifndef DEPOSITO_H
#define DEPOSITO_H

"include struct_h"





int validar_cep(char cep[]);

void Cadastrar_Novo_Deposito(Deposito depositos[], int *contador);

void Consultar_Inf_Depositos(Deposito depositos[], int contador);

void Consultar_Todas_Inf_Depositos(Deposito depositos[], int contador);

void Atualizar_Dados_Deposito(Deposito depositos[], int contador);

void Remover_Deposito(Deposito depositos[], int *contador);

#endif
