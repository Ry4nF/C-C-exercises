#include <stdio.h>
#include <math.h>

#define MAX_VERTICES 99

void defVetor(int n, float vx[], float vy[]){
    for(int i=0;i<n;i++){
        vx[i]= rand()%10;
        vy[i]= rand()%10;
    }
}

void mostraVetor(int n,float vx[], float vy[]){
    for(int i=0; i<n;i++){
        printf("(%6.2f, %6.2f)", vx[i], vy[i]);
    }
}

float prodVetor(float ax, float ay, float bx, float by){
	return(ax*bx + ay*by);
}

geraPoliRegular(int n, float vx[], float vy[], float va[]){

    float ccx=0.0, ccy=0.0, cosAng, normaB, arcos;
	float ax = 1.0f; float ay = 0.0f; 


    for(int i=0;i<n;i++){
        ccx += vx[i];
        ccy += vy[i];
    }
    ccx /= n;
    ccy /= n;

    
    for(int i=0;i<n;i++){
        vx[i] -= ccx;
        vy[i] -= ccy;
    }


    for(int i=0; i<n; i++) {
		cosAng = prodVetor(ax, ay, vx[i], vy[i]);
        normaB = prodVetor(vx[i], vy[i], vx[i], vy[i]);
        normaB = sqrt(normaB);
        cosAng /= normaB; 
        arcos = acos(cosAng); 
        arcos = arcos * 180/M_PI; // M_PI: valor de pi, definido pela lib math.h
        if(vy[i] < 0.0f) arcos = 360 - arcos; 
        va[i] = arcos;
    }
}


void mostraAngulo(int n, float va[]){
	for(int i=0; i<n; i++){
		printf(" %6.2f ", va[i]);
	}	
}

//Bubble sort
void ordenaAngulos(int n, float vx[], float vy[], float va[]) {
    int i, j;
    float auxAng, auxX, auxY;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (va[j] > va[j + 1]) {
            
                auxAng = va[j];
                va[j] = va[j + 1];
                va[j + 1] = auxAng;
                
            
                auxX = vx[j];
                vx[j] = vx[j + 1];
                vx[j + 1] = auxX;

                auxY = vy[j];
                vy[j] = vy[j + 1];
                vy[j + 1] = auxY;
            }
        }
    }
}


void converteVetorPolig(int n, float vx[], float vy[], float vvx[], float vvy[]){
    for(int i=0;i<n;i++){
        vvx[i] = vx[(i+1)%n] - vx[i];
        vvy[i] = vy[(i+1)%n] - vy[i];
        i++;
    }

}


int convexo (int i, int j, float a[], float b[]){
	int w;
	w = a[i]*b[j] - a[j]*b[i];
	return w;	
}


void AnaliseConvesidade (int n, float vvx[], float vvy[]) {
	int i = 0, w;
	while (i<n) {
		w = convexo(i, (i+1)%n, vvx, vvy);
		if(w<0)
			printf("\n vertice %d is concavo \n", i);
		else
			printf("\n Vertice %d is convexo \n", i);
		i++;
	}
}

int main(){

    int n;
	float area, vx[MAX_VERTICES], vy[MAX_VERTICES], vvx[MAX_VERTICES], vvy[MAX_VERTICES], va[MAX_VERTICES];

	system("cls");

    do{
    printf("Digite o valor de n: \n");
    scanf("%d", &n);
    if(n<=2) printf("\n Valor invalido. \n");
    }while(n<=2);


    defVetor(n, vx, vy);
    printf("\n Vertices do poligono: \n");
    mostraVetor(n, vx, vy);

    
    geraPoliRegular(n, vx, vy, va);
    printf("\n\n Vertices do poligono REGULAR: \n");
	mostraVetor(n, vx, vy);

    
    printf("\n\n Angulos: \n");
    mostraAngulo(n, va);
	ordenaAngulos(n, vx, vy, va); 

    
	converteVetorPolig(n, vx, vy, vvx, vvy);
    printf("\n\n Angulos (pos ordenacao): \n");
	mostraAngulo(n, va);
	printf("\n\n Arestas do poligono: \n");
	mostraVetor(n, vvx, vvy);

    
    printf("\n\n Analise de convexidade: \n");
    AnaliseConvesidade(n, vvx, vvy);

    return 0;
}