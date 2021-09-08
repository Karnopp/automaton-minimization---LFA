#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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
	FILE * input;

	int n_estados,i,j,k;

	input = fopen("aut_original.txt" , "r");//leitura de arquivo;
	if(input == NULL)
		printf("Erro, nao foi possivel abrir o arquivo\n");
	int estado_inicial=0, n_estados_finais=0, n_alfa=0;
	char temp;
	int movimentos = 0;

	rewind(input);//retorna para o inicio do arquivo

	fscanf(input, "%i" , &estado_inicial);//estado inicial
	fscanf(input, "%i" , &n_estados);

	int estadospossiveis[n_estados+1];//+1 pois talvez nao seja automato total

	for(i=0; i<n_estados; i++){
		fscanf(input, " %i" , &estadospossiveis[i]);//observar os usos de espaços no " %i"
	}

	fscanf(input, "%i", &n_estados_finais);
	int finais[n_estados_finais];
	for(i=0; i<n_estados_finais; i++){
		fscanf(input, " %i", &finais[i]);
	}

	fscanf(input, "%i" ,&n_alfa);
	char alfabeto[n_alfa];
	for(i=0;i<n_alfa;i++){
		fscanf(input, " %c", &alfabeto[i]);
	}

	fscanf(input, "%i" , &movimentos);
	////verificando se é total ==> ou seja, todos os estados tem produção para cada elemento do alfabeto
	bool total=true;
	if(movimentos!=(2*n_estados)){
		n_estados=n_estados+1;//adicionando novo estado armadilha(trap)
		estadospossiveis[n_estados-1]=n_estados-1;
		total=false;
	}
	int mat[n_estados][n_alfa];
	for(i=0; i<n_estados;i++){//preenchiento da matriz com -1;
		for(j=0; j<n_alfa; j++){
			mat[i][j]=-1;
		}
	}
	int indice=0, aponta=0;
	char letrinha;
	for(k=0; k<movimentos;k++){
		i=0;
		fscanf(input, " %i %c %i" , &indice, &letrinha, &aponta);//leitura das transições
		while(letrinha!=alfabeto[i++]);//ira procurar todos os elementos do alfabeto para ver se o elemneto existe
		i--;//contador
		mat[indice][i]=aponta;//indice = estado atual, i = letra lida, aponta = estado atingido
	}
	if(total==false){
		printf("Automato nao total, -1 nao ha transicao\n");
		printf(" q  ");
		for(i=0;i<n_alfa;i++)
			printf(" %c ",alfabeto[i]);
		printf("\n");
		for(i=0; i<n_estados-1;i++){
			printf(" %i |",i);
			for(j=0; j<n_alfa; j++){
				if(mat[i][j]==-1)
		  		printf("%i ",mat[i][j]);
		    else
					printf(" %i ",mat[i][j]);
		  }
		  printf("\n");
		}
		printf("\n");
	}
	for(i=0; i<n_estados;i++){
		for(j=0; j<n_alfa; j++){
			if(mat[i][j]==-1)
				mat[i][j]=n_estados-1;//criando prodção para estados sem produção indo para o estado trap
		}
	}
	if(total==false)
		printf("adicionado novo estado 'trap'\n");
	printf(" q  ");
	for(i=0;i<n_alfa;i++)
		printf(" %c ",alfabeto[i]);
	printf("\n");
	for(i=0; i<n_estados;i++){
		printf(" %i |",i);
		for(j=0; j<n_alfa; j++){
			printf(" %i ",mat[i][j]);
	  }
	  printf("\n");
	}
	printf("\n");

	//criando tabela inicial de estados não equivalentes
	char m[n_estados-1][n_estados-1];
	int cont=0,z, aux1=0, aux2=0;

	for(i=0; i<n_estados-1;i++){
		for(j=0; j<n_estados-1; j++){
			m[i][j]='O';
		}
	}

	for(i=0; i<n_estados-1; i++){
		for(j=0; j<=n_estados-1; j++){
			if(i>=j){
				for(k=0; k<n_estados_finais; k++){
					if(i+1==finais[k])
						aux1=1;
					if(j==finais[k])
						aux2=1;
				}
				if(aux1!=aux2)
					m[i][j]='X';
			}
			aux1=0;
			aux2=0;
		}
	}
	/////////////printando a tabela de estados nao equivalentes:
	printf("###########################################################\n");
	printf("Marcando estados nao equivalentes:\n");
	printf(" q  ");

	printf("\n");
	for(i=0; i<n_estados-1;i++){
		printf(" %i |",i+1);
		for(j=0; j<n_estados-1; j++)
		{
			if(i>=j)
				printf(" %c ",m[i][j]);
	  }
	  printf("\n");
	}
	printf(" q ");
	for(i=0;i<n_estados-1;i++){
		printf("  %i",i);
	}
	////////////////////// calculando as marcações +
	int tmp;
	for(j=0; j<=n_estados-1; j++){
		for(i=0; i<n_estados-1; i++){
			if(i>=j){
				if(m[i][j]=='O'){
					for(k=0;k<n_alfa;k++){
						if(mat[i+1][k]!=mat[j][k]){
							aux1=mat[i+1][k];
							aux2=mat[j][k];
							if(aux2>aux1){
								tmp=aux1;
								aux1=aux2;
								aux2=tmp;
							}
							if(m[aux1-1][aux2]=='X'){
								m[i][j]='+';
							}
							if(m[aux1-1][aux2]=='O'){
								m[i][j]='?';
							}
							if(m[aux1-1][aux2]=='+'){
								m[i][j]='+';
							}
							if(m[aux1-1][aux2]=='?'){
								m[i][j]='?';
							}

						}
					}
				}
				if(m[i][j]=='?'){
					for(k=0;k<n_alfa;k++){
						if(mat[i+1][k]!=mat[j][k]){
							aux1=mat[i+1][k];
							aux2=mat[j][k];
							if(aux2>aux1){
								tmp=aux1;
								aux1=aux2;
								aux2=tmp;
							}
							if(m[aux1-1][aux2]=='X'){
								m[i][j]='+';
							}

						}
					}
				}
			}
			aux1=0;
			aux2=0;
		}
	}
	/////////
	printf("\n\n");
	for(i=0; i<n_estados-1;i++){
		printf(" %i |",i+1);
		for(j=0; j<n_estados-1; j++)
		{
			if(i>=j)
				printf(" %c ",m[i][j]);
	  }
	  printf("\n");
	}
	printf(" q ");
	for(i=0;i<n_estados-1;i++){
		printf("  %i",i);
	}
	/////////
	for(j=0; j<=n_estados-1; j++){
		for(i=0; i<n_estados-1; i++){
			if(i>=j){
				if(m[i][j]=='O'||m[i][j]=='?'){
					for(k=0;k<n_alfa;k++){
						if(mat[i+1][k]!=mat[j][k]){
							aux1=mat[i+1][k];
							aux2=mat[j][k];
							if(aux2>aux1){
								tmp=aux1;
								aux1=aux2;
								aux2=tmp;
							}
							if(m[aux1-1][aux2]=='X'){
								m[i][j]='+';
								//printf("\n%i %i => %i %i\n",i+1,j,aux1,aux2);
							}
							if(m[aux1-1][aux2]=='+'){
								m[i][j]='+';
								//printf("\n%i %i => %i %i\n",i+1,j,aux1,aux2);
							}
						}
					}
				}
			}
			aux1=0;
			aux2=0;
		}
	}


	////////printando nova tabela (final)
	printf("\n\n q  ");

	printf("\n");
	for(i=0; i<n_estados-1;i++){
		printf(" %i |",i+1);
		for(j=0; j<n_estados-1; j++)
		{
			if(i>=j)
				printf(" %c ",m[i][j]);
	  }
	  printf("\n");
	}
	printf(" q ");
	for(i=0;i<n_estados-1;i++){
		printf("  %i",i);
	}
	printf("\n###########################################################");
	//////////
	int cont1=0,cont2=n_estados;
	for(i=0; i<n_estados-1;i++){
		for(j=0; j<n_estados-1; j++){
			if((m[i][j]=='O'||m[i][j]=='?') && i>=j){
				cont1++;
			}
		}
	}
	int novos_estados[cont1];
	for(i=0; i<cont1;i++){
		novos_estados[i]=cont2;
		cont2++;
	}
	int cont3=0, estados_minimizados[cont1][2];
	for(i=0; i<n_estados-1;i++){
		for(j=0; j<n_estados-1; j++){
			if((m[i][j]=='O'||m[i][j]=='?') && i>=j){
				estados_minimizados[cont3][0]=j;
				estados_minimizados[cont3][1]=i+1;
				cont3++;
			}
		}
	}
	for(i=0; i<cont3;i++){
		//printf("\n:%i %i:\n",estados_minimizados[i][0],estados_minimizados[i][1]);////////////////////////////////////////////TEST ONLY
	}
	for(z=0;z<cont3;z++){
		if(estados_minimizados[z][0]==estado_inicial || estados_minimizados[z][1]==estado_inicial)
			printf("\nEstado %i refere-se a minimizacao dos estados %i e %i e eh inicial",novos_estados[z], estados_minimizados[z][0], estados_minimizados[z][1]);
		else
			printf("\nEstado %i refere-se a minimizacao dos estados %i e %i",novos_estados[z], estados_minimizados[z][0], estados_minimizados[z][1]);
	}
	FILE * output;
	output = fopen("aut_minimizado.txt" , "w");
	if(output == NULL)
		printf("Erro, nao foi possivel abrir o arquivo\n");
	fprintf(output,"%i\n",estado_inicial);
	for(z=0;z<cont3;z++){
		if(estado_inicial==estados_minimizados[z][0]){
			rewind(output);
			fprintf(output,"%i\n",novos_estados[z]);
		}
		if(estado_inicial==estados_minimizados[z][1]){
			rewind(output);
			fprintf(output,"%i\n",novos_estados[z]);
		}
	}
	bool prosseguir=true;
	int aux3=-1;
	fprintf(output,"%i ",n_estados-cont3);
	for(i=0;i<n_estados;i++){
		for(j=0;j<cont3;j++){
			if((estadospossiveis[i]==estados_minimizados[j][0]) || (estadospossiveis[i]==estados_minimizados[j][1])){
				if(j!=aux3){
					fprintf(output,"%i ",novos_estados[j]);
					aux3=j;
				}
				prosseguir=false;
			}
		}
		if(prosseguir==true){
			fprintf(output,"%i ",estadospossiveis[i]);
		}
		prosseguir=true;
	}
	fprintf(output,"\n");
	int n_estados_finais_minimizados=0;
	for(j=0;j<cont3;j++){
		for(i=0;i<n_estados_finais;i++){
			if(finais[i]==estados_minimizados[j][0] && prosseguir==true){
				for(k=0;k<n_estados_finais;k++){
					if(finais[k]==estados_minimizados[j][1]){
						n_estados_finais_minimizados++;
						prosseguir=false;
					}
				}
			}
			if(finais[i]==estados_minimizados[j][1] && prosseguir==true){
				for(k=0;k<n_estados_finais;k++){
					if(finais[k]==estados_minimizados[j][0]){
						n_estados_finais_minimizados++;
						prosseguir=false;
					}
				}
			}
			if(prosseguir==true && (finais[i]==estados_minimizados[j][1]||finais[i]==estados_minimizados[j][0])){
				n_estados_finais_minimizados++;
			}
		}
	}

	fprintf(output,"%i ",n_estados_finais - n_estados_finais_minimizados);
	for(i=0;i<n_estados_finais - n_estados_finais_minimizados;i++){
		if(finais[i]==estados_minimizados[i][0] || finais[i]==estados_minimizados[i][1]){
			fprintf(output,"%i ",novos_estados[i]);
		}
		else{
			fprintf(output,"%i ",finais[i]);
		}
	}
	fprintf(output,"\n");
	fprintf(output,"%i ",n_alfa);
	for(i=0;i<n_alfa;i++){
		fprintf(output,"%c ",alfabeto[i]);
	}

	fprintf(output,"\n%i\n",(n_estados-cont3)*2);

	int cont4=0;
	prosseguir=true;
	printf("\n\n q  ");
	for(i=0;i<n_alfa;i++)
		printf(" %c ",alfabeto[i]);
	printf("\n");

	int estados_nao_minimizados[n_estados-cont3];
	prosseguir=true;
	for(i=0;i<n_estados;i++){
		for(k=0;k<cont3;k++){
			if(i==estados_minimizados[k][0]||i==estados_minimizados[k][1]){
				prosseguir=false;

			}
		}
		if(prosseguir==true){
			estados_nao_minimizados[cont4]=i;
			cont4++;
		}
		prosseguir=true;
	}
	for(i=0;i<cont4;i++){
		printf(" %i |",estados_nao_minimizados[i]);
		for(j=0;j<n_alfa;j++){
			for(k=0;k<cont3;k++){
				if(mat[estados_nao_minimizados[i]][j]==estados_minimizados[k][0]||mat[estados_nao_minimizados[i]][j]==estados_minimizados[k][1]){
					printf(" %i ",novos_estados[k]);
					fprintf(output,"%i %c %i\n",estados_nao_minimizados[i],alfabeto[j],novos_estados[k]);
					prosseguir=false;
				}
			}
			if(prosseguir==true){
				printf(" %i ",mat[estados_nao_minimizados[i]][j]);
				fprintf(output,"%i %c %i \n",estados_nao_minimizados[i],alfabeto[j],mat[estados_nao_minimizados[i]][j]);
			}
			prosseguir=true;
		}
		printf("\n");
	}
	for(i=0;i<cont3;i++){
		printf("*%i |",novos_estados[i]);
		for(j=0;j<n_alfa;j++){
			for(k=0;k<cont3;k++){
				if(mat[estados_minimizados[i][0]][j]==estados_minimizados[k][0]||mat[estados_minimizados[i][1]][j]==estados_minimizados[k][1]||
				mat[estados_minimizados[i][1]][j]==estados_minimizados[k][0]||mat[estados_minimizados[i][0]][j]==estados_minimizados[k][1]){
					printf(" %i ",novos_estados[k]);
					fprintf(output,"%i %c %i \n",novos_estados[i],alfabeto[j],novos_estados[k]);
					prosseguir=false;
				}
			}
			if(prosseguir==true){
				printf(" %i ",mat[estados_minimizados[i][0]][j]);
				fprintf(output,"%i %c %i \n",novos_estados[i],alfabeto[j],mat[estados_minimizados[i][0]][j]);
			}
			prosseguir=true;
		}
		printf("\n");
	}

	fclose(input);
	fclose(output);

}
