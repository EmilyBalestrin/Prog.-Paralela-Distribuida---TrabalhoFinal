#include <iostream>
#include <omp.h>    // Biblioteca para paralelismo com OpenMP
#include <vector>
#include <unistd.h>
#include <iomanip>
#include <algorithm>
#include <sstream>

// Configuração do sleep para Windows e Linux
#ifdef _WIN32
#include <windows.h>
#define sleep_ms(ms) Sleep(ms)           // Windows: Sleep usa milissegundos
#else
#include <unistd.h>
#define sleep_ms(ms) usleep((ms) * 1000) // Linux: usleep usa microssegundos
#endif

using namespace std;

const int LIMITE = 50;          // Distância total da corrida
const int NUM_PILOTOS = 5;   // Quantidade de pilotos (threads)

// Função que simula a corrida de um piloto
void corrida_piloto(int id, vector<double>& tempos, vector<string>& logs) {
    int progresso = 0;                    // Armazena quantos "passos" o corredor já deu
    double inicio = omp_get_wtime();     // Marca o tempo de início da corrida desse corredor

    // Loop principal do corredor
    while (progresso < LIMITE) {
        progresso += rand() % 3 + 1;     // O carro avança 1-3 unidades por vez
        if (progresso > LIMITE) progresso = LIMITE;  // Garante que não passe do limite

        sleep_ms(rand() % 101 + 50); // Pausa entre 50ms e 150ms para simula velocidades diferentes

        // Seção crítica para evitar conflito de threads ao imprimir
        #pragma omp critical
        {
            // Cria a barra de progresso visual
            string visual = string(progresso, '=');
            if (progresso < LIMITE) visual += ">";
            cout << "Carro " << (id + 1) << ": " << visual << endl;
        }
    }

    double fim = omp_get_wtime();              // Marca o tempo final da corrida
    double tempoTotal = fim - inicio;          // Calcula o tempo total da corrida

    // Seção crítica para atualizar os vetores
    #pragma omp critical
    {
        tempos[id] = tempoTotal;               // Armazena o tempo no vetor
        ostringstream oss;
        oss << "Piloto " << (id + 1) << " terminou em "
            << fixed << setprecision(3)
            << tempoTotal << " segundos.";
        logs[id] = oss.str();                  // Salva o log de tempo no vetor
    }
}

// Versão sequencial
void corrida_sequencial(vector<double>& tempos, vector<string>& logs) {
    for (int i = 0; i < NUM_PILOTOS; ++i) {
        corrida_piloto(i, tempos, logs);
    }
}

// Versão paralela
void corrida_paralela(vector<double>& tempos, vector<string>& logs) {
#pragma omp parallel num_threads(NUM_PILOTOS)
    {
        int id = omp_get_thread_num();
        corrida_piloto(id, tempos, logs);
    }
}

// Mostra os resultados na tela
void exibir_resultados(const vector<double>& tempos, const vector<string>& logs) {
    vector<pair<double, int>> resultado;
    for (int i = 0; i < NUM_PILOTOS; ++i) {
        resultado.emplace_back(tempos[i], i);
    }
    sort(resultado.begin(), resultado.end());  // Ordena do menor tempo

    // Imprime resultados
    cout << "\n=== TEMPOS INDIVIDUAIS ===\n";
    for (const auto& log : logs) {
        cout << log << endl;
    }

    cout << "\n=== CLASSIFICAÇÃO FINAL ===\n";
    for (size_t pos = 0; pos < resultado.size(); ++pos) {
        cout << pos + 1 << " lugar - Piloto " << (resultado[pos].second + 1)
             << ": " << fixed << setprecision(3)
             << resultado[pos].first << " segundos." << endl;
    }
}

// Função principal
int main() {
    unsigned seed = time(0);
    srand(seed);

    // Execução sequencial
    vector<double> tempos_seq(NUM_PILOTOS, 0.0);
    vector<string> logs_seq(NUM_PILOTOS);

    cout << "\n=== SIMULACAO DE CORRIDA/QUALIFICACAO (SEQUENCIAL) ===\n";
    double inicio_seq = omp_get_wtime();
    corrida_sequencial(tempos_seq, logs_seq);
    double fim_seq = omp_get_wtime();
    exibir_resultados(tempos_seq, logs_seq);

    // Execução paralela
    srand(seed); // Reseta a seed para mesma sequência aleatória
    vector<double> tempos_par(NUM_PILOTOS, 0.0);
    vector<string> logs_par(NUM_PILOTOS);

    cout << "\n\n=== SIMULACAO DE CORRIDA (PARALELA) ===\n";
    double inicio_par = omp_get_wtime();
    corrida_paralela(tempos_par, logs_par);
    double fim_par = omp_get_wtime();
    exibir_resultados(tempos_par, logs_par);

    // Comparação de desempenho
    double tempo_total_seq = fim_seq - inicio_seq;
    double tempo_total_par = fim_par - inicio_par;

    cout << "\n\n=== ANALISE DE DESEMPENHO ===\n";
    cout << fixed << setprecision(3);
    cout << "Tempo total sequencial: " << tempo_total_seq << " segundos\n";
    cout << "Tempo total paralelo:   " << tempo_total_par << " segundos\n";
    cout << "Speedup: " << tempo_total_seq / tempo_total_par << endl;

    return 0;
}