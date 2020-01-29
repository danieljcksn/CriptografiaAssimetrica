/* 
Trabalho feito por Breno Vitório, Daniel Jackson e Leonardo Damasceno, para a disciplina
de ORI (Organização e Recuperação da Informação), ministrada pelo professor Elinaldo Júnior.
*/



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
unsigned long long int potencia(int base, int expoente);
int criptografaChavePublica(int n, int e, int caractere);
int chavePrivada(int phi, int e);
int descriptografaChavePrivada(int valorCriptografado, int d, int n);



//Verifica se um número dado (p1) é primo ou não.
bool verificaPrimo(int p1){
	int i;

	if(p1 < 1)
		return false;

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
	int e, result;
	/*
	srand(time(NULL)) objetiva inicializar o gerador de números aleatórios
	com o valor da função time(NULL). Este por sua vez, é calculado
	como sendo o total de segundos passados desde 1 de janeiro de 1970
	até a data atual.
	Desta forma, a cada execução o valor da "semente" será diferente.
	*/
	srand(time(NULL));

	e = rand() % (phi-1);
	result = mdc(phi, e);

	while(result != 1 || e < 2){
		e = rand() % (phi-1);
		result = mdc(phi, e);
	}
	return e;
}


//Função para calcular a potência, pois a função pow da biblio math.h não estava funcionando nesse caso.
unsigned long long int potencia(int base, int expoente){
	if(expoente == 0)
		return 1;
	else
		return (base * potencia(base, expoente-1));
}


//A partir de uma chave pública, composta por 'n' e 'e', realiza a criptografia.
int criptografaChavePublica(int n, int e, int caractere){
	//Capaz de armazenar um número de até 19 dígitos.
	unsigned long long int resultadoPot;
	int valorCriptografado;
	resultadoPot = potencia(caractere, e);
	valorCriptografado = resultadoPot % n;
	return valorCriptografado; 
}


//Determina a chave privada responsável por decifrar a mensagem.
int chavePrivada(int phi, int e){
	int d = 1, produto;
	printf("Entrou");
	//A chave privada é chamada de D e é encontrada seguindo o algoritmo:
	//D * E mod Phi(N) == 1
	produto = d * e;
	while(produto % phi != 1){
		d++;
		produto = d * e;
	}
	//d é a chave privada.
	return d;
}


//Retorna o valor ASCII do caractere original, a partir da chave privada.
int descriptografaChavePrivada(int valorCriptografado, int d, int n){
	unsigned long long int resultadoPot;
	int valorDescriptografado;

	//Usaremos o D para descriptografar a Mensagem cifrada, 
	//para cada número da mensagem, iremos elevalo por D e fazer a operação modular por N, 
	//então teremos o valor ASCII original.
	resultadoPot = potencia(valorCriptografado, d);
	valorDescriptografado = resultadoPot % n;

	return valorDescriptografado;
}

