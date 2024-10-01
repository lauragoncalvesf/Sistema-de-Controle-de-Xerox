#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PRECO_POR_PAGINA 0.10

typedef struct {
    int numero;
    char nome_solicitante[50];
    char tipo_solicitante[20]; // Aluno, Professor, Funcionario
    int quantidade_paginas;
    char data_pedido[11]; // formato: dd/mm/yyyy
    float valor_total;
    char status[20]; // Pendente, Concluído, Cancelado
} Pedido;

Pedido **pedidos = NULL;  // Ponteiro para ponteiro de Pedido
int contador_pedidos = 0; // Contador de pedidos
int capacidade = 10;      // Capacidade inicial

// Função para obter a data atual
void obter_data_atual(char *data) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(data, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

// Função para redimensionar o array de pedidos
void redimensionar_pedidos() {
    capacidade *= 2;
    pedidos = realloc(pedidos, capacidade * sizeof(Pedido *));
    if (pedidos == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
}

// Função para adicionar um pedido
void adicionar_pedido() {
    if (contador_pedidos >= capacidade) {
        redimensionar_pedidos();
    }

    pedidos[contador_pedidos] = (Pedido *)malloc(sizeof(Pedido));
    if (pedidos[contador_pedidos] == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    Pedido *novo_pedido = pedidos[contador_pedidos];
    novo_pedido->numero = contador_pedidos + 1;

    printf("Nome do solicitante: ");
    scanf(" %[^\n]", novo_pedido->nome_solicitante);

    printf("Tipo de solicitante (Aluno, Professor, Funcionario): ");
    scanf(" %[^\n]", novo_pedido->tipo_solicitante);

    printf("Quantidade de páginas: ");
    scanf("%d", &novo_pedido->quantidade_paginas);

    obter_data_atual(novo_pedido->data_pedido);
    novo_pedido->valor_total = novo_pedido->quantidade_paginas * PRECO_POR_PAGINA;
    strcpy(novo_pedido->status, "Pendente");

    contador_pedidos++;
    printf("Pedido adicionado com sucesso!\n");
}

// Função para listar todos os pedidos
void listar_pedidos() {
    if (contador_pedidos == 0) {
        printf("Nenhum pedido registrado.\n");
        return;
    }

    for (int i = 0; i < contador_pedidos; i++) {
        Pedido *p = pedidos[i];
        printf("\nPedido #%d\n", p->numero);
        printf("Solicitante: %s\n", p->nome_solicitante);
        printf("Tipo de solicitante: %s\n", p->tipo_solicitante);
        printf("Quantidade de páginas: %d\n", p->quantidade_paginas);
        printf("Data do pedido: %s\n", p->data_pedido);
        printf("Valor total: R$ %.2f\n", p->valor_total);
        printf("Status: %s\n", p->status);
    }
}

// Função para excluir um pedido
void excluir_pedido() {
    int numero;
    printf("Digite o número do pedido que deseja excluir: ");
    scanf("%d", &numero);

    for (int i = 0; i < contador_pedidos; i++) {
        if (pedidos[i]->numero == numero) {
            free(pedidos[i]);
            for (int j = i; j < contador_pedidos - 1; j++) {
                pedidos[j] = pedidos[j + 1];
            }
            contador_pedidos--;
            printf("Pedido excluído com sucesso!\n");
            return;
        }
    }
    printf("Pedido não encontrado.\n");
}

// Função para buscar pedido por número ou nome
void buscar_pedido() {
    char termo[50];
    int encontrado = 0;

    printf("Digite o número ou nome do solicitante: ");
    scanf(" %[^\n]", termo);

    for (int i = 0; i < contador_pedidos; i++) {
        if (pedidos[i]->numero == atoi(termo) || strstr(pedidos[i]->nome_solicitante, termo)) {
            Pedido *p = pedidos[i];
            printf("\nPedido #%d\n", p->numero);
            printf("Solicitante: %s\n", p->nome_solicitante);
            printf("Tipo de solicitante: %s\n", p->tipo_solicitante);
            printf("Quantidade de páginas: %d\n", p->quantidade_paginas);
            printf("Data do pedido: %s\n", p->data_pedido);
            printf("Valor total: R$ %.2f\n", p->valor_total);
            printf("Status: %s\n", p->status);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Nenhum pedido encontrado.\n");
    }
}

// Função para editar um pedido
void editar_pedido() {
    int numero;
    printf("Digite o número do pedido que deseja editar: ");
    scanf("%d", &numero);

    for (int i = 0; i < contador_pedidos; i++) {
        if (pedidos[i]->numero == numero) {
            Pedido *p = pedidos[i];
            printf("Editando pedido #%d\n", p->numero);

            printf("Nome do solicitante atual: %s\n", p->nome_solicitante);
            printf("Digite o novo nome do solicitante (ou pressione enter para manter o atual): ");
            char novo_nome[50];
            scanf(" %[^\n]", novo_nome);
            if (strcmp(novo_nome, "") != 0) {
                strcpy(p->nome_solicitante, novo_nome);
            }

            printf("Quantidade de páginas atual: %d\n", p->quantidade_paginas);
            printf("Digite a nova quantidade de páginas (ou 0 para manter): ");
            int nova_quantidade;
            scanf("%d", &nova_quantidade);
            if (nova_quantidade > 0) {
                p->quantidade_paginas = nova_quantidade;
                p->valor_total = nova_quantidade * PRECO_POR_PAGINA;
            }

            printf("Status atual: %s\n", p->status);
            printf("Digite o novo status (Pendente, Concluído, Cancelado): ");
            char novo_status[20];
            scanf(" %[^\n]", novo_status);
            strcpy(p->status, novo_status);

            printf("Pedido atualizado com sucesso!\n");
            return;
        }
    }
    printf("Pedido não encontrado.\n");
}

// Função para consultar pedidos por status
void consultar_pedidos_por_status() {
    char status[20];
    int encontrado = 0;

    printf("Digite o status (Pendente, Concluído, Cancelado): ");
    scanf(" %[^\n]", status);

    for (int i = 0; i < contador_pedidos; i++) {
        if (strcmp(pedidos[i]->status, status) == 0) {
            Pedido *p = pedidos[i];
            printf("\nPedido #%d\n", p->numero);
            printf("Solicitante: %s\n", p->nome_solicitante);
            printf("Tipo de solicitante: %s\n", p->tipo_solicitante);
            printf("Quantidade de páginas: %d\n", p->quantidade_paginas);
            printf("Data do pedido: %s\n", p->data_pedido);
            printf("Valor total: R$ %.2f\n", p->valor_total);
            printf("Status: %s\n", p->status);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Nenhum pedido com status %s encontrado.\n", status);
    }
}

// Função para calcular total de cópias realizadas e valor arrecadado
void consultar_total_copias_valor() {
    int total_paginas = 0;
    float total_valor = 0.0;

    for (int i = 0; i < contador_pedidos; i++) {
        total_paginas += pedidos[i]->quantidade_paginas;
        total_valor += pedidos[i]->valor_total;
    }

    printf("Total de cópias realizadas: %d\n", total_paginas);
    printf("Valor total arrecadado: R$ %.2f\n", total_valor);
}

// Função para liberar memória alocada para os pedidos
void liberar_memoria() {
    for (int i = 0; i < contador_pedidos; i++) {
        free(pedidos[i]);
    }
    free(pedidos);
}

// Função para exibir o menu
void menu() {
    int opcao;

    do {
        printf("\n----- Sistema de Controle de Xerox -----\n");
        printf("1. Adicionar pedido\n");
        printf("2. Excluir pedido\n");
        printf("3. Listar pedidos\n");
        printf("4. Buscar pedido por número ou nome\n");
        printf("5. Editar pedido\n");
        printf("6. Consultar pedidos por status\n");
        printf("7. Consultar total de cópias e valor arrecadado\n");
        printf("8. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionar_pedido();
                break;
            case 2:
                excluir_pedido();
                break;
            case 3:
                listar_pedidos();
                break;
            case 4:
                buscar_pedido();
                break;
            case 5:
                editar_pedido();
                break;
            case 6:
                consultar_pedidos_por_status();
                break;
            case 7:
                consultar_total_copias_valor();
                break;
            case 8:
                liberar_memoria();
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 8);
}

int main() {
    pedidos = (Pedido **)malloc(capacidade * sizeof(Pedido *));
    if (pedidos == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    menu();
    return 0;
}
