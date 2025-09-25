#include <iostream>
#include <iomanip>
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
struct Cadastrar {
    
    string cadastro(){
        
    }

};

struct Menu {
    void principal() {
        cout << "_________________________________________________\n"
             << "|                                               |\n"
             << "|                MENU PRINCIPAL                 |\n"
             << "|_______________________________________________|\n"
             << "|                                               |\n"
             << "|                 ENTRAR COMO:                  |\n"
             << "|                                               |\n"
             << "|               1- Administrador                |\n"
             << "|                                               |\n"
             << "|               2- Cliente                      |\n"
             << "|                                               |\n"
             << "|               3- Sair do Programa             |\n"
             << "|                                               |\n"
             << "|_______________________________________________|\n";
    } 

    void administrador(){
        cout << "_________________________________________________\n" 
             << "|                                               |\n" 
             << "|                ADMINISTRADOR                  |\n" 
             << "|_______________________________________________|\n" 
             << "|                                               |\n" 
             << "|               1- Login                        |\n" 
             << "|                                               |\n" 
             << "|               2- Cadastrar                    |\n" 
             << "|                                               |\n" 
             << "|               3- Voltar                       |\n" 
             << "|                                               |\n" 
             << "|_______________________________________________|\n";
    }

    void login(){
        cout << "_________________________________________________\n" 
             << "|                                               |\n" 
             << "|                    LOGIN                      |\n" 
             << "|_______________________________________________|\n";

        string usuario, senha;

        cout << "Usuario: ";
        cin >> usuario;
        cout << "Senha: ";
        cin >> senha;
    }

    void cadastro(){
        cout << "_________________________________________________\n"
             << "|                                               |\n" 
             << "|                  CADASTRAR                    |\n"
             << "|_______________________________________________|\n\n";

        string usuario, senha;

        cout << "Usuario: ";
        cin >> usuario;
        cout << "Senha: ";
        cin >> senha;
        cout << "Confirme sua senha: ";
    }
    
    void produtos(){
        cout << "_________________________________________________\n" 
             << "|                                               |\n" 
             << "|                  PRODUTOS                     |\n" 
             << "|_______________________________________________|\n\n"
             << left << setw(5) << "ID" << setw(22) << "   NOME" << setw(6) << "QTD" << setw(10) << "VALOR" << endl;
            
        
        cout << "_________________________________________________\n"
             << "|                                               |\n"
             << "|          1- Adicionar produto ao carrinho     |\n"
             << "|                                               |\n"
             << "|          2- Finalizar compra                  |\n"
             << "|                                               |\n"
             << "|          3- Menu principal                    |\n"
             << "|_______________________________________________|\n";
    }
    
    void metodoPagamento() {
        cout << "_________________________________________________\n"
             << "|                                               |\n"
             << "|             METODO DE PAGAMENTO               |\n"
             << "|_______________________________________________|\n"
             << "|                                               |\n"
             << "|                  1- A vista                   |\n"
             << "|                                               |\n"
             << "|                  2- Cartao                    |\n"
             << "|_______________________________________________|\n";   
    }
    
    void cartao(){
        float valor = 5342.14;
        cout << "_________________________________________________\n"
             << "|                        |                      |\n"
             << "|      PARCELAMENTO      |        VALOR         |\n"
             << "|________________________|______________________|\n"
             << "|                        |                      |\n";
             for(int i = 2; i <= 12; i++) {
                if (i < 4) {
                    cout << "| " << right << setw(2) << i << left << setw(21) << "x sem juros"  << "|   R$ "  << left << setw(15) << valor/i << " |" << endl;
                } else {
                    cout << "| " << right << setw(2) << i << left << setw(21) << "x com 10% juros" << "|   R$ " << left << setw(15) << valor/i + (valor * 0.10)  << " |" << endl;
                }
             }
        cout << "|________________________|______________________|\n";
    }
    
};

int main() {


    Menu menu;

    menu.principal();

    menu.produtos();

    menu.metodoPagamento();

    menu.cartao();
}