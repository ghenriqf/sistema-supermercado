#include <iostream> // Biblioteca padrão
#include <fstream> // Manipulação de arquivos
#include <sstream> // Maniulação de strings
#include <string> // Utilização de strings
#include <iomanip> // Formatação do design
#include <cstdlib> // Funções utilitarias de C
#include <ctime> // Tempo real
#include <vector> // Vetores dinamicos

using namespace std;

string nomeArquivoEstoque = "../produtos.csv"; // CSV = Comma Separated Values
string nomeArquivoAdms = "../adms.csv";

struct Produto {
    int id; 
    string nomeProduto;
    float quantidadeProduto;
    float valorProduto;

    Produto () { // Metodo construtor = Chamado imediatamente ao iniciar a struct!
         id = rand(); 
    }
};

struct Administrador {

    string nomeUsuario;
    string senha;
    
    void cadastrar(Administrador adm) {
        ofstream arquivo("../adms.csv", ios::app); // IOS:APP ---> "Append" ao arquivo existente

        if (arquivo.is_open()) {
            arquivo << adm.nomeUsuario << ',' << adm.senha << "\n";
            arquivo.close();
        }
        else {
            throw runtime_error("ERRO: Nao foi possivel abrir o arquivo");
            // função throw = Lança uma exceção de erro a ser tratado
            // runtime_error = Trata de erros genericos sem explodir o programa!
        }
    }

    Administrador buscarAdministrador (string nomeUsuario) {
        ifstream estoque(nomeArquivoAdms);
        Administrador adm;

        if (!estoque.is_open()) {
            throw runtime_error("ERRO: Nao foi possível abrir o arquivo!");
        }

        string linha;

        while (getline(estoque, linha)) { // Pega a linha do arquivo e passa para a variavel "linha"
            stringstream ss(linha); // transforma essa linha em uma variavel "stringstream" (suscetivel a entradas e saidas do usuario)

            string campo;
            getline(ss, campo, ','); // Divide a string por virgula!

            if (nomeUsuario == campo) {
                adm.nomeUsuario = campo;
                getline(ss,campo,',');
                adm.senha = campo;
                return adm;
            }
        }

        return Administrador{}; // struct vazia
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

    void removerProduto (bool confirmar, int id) {
        Produto produto = estoque.buscarProdutoPorId(id);

        if (!confirmar) {
            throw runtime_error("Informe o id novamente!");
        } else if (produto.nomeProduto.empty()) {
            throw runtime_error("ERRO: Produto nao encontrado!");
        } else {
            estoque.removerProduto(id);
        }
    }
};

void listarProdutos(Estoque& estoque) {

    vector<Produto> produtos = estoque.listarProdutos();
        for (Produto produto : produtos) {
            cout << left << setw(11) << produto.id << setw(25) << produto.nomeProduto << setw(8) << produto.quantidadeProduto << setw(15) << produto.valorProduto << endl;
        }
}

struct Interacao {

    Validacoes validar;
    Estoque estoque;

    void menuPrincipal() {
        string entradaUsuario;
        Interacao interacao;
        
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
             << "_______________________________________________\n";
        
        while (true) {
            cout  << "ESCOLHA A OPCAO: ";
            try {
                cin >> entradaUsuario;
                validar.opcoesMenu(entradaUsuario);
                system("cls"); // Limpa a tela!

                int entradaUsuarioInt = stoi(entradaUsuario);
                switch (entradaUsuarioInt)
                {
                case 1:
                    interacao.menuAdministrador();
                    break;
                
                case 2:
                    interacao.menuProdutos();
                    break;
                case 3:
                    cout << "Obrigado por tudo!";
                    exit(0);
                }
                break;
            } 
            catch (const runtime_error& e) { 
                cout << e.what() << endl;
            }
        }
    } 

    void menuAdministrador(){

        string entradaUsuario;
        Interacao interacao;

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
             << "_______________________________________________\n\n";
         while (true) {
            cout  << "ESCOLHA A OPCAO: ";
            try {
                cin >> entradaUsuario;
                validar.opcoesMenu(entradaUsuario);
                system("cls");

                int entradaUsuarioInt = stoi(entradaUsuario);
                switch (entradaUsuarioInt)
                {
                case 1:
                    interacao.menuLoginAmd();
                    break;
                
                case 2:
                    interacao.menuCadastroAdm();
                    break;
                case 3:
                    return;
                    break;
                }
                break;
            } 
            catch (const runtime_error& e) {
                cout << e.what() << endl;
            }
        }

    }

    void menuLoginAmd(){

        Administrador administrador;
        Interacao interacao;

        while (true)  {
            cout << "_______________________________________________\n" 
                 << "                                               \n" 
                 << "                    LOGIN                      \n" 
                 << "_______________________________________________\n\n";
            try {
                cout << "NOME DE USUARIO: ";
                cin >> administrador.nomeUsuario;

                cout << "SENHA: ";
                cin >> administrador.senha;

                validar.loginAdiministrador(administrador);
                system("cls");
                interacao.menuGerenciarProdutos();
                break;

            } catch (const runtime_error& e) {
                cout << e.what() << endl;
            }
        }
    }

