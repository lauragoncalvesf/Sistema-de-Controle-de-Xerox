#include "pedido.c"

int main() {
    int opcao;
    pedidos = (Pedido **)malloc(capacidade * sizeof(Pedido *));
    if (pedidos == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }
    do {
        printf("\n----- | Menu de Pedidos | -----\n\n");
        printf("1. Adicionar pedido\n");
        printf("2. Listar pedidos\n");
        printf("3. Excluir pedido\n");
        printf("4. Buscar pedido por número ou nome\n");
        printf("5. Editar pedido\n");
        printf("6. Consultar pedidos por status\n");
        printf("7. Consultar total de cópias e valor arrecadado\n");
        printf("0. Sair\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarPedido();
                break;
            case 2:
                listarPedidos();
                break;
            case 3:
                excluirPedido();
                break;
            case 4:
                buscarPedido();
                break;
            case 5:
                editarPedido();
                break;
            case 6:
                consultarPedidosPorStatus();
                break;
            case 7:
                consultarTotalCopiasValor();
                break;
            case 0:
                liberarMemoria();
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
    return 0;
}
