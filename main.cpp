#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

string nomeArquivoAtual = "../produtos.csv";


struct Produto {
    long id; 
    string nomeProduto;
    float quantidadeProduto;
    float valorProduto;

};

struct Estoque {

    void cadastrarProduto(Produto produto) {
        ofstream arquivo(nomeArquivoAtual, ios::app);

        arquivo << "\n";
        arquivo << produto.id << ',' << produto.nomeProduto << ',' << produto.quantidadeProduto << ',' << produto.valorProduto;
    }

    void listarProdutos(string nomeArquivo) {
        ifstream arquivo(nomeArquivo);
        string linha;

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
                default:
                    cout << "R$";
                    cout << left << setw(15) << palavra; 
                    break;
                }  
            }
            cout << endl;
        }

        arquivo.close();
    }

};


void menuPrincipal() {
    
}

int main() {
    Estoque estoque;
    Produto produto;
    Produto produto2;

    produto.nomeProduto = "Suco de laranja";
    produto.quantidadeProduto = 10;
    produto.valorProduto = 24.2;
    
    estoque.cadastrarProduto(produto);
    estoque.listarProdutos(nomeArquivoAtual);
    
}