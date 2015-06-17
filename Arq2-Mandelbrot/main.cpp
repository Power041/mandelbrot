#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;


int main(int argc, char* argv[])
{
	// Arquivo
	ofstream saida;

    // Criar arquivo com acesso binario
	saida.open("mandelbrot.ppm", ios::binary | ios::out);


    // Tamanho da imagem
    const int altura    = 16384;
    const int largura   = 16384;
    const int tamanho   = altura * largura;

	char * header = new char[20];

	sprintf(header, "P6 %d %d 255", largura, altura);

	// escrever header no arquivo de saida
	saida.write(header, strlen(header));

	saida.close();

	return 0;
}
