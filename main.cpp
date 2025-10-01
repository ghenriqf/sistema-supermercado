#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

struct Produto {
    int id;
    string nomeProduto;
    float quantidadeProduto;
    float valorProduto;

    Produto() {
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
        }
        else {
            throw runtime_error("ERRO: Nao foi possivel abrir o arquivo");
        }
    }
};

struct Estoque {

    string nomeArquivoAtual;

    Produto buscarProduto(int id) {
        ifstream estoque(nomeArquivoAtual);

        if (!estoque.is_open()) {
            throw runtime_error("ERRO: Nao foi possível abrir o arquivo!");
        }

        string linha;
        Produto produto;

        while (getline(estoque, linha)) {
            stringstream ss(linha);

            string campo;

            getline(ss, campo, ',');
            produto.id = stoi(campo);

            if (produto.id == id) {
                getline(ss, produto.nomeProduto, ',');

                getline(ss, campo, ',');
                produto.quantidadeProduto = stof(campo);

                getline(ss, campo, ',');
                produto.valorProduto = stof(campo);

                return produto;
            }
        }

        throw runtime_error("ERRO: Produto nao encontrado!");
        estoque.close();
    }

    void atualizarProduto(Produto atualizado) {

        ofstream temp("../temp.csv");
        ifstream arquivo(nomeArquivoAtual);

        if (!arquivo.is_open() || !temp.is_open()) {
            throw runtime_error("ERRO: Nao foi possível abrir o arquivo!");
        }

        string linha;

        while (getline(arquivo, linha)) {
            string id;

            stringstream ss(linha);
            getline(ss, id, ',');

            if (id == to_string(atualizado.id)) {
                temp << atualizado.id << ',' << atualizado.nomeProduto << ',' << atualizado.quantidadeProduto << ',' << atualizado.valorProduto << endl;
            }
            else {
                temp << linha << endl;
            }
        }

        arquivo.close();
        temp.close();

        remove(nomeArquivoAtual.c_str());
        rename("../temp.csv", nomeArquivoAtual.c_str());
    }

    void cadastrarProduto(Produto produto) {
        ofstream arquivo(nomeArquivoAtual, ios::app);

        if (arquivo.is_open()) {
            arquivo << produto.id << ',' << produto.nomeProduto << ',' << produto.quantidadeProduto << ',' << produto.valorProduto << "\n";
        }
        else {
            throw runtime_error("ERRO: Nao foi possivel abrir o arquivo!");
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
    srand(time(0));
}