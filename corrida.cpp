#include <iostream>
#include <omp.h>    // Biblioteca para paralelismo com OpenMP
#include <vector>
#include <unistd.h>
#include <iomanip>
#include <algorithm>
#include <sstream>

using namespace std;

const int LIMITE = 50;          // Distância total da corrida (em "passos")
const int NUM_CORREDORES = 5;   // Quantidade de corredores (threads)

// Função que simula a corrida de um corredor
void correr(int id, vector<double>& tempos, vector<string>& logs) {
    int progresso = 0;                    // Armazena quantos "passos" o corredor já deu
    double inicio = omp_get_wtime();     // Marca o tempo de início da corrida desse corredor

    // Enquanto o corredor não chegar ao fim...
    while (progresso < LIMITE) {
        progresso += rand() % 3 + 1;     // Avança de 1 a 3 passos aleatórios
        if (progresso > LIMITE) progresso = LIMITE;  // Garante que não passe do limite

        usleep(rand() % 100000 + 50000); // Pausa entre 50ms e 150ms para simula velocidades diferentes

        // Cria a barra de progresso visual
        string visual = string(progresso, '=');
        if (progresso < LIMITE) visual += ">";

        // Seção crítica para evitar conflito de threads ao imprimir
        #pragma omp critical
        {
            cout << "Corredor " << (id + 1) << ": " << visual << endl;
        }
    }

    double fim = omp_get_wtime();              // Marca o tempo final da corrida
    double tempoTotal = fim - inicio;          // Calcula o tempo total da corrida

    // Seção crítica para atualizar os vetores
    #pragma omp critical
    {
        tempos[id] = tempoTotal;               // Armazena o tempo no vetor
        ostringstream oss;
        oss << "Corredor " << (id + 1) << " terminou em "
            << fixed << setprecision(3)
            << tempoTotal << " segundos.";
        logs[id] = oss.str();                  // Salva o log de tempo no vetor
    }
}

