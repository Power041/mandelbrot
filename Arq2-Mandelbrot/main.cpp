#include <cstring>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;


int main(int argc, char* argv[])
{
	ofstream saida;

	saida.open("I:\\appdata\\mandelbrot.ppm", ios::binary | ios::out);

    const int altura    = 16384;
    const int largura   = 16384;

	char * header = new char[20];

	sprintf(header, "P6\n%d\n%d\n255\n", largura, altura);

	saida.write(header, strlen(header));

    delete header;

    // Mandelbrot
    int iY, iX;
    float Cx, Cy;
    const float CxMin  =   -2.5;
    const float CxMax  =    1.5;
    const float CyMin  =   -2.0;
    const float CyMax  =    2.0;
    /* */
    float PixelWidth   = (CxMax - CxMin) / largura;
    float PixelHeight  = (CyMax - CyMin) /  altura;
    /* Z=Zx+Zy*i  ;   Z0 = 0 */
    float Zx, Zy;
    float Zx2, Zy2; /* Zx2=Zx*Zx;  Zy2=Zy*Zy  */
    /*  */
    int Iteration;
    const int IterationMax=256;
    /* bail-out value , radius of circle ;  */
    const float EscapeRadius=2;
    float ER2=EscapeRadius*EscapeRadius;
    // buffer for all pixels, removing write overhead each iteration
    char * color = new char[altura*largura*3];
    int iTamanho = 0;

    float processando[4];

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
                    color[iTamanho    ]=0;
                    color[iTamanho + 1]=0;
                    color[iTamanho + 2]=0;
                    iTamanho += 3;
                }
                else
                { /* exterior of Mandelbrot set = white */
                    color[iTamanho    ]=((IterationMax-Iteration) % 8) *  63;  /* Red */
                    color[iTamanho + 1]=((IterationMax-Iteration) % 4) * 127;  /* Green */
                    color[iTamanho + 2]=((IterationMax-Iteration) % 2) * 255;  /* Blue */
                    iTamanho += 3;
                };
            }
    }

    /*write color to the file*/
    saida.write(color, altura*largura*3);
	saida.close();

	return 0;
}
