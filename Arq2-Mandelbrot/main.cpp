// mandelbrot.cpp : Defines the entry point for the console application.
//
#include <cstring>
#include <iostream>
#include <fstream>
#include <cmath>

#define zero {0.0, 0.0, 0.0, 0.0}


using namespace std;

void mandelbrot(char * buf, int X, int Y);

const int altura = 16384;
const int largura = 16384;


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
	char * color = new char[altura*largura * 3];

	for (iY = 0; iY<altura / 4; iY++)
	{
		for (iX = 0; iX<largura / 4; iX++)
		{
			mandelbrot(color, iX, iY);
		}
	}

	/*write color to the file*/
	saida.write(color, altura*largura * 3);
	saida.close();

	return 0;
}

void mandelbrot(char * buf, int X, int Y)
{
	// 4 floats to use with SSE
	const float CxMin = -2.5;
	const float CxMax = 1.5;
	const float CyMin = -2.0;
	const float CyMax = 2.0;
	/* */
	float PixelWidth = (CxMax - CxMin) / (float)largura;
	float PixelHeight = (CyMax - CyMin) / (float)altura;


	float tmp = CyMin + 4 * Y*PixelHeight;
	float Cy[4] = { tmp, tmp, tmp, tmp };
	float widths[4] = { 0, PixelWidth, 2 * PixelWidth, 3 * PixelWidth };
	float heights[4] = { 0, PixelHeight, 2 * PixelHeight, 3 * PixelHeight };
	tmp = CxMin + 4 * X*PixelWidth;
	float Cx[4] = { tmp, tmp, tmp, tmp };
	float * ptrCy = NULL, *ptrHeights = NULL, *ptrCx = NULL, *ptrWidths = NULL;
	ptrCy = Cy;
	ptrHeights = heights;
	ptrCx = Cx;
	ptrWidths = widths;

	// SSE
	__asm
	{
		push edi
		mov edi, ptrHeights
	    movups xmm0, [edi]
		mov edi, ptrCy
		movups xmm1, [edi]
		addps xmm0, xmm1
		movups [edi], xmm0
		mov edi, ptrWidths
		movups xmm0, [edi]
		mov edi, ptrCx
		movups xmm1, [edi]
		addps xmm0, xmm1
		movups[edi], xmm0
		pop edi
	}



	/* Z=Zx+Zy*i  ;   Z0 = 0 */
	float Zx[4] = zero, Zy[4] = zero;
	float Zx2[4] = zero, Zy2[4] = zero; /* Zx2=Zx*Zx;  Zy2=Zy*Zy  */
	float dois[4] = { 2.0, 2.0, 2.0, 2.0 };
	float um[4] = { 1.0, 1.0, 1.0, 1.0 };
	/*  */
	float Iteration[4] = zero;
	float IterationMax[4] = { 256.0, 256.0, 256.0, 256.0 };

	float * ptrZx = NULL, *ptrZy = NULL, *ptrZx2 = NULL, *ptrZy2 = NULL, *ptrDois = NULL;
	float * ptrUm = NULL, *ptrIteration = NULL, *ptrIterationMax = NULL;
	ptrZx = Zx;
	ptrZy = Zy;
	ptrZx2 = Zx2;
	ptrZy2 = Zy2;
	ptrDois = dois;
	ptrUm = um;
	ptrIteration = Iteration;
	ptrIterationMax = IterationMax;

	/* bail-out value , radius of circle ;  */
	const float EscapeRadius = 2;
	float ER2 = EscapeRadius * EscapeRadius;
	float p_ER2[4];
	for (int i = 0; i < 4; i++)
		p_ER2[i] = ER2;

	float * ptrER2 = NULL;
	ptrER2 = p_ER2;

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
	__asm{
		mov esi, ptrZx		// esi = ptrZx
		movups xmm0, [esi]
		mov esi, ptrZy		// esi = ptrZy
		movups xmm1, [esi]
		mov esi, ptrCy		// esi = ptrCy
		movups xmm2, [esi]
		mov esi, ptrCx		// esi = ptrCx
		movups xmm3, [esi]
		mov esi, ptrDois	// esi = ptrDois
		movups xmm4, [esi]
		mov esi, ptrZx2		// esi = ptrZx2
		movups xmm5, [esi]
		mov esi, ptrZy2		// esi = ptrZy2
		movups xmm6, [esi]
		mov esi, ptrER2		// esi = ptrER2
		movups xmm7, [esi]
		/*
		xmm0 = Zx
		xmm1 = Zy
		xmm2 = Cy
		xmm3 = Cx
		xmm4 = [2, 2, 2, 2]
		xmm5 = Zx2
		xmm6 = Zy2
		xmm7 = ER2
		*/
		// Zy = 2 * Zx * Zy + Cy;
		mulps xmm1, xmm0	// xmm1 = Zx*Zy
		mulps xmm1, xmm4	// xmm1 = 2*Zx*Zy
		addps xmm1, xmm2	// xmm1 = 2*Zx*Zy + Cy
		// Zx = Zx2 - Zy2 + Cx;
		movaps xmm0, xmm5	// xmm0 = Zx2
		subps xmm0, xmm6	// xmm0 = Zx2 - Zy2
		addps xmm0, xmm3	// xmm0 = Zx2 - Zy2 + Cx
		// Zx2 = Zx * Zx;
		movaps xmm5, xmm0	 // xmm5 = Zx
		mulps xmm5, xmm0	// xmm5 = Zx*Zx
		// Zy2 = Zy * Zy;
		movaps xmm6, xmm1	// xmm6 = Zy
		mulps xmm6, xmm1	// xmm6 = Zy*Zy
		// Zx2 + Zy2 < ER2;
		movaps xmm8, xmm6	// xmm8 = Zy2
		addps xmm8, xmm5	// xmm8 = Zy2 + Zx2
		cmpltps xmm8, xmm7	// parallel less than xmm8, xmm7 -> xmm8 < xmm7 -> xmm8 = results

	}
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
