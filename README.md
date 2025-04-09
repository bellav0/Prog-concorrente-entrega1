# Primeiro trabalho de prog concorrente
**COMPILAÇÃO**

Para compilar seq.c: gcc -o seq  seq.c -Wall -lm
Para compilar conc.c: gcc -o conc  conc.c -Wall -lm


**EXECUCÃO**
Para executar seq.c: ./seq <tamanho/dimensão do vetor> <nome do arquivo>. Ex.: ./seq 10 arquivoSaida.bin
Para executar conc.c: ./conc <número de threads> <arquivo de sáida do seq.c>. Ex.: ./conc 5 arquivoSaida.bin


**SÁIDA**

A saída do seq.c é um arquivo com a dimensão do vetor (primeira linha), vetor 1 (linhas seguintes), vetor 2 (linhas seguintes ao término do vetor 1) e  o produto interno calculado (última linha).
A de conc.c é o produto interno concorrente e erro relativo.
