#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rbt.h"

#define REPETICOES 35

int tamanhos[] = {
    1, 5, 10, 25, 50, 100, 250, 1000, 2500, 5000, 7500, 10000,
    25000, 50000, 75000, 100000, 250000, 500000, 750000, 1000000,
    2500000, 5000000, 10000000, 25000000, 50000000, 100000000
};

int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

double medir_insercao(int *dados, int n) {
    RBTree *T = rbt_create();
    struct timespec inicio, fim;

    clock_gettime(CLOCK_MONOTONIC, &inicio);
    for (int i = 0; i < n; i++)
        rbt_insert(T, dados[i]);
    clock_gettime(CLOCK_MONOTONIC, &fim);

    double tempo = (fim.tv_sec - inicio.tv_sec) +
                   (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    rbt_free(T);
    return tempo;
}

double medir_busca(int *dados, int n) {
    RBTree *T = rbt_create();
    for (int i = 0; i < n; i++)
        rbt_insert(T, dados[i]);

    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    for (int i = 0; i < n; i++)
        rbt_search(T, dados[i]);
    clock_gettime(CLOCK_MONOTONIC, &fim);

    double tempo = (fim.tv_sec - inicio.tv_sec) +
                   (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    rbt_free(T);
    return tempo;
}

double medir_remocao(int *dados, int n) {
    RBTree *T = rbt_create();
    for (int i = 0; i < n; i++)
        rbt_insert(T, dados[i]);

    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    for (int i = 0; i < n; i++) {
        if (rbt_search(T, dados[i]) != NULL)  // só deleta se existir
            rbt_delete(T, dados[i]);
    }
    clock_gettime(CLOCK_MONOTONIC, &fim);

    double tempo = (fim.tv_sec - inicio.tv_sec) +
                   (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    rbt_free(T);
    return tempo;
}

int main() {
    srand(42);

    FILE *csv = fopen("output/results.csv", "w");
    if (!csv) {
        fprintf(stderr, "Erro ao abrir output/results.csv\n");
        return 1;
    }

    fprintf(csv, "tamanho,insercao,busca,remocao\n");

    for (int t = 0; t < num_tamanhos; t++) {
        int n = tamanhos[t];
        printf("Executando n = %d...\n", n);

        double soma_ins = 0, soma_bus = 0, soma_rem = 0;

        // Aloca array de dados
        int *dados = malloc(n * sizeof(int));
        if (!dados) {
            fprintf(stderr, "Erro ao alocar memória para n = %d\n", n);
            break;
        }

        for (int r = 0; r < REPETICOES; r++) {
            // Gera números aleatórios entre 1 e 100000
            for (int i = 0; i < n; i++)
                dados[i] = (rand() % 100000) + 1;

            soma_ins += medir_insercao(dados, n);
            soma_bus += medir_busca(dados, n);
            soma_rem += medir_remocao(dados, n);
        }

        free(dados);

        double media_ins = soma_ins / REPETICOES;
        double media_bus = soma_bus / REPETICOES;
        double media_rem = soma_rem / REPETICOES;

        fprintf(csv, "%d,%.9f,%.9f,%.9f\n", n, media_ins, media_bus, media_rem);
        printf("  insert=%.6fs  busca=%.6fs  remocao=%.6fs\n",
               media_ins, media_bus, media_rem);
    }

    fclose(csv);
    printf("\nResultados salvos em output/results.csv\n");
    return 0;
}