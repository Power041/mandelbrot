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
	float heights[4] = { PixelHeight, PixelHeight, PixelHeight, PixelHeight };
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

	int resultados[4], resultadoIteration[4];
	int * ptrResultados = NULL, * ptrResultadoIteration = NULL;

	ptrResultados = resultados;
	ptrResultadoIteration = resultadoIteration;

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
		push esi
		push edi

		mov esi, ptrZx		// esi = ptrZx
		movups xmm0, [esi]
		mov esi, ptrZy		// esi = ptrZy
		movups xmm1, [esi]

		mov esi, ptrZx2	// esi = ptrZx2
		movups xmm3, [esi]
		mov esi, ptrZy2	// esi = ptrZy2
		movups xmm4, [esi]
		mov esi, ptrIteration
		movups xmm6, [esi]
		/*
		xmm0 = Zx
		xmm1 = Zy
		xmm3 = Zx2
		xmm4 = Zy2
		xmm5 = Zx2 + Zy2 < ER2
		xmm6 = Iteration
		*/
		// outer loop
		mov ecx, 4
	outer:
		mov esi, ptrCy
		movups xmm0, [esi]
		mov esi, ptrHeights
		movups xmm1, [esi]
		addps xmm0, xmm1
		mov esi, ptrCy
		movups [esi], xmm0
		// xmm7 = Cy
		movaps xmm7, xmm0

		// if (fabs(Cy) < PixelHeight / 2) Cy = 0.0; /* Main antenna */

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

		// Iteration loop
		push ecx
		mov ecx, 256
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
		cmpnltps xmm5, xmm2	// parallel not less than xmm5, ER2-> xmm5 < ER2 -> xmm6 = results (mask 1 = not less)
		mov esi, ptrUm
		movups xmm2, [esi]
		andps xmm5, xmm2	// xmm5 & xmm2 = chooses which of the 4 floats will be incremented or not
		addps xmm6, xmm5	// Iteration has some parts of the vector rising and others static
		loop iter

		// outer counter
		pop ecx

		mov esi, ptrIterationMax
		movups xmm5, [esi] // xmm5 = IterationMax
		cmpeqps xmm5, xmm6 // parallel compare Iteration == IterationMax
		
		movaps xmm0, xmm5
		movaps xmm1, xmm5
		movaps xmm3, xmm5
		/*
			xmm0 = mascara do primeiro pixel ([31:  0])
			xmm1 = mascara do segundo  pixel ([63: 32])
			xmm3 = mascara do terceiro pixel ([95: 64])
			xmm5 = mascara do quarto   pixel ([127:96])
		*/
		punpckldq xmm0, xmm0 // xmm0 = xmm0[31:0], xmm0[31:0], xmm0[63:32], xmm0[63:32]
		punpckldq xmm0, xmm0 // xmm0 = xmm0[31:0], xmm0[31:0], xmm0[31:0], xmm0[31:0]

		punpckldq xmm1, xmm1 // xmm1 = xmm1[31:0], xmm1[31:0], xmm1[63:32], xmm1[63:32]
		punpckhdq xmm1, xmm1 // xmm1 = xmm1[63:32], xmm1[63:32], xmm1[63:32], xmm1[63:32]

		punpckhdq xmm3, xmm3 // xmm3 = xmm3[95:64], xmm3[95:64], xmm3[127:96], xmm3[127:96]
		punpckldq xmm3, xmm3 // xmm3 = xmm3[95:64], xmm3[95:64], xmm3[95:64], xmm3[95:64]

		punpckhdq xmm5, xmm5 // xmm5 = xmm5[95:64], xmm5[95:64], xmm5[127:96], xmm5[127:96]
		punpckhdq xmm5, xmm5 // xmm5 = xmm5[127:96], xmm5[127:96], xmm5[127:96], xmm5[127:96]

		mov esi, ptrResultados
		movd [esi], xmm0
		
		add esi, 4
		movd [esi], xmm1

		add esi, 4
		movd [esi], xmm3

		add esi, 4
		movd [esi], xmm5

		mov esi, ptrIterationMax
		movups xmm0, [esi]

		// parallel (IterationMax - Iteration)
		subps xmm0, xmm6

		punpckldq xmm0, xmm0 
		punpckldq xmm0, xmm0 

		punpckldq xmm1, xmm1 
		punpckhdq xmm1, xmm1 

		punpckhdq xmm3, xmm3 
		punpckldq xmm3, xmm3 

		punpckhdq xmm5, xmm5 
		punpckhdq xmm5, xmm5

		mov esi, ptrResultadoIteration
		movd[esi], xmm0

		add esi, 4
		movd[esi], xmm1

		add esi, 4
		movd[esi], xmm3

		add esi, 4
		movd[esi], xmm5

		/*
			buf[Y+0][X] buf[Y+0][X+1] buf[Y+0][X+2] buf[Y+0][X+3]
			buf[Y+1][X] buf[Y+1][X+1] buf[Y+1][X+2] buf[Y+1][X+3]
			buf[Y+2][X] buf[Y+2][X+1] buf[Y+2][X+2] buf[Y+2][X+3]
			buf[Y+3][X] buf[Y+3][X+1] buf[Y+3][X+2] buf[Y+3][X+3]		
		*/
		push ecx

		mov edi, ptrResultados

		mov ecx, 4
	write:
		mov esi, buf

		// 3*(4*Y+cntY)*largura -> 3*largura*(4*Y+cntY)
		mov eax, 3
		mul largura
		mov ebx, eax

		mov eax, 4
		mul Y
		mov edx, ecx
		pop ecx	// cntY
		add eax, ecx 
		push ecx
		mov ecx, edx
		mul ebx

		// buf + 3*(4*Y+cntY)*largura
		add esi, eax

		// 3*(4*X+cntX)
		mov eax, 4
		mul X
		add eax, ecx
		mov ebx, eax
		mov eax, 3
		mul ebx

		// buf + 3*(4*Y+cntY)*largura + 3*(4*X+cntX)
		add esi, eax

		movd eax, [edi]
		add edi, 4

		cmp eax, 0	// eax == 0 -> Iteration != IterationMax
		jne preigual
		push edi
		mov edi, ptrResultadoIteration
		// we need to get the element on resultadoIteration
		// relevant to the current cntX
		mov eax, 4
		mul ecx
		add edi, eax

		mov eax, [edi]
		cdq
		mov ebx, 8
		div ebx
		mov ebx, 63
		mul ebx
		mov BYTE PTR [esi], al
		inc esi

		mov eax, [edi]
		cdq
		mov ebx, 4
		div ebx
		mov ebx, 127
		mul ebx
		mov BYTE PTR [esi], al
		inc esi

		mov eax, [edi]
		cdq
		mov ebx, 2
		div ebx
		mov ebx, 255
		mul ebx
		mov BYTE PTR [esi], al

		pop edi

		// loop write
		dec ecx
		cmp ecx, 0
		ja write
		
		pop ecx
		// loop outer
		dec ecx
		cmp ecx, 0
		ja outer

		//else
		//{ /* exterior of Mandelbrot set = white */
		//	buf[3*(4*Y+cntY)*largura + 3*(4*X+cntX)   ] = ((IterationMax - Iteration) % 8) *  63;  /* Red */
		//	buf[3*(4*Y+cntY)*largura + 3*(4*X+cntX) + 1] = ((IterationMax - Iteration) % 4) * 127;  /* Green */
		//	buf[3*(4*Y+cntY)*largura + 3*(4*X+cntX) + 2] = ((IterationMax - Iteration) % 2) * 255;  /* Blue */
		//}

	preigual:
		push ecx
		mov ecx, 3
	igual:
		//if (Iteration == IterationMax)
		//{ /*  interior of Mandelbrot set = black */
		//	buf[3*(4*Y+cntY)*largura + 3*(4*X+cntX)    ] = 0;
		//	buf[3*(4*Y+cntY)*largura + 3*(4*X+cntX) + 1] = 0;
		//	buf[3*(4*Y+cntY)*largura + 3*(4*X+cntX) + 2] = 0;
		//}
		mov BYTE PTR [esi], 0
		inc esi
		loop igual

		pop ecx
		// loop write
		dec ecx
		cmp ecx, 0
		ja write

		pop ecx

		// loop outer
		dec ecx
		cmp ecx, 0
		ja outer

		pop edi
		pop esi
	}
}
