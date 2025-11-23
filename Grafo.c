#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char nomes[50][100];
int matrizAdj[50][50];
int qtdCreches = 0;
typedef struct Node {
    char creche[100];
    double distancia;
    struct Node* next;
} Node;
typedef struct {
    Node* head;
} Lista;
Lista listas[50];
void initLista(Lista* l) {
    l->head = NULL;
}
void inserirLista(Lista* l, const char* nome, double dist) {
    Node* novo = (Node*)malloc(sizeof(Node));
    strcpy(novo->creche, nome);
    novo->distancia = dist;
    novo->next = NULL;

    if (l->head == NULL) {
        l->head = novo;
    } else {
        Node* aux = l->head;
        while (aux->next != NULL)
            aux = aux->next;
        aux->next = novo;
    }
}
double buscarDistancia(Lista* l, const char* nome) {
    Node* aux = l->head;
    while (aux != NULL) {
        if (strcmp(aux->creche, nome) == 0)
            return aux->distancia;
        aux = aux->next;
    }
    return -1;
}
void listarOrdenado(Lista* l) {
    int count = 0;
    Node* aux = l->head;
    while (aux != NULL) {
        count++;
        aux = aux->next;
    }
    if (count == 0) return;
    Node** vet = malloc(count * sizeof(Node*));
    aux = l->head;
    for (int i = 0; i < count; i++) {
        vet[i] = aux;
        aux = aux->next;
    }
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (vet[i]->distancia > vet[j]->distancia) {
                Node* tmp = vet[i];
                vet[i] = vet[j];
                vet[j] = tmp;
            }
        }
    }
    for (int i = 0; i < count; i++) {
        printf("%s - %.2f km\n", vet[i]->creche, vet[i]->distancia);
    }
    free(vet);
}
int getIndex(const char* nome) {
    for (int i = 0; i < qtdCreches; i++) {
        if (strcmp(nomes[i], nome) == 0)
            return i;
    }
    return -1;
}
int addCreche(const char* nome) {
    int idx = getIndex(nome);
    if (idx != -1) return idx;
    strcpy(nomes[qtdCreches], nome);
    initLista(&listas[qtdCreches]);
    return qtdCreches++;
}
void carregarArquivo(const char* arquivo) {
    FILE* f = fopen(arquivo, "r");
    if (!f) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    char linha[200];
    while (fgets(linha, sizeof(linha), f)) {
        char c1[100], c2[100];
        double dist;
        sscanf(linha, "%[^;];%[^;];%lf", c1, c2, &dist);
        int i = addCreche(c1);
        int j = addCreche(c2);
        if (buscarDistancia(&listas[i], c2) == -1)
            inserirLista(&listas[i], c2, dist);
        if (buscarDistancia(&listas[j], c1) == -1)
            inserirLista(&listas[j], c1, dist);
        matrizAdj[i][j] = matrizAdj[j][i] = 1;
    }
    fclose(f);
}
void listarConexoes() {
    printf("\nNumero de conexoes por creche:\n");
    for (int i = 0; i < qtdCreches; i++) {
        int count = 0;
        for (int j = 0; j < qtdCreches; j++)
            if (matrizAdj[i][j] == 1) count++;

        printf("%s: %d conexoes\n", nomes[i], count);
    }
}
void listarConexoesCreche(const char* nome) {
    int i = getIndex(nome);
    if (i == -1) {
        printf("Creche nao encontrada!\n");
        return;
    }

    printf("\nConexoes de %s:\n", nome);
    listarOrdenado(&listas[i]);
}
void distanciaEntre(const char* a, const char* b) {
    int i = getIndex(a);
    if (i == -1) {
        printf("Primeira creche nao encontrada.\n");
        return;
    }

    double d = buscarDistancia(&listas[i], b);
    if (d == -1)
        printf("Não existe ligacao entre %s e %s.\n", a, b);
    else
        printf("Distancia entre %s e %s: %.2f km\n", a, b, d);
}
void novaConexao(const char* c1, const char* c2, double dist) {
    int i = addCreche(c1);
    int j = addCreche(c2);
    if (buscarDistancia(&listas[i], c2) == -1)
        inserirLista(&listas[i], c2, dist);
    if (buscarDistancia(&listas[j], c1) == -1)
        inserirLista(&listas[j], c1, dist);
    matrizAdj[i][j] = matrizAdj[j][i] = 1;
    printf("Nova conexao adicionada!\n");
}

int main() {
    carregarArquivo("creches.txt");
    listarConexoes();
    listarConexoesCreche("JoaoGama");
    distanciaEntre("AntonioMartins", "PorfiroGabrielDosAnjos");
    novaConexao("NovaCreche", "JoaoGama", 3.3);
    listarConexoesCreche("JoaoGama");
    listarConexoes();
    return 0;
}