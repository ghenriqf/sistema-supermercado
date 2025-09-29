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
    string confSenha;
    

    void cadastrar(Administrador adm) {
        if (senha == confSenha){
            ofstream arquivo("../adms.csv", ios::app);
    
            if (arquivo.is_open()) {
                arquivo << adm.nomeUsuario << ',' << adm.senha << "\n";
                arquivo.close();
                cout << "Conta criada com sucesso!" << endl;
            } else {
                throw runtime_error("ERRO: Nao foi possivel abrir o arquivo");
            }
        } else {
            cout << "As senhas nao coincidem!" << endl;
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

struct Menu {
    Estoque estoque;

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
             << "|_______________________________________________|\n"
             << "|                                               |\n" 
             << "|                  1- Voltar                    |\n"
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
    }
    
    void produtos(){
        cout << "_________________________________________________\n" 
             << "|                                               |\n" 
             << "|                  PRODUTOS                     |\n" 
             << "|_______________________________________________|\n\n"
             << left << setw(9) << "ID" << setw(25) << "   NOME" << setw(8) << "QTD" << setw(15) << "VALOR" << endl;

        estoque.listarProdutos(nomeArquivoAtual);
        
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
             << "|              METODO DE PAGAMENTO              |\n"
             << "|_______________________________________________|\n"
             << "|                                               |\n"
             << "|                  1- A vista                   |\n"
             << "|                                               |\n"
             << "|                  2- Cartao                    |\n"
             << "|                                               |\n"
             << "|                  3- Voltar                    |\n"
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

struct Navegacao {

    Administrador adm;
    Menu menu;
    int opcao = 0;

    void admin(){
        cin >> opcao;
        switch (opcao) {
        case 1: {
            string usuario, senha;
            cout << "Usuario:";
            cin >> usuario;
            cout << "Senha: ";
            cin >> senha;
            break;
        } case 2: {
            cout << "Usuario: ";
            cin >> adm.nomeUsuario;
            cout << "Senha: ";
            cin >> adm.senha;
            cout << "Confirme sua senha: ";
            cin >> adm.confSenha;
            adm.cadastrar(adm);
        }
        default:
            break;
        }
    }

    void cliente(){
        opcao = 0;
        while (opcao < 3) {
            menu.produtos();
            cin >> opcao;
            switch (opcao)
            {
            case 1:
                cout << "Adiciona o produto: " << endl;
                break;
    
            case 2:
            finalizarCompra();
            opcao = 0;
            default:
            break;
        }
    }
}

void finalizarCompra(){
        menu.metodoPagamento();
        cin >> opcao;
        switch (opcao)
        {
        case 1:
            cout << "Obrigado pela compra! volte sempre." << endl;
            break;
        case 2:
            parcelamento();
        default:
            break;
        }
    }

    void parcelamento(){
        menu.cartao();
    }
    
};

int main() {

    Navegacao nav;
    Administrador admin;
    Menu menu;
    
    
    int opcao = 0;
    
    
    while (opcao < 3){
        menu.principal();
        cin >> opcao;
        switch (opcao) {
            case 1:
            menu.administrador();
            nav.admin();
            opcao = 0;
            break;
            
            case 2:
            nav.cliente();
            opcao = 0;
            break;
        }
    }

    cout << "Obrigado pela visita! ate mais.";
}