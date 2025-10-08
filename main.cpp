#include <iostream> // Biblioteca padrão
#include <fstream> // Manipulação de arquivos
#include <sstream> // Maniulação de strings
#include <string> // Utilização de strings
#include <iomanip> // Formatação do design
#include <cstdlib> // Funções utilitarias de C
#include <ctime> // Tempo real
#include <vector> // Vetores dinamicos
#include <limits>

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

    vector<Produto> listarProdutos() { // Vetor dinamico!
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
            produto.id = stoi(campo); // STOI --> String to int

            getline(ss, produto.nomeProduto, ',');

            getline(ss, campo, ',');
            produto.quantidadeProduto = stof(campo); // STOF --> String to float

            getline(ss, campo, ',');
            produto.valorProduto = stof(campo);

            produtos.push_back(produto); // Adiciona os valores como um novo elemento do vetor

        }
        
        arquivo.close();
        return produtos;
    }

    void atualizarProduto(Produto atualizado) {

        ofstream temp("../temp.csv"); // Novo arquivo
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

        remove(nomeArquivoEstoque.c_str()); // c_str --> String com funcionalidades de C
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
    
    void opcoesMenu(string entrada, int opcoes) {
        if (opcoes == 3) {
            if (entrada != "1" && entrada != "2" && entrada != "3" ) {
                throw invalid_argument("ERRO: Entrada invalida!");
        } else if (opcoes == 4){
            if (entrada != "1" && entrada != "2" && entrada != "3" && entrada != "4") {
                throw invalid_argument("ERRO: Entrada invalida!");
            }
        }
        }
    }

    void cadastrarProduto(Produto produto) {
        vector <Produto> produtos = estoque.listarProdutos();

        for (Produto prod : produtos) { // Lista "produtos" um por um
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

    void validarAtualizarProduto(Produto atualizado) {
        if (atualizado.nomeProduto.length() <= 2 || atualizado.nomeProduto.length() > 25) {
            throw runtime_error("ERRO: Nome do produto invalido!");

        } else if (atualizado.quantidadeProduto <= 0) {
            throw runtime_error("ERRO: Quantidade invalida!");

        } else if (atualizado.valorProduto <= 0) {
            throw runtime_error("ERRO: Valor invalido!");
        } else {
            estoque.atualizarProduto(atualizado);
        }
    }

    void cadastrarAdministrador(Administrador administrador, string confSenha) {
        Administrador admBusca = adm.buscarAdministrador(administrador.nomeUsuario);

        if (administrador.nomeUsuario.find(' ') != string::npos) {
                    throw runtime_error("ERRO: Nome do usuario nao pode conter espacos!");
        }
        else if(!admBusca.nomeUsuario.empty()) {
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

    void removerProduto (int id) {
        Produto produto = estoque.buscarProdutoPorId(id);

        if (produto.nomeProduto.empty()) {
            throw runtime_error("ERRO: Produto nao encontrado!");
        } else {
            estoque.removerProduto(id);
        }
    }

    Produto buscarProduto (string id) {
        Produto produto;

        try {
            int idInteiro = stoi(id);
            produto = estoque.buscarProdutoPorId(idInteiro);

            if (produto.nomeProduto.empty()) {
                throw runtime_error("ERRO: Produto nao encontrado!");
            }
        } catch (const invalid_argument& e) {
            throw invalid_argument("ERRO: Id invalido!");
        }

        return produto;
    }
};

struct Interacao {

    Validacoes validar;
    Estoque estoque;

    void listarProdutos(Estoque& estoque) {

    vector<Produto> produtos = estoque.listarProdutos();
        for (Produto produto : produtos) {
            cout << left << setw(11) << produto.id << setw(25) << produto.nomeProduto << setw(8) << produto.quantidadeProduto << setw(15) << produto.valorProduto << endl;
        }
    }

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
            try { // Trata o escopo como uma area de perigo, usando catch para trata-lo, caso algo dê errado
                cin >> entradaUsuario;
                validar.opcoesMenu(entradaUsuario, 3);
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
            catch (const invalid_argument& e) { // <-- Tipo de variavel que a função "what" utiliza
                cout << e.what() << endl; // Retorna de onde veio o erro, resetando o programa
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
                validar.opcoesMenu(entradaUsuario, 3);
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
                    return; // Fecha a função
                    break;
                }
                break;
            } 
            catch (const invalid_argument& e) {
                cout << e.what() << endl;
            }
        }

    }

    void menuLoginAmd(){

        Administrador administrador;
        
        cout << "_______________________________________________\n" 
             << "                                               \n" 
             << "                    LOGIN                      \n" 
             << "_______________________________________________\n\n";
        while (true)  {
            try {
                cout << "NOME DE USUARIO: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, administrador.nomeUsuario);

                cout << "SENHA: ";
                cin >> administrador.senha;

                validar.loginAdiministrador(administrador);
                system("cls");
                menuGerenciarProdutos();
                break;

            } catch (const runtime_error& e) {
                cout << e.what() << endl;
            }
        }
    }

    void menuCadastroAdm(){

        Administrador administrador;
        string confSenha;

        while (true){
            cout << "_______________________________________________\n"
                 << "                                               \n" 
                 << "                  CADASTRAR                    \n"
                 << "_______________________________________________\n\n";
            try {
                cout << "NOME DE USUARIO: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, administrador.nomeUsuario);

                cout << "SENHA: ";
                cin >> administrador.senha;

                cout << "CONFIRME A SENHA: ";
                cin >> confSenha;

                validar.cadastrarAdministrador(administrador, confSenha);
                cout << "Administrador cadastrado com sucesso!" << endl;

                menuLoginAmd();
                system("cls");
                break;
            } catch (const runtime_error& e) {
                system("cls");
                cout << e.what() << endl;
            } 
        }
    }

    void menuGerenciarProdutos() {
        
        string entradaUsuario;

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
             << "             4| Voltar                         \n" 
             << "_______________________________________________\n\n";
        
        while (true) {
            cout << "ESCOLHA A OPCAO: ";
            try {
                cin >> entradaUsuario;
                validar.opcoesMenu(entradaUsuario, 4);
                system("cls");

                int entradaUsuarioInt = stoi(entradaUsuario);
                switch (entradaUsuarioInt)
                {
                case 1:
                    menuAtualizarProduto();
                    break;
                
                case 2:
                    menuCadastrarProduto();
                    break;
                case 3:
                    menuRemoverProduto();
                    break;
                case 4:
                    return;
                    break;
                }
                break;
            } 
            catch (const invalid_argument& e) {
                cout << e.what() << endl;
            }
        }
    }


    void menuAtualizarProduto() {

        string entradaUsuario;
        Produto produto;

        cout << "_______________________________________________\n" 
            << "                                                \n" 
            << "                ATUALIZAR PRODUTO               \n" 
            << "________________________________________________\n";
        listarProdutos(estoque);
        cout << "________________________________________________\n"
             << "             DIGITE 999 PARA SAIR               \n"
             << "________________________________________________\n\n";

        while (true) {
            try {
                cout << "INFORME O ID DO PRODUTO: ";
                cin >> entradaUsuario;
                if (entradaUsuario == "999") {
                    return;
                }
                produto = validar.buscarProduto(entradaUsuario);
                system("cls");
                break;
            } catch (const exception& e) {
                cerr << e.what() << endl;
            }
        }

        Produto atualizado = produto;

        while (true) {
            cout << "________________________________________________\n";
            cout << left << setw(25) << "1|NOME" 
                << setw(12) << "2|QUANT" 
                << setw(15) << "3|VALOR" 
                << endl;

            cout << left << setw(25) << atualizado.nomeProduto 
                << setw(12) << atualizado.quantidadeProduto 
                << setw(15) << atualizado.valorProduto 
                << endl;

            cout << "________________________________________________\n"
                 << "             DIGITE 999 PARA SAIR               \n"
                 << "________________________________________________\n";
            cout << "O QUE DESEJA ALTERAR: ";

            cin >> entradaUsuario;

            if (entradaUsuario == "999") break; // sai do menu de atualização

            int entradaUsuarioInt;
            try {
                entradaUsuarioInt = stoi(entradaUsuario);
                validar.opcoesMenu(entradaUsuario, 3); // valida se é 1, 2 ou 3
                system("cls");
            } catch (const exception& e) {
                cerr << e.what() << endl;
                continue; // volta para escolher a opção
            }

            switch (entradaUsuarioInt) {
                case 1:
                    cout << "INFORME O NOVO NOME: ";
                    cin >> atualizado.nomeProduto;
                    system("cls");
                    cout << "NOME ATUALIZADO COM SUCESSO!" << endl;
                    break;

                case 2:
                    while (true) {
                        cout << "INFORME A NOVA QUANTIDADE: ";
                        string quantidade;
                        cin >> quantidade;
                        try {
                            float quantidadeFloat = stof(quantidade);
                            atualizado.quantidadeProduto = quantidadeFloat;
                            system("cls");
                            cout << "QUANTIDADE ATUALIZADA COM SUCESSO!" << endl;
                            break;
                        } catch (const invalid_argument&) {
                            cerr << "ERRO: Entrada invalida" << endl;
                        }
                    }
                    break;

                case 3:
                    while (true) {
                        cout << "INFORME O NOVO VALOR: ";
                        string valor;
                        cin >> valor;
                        try {
                            float valorFloat = stof(valor);
                            atualizado.valorProduto = valorFloat;
                            system("cls");
                            cout << "VALOR ATUALIZADO COM SUCESSO!" << endl;
                            break;
                        } catch (const invalid_argument&) {
                            cerr << "ERRO: Entrada invalida" << endl;
                        }
                    }
                    break;
            }

            // tenta validar o produto atualizado
            try {
                validar.validarAtualizarProduto(atualizado);
            } catch(const exception& e) {
                cerr << e.what() << endl;
            }
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

    }

    void menuRemoverProduto() {

        Produto produto;
        string entradaUsuario;
        
        while (true) {
            cout << "________________________________________________\n" 
                 << "                                                \n" 
                 << "                REMOVER PRODUTO                 \n" 
                 << "________________________________________________\n";
            listarProdutos(estoque);
            cout << "________________________________________________\n"
                 << "              DIGITE 0 PARA SAIR                \n"
                 << "________________________________________________\n\n";

            try {

                cout << "INFORME O ID:";
                cin >> entradaUsuario;

                if (entradaUsuario == "0") return;

                produto = validar.buscarProduto(entradaUsuario);

                while (true) {
                    cout << "TEM CERTEZA QUE DESEJA REMOVER: " << produto.nomeProduto << endl;
                    cout << "1)Sim" << endl << "2)Nao" << endl << ":";
                    cin >> entradaUsuario;
    
                    if (entradaUsuario == "1") {
                        validar.removerProduto(produto.id);
                        cout << "PRODUTO REMOVIDO COM SUCESSO!";
                        break;
                    } else if (entradaUsuario == "2") {
                        system("cls");
                        break;
                    } else {
                        cout << "ERRO: Entrada invalida!" << endl;
                        continue;
                    }
                }

            } catch(const exception& e) {
                cerr << e.what() << endl;
            }
        }

    }
    
    void menuProdutos(){

        string entradaUsuario;
        Interacao interacao;

        cout << "_________________________________________________\n" 
             << "                                                 \n" 
             << "                    PRODUTOS                     \n" 
             << "_________________________________________________\n\n"
             << left << setw(11) << "ID" << setw(25) << "NOME" << setw(8) << "QUANT" << setw(15) << "VALOR" << endl;
        listarProdutos(estoque);
        
        cout << "_________________________________________________\n"
             << "                                                 \n"
             << "            1| Adicionar produto ao carrinho     \n"
             << "                                                 \n"
             << "            2| Ver carrinho                      \n"
             << "                                                 \n"
             << "            3| Finalizar compra                  \n"
             << "                                                 \n"
             << "            4| Menu principal                    \n"
             << "_________________________________________________\n\n";

        while (true) {
            cout  << "ESCOLHA A OPCAO: ";
            try {
                cin >> entradaUsuario;
                validar.opcoesMenu(entradaUsuario, 4);
                system("cls");
                int entradaUsuarioInt = stoi(entradaUsuario);
                switch (entradaUsuarioInt)
                {
                case 1:
                    adicionarCarrinho();
                    break;
                
                case 2:
                    verCarrinho();
                    break;

                case 3:
                    metodoPagamento();
                    break;
                case 4:
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

    void adicionarCarrinho() {

    }

    void verCarrinho() {

    }
    
    void metodoPagamento() {

        string entradaUsuario;

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

        while (true) {
            cout << "ESCOLHA UMA OPCAO: ";
            
            try {
                cin >> entradaUsuario;
                validar.opcoesMenu(entradaUsuario, 3);
                int entradaUsuarioInt = stoi(entradaUsuario);

                switch (entradaUsuarioInt) {
                case 1:
                    cout << "OBRIGADO PELA COMPRA!" << endl;
                    break;
                
                case 2:
                    cartao();
                    break;

                case 3:
                    return;
                    break;
                }
            } catch(const runtime_error& e) {
                cout << e.what() << endl;
            }
        }
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
        interacao.menuAtualizarProduto();
    }
}