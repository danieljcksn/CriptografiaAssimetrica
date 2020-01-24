#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

// - - - - P R O T Ó T I P O S - - - - // 
bool verificaPrimo(int p1);
int mdc(int n1,int n2);
int mdc(int n1,int n2);
int criptografa(int n, int e, int caractere);


//Verifica se um número dado (p1) é primo ou não.
bool verificaPrimo(int p1){
	int i;

	for(i = 2; i< p1; i++){
		if(p1 % i == 0)
			return false;	
	}

	return true;
}


//Calcula o MDC entre dois números (n1 e n2).
int mdc(int n1,int n2){
    if(n1>n2){  // Condições para se calcular o MDC usando o algoritmo de Euclides
	    if(n1%n2!=0){
	        int resto = n1%n2; // Procedimento
	        mdc(n2,resto);
	    }else
	        return n2; // Se o resto é 0, então o programa retorna o n2
	}else{
        if(n2%n1!=0){  // Mesmo procedimento, para quando n2 é maior que n1
            int resto = n2%n1;
            mdc(n1,resto);
        }else
            return n1;
	}
}


//Encontra o valor de 'e'. 'e' deve ser co-primo em relação a Phi(n) e também 1 < e < Phi(n)
int coPrimo(int phi){
	int n, result;
	/*
	srand(time(NULL)) objetiva inicializar o gerador de números aleatórios
	com o valor da função time(NULL). Este por sua vez, é calculado
	como sendo o total de segundos passados desde 1 de janeiro de 1970
	até a data atual.
	Desta forma, a cada execução o valor da "semente" será diferente.
	*/
	srand(time(NULL));

	n = rand() % (phi-1);
	result = mdc(phi, n);

	while(result != 1){
		n = rand() % phi;
		result = mdc(phi, n);
	}
	return n;
}

//A partir de uma chave pública, composta por 'n' e 'e', realiza a criptografia.
//int criptografa(int n, int e, int caractere){

//	return 
//}

// - - - - M A I N - - - - - // 
int main(void){
	int p1, p2, n, phi, e, i, contador, iteracoes = 0;
	char linha[50], c, linha2[50], nomeSaida[5] = "1.txt";
	FILE *arquivo, *arq, saida;

	printf("Você precisa realizar a inserção de dois números primos:\n");
	
	printf("Insira o primeiro número primo!\n");
	scanf("%d", &p1);

	//Garantindo que os números inseridos são números primos.
	while(!verificaPrimo(p1)){
		printf("O número inserido não é primo. Tente novamente!\n");
		printf("Novo número: ");
		scanf("%d", &p1);
		if(verificaPrimo(p1))
			break;
	}

	printf("Insira o segundo número primo!\n");
	scanf("%d", &p2);

	while(!verificaPrimo(p2)){
		printf("O número inserido não é primo. Tente novamente!\n");
		printf("Novo número: ");
		scanf("%d", &p2);
		if(verificaPrimo(p2))
			break;
	}

	//Limpando a tela
	printf("\e[H\e[2J");

	//Calculando 'n'
	n = p1 * p2;

	/* A função Phi(n) retorna a quantidade de números inferiores ou iguais a n
	que são Co-Primos com respeito a ele. Phi(n) = Phi(p1) * Phi(p2)
	Como p1 e p2 são primos, phi é (p1 - 1) * (p2 - 1) */

	phi = (p1-1) * (p2-1);	

	/* Definindo um número aleatório 'e'. Deve satisfazer as condições: ser maior que 1 e menor que Phi(n), também deve ser primo entre Phi(n).
	Ou seja, mdc(phi(n), e) deve ser 1, para 1 < e < Phi(n). */

	e = coPrimo(phi);

	arquivo = fopen("conjunto.txt", "r");
	while(fgets(linha, sizeof(linha), arquivo) != NULL){
		iteracoes++;
		contador = 0;
		//Verifica o tamanho da string antes da quebra de linha (\n)
		for(i = 0; i < sizeof(linha); i++){
			contador++;
			if(linha[i] == 10){
				contador -= 1;
				break;
			}
		}

		//Criando uma string com o exato tamanho do endereço do arq
		char line[contador];

		//Copia o endereço para uma variável com tamanho adequado.
		for(i = 0; i < contador; i++)
			line[i] = linha[i];
		
		/*Para solucionar um problema com o armazenamento do primeiro endereço (a.txt), o qual
		trazia anteriormente consigo lixo da memória na última posição da string.*/
		if(iteracoes == 1){
		//caso seja a primeira iteração, ou seja, primeiro endereço lido
			line[i] = '\0';
			//atribui nulo ao último caractere, eliminando-o.
		}

		//Só pra verificar se os arquivos estão sendo lidos corretamente.
		printf("\n- - - - - - -\nArquivo [%s]\n", line);
		//Abrindo os arquivos .txt a partir do endereço obtido.
		arq = fopen(line, "r");

		//Verificando se o arq foi aberto corretamente.
		if(arq == NULL)
			printf("Erro na abertura de arquivo.\n");
		else{
			//Lendo o arquivo, caractere por caractere.
			c = fgetc(arq);
			while(c != EOF){
				printf("%c", c);
				c = fgetc(arq);
			}
		}
		fclose(arq);
	}
	fclose(arquivo);


	
	//criptografa(n, e, )
	return 0;
}