

typedef struct{
    int numero;
    char nomeSolicitante[50];
    char tipoSolicitante[20]; // Aluno, Professor, Funcionario
    int quantidadePaginas;
    char dataPedido[11]; // formato: dd/mm/yyyy
    float valorTotal;
    char status[20]; // Pendente, Concluído, Cancelado
} Pedido;