// - - - - M A I N - - - - - // 
int main(void){
	int p1, p2, n, phi, e, d, i, contador, counter, iteracoes = 0, codAscii = 97, valorCriptografado, valorDescriptografado, numArqs = 0, escolha;
	char linha[50], c, c1[10], arqSaida[11] = "__Crip.txt", arqOrig[15] = "__Original.txt";
	FILE *arquivo, *arq, *saida, *indexSaida;

	//Limpando a tela
	printf("\e[H\e[2J");

	printf("Digite o endereço dos arquivos de texto que deseja criptografar em 'conjunto.txt'! =)\n........................................................\n");
	printf("Você precisa realizar a inserção de dois números primos:\n");
	
	printf("Insira o primeiro número primo: ");
	scanf("%d", &p1);

	//Garantindo que os números inseridos são números primos.
	while(!verificaPrimo(p1)){
		printf("O número inserido não é primo. Tente novamente!\n");
		printf("Novo número: ");
		scanf("%d", &p1);
		if(verificaPrimo(p1))
			break;
	}

	printf("Insira o segundo número primo: ");
	scanf("%d", &p2);

	while(!verificaPrimo(p2)){
		printf("O número inserido não é primo. Tente novamente!\n");
		printf("Novo número: ");
		scanf("%d", &p2);
		if(verificaPrimo(p2))
			break;
	}

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

	printf("Sua chave pública é [%d, %d]\n", n, e);
	indexSaida = fopen("conjuntoCriptografado.txt", "w");
	arquivo = fopen("conjunto.txt", "r");


	printf("\n........ Conteúdo dos Arquivos ........\n");
	while(fgets(linha, sizeof(linha), arquivo) != NULL){
		iteracoes++;
		numArqs++;

		//Variando o nome do arquivo de saída (criptografado).
		arqSaida[0] = codAscii;
		codAscii++;

		//Cria um conjunto com os endereços dos arquivos de saída.
		fprintf(indexSaida, "%s", arqSaida);
		fprintf(indexSaida, "\n");		


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
		
		//caso seja a primeira iteração, ou seja, caso seja o primeiro endereço de arquivo lido.
		if(iteracoes == 1){
			line[i] = '\0';
			//atribui nulo ao último caractere, eliminando-o e corrigindo o problema.
		}

		//O uso de \e[1m%s\e[m é para tornar o nome do arquivo negrito.
		printf("- - - - - -\nArquivo \e[1m%s\e[m:\n", line);
		//Abrindo os arquivos .txt a partir do endereço obtido.
		arq = fopen(line, "r");
		//Verificando se o arq foi aberto corretamente.
		if(arq == NULL)
			printf("Erro na abertura de arquivo.\n");
		else{
			//Lendo o arquivo, caractere por caractere.
			c = fgetc(arq);

			//Cria o arquivo de saída.
			saida = fopen(arqSaida, "w");
			while(c != EOF){
				valorCriptografado = criptografaChavePublica(n, e, c);
				fprintf(saida, "%d", valorCriptografado);
				fprintf(saida, "\n");
				printf("%c", c);
				c = fgetc(arq);
			}
			printf("\n");
			fclose(saida);
		}
		remove(line);
		fclose(arq);
	}
	fclose(arquivo);
	fclose(indexSaida);
	printf("\n.......................................\nCriptografia realizada com sucesso. Os arquivos originais foram deletados.\n\n");


	printf("\nDeseja descriptografar os arquivos?\n1 - Sim\n2 - Não\nSua resposta: ");
	scanf("%d", &escolha);

	if(escolha == 1){

		//Descriptografando os arquivos.
		d = chavePrivada(phi, e);
		printf("Sua chave privada é [%d]\n", d);
		iteracoes = 0;
		numArqs = 0;
		codAscii = 97;
		arquivo = fopen("conjuntoCriptografado.txt", "r");

		while(fgets(linha, sizeof(linha), arquivo) != NULL){
			counter = 0;
			iteracoes++;
			numArqs++;
			//Garante que os nomes dos arquivos de saída serão modificados (a.txt, b.txt, c.txt, ...)
			arqOrig[0] = codAscii;
			codAscii++;
			

			//Abrindo o arquivo no qual serão salvos os caracteres originais.
			saida = fopen(arqOrig, "w");

			//Verifica o tamanho da string antes da quebra de linha (\n)
			for(i = 0; i < sizeof(linha); i++){
				counter++;
				if(linha[i] == 10){
					counter -= 1;
					break;
				}
			}		

			//Foi necessário definir o tamanho como 11, pois colocando um contador erros estavam ocorrendo.
			char line[11];

			for(i = 0; i < counter; i++)
				line[i] = linha[i];		

			if(iteracoes == 1){
				line[i] = '\0';
				//atribui nulo ao último caractere, eliminando-o e corrigindo o problema.
			}

			arq = fopen(line, "r");
			//Verificando se o arq foi aberto corretamente.
			if(arq == NULL)
				printf("Erro na abertura de arquivo.\n");
			else{
				while(fgets(c1, sizeof(c1), arq) != NULL){
					//Convertendo a 'string' do arquivo em um número, para que seja possível realizar as operações.
					valorCriptografado = atoi(c1);
					valorDescriptografado = descriptografaChavePrivada(valorCriptografado, d, n);
					fprintf(saida, "%c", valorDescriptografado);
				}
				printf("\n");
			}
			printf("Valores:\nD = %d\nE = %d\nPhi(n) = %d\nN = %d\n", d, e, phi, n);
			//remove(line);
			fclose(arq);
		}
		fclose(arquivo);
		printf("\nOs arquivos foram descriptografados! =)\n");
	}

	return 0;
}