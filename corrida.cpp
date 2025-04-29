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

