#include <stdio.h>
#include <math.h>
#define MAX_GRAU 10


void lerPolinomio(double polinomio[], int *ponteiroGrau){

    int grau, i;
    zerarPolinomio(polinomio);

    printf("\nDigite o grau do polinomio (maximo %d): ", MAX_GRAU);
    scanf("%d", &grau);

    while (grau < 0 || grau > MAX_GRAU){

        printf("Grau invalido. Digite novamente (0 a %d): ", MAX_GRAU);
        scanf("%d", &grau);
    }

    *ponteiroGrau = grau;
    printf("Digite os coeficientes do termo x^%d ate o termo x^0:\n", grau);

    for (i = grau; i >= 0; i--){
    
        double coef;
        printf("Coeficiente de x^%d: ", i);
        scanf("%lf", &coef);
        polinomio[MAX_GRAU - i] = coef;
    }
}


int encontrarGrauPolinomio(const double polinomio[]){

    int i;
    for (i = 0; i <= MAX_GRAU; i++)
    {
        if (polinomio[i] != 0.0){
            return (MAX_GRAU - i);
        }
    }
    return 0;
}


 void zerarPolinomio(double polinomio[]){
     int i;
     for (i = 0; i <= MAX_GRAU; i++){
        polinomio[i] = 0.0;
     }
 }



void imprimirPolinomio(const double polinomio[], char nome){

    int i;
    int grau = encontrarGrauPolinomio(polinomio);
    printf("\n%c(x) = ", nome);

    {
        int ehNulo = 1;
        for (i = 0; i <= MAX_GRAU; i++)
        {
            if (polinomio[i] != 0.0)
            {
                ehNulo = 0;
                break;
            }
        }
        if (ehNulo)
        {
            printf("0\n");
            return;
        }
    }

    int primeiroTermo = 1;

    for (i = 0; i <= MAX_GRAU; i++){
    
        double coef = polinomio[i];
        if (coef != 0.0){
        
            int exp = MAX_GRAU - i;

            if (primeiroTermo){
            
                
                if (coef < 0){
                
                    printf("-");
                }
                primeiroTermo = 0;
            }
            else{
            
               
                if (coef < 0){
                
                    printf(" - ");
                }
                else{
                
                    printf(" + ");
                }
            }

            if (exp == 0){
            
                printf("%.2f", (coef < 0 ? -coef : coef));
            }

            else{
            
                if ( (coef == 1.0) || (coef == -1.0) ){
                
                    printf("x");
                }
                else{
                
                    printf("%.2fx", (coef < 0 ? -coef : coef));
                }

                if (exp != 1){
                
                    printf("^%d", exp);
                }
            }
        }
    }
    printf("\n");
}



double avaliarPolinomio(const double polinomio[], double x){

    double soma = 0.0;
    int i;
    for (i = 0; i <= MAX_GRAU; i++){
    
        if (polinomio[i] != 0.0){
        
            int exp = MAX_GRAU - i;
            soma += polinomio[i] * pow(x, exp);
        }
    }
    return soma;
}



void somarPolinomios(const double p1[], const double p2[],
                     double resultado[], int *ponteiroGrauDoResultado){

    int i;
    zerarPolinomio(resultado);

    for (i = 0; i <= MAX_GRAU; i++){
    
        resultado[i] = p1[i] + p2[i];
    }
    *ponteiroGrauDoResultado = encontrarGrauPolinomio(resultado);
}




void multiplicarPolinomios(const double p1[], const double p2[],
                           double resultado[], int *ponteiroGrauDoResultado){

    int i, j;
    zerarPolinomio(resultado);


    for (i = 0; i <= MAX_GRAU; i++){
    
        if (p1[i] != 0.0){
        
            for (j = 0; j <= MAX_GRAU; j++){
            
                if (p2[j] != 0.0){
                
                    int expP1 = (MAX_GRAU - i);
                    int expP2 = (MAX_GRAU - j);
                    int expR  = expP1 + expP2; 
                    if (expR <= MAX_GRAU){
                    
                        int indice = (MAX_GRAU - expR);
                        resultado[indice] += p1[i] * p2[j];
                    }
                }
            }
        }
    }

    *ponteiroGrauDoResultado = encontrarGrauPolinomio(resultado);
}



int main(){

    double polinomio1[MAX_GRAU+1], polinomio2[MAX_GRAU+1], polinomioR[MAX_GRAU+1];
    int grauP = 0, grauQ = 0, grauR = 0;

    zerarPolinomio(polinomio1);
    zerarPolinomio(polinomio2);
    zerarPolinomio(polinomioR);

    int opcao;

    do{
        printf("\n=== CALCULADORA DE POLINOMIOS ===\n");
        printf("1 - Ler Polinomio 1\n");
        printf("2 - Ler Polinomio 2\n");
        printf("3 - Somar  polinomio 1 e 2 (resultado em R)\n");
        printf("4 - Multiplicar polinomio 1 e 2 (resultado em R)\n");
        printf("5 - Avaliar polinomio 1 em funcao de x\n");
        printf("6 - Avaliar polinomio 2 em funcao de x\n");
        printf("7 - Imprimir polinomio 1\n");
        printf("8 - Imprimir polinomio 2\n");
        printf("9 - Imprimir Resultado\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        

      
        switch(opcao){
        
            case 1:
                lerPolinomio(polinomio1, &grauP);
                printf("\nPolinomio 1 atualizado!\n");
                imprimirPolinomio(polinomio1, 'p1');
                break;

            case 2:
                lerPolinomio(polinomio2, &grauQ);
                printf("\nPolinomio 2 atualizado!\n");
                imprimirPolinomio(polinomio2, 'p2');
                break;

            case 3:
                somarPolinomios(polinomio1, polinomio2, polinomioR, &grauR);
                printf("\nSoma concluida: R = p1 + p2\n");
                imprimirPolinomio(polinomioR, 'R');
                break;

            case 4:
                multiplicarPolinomios(polinomio1, polinomio2, polinomioR, &grauR);
                printf("\nMultiplicacao concluida: R = p1 * p2\n");
                imprimirPolinomio(polinomioR, 'R');
                break;

            case 5:
            {
                double x;
                printf("\nDigite o valor de x para avaliar p1(x): ");
                scanf("%lf", &x);
                double valor = avaliarPolinomio(polinomio1, x);
                printf("p1(%.2f) = %.4f\n", x, valor);
                break;
            }

            case 6:
            {
                double x;
                printf("\nDigite o valor de x para avaliar p2(x): ");
                scanf("%lf", &x);
                double valor = avaliarPolinomio(polinomio2, x);
                printf("p2(%.2f) = %.4f\n", x, valor);
                break;
            }

            case 7:
                imprimirPolinomio(polinomio1, 'p1');
                break;

            case 8:
                imprimirPolinomio(polinomio2, 'p2');
                break;

            case 9:
                imprimirPolinomio(polinomioR, 'Resultado');
                break;

            case 0:
                printf("\nEncerrando o programa...\n");
                break;
            

            default:
                printf("\nOpcao invalida!\n");
                break;
        }
      

    } while(opcao != 0);

    return 0;
}
