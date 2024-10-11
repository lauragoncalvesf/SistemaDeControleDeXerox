#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define PRECO_POR_PAGINA 0.10

// Definição da struct de Pedido
typedef struct Pedido{
    int numero;
    char nomeSolicitante[50];
    char tipoSolicitante[20];
    int quantidadePaginas;
    char dataPedido[11];
    float valorTotal;
    char status[15];
    struct Pedido * proximo;
} Pedido;

// Função para obter a data atual dd/mm/yyyy
void obterData(char *data); 

