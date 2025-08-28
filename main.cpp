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
        cout << "|------|MENU PRINCIPAL|------|" << endl;
        cout << "|                            |" << endl;
        cout << "|       ENTRAR COMO...       |" << endl;
        cout << "|                            |" << endl;
        cout << "|    1)  ADMINISTRADOR       |" << endl;
        cout << "|                            |" << endl;
        cout << "|    2)    CLIENTE           |" << endl;
        cout << "|                            |" << endl;
        cout << "|    3) SAIR DO PROGRAMA     |" << endl;
        cout << "|----------------------------|" << endl;
    } 

    void login(){
        cout << "|----------|LOGIN|-----------|" << endl;
        cout << "|                            |" << endl;
        cout << "|      1)  ENTRAR            |" << endl;
        cout << "|                            |" << endl;
        cout << "|      2) CADASTRAR          |" << endl;
        cout << "|                            |" << endl;
        cout << "|      3)  VOLTAR            |" << endl;
        cout << "|----------------------------|" << endl;
    }
    
    void produtos(){
        cout << "                               **         " << endl;
        cout << "                             *_*.*       " << endl;
        cout << "                            /**\\**         " << endl;
        cout << "                           **.***            " << endl;
        cout << "                           ***/            " << endl;
        cout << "                           \\*            " << endl;
        cout << "                         _____            " << endl;
        cout << "                        |_____|            " << endl;
        cout << "                         \\   /             " << endl;
        cout << "                         |  |             " << endl;
        cout << "  _______________________/__\\_________" << endl;
        cout << " //////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << endl;
        cout << " |------------|PRODUTOS|-------------|" << endl;
        cout << "///////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << endl;
        cout << "| " << left << setw(5) << "ID" << setw(15) << "   NOME" << "| " << setw(6) << "QTD" << setw(10) << "VALOR" << "|" << endl;
        cout << "| " << left << setw(5) << "0" << setw(15) << "Banana" << "| " << setw(6) << "152" << setw(10) << "R$5,20" << "|" << endl;
        cout << "| " << left << setw(5) << "1" << setw(15) << "Morango" << "| " << setw(6) << "85" << setw(10) << "R$8,54" << "|" << endl;
        cout << "| " << left << setw(5) << "2" << setw(15) << "Kiwi" << "| " << setw(6) << "98" << setw(10) << "R$4,87" << "|" << endl;
        cout << "| " << left << setw(5) << "3" << setw(15) << "Goiaba" << "| " << setw(6) << "63" << setw(10) << "R$6,32" << "|" << endl;
        cout << "|---------------------------------------|" << endl;
        cout << "|                                       |" << endl;
        cout << "_________________________________________" << endl;
        cout << "|                                       |" << endl;
        cout << "|   1) ADICIONAR PRODUTO AO CARRINHO    |" << endl;
        cout << "|                                       |" << endl;
        cout << "|   2) MENU PRINCIPAL                   |" << endl;
        cout << "|                                       |" << endl;
        cout << "|   3) FINALIZAR COMPRA                 |" << endl;
        cout << "|---------------------------------------|" << endl;
    }
    
    void metodoPagamento() {
        cout << "+---------|METODO DE PAGAMENTO|---------+" << endl;
        cout << "|                                       |" << endl;
        cout << "|           1) A VISTA                  |" << endl;
        cout << "|                                       |" << endl;
        cout << "|           2) CARTAO                   |" << endl;
        cout << "+---------------------------------------+" << endl;   
    }
    
    void cartao(){
        float valor = 5342.14;
        cout << "+--------------------+-------------+" << endl;
        cout << "| Parcelamento       | Valor (R$)  |" << endl;
        cout << "+--------------------+-------------+" << endl;
        cout << "|                    |             |" << endl;
        cout << "|" << left << setw(20) << " 2x SEM JUROS"  << "| R$"  << right << setw(9) << valor/2   << " |" << endl;
        cout << "|" << left << setw(20) << " 3x SEM JUROS" << "| R$" << right << setw(9) << valor/3   << " |" << endl;
        cout << "|" << left << setw(20) << " 4x COM 10% JUROS" << "| R$" << right << setw(9) << valor/4 + (valor * 0.10)  << " |" << endl;
        cout << "|" << left << setw(20) << " 5x COM 10% JUROS" << "| R$" << right << setw(9) << valor/5 + (valor * 0.10) << " |" << endl;
        cout << "|" << left << setw(20) << " 6x COM 10% JUROS" << "| R$" << right << setw(9) << valor/6 + (valor * 0.10) << " |" << endl;
        cout << "|" << left << setw(20) << " 7x COM 10% JUROS" << "| R$" << right << setw(9) << valor/7 + (valor * 0.10) << " |" << endl;
        cout << "|" << left << setw(20) << " 8x COM 10% JUROS" << "| R$" << right << setw(9) << valor/8 + (valor * 0.10) << " |" << endl;
        cout << "|" << left << setw(20) << " 9x COM 10% JUROS" << "| R$" << right << setw(9) << valor/9  + (valor * 0.10)<< " |" << endl;
        cout << "|" << left << setw(20) << " 10x COM 10% JUROS" << "| R$" << right << setw(9) << valor/10 + (valor * 0.10) << " |" << endl;
        cout << "|" << left << setw(20) << " 11x COM 10% JUROS" << "| R$" << right << setw(9) << valor/11 + (valor * 0.10) << " |" << endl;
        cout << "|" << left << setw(20) << " 12x COM 10% JUROS" << "| R$" << right << setw(9) << valor/12 + (valor * 0.10) << " |" << endl;
        cout << "+--------------------+-------------+" << endl;
    }
    
};

int main() {

    Menu menu;

    menu.produtos();

}