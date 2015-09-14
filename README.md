# mandelbrot
Cria imagem demonstrando um conjunto de Mandelbrot, dado um tamanho.

# Branches
Há dois branches nesse projeto, o **master** é a versão que foi utilizada como base para os testes e o branch **simd** é a implementação do mesmo utilizando *inline assembly* com instruções vetoriais x86.

# Arquivos
  * main.cpp - Arquivo principal do projeto, gera a imagem e a escreve num arquivo na pasta atual, chamado mandelbrot.ppm
  
# Utilização
Basta utilizar na linha de comando "mandelbrot.exe tamanho", ex. "mandelbrot.exe 1024" gera uma imagem de 1024 por 1024 pixels.

# Implementação
O branch **simd** implementa o branch **master** utilizando *inline assembly* IA-32, com instruções vetoriais SSE, de modo a obter ganhos de performance na criação da imagem.

Assim, foram feitos testes com diferentes tamanhos de imagem, de modo que o programa tivesse que calcular mais pixels, para que se pudesse compará-los. Os resultados obtidos (utilizando VC++) estão a seguir (em segundos):

  ![Resultados](https://cloud.githubusercontent.com/assets/1683404/9861832/312ff50c-5b0b-11e5-92e5-ae22f74d3518.PNG)
  
  ![Comparação](https://cloud.githubusercontent.com/assets/1683404/9861833/32cc9320-5b0b-11e5-906f-fc85514618c2.PNG)
  
  # Conclusão
  
  Pode-se observar que o ganho de performance do SIMD foi pequeno, ao compará-lo com o original. Tal ganho reduzido pode ser atribuído a implementação, onde alguns passos podem ter ocorrido descuidos originados da complexidade de se trabalhar com *inline assembly*. Uma solução seria usar a biblioteca *intrinsics* que a Intel provê para uso com C/C++, onde as instruções SSE/MMX são utilizadas mais eficientemente.
