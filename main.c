#include "pedido.c"

int main() {
    pedidos = (Pedido **)malloc(capacidade * sizeof(Pedido *));
    if (pedidos == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    menu();
    return 0;
}
