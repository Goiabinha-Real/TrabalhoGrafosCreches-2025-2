#include <stdio.h>
#include <stdlib.h>
#include "grafo.c"

int main() {
    int opcao;
    char nome1[100], nome2[100], arquivo[100];
    double dist;

    printf("Carregando arquivo padrao: creches.txt...\n");
    carregarArquivo("creches.txt");

    do {
        printf("\n======= MENU =======\n");
        printf("1 - Listar conexoes por creche\n");
        printf("2 - Listar conexoes de uma creche\n");
        printf("3 - Distancia entre duas creches\n");
        printf("4 - Adicionar nova conexao\n");
        printf("5 - Carregar outro arquivo\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {

            case 1:
                listarConexoes();
                break;

            case 2:
                printf("Nome da creche: ");
                fgets(nome1, 100, stdin);
                nome1[strcspn(nome1, "\n")] = 0;
                listarConexoesCreche(nome1);
                break;

            case 3:
                printf("Creche A: ");
                fgets(nome1, 100, stdin);
                nome1[strcspn(nome1, "\n")] = 0;

                printf("Creche B: ");
                fgets(nome2, 100, stdin);
                nome2[strcspn(nome2, "\n")] = 0;

                distanciaEntre(nome1, nome2);
                break;

            case 4:
                printf("Creche A: ");
                fgets(nome1, 100, stdin);
                nome1[strcspn(nome1, "\n")] = 0;

                printf("Creche B: ");
                fgets(nome2, 100, stdin);
                nome2[strcspn(nome2, "\n")] = 0;

                printf("Distancia: ");
                scanf("%lf", &dist);
                getchar();

                novaConexao(nome1, nome2, dist);
                break;

            case 5:
                printf("Arquivo: ");
                fgets(arquivo, 100, stdin);
                arquivo[strcspn(arquivo, "\n")] = 0;

                carregarArquivo(arquivo);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}
