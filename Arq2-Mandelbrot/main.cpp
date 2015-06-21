#include <cstring>
#include <iostream>
#include <fstream>
#include <cmath>

#define asm_part1 " push %%edi\n\t \
                    movl %1, %%edi\n\t \
                    movups (%%edi), %%xmm0\n\t \
                    movl %0, %%edi\n\t \
                    movups (%%edi), %%xmm1\n\t \
                    addps %%xmm1, %%xmm0\n\t \
                    movups %%xmm0, (%%edi)\n\t \
                    pop %%edi\n\t"


using namespace std;

void mandelbrot (char * buf, int X, int Y);

const int altura    = 16384;
const int largura   = 16384;


int main(int argc, char* argv[])
{
	ofstream saida;

	saida.open("I:\\appdata\\mandelbrot.ppm", ios::binary | ios::out);


	char * header = new char[20];

	sprintf(header, "P6\n%d\n%d\n255\n", largura, altura);

	saida.write(header, strlen(header));

    delete header;

    // Mandelbrot
    int iY, iX;

    // buffer for all pixels, removing write overhead each iteration
    char * color = new char[altura*largura*3];

    for(iY=0;iY<altura/4;iY++)
    {
        for(iX=0;iX<largura/4;iX++)
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
    // 4 floats to use with SSE
    const float CxMin  =   -2.5;
    const float CxMax  =    1.5;
    const float CyMin  =   -2.0;
    const float CyMax  =    2.0;
    /* */
    float PixelWidth   = (CxMax - CxMin) / largura;
    float PixelHeight  = (CyMax - CyMin) /  altura;


    float tmp = CyMin + 4*Y*PixelHeight;
    float Cy[4] = {tmp, tmp, tmp, tmp};
    float widths[4] = {0, PixelWidth, 2*PixelWidth, 3*PixelWidth};
    float heights[4] = {0, PixelHeight, 2*PixelHeight, 3*PixelHeight};
    tmp = CxMin + 4*X*PixelWidth;
    float Cx[4] = {tmp, tmp, tmp, tmp};
    float * ptrCy = NULL, * ptrHeights = NULL, * ptrCx = NULL, * ptrWidths = NULL;
    ptrCy = Cy;
    ptrHeights = heights;
    ptrCx = Cx;
    ptrWidths = widths;

    // SSE
    asm(asm_part1
        : "=m" (ptrCy), "=m" (ptrHeights)
        :
        : "xmm0", "xmm1");

    asm(asm_part1
        : "=m" (ptrCx), "=m" (ptrWidths)
        :
        : "xmm0", "xmm1");



    /* Z=Zx+Zy*i  ;   Z0 = 0 */
    float Zx[4], Zy[4];
    float Zx2[4], Zy2[4]; /* Zx2=Zx*Zx;  Zy2=Zy*Zy  */
    /*  */
    int Iteration;
    const int IterationMax = 256;
    /* bail-out value , radius of circle ;  */
    const float EscapeRadius = 2;
    float ER2 = EscapeRadius * EscapeRadius;

    int cntY, cntX;

//    for (cntY = 0; cntY < 4; cntY++)
//    {
//        Cy = CyMin + (4*Y + cntY) * PixelHeight;
//        if (fabs(Cy) < PixelHeight/2) Cy = 0.0; /* Main antenna */
//        for (cntX = 0; cntX < 4; cntX++)
//        {
//            Cx = CxMin + (4*X + cntX) * PixelWidth;
//            /* initial value of orbit = critical point Z= 0 */
//
//            // zerar Zx
//            Zx = 0.0;
//            Zy = 0.0;
//            Zx2 = Zx * Zx;
//            Zy2 = Zy * Zy;
//            /* */
//            for (Iteration = 0; Iteration < IterationMax && ((Zx2 + Zy2) < ER2); Iteration++)
//            {
//                Zy = 2 * Zx * Zy + Cy;
//                Zx = Zx2 - Zy2 + Cx;
//                Zx2 = Zx * Zx;
//                Zy2 = Zy * Zy;
//            }
//            /* compute  pixel color (24 bit = 3 bytes) */
//            if (Iteration == IterationMax)
//            { /*  interior of Mandelbrot set = black */
//                buf[3*(4*Y+cntY)*largura + 3*(4*X+cntX)    ] = 0;
//                buf[3*(4*Y+cntY)*largura + 3*(4*X+cntX) + 1] = 0;
//                buf[3*(4*Y+cntY)*largura + 3*(4*X+cntX) + 2] = 0;
//                iTamanho += 3;
//            }
//            else
//            { /* exterior of Mandelbrot set = white */
//                buf[3*(4*Y+cntY)*largura + 3*(4*X+cntX)   ] = ((IterationMax - Iteration) % 8) *  63;  /* Red */
//                buf[3*(4*Y+cntY)*largura + 3*(4*X+cntX) + 1] = ((IterationMax - Iteration) % 4) * 127;  /* Green */
//                buf[3*(4*Y+cntY)*largura + 3*(4*X+cntX) + 2] = ((IterationMax - Iteration) % 2) * 255;  /* Blue */
//                iTamanho += 3;
//            }
//        }
//    }
}
