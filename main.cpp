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
        cout << "___________|MENU PRINCIPAL|___________" << endl
             << "                                      " << endl
             << "            ENTRAR COMO...            " << endl
             << "                                      " << endl
             << "         1)  ADMINISTRADOR            " << endl
             << "                                      " << endl
             << "         2)    CLIENTE                " << endl
             << "                                      " << endl
             << "         3) SAIR DO PROGRAMA          " << endl
             << "______________________________________" << endl;
    } 

    void login(){
        cout << "_______________|LOGIN|________________" << endl
             << "                                      " << endl
             << "            ENTRAR COMO...            " << endl
             << "                                      " << endl
             << "         1)  ADMINISTRADOR            " << endl
             << "                                      " << endl
             << "         2)    CLIENTE                " << endl
             << "                                      " << endl
             << "         3) SAIR DO PROGRAMA          " << endl
             << "______________________________________" << endl;
    }
    
    void produtos(){
        cout << "_______________|PRODUTOS|________________" << endl
             << left << setw(5) << "ID" << setw(22) << "   NOME" << setw(6) << "QTD" << setw(10) << "VALOR" << endl
             << left << setw(5) << "0" << setw(22) << "Banana" << setw(6) << "152" << setw(10) << "R$5,20" << endl
             << left << setw(5) << "1" << setw(22) << "Morango" << setw(6) << "85" << setw(10) << "R$8,54" << endl
             << left << setw(5) << "2" << setw(22) << "Kiwi" << setw(6) << "98" << setw(10) << "R$4,87" << endl
             << left << setw(5) << "3" << setw(22) << "Goiaba" << setw(6) << "63" << setw(10) << "R$6,32" << endl
             << "_________________________________________" << endl
             << "                                         " << endl
             << "     1) ADICIONAR PRODUTO AO CARRINHO    " << endl
             << "                                         " << endl
             << "     2) MENU PRINCIPAL                   " << endl
             << "                                         " << endl
             << "     3) FINALIZAR COMPRA                 " << endl
             << "_________________________________________" << endl;
    }
    
    void metodoPagamento() {
        cout << "__________|METODO DE PAGAMENTO|__________" << endl
             << "                                         " << endl
             << "              1) A VISTA                 " << endl
             << "                                         " << endl
             << "              2) CARTAO                  " << endl
             << "_________________________________________" << endl;   
    }
    
    void cartao(){
        float valor = 5342.14;
        cout << "____________________________________" << endl
             << "|                    |             |" << endl
             << "|    Parcelamento    | Valor (R$)  |" << endl
             << "|____________________|_____________|" << endl
             << "|                    |             |" << endl
             << "|" << left << setw(20) << " 2x SEM JUROS"  << "| R$"  << right << setw(9) << valor/2   << " |" << endl
             << "|" << left << setw(20) << " 3x SEM JUROS" << "| R$" << right << setw(9) << valor/3   << " |" << endl
             << "|" << left << setw(20) << " 4x COM 10% JUROS" << "| R$" << right << setw(9) << valor/4 + (valor * 0.10)  << " |" << endl
             << "|" << left << setw(20) << " 5x COM 10% JUROS" << "| R$" << right << setw(9) << valor/5 + (valor * 0.10) << " |" << endl
             << "|" << left << setw(20) << " 6x COM 10% JUROS" << "| R$" << right << setw(9) << valor/6 + (valor * 0.10) << " |" << endl
             << "|" << left << setw(20) << " 7x COM 10% JUROS" << "| R$" << right << setw(9) << valor/7 + (valor * 0.10) << " |" << endl
             << "|" << left << setw(20) << " 8x COM 10% JUROS" << "| R$" << right << setw(9) << valor/8 + (valor * 0.10) << " |" << endl
             << "|" << left << setw(20) << " 9x COM 10% JUROS" << "| R$" << right << setw(9) << valor/9  + (valor * 0.10)<< " |" << endl
             << "|" << left << setw(20) << " 10x COM 10% JUROS" << "| R$" << right << setw(9) << valor/10 + (valor * 0.10) << " |" << endl
             << "|" << left << setw(20) << " 11x COM 10% JUROS" << "| R$" << right << setw(9) << valor/11 + (valor * 0.10) << " |" << endl
             << "|" << left << setw(20) << " 12x COM 10% JUROS" << "| R$" << right << setw(9) << valor/12 + (valor * 0.10) << " |" << endl
             << "|____________________|_____________|" << endl;
    }
    
};

int main() {

    Menu menu;

    menu.produtos();

}