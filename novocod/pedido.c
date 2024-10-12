#include "pedido.h"

int obterOpcaoMenu(){
    char entrada[50]; // Buffer para a entrada do usuário
    int opcao = -1;

    while (1)
    {
        printf("Digite uma opção do menu: ");
        fgets(entrada, 50, stdin);              // Captura a entrada como string
        entrada[strcspn(entrada, "\n")] = '\0'; // Remove o '\n'

        // Verifica se a entrada contém apenas números
        if (apenasNumeros(entrada))
        {
            opcao = atoi(entrada); // Converte a string para inteiro
            break;
        }
        else
        {
            printf("Entrada inválida! Por favor, insira um número.\n");
        }
    }

    return opcao;
}

void obterData(char *data){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(data, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

int apenasLetras(const char *str){
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isalpha(str[i]) && str[i] != ' ')
        {
            return 0; // Contém algo que não é letra ou espaço
        }
    }
    return 1; // Apenas letras ou espaços
}

int apenasNumeros(const char *str){
    for (int i = 0; i < strlen(str); i++)
    {
        if (!isdigit(str[i]))
        {
            return 0; // Contém algo que não é número
        }
    }
    return 1; // Apenas números
}

// Função para obter uma entrada apenas com caracteres
void obterEntradaApenasCaracteres(char *buffer, int tamanho, const char *prompt) {
    char entradaTemp[tamanho];

    while (1) {
        printf("%s", prompt);
        fgets(entradaTemp, tamanho, stdin);
        entradaTemp[strcspn(entradaTemp, "\n")] = 0; // Remove o '\n'

        // Verifica se a entrada não está vazia e se contém apenas letras
        if (strlen(entradaTemp) > 0 && apenasLetras(entradaTemp)) {
            strcpy(buffer, entradaTemp);
            break;
        } else {
            printf("Entrada inválida! Por favor, insira apenas letras.\n");
        }
    }
}

// Função para obter o tipo de solicitante
void obterTipoSolicitante(Pedido *pedido) {
    int opcao;
    while (1) {
        printf("Tipo de solicitante:\n 1. Aluno\n 2. Professor\n 3. Funcionário\n Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o caractere de nova linha do buffer

        if (opcao == 1) {
            strcpy(pedido->tipoSolicitante, "Aluno");
            break;
        } else if (opcao == 2) {
            strcpy(pedido->tipoSolicitante, "Professor");
            break;
        } else if (opcao == 3) {
            strcpy(pedido->tipoSolicitante, "Funcionário");
            break;
        } else {
            printf("Opção inválida! Por favor, escolha 1, 2 ou 3.\n");
        }
    }
}

void obterQuantidadePaginas(int *quantidade) {
    char entrada[10];

    while (1) {
        printf("Quantidade de páginas: ");
        fgets(entrada, sizeof(entrada), stdin);

        entrada[strcspn(entrada, "\n")] = 0; // Remove o '\n'

        if (apenasNumeros(entrada)) {
            *quantidade = atoi(entrada);
            break; // Saia do loop se a entrada é válida
        } else {
            printf("Entrada inválida! Por favor, insira apenas números.\n");
        }
    }
}

void salvarPedidoNoArquivo(Pedido* lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");  // Abre o arquivo no modo de escrita (substitui o conteúdo anterior)
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Pedido* atual = lista;
    while (atual != NULL) {
        fprintf(arquivo, "Numero do Pedido: %d\n", atual->numero);
        fprintf(arquivo, "Nome do Solicitante: %s\n", atual->nomeSolicitante);
        fprintf(arquivo, "Tipo de Solicitante: %s\n", atual->tipoSolicitante);
        fprintf(arquivo, "Quantidade de Páginas: %d\n", atual->quantidadePaginas);
        fprintf(arquivo, "Data do Pedido: %s\n", atual->dataPedido);
        fprintf(arquivo, "Status do Pedido: %s\n", atual->status);
        fprintf(arquivo, "-----------------------------------\n");
        atual = atual->proximo;
    }

    fclose(arquivo);
}

void carregarPedidosDoArquivo(Pedido** lista, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo. Criando um novo arquivo.\n");
        return; // Se o arquivo não existir, não faz nada
    }

    Pedido* novoPedido;
    while (!feof(arquivo)) {
        novoPedido = (Pedido*) malloc(sizeof(Pedido));
        if (fscanf(arquivo, "Numero do Pedido: %d\n", &novoPedido->numero) != 1) {
            free(novoPedido);
            break; // Para caso não conseguir ler o número, sai do loop
        }
        fscanf(arquivo, "Nome do Solicitante: %[^\n]\n", novoPedido->nomeSolicitante);
        fscanf(arquivo, "Tipo de Solicitante: %[^\n]\n", novoPedido->tipoSolicitante);
        fscanf(arquivo, "Quantidade de Páginas: %d\n", &novoPedido->quantidadePaginas);
        fscanf(arquivo, "Data de Cadastro: %[^\n]\n", novoPedido->dataPedido);
        fscanf(arquivo, "Status do Pedido: %[^\n]\n", novoPedido->status);
        fscanf(arquivo, "-----------------------------------\n"); // Ignora a linha separadora

        // Insere o pedido na lista
        novoPedido->proximo = NULL; // Inicializa o próximo como NULL
        inserirPedidoNaLista(lista, novoPedido);
    }

    fclose(arquivo);
}

