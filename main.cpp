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
    
    void cadastrarProduto(Produto produto) {
        ofstream arquivo(nomeArquivoEstoque, ios::app);

        if (arquivo.is_open()) {
            arquivo << produto.id << ',' << produto.nomeProduto << ',' << produto.quantidadeProduto << ',' << produto.valorProduto << "\n";
            arquivo.close();
        }
        else {
            throw runtime_error("ERRO: Nao foi possivel abrir o arquivo!");
            arquivo.close();
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

    void removerProduto(int id) {
        ofstream temp("../temp.csv");
        ifstream arquivo(nomeArquivoEstoque);

        if (!arquivo.is_open() || !temp.is_open()) {
            throw runtime_error("ERRO: Nao foi possível abrir o arquivo!");
        }

        string linha;

        while (getline(arquivo, linha)) {
            string campo;

            stringstream ss(linha);
            getline(ss, campo, ',');

            if (to_string(id) == campo) {
                continue;
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

    Produto buscarProdutoPorId(int id) {
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

        estoque.close();
        return Produto{};
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
        vector <Produto> produtos = estoque.listarProdutos();

        for (Produto prod : produtos) {
            if (prod.nomeProduto == produto.nomeProduto ) {
                throw runtime_error("ERRO: Produto ja cadastrado!");
            }
        }
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

struct Menu {

    Validacoes validar;
    
    string principal() {
        
        string entradaUsuario;

        cout << "_______________________________________________\n"
             << "                                               \n"
             << "                MENU PRINCIPAL                 \n"
             << "_______________________________________________\n"
             << "                                               \n"
             << "               1| Administrador                \n"
             << "                                               \n"
             << "               2| Cliente                      \n"
             << "                                               \n"
             << "               3| Sair do Programa             \n"
             << "                                               \n"
             << "_______________________________________________\n"
             << "ESCOLHA A OPCAO: ";
             cin >> entradaUsuario;
            try {
                validar.opcoesMenu(entradaUsuario);
                return entradaUsuario;
            } catch (const runtime_error& e) {
                cout << e.what();
            }
            
    } 

    string administrador(){

        string entradaUsuario;

        cout << "_______________________________________________\n" 
             << "                                               \n" 
             << "                ADMINISTRADOR                  \n" 
             << "_______________________________________________\n" 
             << "                                               \n" 
             << "               1| Login                        \n" 
             << "                                               \n" 
             << "               2| Cadastrar                    \n" 
             << "                                               \n" 
             << "               3| Voltar                       \n" 
             << "                                               \n" 
             << "_______________________________________________\n\n"
             << "ESCOLHA A OPCAO: ";
            cin >> entradaUsuario;
            try {
                validar.opcoesMenu(entradaUsuario);
                return entradaUsuario;
            } catch (const runtime_error& e) {
                cout << e.what();
            }

    }

    void login(){

        Administrador administrador;

        cout << "_______________________________________________\n" 
             << "                                               \n" 
             << "                    LOGIN                      \n" 
             << "_______________________________________________\n\n";
            cout << "NOME DE USUARIO: ";
            cin >> administrador.nomeUsuario;
            cout << "SENHA: ";
            cin >> administrador.senha;
            try {
                validar.loginAdiministrador(administrador);
                cout << "Administrador conectado com sucesso!";
            } catch (const runtime_error& e) {
                cout << e.what();
            }
    }

    void cadastro(){

        Administrador administrador;
        string confSenha;

        cout << "_______________________________________________\n"
             << "                                               \n" 
             << "                  CADASTRAR                    \n"
             << "_______________________________________________\n\n";
            cout << "LOGIN: ";
            cin >> administrador.nomeUsuario;
            cout << "SENHA: ";
            cin >> administrador.senha;

            try {
                validar.cadastrarAdministrador(administrador, confSenha);
                cout << "Administrador cadastrado com sucesso!";
            } catch (const runtime_error& e) {
                cout << e.what();
            } 


    }
    
    void produtos(){
        cout << "_______________________________________________\n" 
             << "                                               \n" 
             << "                  PRODUTOS                     \n" 
             << "_______________________________________________\n\n"
             << left << setw(9) << "ID" << setw(25) << "   NOME" << setw(8) << "QTD" << setw(15) << "VALOR" << endl;

        
        cout << "_______________________________________________\n"
             << "                                               \n"
             << "          1| Adicionar produto ao carrinho     \n"
             << "                                               \n"
             << "          2| Finalizar compra                  \n"
             << "                                               \n"
             << "          3| Menu principal                    \n"
             << "_______________________________________________\n\n";
    }
    
    void metodoPagamento() {
        cout << "_______________________________________________\n"
             << "                                               \n"
             << "              METODO DE PAGAMENTO              \n"
             << "_______________________________________________\n"
             << "                                               \n"
             << "                 1| A vista                    \n"
             << "                                               \n"
             << "                 2| Cartao                     \n"
             << "                                               \n"
             << "                 3| Voltar                     \n"
             << "_______________________________________________\n\n";   
    }
    
    void cartao(){
        float valor = 5342.14;
        cout << "_______________________________________________\n"
             << "                        |                      \n"
             << "      PARCELAMENTO      |        VALOR         \n"
             << "________________________|______________________\n"
             << "|                       |                      \n";
             for(int i = 2; i <= 12; i++) {
                if (i < 4) {
                    cout << "| " << right << setw(2) << i << left << setw(21) << "x sem juros"  << "|   R$ "  << left << setw(15) << valor/i << " |" << endl;
                } else {
                    cout << "| " << right << setw(2) << i << left << setw(21) << "x com 10% juros" << "|   R$ " << left << setw(15) << valor/i + (valor * 0.10)  << " |" << endl;
                }
             }
        cout << "_______________________|_______________________\n\n";
    }
    
};


int main() {
    srand(time(0));
}