    void menuCadastroAdm(){

        Administrador administrador;
        Interacao interacao;
        string confSenha;

        while (true){
            cout << "_______________________________________________\n"
                 << "                                               \n" 
                 << "                  CADASTRAR                    \n"
                 << "_______________________________________________\n\n";
            try {
                cout << "NOME DE USUARIO: ";
                cin >> administrador.nomeUsuario;

                cout << "SENHA: ";
                cin >> administrador.senha;

                cout << "CONFIRME A SENHA: ";
                cin >> confSenha;

                validar.cadastrarAdministrador(administrador, confSenha);
                cout << "Administrador cadastrado com sucesso!" << endl;

                interacao.menuLoginAmd();
            } catch (const runtime_error& e) {
                cout << e.what() << endl;
            } 
        }
    }

    void menuGerenciarProdutos() {
        
        string entradaUsuario;
        Interacao interacao;

        cout << "_______________________________________________\n" 
             << "                                               \n" 
             << "              GERENCIAR ESTOQUE                \n" 
             << "_______________________________________________\n" 
             << "                                               \n" 
             << "             1| Atualizar produto              \n" 
             << "                                               \n" 
             << "             2| Cadastrar produto              \n" 
             << "                                               \n" 
             << "             3| Remover produto                \n" 
             << "                                               \n" 
             << "_______________________________________________\n\n";
        
        while (true) {
            cout  << "ESCOLHA A OPCAO: ";
            try {
                cin >> entradaUsuario;
                validar.opcoesMenu(entradaUsuario);
                system("cls");

                int entradaUsuarioInt = stoi(entradaUsuario);
                switch (entradaUsuarioInt)
                {
                case 1:
                    interacao.manuAtualizarProduto();
                    break;
                
                case 2:
                    interacao.menuCadastrarProduto();
                    break;
                case 3:
                    interacao.menuRemoverProduto();
                    break;
                }
                break;
            } 
            catch (const runtime_error& e) {
                cout << e.what() << endl;
            }
        }
    }


    void manuAtualizarProduto() {

        string entradaUsuario;

        cout << "_______________________________________________\n" 
             << "                                               \n" 
             << "              ATUALIZAR PRODUTO                \n" 
             << "_______________________________________________\n";
        vector<Produto> produtos = estoque.listarProdutos();
        for (Produto produto : produtos) {
            cout << left << setw(11) << produto.id << setw(25) << produto.nomeProduto << setw(8) << produto.quantidadeProduto << setw(15) << produto.valorProduto << endl;
        }
        
        

    }

    void menuCadastrarProduto() {

        string entradaUsuario;
        Produto produto;
        string quantidade;
        string valor;

         cout << "_______________________________________________\n" 
             << "                                                \n" 
             << "               CADASTRAR PRODUTO                \n" 
             << "________________________________________________\n";

        while (true) {
            try
            {
                cout << "INFORME O NOME DO PRODUTO: ";
                cin >> produto.nomeProduto;

                cout << "INFORME A QUANTIDADE: ";
                cin >> quantidade;
                
                cout << "INFORME O VALOR: ";
                cin >> produto.valorProduto;

                validar.cadastrarProduto(produto);
                cout << "Produto cadastrado com sucesso!";
                return;
            }
            catch(const exception& e) {
                cerr << e.what() << endl;
            }
            
        }      
    }

    void menuRemoverProduto() {

        string id;
        Produto produto;

        cout << "________________________________________________\n" 
             << "                                                \n" 
             << "                REMOVER PRODUTO                 \n" 
             << "________________________________________________\n";
        listarProdutos(estoque);

        cout << "INFORME O ID DO PRODUTO QUE DESEJA REMOVER: ";
        cin >> id;

        int inteiroId = stoi(id);
        estoque.buscarProdutoPorId(inteiroId);
        

        cout << "TEM CERTEZA QUE DESEJA REMOVER ";


    }
    
    void menuProdutos(){

        string entradaUsuario;

        cout << "_________________________________________________\n" 
             << "                                                 \n" 
             << "                    PRODUTOS                     \n" 
             << "_________________________________________________\n\n"
             << left << setw(11) << "ID" << setw(25) << "NOME" << setw(8) << "QUANT" << setw(15) << "VALOR" << endl;
        
        vector<Produto> produtos = estoque.listarProdutos();
        for (Produto produto : produtos) {
            cout << left << setw(11) << produto.id << setw(25) << produto.nomeProduto << setw(8) << produto.quantidadeProduto << setw(15) << produto.valorProduto << endl;
        }
        
        cout << "_________________________________________________\n"
             << "                                                 \n"
             << "            1| Adicionar produto ao carrinho     \n"
             << "                                                 \n"
             << "            2| Finalizar compra                  \n"
             << "                                                 \n"
             << "            3| Menu principal                    \n"
             << "_________________________________________________\n\n";

        while (true) {
            cout  << "ESCOLHA A OPCAO: ";
            try {
                cin >> entradaUsuario;
                validar.opcoesMenu(entradaUsuario);
                system("cls");

                int entradaUsuarioInt = stoi(entradaUsuario);
                switch (entradaUsuarioInt)
                {
                case 1:
                    break;
                
                case 2:
                    break;
                case 3:
                    break;
                }
                break;
            } 
            catch (const runtime_error& e) {
                cout << e.what() << endl;
            }
        }
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
    srand(time(0)); // Valor aleatorio baseado no tempo local atual!

    Interacao interacao;

    while (true) {
        interacao.menuPrincipal();
    }
}