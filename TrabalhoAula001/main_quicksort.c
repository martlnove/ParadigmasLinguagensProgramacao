#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// QuickSort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
        }
    }

    int temp = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = temp;
    return i + 1;
}

void quicksort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// Geração de listas
void gerar_lista(int *arr, int n, const char *tipo) {
    for (int i = 0; i < n; i++) {
        if (strcmp(tipo, "crescente") == 0) arr[i] = i;
        else if (strcmp(tipo, "decrescente") == 0) arr[i] = n - i;
        else arr[i] = rand() % 10000;
    }
}

// Medição de tempo
double medir_tempo(int *arr, int n) {
    clock_t inicio = clock();
    quicksort(arr, 0, n - 1);
    clock_t fim = clock();
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

// Salvando resultado
void salvar_resultado(FILE *f, const char *tipo_lista, int n, int execucao, double tempo) {
    fprintf(f, "%s\t%d\t%d\t%.6f\n", tipo_lista, n, execucao, tempo);
}

// Salvando média
void salvar_media(FILE *f, const char *tipo_lista, int n, double media) {
    fprintf(f, "%s\t%d\tMEDIA\t%.6f\n", tipo_lista, n, media);
}

// Principal
int main() {
    srand(time(NULL));
    int tamanhos[] = {100, 1000, 2000, 3000, 4000, 5000, 10000};
    const char *tipos[] = {"crescente", "decrescente", "aleatoria"};
    const char *arquivo_saida = "resultado_quicksort.txt";

    FILE *f = fopen(arquivo_saida, "w");
    if (f == NULL) {
        printf("Erro ao abrir arquivo de saída.\n");
        return 1;
    }

    for (int t = 0; t < 3; t++) {
        for (int i = 0; i < 7; i++) {
            int n = tamanhos[i];
            double soma_tempos = 0.0;

            for (int exec = 1; exec <= 30; exec++) {
                int *arr = malloc(n * sizeof(int));
                if (arr == NULL) {
                    printf("Erro de memória.\n");
                    return 1;
                }

                gerar_lista(arr, n, tipos[t]);
                double tempo = medir_tempo(arr, n);
                salvar_resultado(f, tipos[t], n, exec, tempo);
                soma_tempos += tempo;
                free(arr);
            }

            double media = soma_tempos / 30.0;
            salvar_media(f, tipos[t], n, media);
        }
    }

    fclose(f);
    printf("Experimentos concluídos. Resultados salvos em %s\n", arquivo_saida);
    return 0;
}