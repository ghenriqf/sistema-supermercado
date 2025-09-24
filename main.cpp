#include <iostream>
#include <iomanip>
using namespace std;

struct Produto {
    string nomeProduto;
    float quantidadeProduto;
    float valorProduto;
    
};

struct Estoque {
    


    void cadastrarProduto(Produto produto) {
        
    }

    string listarProdutos() {

    } 

};

struct Menu {
    void principal() {
        cout << "_________________________________________________\n"
             << "|                                               |\n"
             << "|                 MENU PRINCIPAL                |\n"
             << "|_______________________________________________|\n"
             << "|ENTRAR COMO:                                   |\n"
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

    void cadastrar(){
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
             << "|                  1- a vista                   |\n"
             << "|                                               |\n"
             << "|                  2) CARTAO                    |\n"
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