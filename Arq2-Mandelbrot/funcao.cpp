// Mandelbrot implementado numa funcao

#include <cstring>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

const int altura    = 1024;
const int largura   = 1024;

void mandelbrot(char*, int, int);

int main(int argc, char* argv[])
{
	ofstream saida;

	saida.open("mandelbrot.ppm", ios::binary | ios::out);

	char * header = new char[20];

	sprintf(header, "P6\n%d\n%d\n255\n", largura, altura);

	saida.write(header, strlen(header));

    delete header;

    // Mandelbrot
    int iY, iX;

    // buffer for all pixels, removing write overhead each iteration
    char * color = new char[altura*largura*3];

    for(iY=0;iY<altura;iY++)
    {
        for(iX=0;iX<largura;iX++)
        {
             mandelbrot(color, iX, iY);
        }
    }

    /*write color to the file*/
    saida.write(color, altura*largura*3);
	saida.close();

	return 0;
}


void mandelbrot (char * buf, int X, int Y)
{
    // manter offset da posicao atual na imagem
    static int iTamanho = 0;

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
    const int IterationMax = 256;
    /* bail-out value , radius of circle ;  */
    const double EscapeRadius = 2;
    double ER2 = EscapeRadius * EscapeRadius;
    Cy = CyMin + Y * PixelHeight;
    if (fabs(Cy) < PixelHeight/2) Cy = 0.0; /* Main antenna */
    Cx = CxMin + X * PixelWidth;
    /* initial value of orbit = critical point Z= 0 */
    Zx = 0.0;
    Zy = 0.0;
    Zx2 = Zx * Zx;
    Zy2 = Zy * Zy;
    /* */
    for (Iteration = 0; Iteration < IterationMax && ((Zx2 + Zy2) < ER2); Iteration++)
    {
        Zy = 2 * Zx * Zy + Cy;
        Zx = Zx2 - Zy2 + Cx;
        Zx2 = Zx * Zx;
        Zy2 = Zy * Zy;
    };
    /* compute  pixel color (24 bit = 3 bytes) */
    if (Iteration == IterationMax)
    { /*  interior of Mandelbrot set = black */
        buf[iTamanho    ] = 0;
        buf[iTamanho + 1] = 0;
        buf[iTamanho + 2] = 0;
        iTamanho += 3;
    }
    else
    { /* exterior of Mandelbrot set = white */
        buf[iTamanho    ] = ((IterationMax - Iteration) % 8) *  63;  /* Red */
        buf[iTamanho + 1] = ((IterationMax - Iteration) % 4) * 127;  /* Green */
        buf[iTamanho + 2] = ((IterationMax - Iteration) % 2) * 255;  /* Blue */
        iTamanho += 3;
    };
}
