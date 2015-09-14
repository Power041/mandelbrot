// mandelbrot.cpp : Defines the entry point for the console application.
//
#include <cstring>
#include <iostream>
#include <fstream>
#include <cmath>

#define zero {0.0, 0.0, 0.0, 0.0}

#define iterMax	4096
#define iterMaxf	iterMax.0

using namespace std;

void mandelbrot(char * buf, int X, int Y);

int width = 4096, height = 4096;

int main(int argc, char* argv[])
{
	if (argc < 2) {
		printf("usage: mandelbrot.exe size");
		return 0;
	}

	width = atoi(argv[1]);
	height = width;

	ofstream saida;

	saida.open(".\\mandelbrot.ppm", ios::binary | ios::out);

	char * header = new char[21];

	sprintf(header, "P6\n%d\n%d\n255\n", width, height);

	saida.write(header, strlen(header));

	delete header;

	// Mandelbrot
	int iY, iX;

	// buffer for all pixels, removing write overhead each iteration
	char * color = new char[height * width * 3];

	for (iY = 0; iY<height / 4; iY++)
		for (iX = 0; iX<width / 4; iX++)
			mandelbrot(color, iX, iY);

	/*write color to the file*/
	saida.write(color, height*width * 3);
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
	float PixelWidth = (CxMax - CxMin) / (float)width;
	float PixelHeight = (CyMax - CyMin) / (float)height;

	float zeros[4] = zero ;

	float tmp = CyMin + 4 * Y*PixelHeight;
	float Cy[4] = { tmp, tmp, tmp, tmp };
	float widths[4] = { 0, PixelWidth, 2 * PixelWidth, 3 * PixelWidth };
	float heights[4] = { PixelHeight, PixelHeight, PixelHeight, PixelHeight };
	tmp = CxMin + 4 * X*PixelWidth;
	float Cx[4] = { tmp, tmp, tmp, tmp };
	float * ptrCy = NULL, *ptrHeights = NULL, *ptrCx = NULL, *ptrWidths = NULL, * ptrZeros = NULL;
	ptrCy = Cy;
	ptrHeights = heights;
	ptrCx = Cx;
	ptrWidths = widths;
	ptrZeros = zeros;

	// SSE
	__asm
	{
		push edi		
		// Cy = Cy - Heights
		// so the loop starts with Cy = Cy - Heights + Heights = Cy
		mov edi, ptrHeights
		movups xmm0, [edi]
		mov edi, ptrCy
		movups xmm1, [edi]
		subps xmm0, xmm1
		movups[edi], xmm0

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
	float IterationMax[4] = { iterMaxf, iterMaxf, iterMaxf, iterMaxf };


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

	int resultados[4], resultadoIteration[4];
	int * ptrResultados = NULL, * ptrResultadoIteration = NULL;

	ptrResultados = resultados;
	ptrResultadoIteration = resultadoIteration;

	int outerLoop = 4, writeLoop = 4;

	__asm{
		push esi
		push edi

		/*
		xmm0 = Zx
		xmm1 = Zy
		xmm3 = Zx2
		xmm4 = Zy2
		xmm5 = Zx2 + Zy2 < ER2
		xmm6 = Iteration
		*/
		// outer loop
		mov outerLoop, 4
	outer:
		mov esi, ptrCy
		movups xmm0, [esi]
		mov esi, ptrHeights
		movups xmm1, [esi]
		addps xmm0, xmm1
		mov esi, ptrCy
		movups [esi], xmm0

		// if (fabs(Cy) < PixelHeight / 2) Cy = 0.0; /* Main antenna */
		finit 
		fld Cy
		fabs
		fld PixelHeight
		fld dois
		fdiv
		fcomip ST(0), ST(1)
		ja zerarCy
		ffree ST(0)
		// xmm7 = Cy
		movaps xmm7, xmm0
		jmp zerar
	zerarCy:
		xorps xmm7, xmm7
	zerar:
		// zerar Zx
		// Zx = 0.0;
		// Zy = 0.0;
		// Zx2 = Zx * Zx;
		// Zy2 = Zy * Zy;
		xorps xmm0, xmm0
		xorps xmm1, xmm1
		xorps xmm3, xmm3
		xorps xmm4, xmm4
		xorps xmm6, xmm6

		xorps xmm5, xmm5
		cmpeqps xmm5, xmm0

		mov esi, ptrZeros
		movups xmm2, [esi]
		xorps xmm2, xmm2
		movups [esi], xmm2

		// Iteration loop
		mov ecx, iterMax
	iter:
		// Zy = 2 * Zx * Zy + Cy;
		mov esi, ptrDois
		movups xmm2, [esi]
		
		mulps xmm1, xmm0	// xmm1 = Zx*Zy

		mulps xmm1, xmm2	// xmm1 = 2*Zx*Zy

		movups xmm2, xmm7
		
		addps xmm1, xmm2	// xmm1 = 2*Zx*Zy + Cy

		// Zx = Zx2 - Zy2 + Cx;
		movaps xmm0, xmm3	// xmm0 = Zx2

		subps xmm0, xmm4	// xmm0 = Zx2 - Zy2
		mov esi, ptrCx
		movups xmm2, [esi]

		addps xmm0, xmm2	// xmm0 = Zx2 - Zy2 + Cx

		// Zx2 = Zx * Zx;
		movaps xmm3, xmm0	// xmm3 = Zx

		mulps xmm3, xmm0	// xmm3= Zx*Zx

		// Zy2 = Zy * Zy;
		movaps xmm4, xmm1	// xmm4 = Zy

		mulps xmm4, xmm1	// xmm4 = Zy*Zy

		// Zx2 + Zy2 < ER2;
		
		movaps xmm5, xmm4	// xmm5 = Zy2
		addps xmm5, xmm3	// xmm5 = Zy2 + Zx2
		mov esi, ptrER2
		movups xmm2, [esi]
		cmpnltps xmm5, xmm2	// parallel less than xmm5, ER2-> xmm5 < ER2 -> xmm5 = results (mask 0 = not less)

		mov esi, ptrZeros
		movups xmm2, [esi]
		orps xmm2, xmm5
		movups [esi], xmm2
		movaps xmm5, xmm2

		mov esi, ptrUm
		movups xmm2, [esi]
		andps xmm2, xmm5	// xmm5 & xmm2 = chooses which of the 4 floats will be incremented or not
		addps xmm6, xmm2	// Iteration has some parts of the vector rising and others static
		loop iter


		mov esi, ptrIterationMax
		movups xmm5, [esi] // xmm5 = IterationMax
		cmpeqps xmm5, xmm6 // parallel compare Iteration == IterationMax

		mov esi, ptrResultados
		cvtps2dq xmm5, xmm5

		movups [esi], xmm5

		mov esi, ptrIterationMax
		movups xmm0, [esi]

		// parallel (IterationMax - Iteration)
		subps xmm0, xmm6
		cvtps2dq xmm0, xmm0

		mov esi, ptrResultadoIteration
		movups [esi], xmm0

		mov edi, ptrResultados


		mov writeLoop, 4
	write:
		mov esi, buf

		// 3*(4*Y+cntY)*width -> 3*width*(4*Y+cntY)
		mov eax, 3
		mul width
		mov ebx, eax

		mov eax, 4
		mul Y
		// cntY = outerLoop
		add eax, outerLoop
		dec eax
		mul ebx

		// buf + 3*(4*Y+cntY)*width
		add esi, eax

		// 3*(4*X+cntX)
		mov eax, 4
		mul X
		add eax, writeLoop
		dec eax
		mov ebx, eax
		mov eax, 3
		mul ebx

		// buf + 3*(4*Y+cntY)*width + 3*(4*X+cntX)
		add esi, eax

		movd xmm0, [edi]
		movd eax, xmm0
		add edi, 4

		cmp eax, 0	// eax == 0 -> Iteration != IterationMax
		jne preigual
		// Iteration != IterationMax
		push edi
		mov edi, ptrResultadoIteration
		// we need to get the element on resultadoIteration
		// relevant to the current cntX
		mov eax, 4
		mov ebx, writeLoop
		dec ebx
		mul ebx
		add edi, eax

		//	buf[3*(4*Y+cntY)*width + 3*(4*X+cntX)   ] = ((IterationMax - Iteration) % 8) *  63;  /* Red */
		mov eax, [edi]
		cdq
		mov ebx, 8
		div ebx
		mov eax, edx
		mov ebx, 63
		mul ebx
		mov BYTE PTR [esi], al
		inc esi

		//	buf[3*(4*Y+cntY)*width + 3*(4*X+cntX) + 1] = ((IterationMax - Iteration) % 4) * 127;  /* Green */
		mov eax, [edi]
		cdq
		mov ebx, 4
		div ebx
		mov eax, edx
		mov ebx, 127
		mul ebx
		mov BYTE PTR [esi], al
		inc esi

		//	buf[3*(4*Y+cntY)*width + 3*(4*X+cntX) + 2] = ((IterationMax - Iteration) % 2) * 255;  /* Blue */
		mov eax, [edi]
		cdq
		mov ebx, 2
		div ebx
		mov eax, edx
		mov ebx, 255
		mul ebx
		mov BYTE PTR [esi], al

		pop edi

		// loop write
		dec writeLoop
		cmp DWORD PTR writeLoop, 0
		ja write
		
		// loop outer
		dec outerLoop
		cmp DWORD PTR outerLoop, 0
		ja outer

		jmp fim

	preigual:
		mov ecx, 3
	igual:
		//if (Iteration == IterationMax)
		//{ /*  interior of Mandelbrot set = black */
		//	buf[3*(4*Y+cntY)*width + 3*(4*X+cntX)    ] = 0;
		//	buf[3*(4*Y+cntY)*width + 3*(4*X+cntX) + 1] = 0;
		//	buf[3*(4*Y+cntY)*width + 3*(4*X+cntX) + 2] = 0;
		//}
		mov BYTE PTR [esi], 0
		inc esi
		loop igual

		// loop write
		dec writeLoop
		cmp DWORD PTR writeLoop, 0
		ja write

		// loop outer
		dec outerLoop
		cmp DWORD PTR outerLoop, 0
		ja outer

	fim:
		pop edi
		pop esi
	}
	_mm_empty();
}
