#include "pedido.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


Pedido **pedidos = NULL;  // Ponteiro para ponteiro de Pedido
int contadorPedidos = 0; // Contador de pedidos
int capacidade = 100;      // Capacidade inicial

// Função para obter a data atual
void obterData(char *data) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(data, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

// Função para redimensionar o array de pedidos
void redimensionarPedidos() {
    capacidade *= 2;
    pedidos = realloc(pedidos, capacidade * sizeof(Pedido *));
    if (pedidos == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
}

// Função para adicionar um pedido
void adicionarPedido() {
    if (contadorPedidos >= capacidade) {
        redimensionarPedidos();
    }

    pedidos[contadorPedidos] = (Pedido *)malloc(sizeof(Pedido));
    if (pedidos[contadorPedidos] == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    Pedido *novoPedido = pedidos[contadorPedidos];
    novoPedido->numero = contadorPedidos + 1;

    printf("Nome do solicitante: ");
    scanf(" %[^\n]", novoPedido->nomeSolicitante);

    printf("Tipo de solicitante (Aluno, Professor, Funcionario): ");
    scanf(" %[^\n]", novoPedido->tipoSolicitante);

    printf("Quantidade de páginas: ");
    scanf("%d", &novoPedido->quantidadePaginas);

    obterData(novoPedido->dataPedido);
    novoPedido->valorTotal = novoPedido->quantidadePaginas * PRECO_POR_PAGINA;
    strcpy(novoPedido->status, "Pendente");

    contadorPedidos++;
    printf("Pedido adicionado com sucesso!\n");
}

// Função para listar todos os pedidos
void listarPedidos() {
    if (contadorPedidos == 0) {
        printf("Nenhum pedido registrado.\n");
        return;
    }

    for (int i = 0; i < contadorPedidos; i++) {
        Pedido * p = pedidos[i];
        printf("\nPedido #%d\n", p->numero);
        printf("Solicitante: %s\n", p->nomeSolicitante);
        printf("Tipo de solicitante: %s\n", p->tipoSolicitante);
        printf("Quantidade de páginas: %d\n", p->quantidadePaginas);
        printf("Data do pedido: %s\n", p->dataPedido);
        printf("Valor total: R$ %.2f\n", p->valorTotal);
        printf("Status: %s\n", p->status);
    }
}

// Função para excluir um pedido
void excluirPedido() {
    int numero;
    printf("Digite o número do pedido que deseja excluir: ");
    scanf("%d", &numero);

    for (int i = 0; i < contadorPedidos; i++) {
        if (pedidos[i]->numero == numero) {
            free(pedidos[i]);
            for (int j = i; j < contadorPedidos - 1; j++) {
                pedidos[j] = pedidos[j + 1];
            }
            contadorPedidos--;
            printf("Pedido excluído com sucesso!\n");
            return;
        }
    }
    printf("Pedido não encontrado.\n");
}

// Função para buscar pedido por número ou nome
void buscarPedido() {
    char termo[50];
    int encontrado = 0;

    printf("Digite o número ou nome do solicitante: ");
    scanf(" %[^\n]", termo);

    for (int i = 0; i < contadorPedidos; i++) {
        if (pedidos[i]->numero == atoi(termo) || strstr(pedidos[i]->nomeSolicitante, termo)) {
            Pedido *p = pedidos[i];
            printf("\nPedido #%d\n", p->numero);
            printf("Solicitante: %s\n", p->nomeSolicitante);
            printf("Tipo de solicitante: %s\n", p->tipoSolicitante);
            printf("Quantidade de páginas: %d\n", p->quantidadePaginas);
            printf("Data do pedido: %s\n", p->dataPedido);
            printf("Valor total: R$ %.2f\n", p->valorTotal);
            printf("Status: %s\n", p->status);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Nenhum pedido encontrado.\n");
    }
}

// Função para editar um pedido
void editarPedido() {
    int numero;
    printf("Digite o número do pedido que deseja editar: ");
    scanf("%d", &numero);

    for (int i = 0; i < contadorPedidos; i++) {
        if (pedidos[i]->numero == numero) {
            Pedido *p = pedidos[i];
            printf("Editando pedido #%d\n", p->numero);

            printf("Nome do solicitante atual: %s\n", p->nomeSolicitante);
            printf("Digite o novo nome do solicitante (ou pressione enter para manter o atual): ");
            char novo_nome[50];
            scanf(" %[^\n]", novo_nome);
            if (strcmp(novo_nome, "") != 0) {
                strcpy(p->nomeSolicitante, novo_nome);
            }

            printf("Quantidade de páginas atual: %d\n", p->quantidadePaginas);
            printf("Digite a nova quantidade de páginas (ou 0 para manter): ");
            int novaQuantidade;
            scanf("%d", &novaQuantidade);
            if (novaQuantidade > 0) {
                p->quantidadePaginas = novaQuantidade;
                p->valorTotal = novaQuantidade * PRECO_POR_PAGINA;
            }

            printf("Status atual: %s\n", p->status);
            printf("Digite o novo status (Pendente, Concluído, Cancelado): ");
            char novoStatus[20];
            scanf(" %[^\n]", novoStatus);
            strcpy(p->status, novoStatus);

            printf("Pedido atualizado com sucesso!\n");
            return;
        }
    }
    printf("Pedido não encontrado.\n");
}

// Função para consultar pedidos por status
void consultarPedidosPorStatus() {
    char status[20];
    int encontrado = 0;

    printf("Digite o status (Pendente, Concluído, Cancelado): ");
    scanf(" %[^\n]", status);

    for (int i = 0; i < contadorPedidos; i++) {
        if (strcmp(pedidos[i]->status, status) == 0) {
            Pedido *p = pedidos[i];
            printf("\nPedido #%d\n", p->numero);
            printf("Solicitante: %s\n", p->nomeSolicitante);
            printf("Tipo de solicitante: %s\n", p->tipoSolicitante);
            printf("Quantidade de páginas: %d\n", p->quantidadePaginas);
            printf("Data do pedido: %s\n", p->dataPedido);
            printf("Valor total: R$ %.2f\n", p->valorTotal);
            printf("Status: %s\n", p->status);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Nenhum pedido com status %s encontrado.\n", status);
    }
}

// Função para calcular total de cópias realizadas e valor arrecadado
void consultarTotalCopiasValor() {
    int totalPaginas = 0;
    float totalValor = 0.0;

    for (int i = 0; i < contadorPedidos; i++) {
        totalPaginas += pedidos[i]->quantidadePaginas;
        totalValor += pedidos[i]->valorTotal;
    }

    printf("Total de cópias realizadas: %d\n", totalPaginas);
    printf("Valor total arrecadado: R$ %.2f\n", totalValor);
}

// Função para liberar memória alocada para os pedidos
void liberarMemoria() {
    for (int i = 0; i < contadorPedidos; i++) {
        free(pedidos[i]);
    }
    free(pedidos);
}