void inserirPedidoNaLista(Pedido** lista, Pedido* novoPedido) {
    if (*lista == NULL) {
        *lista = novoPedido;  // Se a lista estiver vazia, o novo pedido é o primeiro
    } else {
        Pedido* atual = *lista;
        while (atual->proximo != NULL) {
            atual = atual->proximo;  // Percorre até o final da lista
        }
        atual->proximo = novoPedido;  // Insere o novo pedido no final
    }
}

void adicionarPedido(Pedido ** listaPedido){
    Pedido * novoPedido = (Pedido*)malloc(sizeof(Pedido));
    if (novoPedido == NULL){
        printf("Erro ao alocar memória.\n");
        return;
    }
    
    obterEntradaApenasCaracteres(novoPedido->nomeSolicitante, sizeof(novoPedido->nomeSolicitante), "Nome do solicitante: ");
    obterTipoSolicitante(novoPedido);
    obterQuantidadePaginas(&novoPedido->quantidadePaginas);
    obterData(novoPedido->dataPedido);
    novoPedido->valorTotal = novoPedido->quantidadePaginas * PRECO_POR_PAGINA;
    if (novoPedido->quantidadePaginas > 50){
        novoPedido->valorTotal *= 0.9;
    }
    strcpy(novoPedido->status, "Pendente");

    novoPedido->proximo = NULL; 

    if(*listaPedido == NULL){
        novoPedido->numero = 1;
        *listaPedido = novoPedido;
    }else{
        Pedido * atual = *listaPedido;
        while(atual->proximo != NULL){
            atual = atual->proximo;
        }
        novoPedido->numero = atual->numero + 1;
        atual->proximo = novoPedido;
    }

    printf("Pedido criado com sucesso! Número do pedido: %d\n", novoPedido->numero);
}

// Função para listar os pedidos
void listarPedidos(Pedido *lista) {
    Pedido *atual = lista;
    if (atual == NULL) {
        printf("Nenhum pedido cadastrado.\n");
        return;
    }
    printf("Lista de Pedidos:\n");
    while (atual != NULL) {
        printf("Número do Pedido: %d\n", atual->numero);
        printf("Nome do Solicitante: %s\n", atual->nomeSolicitante);
        printf("Tipo de Solicitante: %s\n", atual->tipoSolicitante);
        printf("Quantidade de Páginas: %d\n", atual->quantidadePaginas);
        printf("Status: %s\n", atual->status);
        printf("Data de Cadastro: %s\n", atual->dataPedido);
        printf("------------------------\n");
        atual = atual->proximo;
    }
}

// Função para excluir um pedido e atualizar os números
void excluirPedido(Pedido** lista) {
    if(*lista == NULL){
        printf("Nenhum pedido para excluir!\n");
        return;
    }
    Pedido* atual = *lista;
    Pedido* anterior = NULL;
    int numeroExcluir;

    printf("\nDigite o número do pedido que deseja excluir: ");
    scanf("%d", &numeroExcluir);
    getchar();

    // Procura pelo pedido a ser excluído
    while (atual != NULL && atual->numero != numeroExcluir) {
        anterior = atual; // Armazena o ponteiro do pedido anterior
        atual = atual->proximo; // Move para o próximo pedido
    }

    // Se o pedido não for encontrado
    if (atual == NULL) {
        printf("Pedido com número %d não encontrado.\n", numeroExcluir);
        return;
    }

    // Se o pedido a ser excluído é o primeiro da lista
    if (anterior == NULL) {
        *lista = atual->proximo; // Atualiza a cabeça da lista
    } else {
        anterior->proximo = atual->proximo; // Atualiza o ponteiro do anterior
    }

    free(atual); // Libera a memória do pedido excluído

    Pedido *aux = *lista;
    int novoNumero = 1;

    while(aux != NULL){
        aux->numero = novoNumero;
        novoNumero ++;
        aux = aux->proximo;
    }
    printf("Pedido com número %d excluído com sucesso.\n", numeroExcluir);
}