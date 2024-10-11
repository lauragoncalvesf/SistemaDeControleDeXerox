#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pedido.h"

int main() {
    Pedido* listaPedidos = NULL;  // Inicializa a lista de pedidos como vazia
    const char* nomeArquivo = "pedidos_xerox.txt";
    float precoPorCopia = 0.10;  // Preço por cópia

    // Carrega os pedidos existentes do arquivo
    carregarPedidosDoArquivo(&listaPedidos, nomeArquivo);

    int quantidadePaginas, opcao;

    do {
        printf("1. Cadastrar novo pedido\n");
        printf("2. Listar pedidos\n");
        printf("3. Buscar pedido por número\n");
        printf("4. Buscar pedido por #nome\n");
        printf("5. Excluir pedido\n");
        printf("6. Editar pedido\n");
        printf("7. Consultar pedidos por status\n");
        printf("8. Consultar total de cópias e valor arrecadado\n");
        printf("9. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                // Coleta de dados do pedido
                char nomeCliente[50], tipoSolicitante[20], status[15];
                printf("Nome do Solicitante: ");
                scanf(" %[^\n]%*c", nomeCliente);  // Lê string com espaços
                printf("Tipo de Solicitante (aluno, funcionario, professor): ");
                scanf(" %[^\n]%*c", tipoSolicitante);
                printf("Quantidade de Páginas: ");
                scanf("%d", &quantidadePaginas);
                
                // Coletar o status do pedido
                printf("Status do Pedido (pendente, concluido, cancelado): ");
                scanf(" %[^\n]%*c", status);

                // Calcula o próximo número do pedido
                int numeroPedido = 1;
                if (listaPedidos != NULL) {
                    Pedido* atual = listaPedidos;
                    while (atual->proximo != NULL) {
                        atual = atual->proximo; // Move para o final da lista
                    }
                    numeroPedido = atual->numero + 1; // O próximo número será um a mais que o último
                }

                // Criação e inserção do pedido na lista
                Pedido* novoPedido = criarPedido(numeroPedido, nomeCliente, tipoSolicitante, quantidadePaginas, status);
                inserirPedidoNaLista(&listaPedidos, novoPedido);

                // Exibe o pedido inserido
                exibirPedido(novoPedido);

                // Salvando a lista inteira no arquivo
                salvarListaNoArquivo(listaPedidos, nomeArquivo);

                printf("Pedido cadastrado e salvo com sucesso!\n");
                break;
            }
            case 2:
                listarPedidos(listaPedidos);
                break;
            case 3: {
                int numeroPedido; // Declare a variável aqui
                printf("Digite o número do pedido: ");
                scanf("%d", &numeroPedido);
                Pedido* p = buscarPedidoPorNumero(listaPedidos, numeroPedido);
                if (p != NULL) {
                    exibirPedido(p);
                } else {
                    printf("Pedido não encontrado.\n");
                }
                break;
            }
            case 4: {
                char nome[50];
                printf("Digite o nome do cliente: ");
                scanf(" %[^\n]%*c", nome);
                Pedido* p = buscarPedidoPorNome(listaPedidos, nome);
                if (p != NULL) {
                    exibirPedido(p);
                } else {
                    printf("Pedido não encontrado.\n");
                }
                break;
            }
            case 5: {
                int numeroPedido; // Declare a variável aqui
                printf("Digite o número do pedido a ser excluído: ");
                scanf("%d", &numeroPedido);
                excluirPedido(&listaPedidos, numeroPedido);
                salvarListaNoArquivo(listaPedidos, nomeArquivo);
                break;
            }
            case 6: {
                int numeroPedido; // Declare a variável aqui
                printf("Digite o número do pedido a ser editado: ");
                scanf("%d", &numeroPedido);
                Pedido* pedidoEditar = buscarPedidoPorNumero(listaPedidos, numeroPedido);
                if (pedidoEditar != NULL) {
                    editarPedido(pedidoEditar);
                    salvarListaNoArquivo(listaPedidos, nomeArquivo);
                } else {
                    printf("Pedido não encontrado.\n");
                }
                break;
            }
            case 7: {
                char status[15];
                printf("Digite o status do pedido a ser consultado (pendente, concluido, cancelado): ");
                scanf(" %[^\n]%*c", status);
                consultarPorStatus(listaPedidos, status);
                break;
            }
            case 8:
                calcularTotalCopiasEValor(listaPedidos, precoPorCopia);
                break;
            case 9:
                printf("Saindo...\n");
                liberarMemoria(listaPedidos);  // Libera a memória antes de sair
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 9);

    return 0;
}
