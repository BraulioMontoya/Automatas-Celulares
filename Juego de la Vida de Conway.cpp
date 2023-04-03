#include<time.h>
#include<stdlib.h>
#include<graphics.h>

int main() {
    srand(time(NULL));

    int iteraciones = 50, limite = 1500;

    int suma, cont, x, y;
    int entrada[400][300], salida[400][300];

    initwindow(400, 300);

    for(int i = 0; i < 400; i++) {
        for(int j = 0; j < 300; j++) {
			entrada[i][j] = 0;
            salida[i][j] = 0;
		}
    }

    cont = 0;
    while(cont < limite) {
        x = rand()%399 + 1;
        y = rand()%299 + 1;

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
        for(int i = 0; i < 400; i++) {
            for(int j = 0; j < 300; j++) {
                if(entrada[i][j] == 1) {
                    putpixel(i, j, WHITE);
                }
            }
        }

        for(int i = 1; i < 399; i++) {
            for(int j = 1; j < 299; j++) {
                suma = entrada[i][j - 1] + entrada[i][j + 1];
                suma += entrada[i - 1][j - 1] + entrada[i - 1][j] + entrada[i - 1][j + 1];
                suma += entrada[i + 1][j - 1] + entrada[i + 1][j] + entrada[i + 1][j + 1];

                if(entrada[i][j] == 0 && suma == 3) {
                    salida[i][j] = 1;
                }

                if(entrada[i][j] == 1 && (suma == 2 || suma == 3)) {
                    salida[i][j] = 1;
                }
            }
        }

        for(int i = 0; i < 400; i++) {
            for(int j = 0; j < 300; j++) {
                entrada[i][j] = salida[i][j];
                salida[i][j] = 0;
            }
        }

        delay(500);
        cleardevice();

        cont++;
    }
    
    for(int i = 0; i < 400; i++) {
        for(int j = 0; j < 300; j++) {
            if(entrada[i][j] == 1) {
                putpixel(i, j, WHITE);
            }
        }
    }

    system("pause");
    closegraph();

    return 0;
}