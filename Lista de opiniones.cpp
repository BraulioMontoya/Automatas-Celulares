#include<time.h>
#include<stdlib.h>
#include<graphics.h>

int main() {
    srand(time(NULL));

    int suma;
    int entrada[400], salida[400];

    initwindow(400, 300);

    for(int i = 0; i < 400; i++) {
        entrada[i] = rand()%2;
    }

    for(int i = 0; i < 300; i++) {
		for(int j = 0; j < 400; j++) {
			if(entrada[j] == 1) {
				putpixel(j, i, WHITE);
            }
		}
		
		for(int k = 1; k < 399; k++) {
			suma = entrada[k - 1] + entrada[k] + entrada[k + 1];

            //Si la mayoría es 1, el siguiente sera 1.
			if(suma > 1) {
				salida[k] = 1;
			}
		}
		
		for(int l = 0; l < 400; l++) {
			entrada[l] = salida[l];
			salida[l] = 0;
		}
	}

    system("pause");
    closegraph();

    return 0;
}