//faz fatoração LU de uma matriz e armazena em um arquivo binario
#include <stdio.h>
#include <stdlib.h>

//prototipo de funções
void menu();
float alocaMatriz();
int imprime();
float fatora();

//funcao principal
int main(){
	menu();
}
//fim funcao principal

//funcao menu
void menu(){
	alocaMatriz();	
	imprime();
}
//fim funcao menu


float alocaMatriz(){
	int m;	//numero de linhas da matriz
	int n;  //numero de colunas da matriz
	int i,j;
	int k,aux;
  	float t;
  	float **p;
	float **temp; //indice usado para alocar a matriz com a funcao malloc
	FILE *matrizFatorada,*matrizOriginal,*linha,*coluna;
	matrizOriginal=fopen("matrizOriginal.bin","wb");
	matrizFatorada = fopen("matrizFatorada.bin","wb");
	linha=fopen("linha.bin","wb");
	coluna=fopen("coluna.bin","wb");
	printf("Digite o numero de linhas da matriz:");
	scanf("%d",&m);
	printf("Digite o numero de colunas da matriz:");
	scanf("%d",&n);
	__fpurge(stdin);

	//aloca a matriz
	p = malloc(m * sizeof(float *));
	temp = malloc(m * sizeof(float *));
	for (i=0;i<m;i++){
		p[i]=malloc(n * sizeof(float));
		temp[i] = malloc(n * sizeof(float));
	}	

	//adiciona dados do usuário a matriz
	for (i=0;i<m;i++){
		for (j=0;j<n;j++){
			printf("%d%d:",i,j);
			scanf("%f",&t);
			temp[i][j]=t;
			p[i][j]=t;
		}
	}

	//grava nmatriz original e um arquivo
	fwrite(&temp,sizeof(float),1,matrizOriginal);
	fclose(matrizOriginal);
	
	//fatora matriz em LU
	t=0;
   for (i=0;i<m;i++){
     k=i+1;
     while (k<m){
    if (p[i][i] == 0 && p[k][i] !=0){
        for (j=0;j<m;j++){
            aux=p[i][j];
            p[i][j]=p[k][j];
            p[k][j]=aux;
            }
        }
        if (p[i][i] !=0 && p[k][i] !=0){
             t=p[k][i]/p[i][i];
             for (j=0;j<m;j++){
                 p[k][j]=p[k][j] -t*p[i][j];
                 }
            }
    k++;
  }
 }


	fwrite(&p,sizeof(float),1,matrizFatorada);
	fwrite(&m,sizeof(int),1,linha);
	fwrite(&n,sizeof(int),1,coluna);

	fclose(matrizFatorada);

	/*
	//desaloca matriz p
	for (i=0;i<m;i++){
		free(p[m-i]);
	}	
	free(p);
	
	//desaloca matriz temp
	for (i=0;i<m;i++){
		free(temp[m-i]);
	}	
	free(temp);
	*/
	fclose(linha);
	fclose(coluna);
	
}

//função imprime matriz
int imprime(){
	float **mt,**tmp;
	int i,j,m,n;
	FILE *matrizFatorada,*matrizOriginal,*linha,*coluna;
	matrizOriginal = fopen("matrizOriginal.bin","rb");
	matrizFatorada = fopen("matrizFatorada.bin","rb");
	linha=fopen("linha.bin","rb");
	coluna=fopen("coluna.bin","rb");
	if(matrizFatorada == NULL){
		return 0;
	}

	if(linha == NULL){
		return 0;
	}

	if (coluna == NULL){
		return 0;
	}

	fread(&m,sizeof(int),1,linha); //le quantidade de linhas da matriz
	fread(&n,sizeof(int),1,coluna); //le quantidade de colunas da matriz


	fread(&tmp,sizeof(float),1,matrizOriginal); //abre arquivo da matriz original
	printf("Imprime matriz Original\n");
	for (i=0;i<m;i++){
		for (j=0;j<n;j++){
			printf("%f ",tmp[i][j]);
		}
		printf("\n");
	}
	fclose(matrizOriginal); //fecha arquivo com matriz original

	fread(&mt,sizeof(float),1,matrizFatorada); //abre arquivo com matiz fatorada
	printf("Imprime matriz fatorada\n");
	for (i=0;i<m;i++){
		for (j=0;j<n;j++){
			printf("%f ",mt[i][j]);
		}
		printf("\n");
	}
	fclose(matrizFatorada);

	//desaloca matgriz mt e temp
	for (i=0;i<m;i++){
		free(mt[m-i]);
		free(tmp[m-i]);
	}	
	free(mt);
	free(tmp);

	fclose(linha);
	fclose(coluna);
}

