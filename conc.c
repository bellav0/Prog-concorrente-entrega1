

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int nthreads;
float *vetor_1;
float *vetor_2;
typedef struct
{
    int indexIni;
    int indexEnd;
} Args;

double calcErroRelativo(double prodIntSeq, double prodIntCon)
{
    return (fabs((prodIntSeq - prodIntCon) / prodIntSeq));
}

void *calcProdutoInterno(void *args)
{
    Args *argumentos = (Args *)args;
    double *soma = (double *)malloc(sizeof(double));
    *soma = 0;
    for (int i = argumentos->indexIni; i <= argumentos->indexEnd; i++)
    {

        *soma += vetor_1[i] * vetor_2[i];
    }

    pthread_exit((void *)soma);
}

int main(int argc, char *argv[])
{
    FILE *arquivo;
    pthread_t *tid_sistema;
    int n, division;
    Args *args = NULL;
    double produtoInterno_conc = 0;
    double produtoInterno_seq = 0;
    double erroRelativo = 0;

    if (argc < 3)
    {
        printf("Erro: insira <n_de_threads> <nome do arquivo>\n");
        return 1;
    }

    arquivo = fopen(argv[2], "r");
    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    if (fscanf(arquivo, "%d", &n) != 1)
    {
        printf("Erro ao ler o tamanho do vetor\n");
        fclose(arquivo);
        return 1;
    }

    vetor_1 = (float *)malloc(n * sizeof(float));
    vetor_2 = (float *)malloc(n * sizeof(float));

    if (vetor_1 == NULL || vetor_2 == NULL)
    {
        perror("Erro ao alocar memória");
        fclose(arquivo);
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        if (fscanf(arquivo, "%f", &vetor_1[i]) != 1)
        {
            printf("Erro ao ler os elementos do vetor 1\n");
            fclose(arquivo);
            return 1;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (fscanf(arquivo, "%f", &vetor_2[i]) != 1)
        {
            printf("Erro ao ler os elementos do vetor 2\n");
            fclose(arquivo);
            return 1;
        }
    }

    if (fscanf(arquivo, "%lf", &produtoInterno_seq) != 1)
    {
        printf("Erro ao ler produto interno calculado no sequencial\n");
        fclose(arquivo);
        return 1;
    }
    fclose(arquivo);

    nthreads = atoi(argv[1]);
    if (nthreads > n)
    {
        printf("Número de threads precisa ser menor ou igual ao tamanho do vetor\n");
        return 1;
    }

    tid_sistema = (pthread_t *)malloc(nthreads * sizeof(pthread_t));
    args = (Args *)malloc(nthreads * sizeof(Args));

    if (tid_sistema == NULL || args == NULL)
    {
        perror("Erro ao alocar memória");
        return 1;
    }

    division = (int)ceilf((float)n / nthreads);
    for (int i = 0; i < nthreads; i++)
    {
        args[i].indexIni = i * division;
        args[i].indexEnd = (i + 1) * division - 1;
        if (args[i].indexEnd >= n)
        {
            args[i].indexEnd = n - 1;
        };
        if (pthread_create(&tid_sistema[i], NULL, calcProdutoInterno, (void *)&args[i]))
        {
            printf("--ERRO: pthread_create()\n");
            return 1;
        }
    }

    double *somaParcial;
    for (int i = 0; i < nthreads; i++)
    {
        if (pthread_join(tid_sistema[i], (void **)&somaParcial))
        {
            printf("--ERRO: pthread_join() da thread %d\n", i);
        }
        else
        {
            produtoInterno_conc += *somaParcial;

            free(somaParcial);
        }
    }
    erroRelativo = calcErroRelativo(produtoInterno_seq, produtoInterno_conc);

    printf("Produto interno concorrente: %lf\n", produtoInterno_conc);
    printf("Produto interno sequencial: %lf\n", produtoInterno_seq);
    printf("Erro relativo %.20lf\n", erroRelativo);
    free(tid_sistema);
    free(args);
    free(vetor_1);
    free(vetor_2);

    return 0;
}
