#ifndef XEROX_H
#define XEROX_H

// Definição da estrutura de um pedido
typedef struct Pedido {
    int numero;              // Número do pedido
    char nomeCliente[50];
    char tipoSolicitante[20];
    int quantidadePaginas;
    char dataCadastro[20];   // Data e hora de cadastro
    char status[15];         // Status do pedido
    struct Pedido* proximo;  // Ponteiro para o próximo pedido (lista encadeada)
} Pedido;

// Funções para manipular pedidos
Pedido* criarPedido(int numero, char nome[], char tipo[], int paginas, char status[]);
void exibirPedido(Pedido* p);
void salvarListaNoArquivo(Pedido* lista, const char* nomeArquivo);
void inserirPedidoNaLista(Pedido** lista, Pedido* novoPedido);
void listarPedidos(Pedido* lista);
Pedido* buscarPedidoPorNumero(Pedido* lista, int numero);
Pedido* buscarPedidoPorNome(Pedido* lista, char nome[]);
void excluirPedido(Pedido** lista, int numero);
void editarPedido(Pedido* p);
void consultarPorStatus(Pedido* lista, char status[]);
void calcularTotalCopiasEValor(Pedido* lista, float precoPorCopia);
void liberarMemoria(Pedido* lista);  // Função para liberar a memória
void carregarPedidosDoArquivo(Pedido** lista, const char* nomeArquivo);

#endif
