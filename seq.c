// arquivo para gerar vetores aleatórios, calcular seu produto interno e armazenar em um arquivo
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000
int calculaProdutoInterno(float *vetor_1, float *vetor_2, int n, FILE *arquivo)
{
    double soma = 0;
    for (int i = 0; i < n; i++)
    {
        soma += vetor_1[i] * vetor_2[i];
        if (i < n - 1)
        {
            fprintf(arquivo, "%f ", vetor_2[i]);
        }
        else
        {
            fprintf(arquivo, "%f\n", vetor_2[i]);
        }
    }
    return soma;
}

int main(int argc, char *argv[])
{
    int n;
    float *vetor_1;
    float *vetor_2;
    int fator = 1;
    double produtoInterno;

    if (argc < 3)
    {
        printf("Uso: %s <tamanho_do_vetor> <caminho_do_arquivo> \n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);
    FILE *arquivo = fopen(argv[2], "w");
    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    fprintf(arquivo, "%d\n", n);

    vetor_1 = (float *)malloc(n * sizeof(float));
    vetor_2 = (float *)malloc(n * sizeof(float));

    srand(time(NULL));

    for (int i = 0; i < n; i++)
    {
        float elem_1 = (rand() % 2001) - 1000;
        float elem_2 = (rand() % 2001) - 1000;
        vetor_1[i] = elem_1;
        vetor_2[i] = elem_2;
        fator *= -1;
        if (i < n - 1)
        {
            fprintf(arquivo, "%f ", elem_1);
        }
        else
        {
            fprintf(arquivo, "%f\n", elem_1);
        }
    }

    produtoInterno = calculaProdutoInterno(vetor_1, vetor_2, n, arquivo);

    fprintf(arquivo, "%lf\n", produtoInterno);
    free(vetor_1);
    free(vetor_2);
    fclose(arquivo);
    return 0;
}
