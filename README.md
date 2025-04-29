# 🏁 Simulação Paralela de Corrida com OpenMP

## 📌 Introdução

Este projeto foi desenvolvido como parte do trabalho final da disciplina de **Programação Paralela e Distribuída**, com o objetivo de aplicar conceitos de concorrência e paralelismo de forma prática e criativa. A proposta simula uma corrida entre múltiplos corredores (threads), destacando o uso do modelo de memória compartilhada com OpenMP e avaliando o desempenho da execução paralela.

## 🛠️ Tecnologias Utilizadas

- **Linguagem**: C++  
- **Paralelismo**: OpenMP  
- **Compiladores**: `g++` (Linux) ou `MSVC`/`MinGW` (Windows)
- **Outros recursos**: `unistd.h` para temporização no Linux

## 🎮 O que o código faz

O programa simula uma corrida com cinco corredores, onde cada um avança em passos aleatórios até completar um percurso definido. Cada corredor é representado por uma *thread*, e o progresso de todos é exibido em tempo real com barras visuais. Ao final, o tempo de cada corredor é registrado e é apresentado um ranking de chegada.

- Os corredores são executados em paralelo com `#pragma omp parallel`.
- A sincronização de saídas no console e dos vetores de resultado é feita com `#pragma omp critical`.
- A aleatoriedade no tempo de execução simula diferenças de velocidade entre os corredores.

## 🖥️ Como executar

### ✅ Linux

1. Instale o compilador `g++` com suporte ao OpenMP:
   ```bash
   sudo apt update
   sudo apt install g++
   ```

2. Compile o código com a flag `-fopenmp`:
   ```bash
   g++ corrida.cpp -o corrida -fopenmp
   ```

3. Execute:
   ```bash
   ./corrida
   ```

> **Nota**: O código usa `unistd.h` para a função `usleep`. Isso funciona nativamente no Linux.

---

### 🪟 Windows

1. Use [MinGW-w64 (MSYS2)](https://www.msys2.org/) ou [MinGW-w64 standalone](https://sourceforge.net/projects/mingw-w64/)
 com suporte a OpenMP.

2. Compile com:
   ```bash
   g++ corrida.cpp -o corrida.exe -fopenmp
   ```

3. Execute o programa:
   ```bash
   corrida.exe
   ```

> ⚠️ Em sistemas Windows, `usleep` não está disponível por padrão. Recomenda-se substituir `usleep()` por `Sleep()` (Windows API) ou usar bibliotecas compatíveis, caso queira plena portabilidade.

---
