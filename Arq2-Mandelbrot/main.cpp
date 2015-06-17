#include <cstring>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;


int main(int argc, char* argv[])
{
	// Arquivo
	ofstream saida;

    // Criar arquivo com acesso binario
	saida.open("mandelbrot.ppm", ios::binary | ios::out);


    // Tamanho da imagem
    const int altura    = 1024;
    const int largura   = 1024;

	char * header = new char[20];

	sprintf(header, "P6\n%d\n%d\n255\n", largura, altura);

	// escrever header no arquivo de saida
	saida.write(header, strlen(header));

    delete header;

    // Variaveis Mandelbrot
    int iY, iX;
    double Cx, Cy;
    const double CxMin  =   -2.5;
    const double CxMax  =    1.5;
    const double CyMin  =   -2.0;
    const double CyMax  =    2.0;
    /* */
    double PixelWidth   = (CxMax - CxMin) / largura;
    double PixelHeight  = (CyMax - CyMin) /  altura;
    /* Z=Zx+Zy*i  ;   Z0 = 0 */
    double Zx, Zy;
    double Zx2, Zy2; /* Zx2=Zx*Zx;  Zy2=Zy*Zy  */
    /*  */
    int Iteration;
    const int IterationMax=256;
    /* bail-out value , radius of circle ;  */
    const double EscapeRadius=2;
    double ER2=EscapeRadius*EscapeRadius;
    char color[3];

    for(iY=0;iY<altura;iY++)
    {
         Cy=CyMin + iY*PixelHeight;
         if (fabs(Cy)< PixelHeight/2) Cy=0.0; /* Main antenna */
         for(iX=0;iX<largura;iX++)
         {
                Cx=CxMin + iX*PixelWidth;
                /* initial value of orbit = critical point Z= 0 */
                Zx=0.0;
                Zy=0.0;
                Zx2=Zx*Zx;
                Zy2=Zy*Zy;
                /* */
                for (Iteration=0;Iteration<IterationMax && ((Zx2+Zy2)<ER2);Iteration++)
                {
                    Zy=2*Zx*Zy + Cy;
                    Zx=Zx2-Zy2 +Cx;
                    Zx2=Zx*Zx;
                    Zy2=Zy*Zy;
                };
                /* compute  pixel color (24 bit = 3 bytes) */
                if (Iteration==IterationMax)
                { /*  interior of Mandelbrot set = black */
                    color[0]=0;
                    color[1]=0;
                    color[2]=0;
                }
                else
                { /* exterior of Mandelbrot set = white */
                    color[0]=((IterationMax-Iteration) % 8) *  63;  /* Red */
                    color[1]=((IterationMax-Iteration) % 4) * 127;  /* Green */
                    color[2]=((IterationMax-Iteration) % 2) * 255;  /* Blue */
                };
                /*write color to the file*/
                saida.write(color, 3);
            }
    }

	saida.close();

	return 0;
}
