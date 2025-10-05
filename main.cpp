#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

struct Tempo
{
    int hora, minuto, segundo;

    Tempo ()    {
        time_t tempo = time(0);
        tm* x = localtime(&tempo);
        hora = x -> tm_hour;
        minuto = x -> tm_min;
        segundo = x -> tm_sec;
        
        cout << setfill('0') << setw(2) << hora << ":" << setw(2) << minuto << ":" << setw(2) << segundo;
        // Se o setw for menor de 2, ele adiciona um 0 a esquerda
    }
    
};

int main()  {
    Tempo();
}