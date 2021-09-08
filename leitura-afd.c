#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
no arquivo:

estado_inicial
numero_estados estado_0 estado_1 estado_2 ...
numero_estados_finais estado_0 estado_1 estado_2 ...
tamanho_alfabeto simbolo_0 simbolo_1 simbolo_2 ...
numero_transicoes
estado_de_partida0 simbolo_lido0 estado_chegada0
estado_de_partida1 simbolo_lido1 estado_chegada1
.
.
.
ver aut_original.txt
*/
int main(){
	FILE * lfa_;
	
	int n_estados,i,j,k;
	
	lfa_ = fopen("aut_original.txt" , "r");//leitura de arquivo;

    int estadoatual=0, n_estados_finais=0, n_alfa=0;
    char temp;
    int movimentos = 0;

    rewind(lfa_);//retorna para o inicio do arquivo
    
    fscanf(lfa_, "%i" , &estadoatual);//estado inicial
    fscanf(lfa_, "%i" , &n_estados);

    int estadospossiveis[n_estados];

    for(i=0; i<n_estados; i++)
    {
    	fscanf(lfa_, " %i" , &estadospossiveis[i]);//observar os usos de espaços no " %i"
    }
    
    fscanf(lfa_, "%i", &n_estados_finais);
    int finais[n_estados_finais];
    for(i=0; i<n_estados_finais; i++)
    {
    	fscanf(lfa_, " %i", &finais[i]);
    }
    
    fscanf(lfa_, "%i" ,&n_alfa);
    char alfabeto[n_alfa];
    int mat[n_estados][n_alfa];
    for(i=0;i<n_alfa;i++)
    {
    	fscanf(lfa_, " %c", &alfabeto[i]);
    }
    
    fscanf(lfa_, "%i" , &movimentos);
    
    for(i=0; i<n_estados;i++)//preenchiento da matriz com -1;
    {
    	for(j=0; j<n_alfa; j++)
    	{
    		mat[i][j]=-1;
    	}
    }
	int esquerda[movimentos], direita[movimentos]; //esquerda estado de começo, direita = estado de chegada
    int indice=0, aponta=0;
    char letrinha;
    for(k=0; k<movimentos;k++)
    {
		i=0;
		fscanf(lfa_, " %i %c %i" , &indice, &letrinha, &aponta);//leitura das transições
		esquerda[k]=indice;
		direita[k]=aponta;
		while(letrinha!=alfabeto[i++]);//ira procurar todos os elementos do alfabeto para ver se o elemneto existe
		i--;//contador
		mat[indice][i]=aponta;//indice = estado atual, i = letra lida, aponta = estado atingido
    }
    printf(" q  ");
    for(i=0;i<n_alfa;i++)
    	printf(" %c ",alfabeto[i]);
    printf("\n");
    for(i=0; i<n_estados;i++)
    {
    	printf(" %i |",i);
    	for(j=0; j<n_alfa; j++)
    	{
    		if(mat[i][j]==-1)
      			printf("%i ",mat[i][j]);
        	else
				printf(" %i ",mat[i][j]);
      	}
      	printf("\n");
      	
    }
    printf("obs: -1 => significa que nao ha transicao naquele estado lendo aquela letra \n");
	
	
}
