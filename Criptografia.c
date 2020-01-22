#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <stdbool.h>

bool verificaPrimo(int p1){
	int i;

	for(i = 2; i< p1; i++){
		if(p1 % i == 0)
			return false;	
	}

	return true;
}

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


int coPrimo(int phi){
	int n, result;
	n = rand() % phi;
	result = mdc(phi, n);

	while(result != 1){
		n = rand() % phi;
		result = mdc(phi, n);
		printf("%d", n);
	}
	printf("%d", n);
	return n;

}

int main(void){
	int p1, p2, n, phi, e, i, contador;
	char linha[50], c, linha2[50];
	FILE *arquivo, *arq;
	/*
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
	*/
	arquivo = fopen("conjunto.txt", "r");
	while(fgets(linha, sizeof(linha), arquivo) != NULL){
		contador = 0;
		//Verifica o tamanho da string antes da quebra de linha (\n)
		for(i = 0; i < sizeof(linha); i++){
			if(linha[i] == 10)
				break;
			contador++;
		}

		//Criando uma string com o exato tamanho do endereço do arquivo
		char line[contador];

		//Copiando para este o endereço do arquivo em questão
		for(i = 0; i < contador; i++)
			line[i] = linha[i];
		
		printf("%s", line);
		arq = fopen(line, "r");
		//if(arq == NULL){
		//	printf("Erro\n");
		//}

	}

	fclose(arquivo);


	//n = p1 * p2;
	//phi = (p1-1) * (p2-1);	
	//e = coPrimo(phi);
	return 0;
}