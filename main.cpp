#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

string nomeArquivoAtual = "../produtos.csv";

struct Produto {
    int id; 
    string nomeProduto;
    float quantidadeProduto;
    float valorProduto;

    Produto () {
         id = rand();
    }
};

struct Administrador {

    string nomeUsuario;
    string senha;
    
    void cadastrar(Administrador adm) {
        ofstream arquivo("../adms.csv", ios::app);

        if (arquivo.is_open()) {
            arquivo << adm.nomeUsuario << ',' << adm.senha << "\n";
            arquivo.close();
        } else {
            throw runtime_error("ERRO: Nao foi possivel abrir o arquivo");
        }
    }


};

struct Estoque {

    
    void cadastrarProduto(Produto produto) {
        ofstream arquivo(nomeArquivoAtual, ios::app);

        if (arquivo.is_open()) {
            arquivo << "\n";
            arquivo << produto.id << ',' << produto.nomeProduto << ',' << produto.quantidadeProduto << ',' << produto.valorProduto;
        } else {
              throw runtime_error("ERRO: Nao foi possivel abrir o arquivo");
        }
        
    }

    void listarProdutos(string nomeArquivo) {
        ifstream arquivo(nomeArquivo);
        string linha;

        if (arquivo.is_open()) {
            while (getline(arquivo, linha)) {
                stringstream ss(linha);
                string palavra;

                int coluna = 0;
                while (getline(ss, palavra, ',')) {
                    switch (coluna) {
                    case 0:
                        cout << left << setw(9) << palavra; 
                        coluna++;
                        break;
                    case 1:
                        cout << left << setw(25) << palavra; 
                        coluna++;
                        break;
                    case 2:
                        cout << left << setw(8) << palavra; 
                        coluna++;
                        break;
                    case 3:
                        cout << "R$";
                        cout << left << setw(15) << palavra; 
                        break;
                }  
            } 
            
            cout << endl;

            } 
        } 
        else {
              throw runtime_error("ERRO: Nao foi possivel abrir o arquivo");
        }
        arquivo.close();
    }

};

int main() {

}