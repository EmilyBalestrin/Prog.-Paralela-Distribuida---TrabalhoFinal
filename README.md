# 🏁 Simulação de Corrida com OpenMP

## 📌 Introdução  
Este projeto foi desenvolvido como parte do trabalho final da disciplina de **Programação Paralela e Distribuída**, com o objetivo de aplicar conceitos de concorrência e paralelismo de forma prática e criativa. A proposta simula uma corrida de carros entre múltiplos pilotos (threads), destacando o uso do modelo de memória compartilhada com OpenMP e comparando o desempenho entre execuções sequencial e paralela.

## 🛠️ Tecnologias Utilizadas  
- **Linguagem**: C++  
- **Paralelismo**: OpenMP  
- **Compiladores**: `g++` (Linux) ou `MSVC`/`MinGW` (Windows)  
- **Outros recursos**: `unistd.h` para temporização no Linux e `<windows.h>` para temporização no Windows  

## 🎮 Funcionalidades Principais  
O programa simula uma corrida com cinco pilotos de carro, onde cada um avança em distâncias (unidades) aleatórias até completar um percurso definido. São realizadas **duas simulações**:  

1. **🏎️ Versão Sequencial** (Qualificação):  
   - Pilotos competem um de cada vez.  
   - Usada como baseline para comparação de desempenho.  

2. **🚥 Versão Paralela** (Corrida Real):  
   - Todos os pilotos competem simultaneamente, cada um em uma *thread*.  
   - Utiliza `#pragma omp parallel` para paralelismo.
     
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
   ./corrida.exe
   ```
