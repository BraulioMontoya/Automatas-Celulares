#include<time.h>
#include<stdlib.h>
#include<graphics.h>

int main() {
    srand(time(NULL));

    /*
        Estados:
            0 -> tierra / persona sana.
            1 -> agua.
            2 -> persona enferma.
            3 -> persona muerta.
    */

    int iteraciones = 30, limite_agua = 1500, limite_enfermos = 3000;

    int suma, cont, vecinos, x, y;
    int entrada[400][300], salida[400][300];

    initwindow(400, 300);

    for(int i = 0; i < 400; i++) {
        for(int j = 0; j < 300; j++) {
			entrada[i][j] = 0;
            salida[i][j] = 0;
		}
    }

    //Generando mapa.
    cont = 0;
    while(cont < limite_agua) {
        x = rand()%398 + 1;
        y = rand()%298 + 1;

        if(entrada[x][y] == 0) {
            entrada[x][y - 1] = rand()%2;
            entrada[x][y] = 1;
            entrada[x][y + 1] = rand()%2;
            entrada[x - 1][y - 1] = rand()%2;
            entrada[x - 1][y] = rand()%2;
            entrada[x - 1][y + 1] = rand()%2;
            entrada[x + 1][y - 1] = rand()%2;
            entrada[x + 1][y] = rand()%2;
            entrada[x + 1][y + 1] = rand()%2;

            cont += entrada[x][y - 1] + entrada[x][y] + entrada[x][y + 1];
            cont += entrada[x - 1][y - 1] + entrada[x - 1][y] + entrada[x - 1][y + 1];
            cont += entrada[x + 1][y - 1] + entrada[x + 1][y] + entrada[x + 1][y + 1];
        }
    }

    cont = 0;
    while(cont < iteraciones) {
        for(int i = 1; i < 399; i++) {
            for(int j = 1; j < 299; j++) {
                suma = entrada[i][j - 1] + entrada[i][j + 1];
                suma += entrada[i - 1][j - 1] + entrada[i - 1][j] + entrada[i - 1][j + 1];
                suma += entrada[i + 1][j - 1] + entrada[i + 1][j] + entrada[i + 1][j + 1];

                salida[i][j] = entrada[i][j];

                if(entrada[i][j] == 0 && suma > 2) {
                    salida[i][j] = 1;
                }

                if(entrada[i][j] == 1 && suma < 3) {
                    salida[i][j] = 0;
                }
            }
        }

        for(int i = 0; i < 400; i++) {
            for(int j = 0; j < 300; j++) {
                entrada[i][j] = salida[i][j];
                salida[i][j] = 0;
            }
        }

        cont++;
    }

    //Simulando epidemia.
    cont = 0;
    while(cont < limite_agua) {
        x = rand()%400;
        y = rand()%300;

        if(entrada[x][y] == 0) {
            entrada[x][y] = 2;
            cont++;
        }
    }

    cont = 0;
    while(cont < iteraciones) {
        for(int i = 0; i < 400; i++) {
            for(int j = 0; j < 300; j++) {
                switch(entrada[i][j]) {
                    case 0:
                        putpixel(i, j, BROWN);
                        break;

                    case 1:
                        putpixel(i, j, CYAN);
                        break;

                    case 2:
                        putpixel(i, j, YELLOW);
                        break;

                    default:
                        putpixel(i, j, RED);
                }
            }
        }

        for(int i = 1; i < 399; i++) {
            for(int j = 1; j < 299; j++) {
                salida[i][j] = entrada[i][j];

                if(entrada[i][j] != 1) {
                    suma = 0;
                    vecinos = 0;

                    for(int k = i - 1; k < i + 2; k++) {
                        for(int l = j - 1; l < j + 2; l++) {
                            if(entrada[k][l] != 1 && k != i && l != j) {
                                suma += entrada[k][l];
                                vecinos++;
                            }
                        }
                    }

                    if(entrada[i][j] == 0 && suma >= 2) {
                        salida[i][j] = 2;
                    }

                    if(entrada[i][j] == 2 && suma >= 2 * vecinos) {
                        salida[i][j] = 3;
                    }
                }
            }
        }

        for(int i = 0; i < 400; i++) {
            for(int j = 0; j < 300; j++) {
                entrada[i][j] = salida[i][j];
                salida[i][j] = 0;
            }
        }

        cont++;
    }
    
    for(int i = 0; i < 400; i++) {
        for(int j = 0; j < 300; j++) {
            switch(entrada[i][j]) {
                case 0:
                    putpixel(i, j, BROWN);
                    break;

                case 1:
                    putpixel(i, j, CYAN);
                    break;

                case 2:
                    putpixel(i, j, YELLOW);
                    break;

                default:
                    putpixel(i, j, RED);
            }
        }
    }

    system("pause");
    closegraph();

    return 0;
}