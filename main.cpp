#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>


using namespace std;

string nomeArquivoEstoque = "../produtos.csv";
string nomeArquivoAdms = "../adms.csv";

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

    Administrador buscarAdministrador (string nomeUsuario) {
        ifstream estoque(nomeArquivoAdms);
        Administrador adm;

        if (!estoque.is_open()) {
            throw runtime_error("ERRO: Nao foi possível abrir o arquivo!");
        }

        string linha;

        while (getline(estoque, linha)) {
            stringstream ss(linha);

            string campo;
            getline(ss, campo, ',');

            if (nomeUsuario == campo) {
                adm.nomeUsuario = campo;
                getline(ss,campo,',');
                adm.senha = campo;
                return adm;
            }
        }

        return Administrador{};
    }
};

struct Estoque {

    Produto buscarProduto(int id) {
        ifstream estoque(nomeArquivoEstoque);

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

        return Produto{};
        estoque.close();
    }

    void atualizarProduto(Produto atualizado) {

        ofstream temp("../temp.csv");
        ifstream arquivo(nomeArquivoEstoque);

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

        remove(nomeArquivoEstoque.c_str());
        rename("../temp.csv", nomeArquivoEstoque.c_str());
    }

    void cadastrarProduto(Produto produto) {
        ofstream arquivo(nomeArquivoEstoque, ios::app);

        if (arquivo.is_open()) {
            arquivo << produto.id << ',' << produto.nomeProduto << ',' << produto.quantidadeProduto << ',' << produto.valorProduto << "\n";
        }
        else {
            throw runtime_error("ERRO: Nao foi possivel abrir o arquivo!");
        }
    }

    vector<Produto> listarProdutos() {
        ifstream arquivo(nomeArquivoEstoque);
        string linha;
        vector<Produto> produtos;

        if (!arquivo.is_open()) {
            throw runtime_error("ERRO: Nao foi possível abrir o arquivo!");
        }
        
        while (getline(arquivo, linha)) {
            stringstream ss(linha);
            Produto produto;
            string campo;

            getline(ss, campo, ',');
            produto.id = stoi(campo);

            getline(ss, produto.nomeProduto, ',');

            getline(ss, campo, ',');
            produto.quantidadeProduto = stof(campo);

            getline(ss, campo, ',');
            produto.valorProduto = stof(campo);

            produtos.push_back(produto);
           
        }
        
        
        arquivo.close();
        return produtos;
    }
};

struct Validacoes {

    Estoque estoque;
    Administrador adm;
    
    void opcoesMenu(string entrada) {
        if (entrada != "1" && entrada != "2" && entrada != "3" ) {
            throw runtime_error("ERRO: Entrada invalida!");
        }
    }

    void cadastrarProduto(Produto produto) {
        
        if (produto.nomeProduto.length() <= 2 || produto.nomeProduto.length() > 25) {
            throw runtime_error("ERRO: Nome do produto invalido!");

        } else if (produto.quantidadeProduto <= 0) {
            throw runtime_error("ERRO: Quantidade invalida!");

        } else if (produto.valorProduto <= 0) {
            throw runtime_error("ERRO: Valor invalido!");
        } else {
            estoque.cadastrarProduto(produto);
        }

    }

    void cadastrarAdministrador(Administrador administrador, string confSenha) {
        Administrador admBusca = adm.buscarAdministrador(administrador.nomeUsuario);

        if(!admBusca.nomeUsuario.empty()) {
            throw runtime_error("ERRO: Nome de usuario ja cadastrado!");
        }
        else if (administrador.nomeUsuario.length() <= 2 || administrador.nomeUsuario.length() > 25) {
            throw runtime_error("ERRO: Nome de usuario invalido!");

        } else if (administrador.senha != confSenha) {
            throw runtime_error("ERRO: As senhas nao coincidem!");

        } else if (administrador.senha.length() <= 2) {
            throw runtime_error("ERRO: Senha invalida!");
        } else {
            adm.cadastrar(administrador);
        }
    }

    void loginAdiministrador (Administrador administrador) {
        Administrador admBusca = adm.buscarAdministrador(administrador.nomeUsuario);

        if (admBusca.nomeUsuario.empty()) {
            throw runtime_error("ERRO: Login invalido!");
        }

        else if (admBusca.senha != administrador.senha) {
            throw runtime_error("ERRO: Senha invalida!");
        }

    }
};

int main() {
    srand(time(0));
}