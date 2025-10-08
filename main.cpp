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


// Variaveis globais referentes aos nomes dos arquivos csv - CSV = Comma Separated Values
string nomeArquivoEstoque = "../produtos.csv";
string nomeArquivoAdms = "../adms.csv";

struct Produto {
    int id; 
    string nomeProduto;
    float quantidadeProduto;
    float valorProduto;

    Produto () { // Metodo construtor
         id = rand(); 
    }
};

struct Carrinho {

    vector<Produto> produtosCarrinho;
    float valorCompra;


    void adicionarProduto(Produto produto) {
        produtosCarrinho.push_back(produto);

        valorCompra += (produto.valorProduto * produto.quantidadeProduto);
    }

    void removerProduto(int id) {
        int i = 0;
        for (Produto produto : produtosCarrinho) {
            if (produto.id == id) {
                produtosCarrinho.erase(produtosCarrinho.begin() + i);
                return;
            }
            i++;
        }
    }

};

struct Administrador {

    string nomeUsuario;
    string senha;
    
    void cadastrar(Administrador adm) {
        ofstream arquivo(nomeArquivoAdms, ios::app); // IOS:APP - "Append" ao arquivo existente

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
            produto.id = stoi(campo); // stoi(string) - String to int

            getline(ss, produto.nomeProduto, ',');

            getline(ss, campo, ',');
            produto.quantidadeProduto = stof(campo); // stof(string) - String to float

            getline(ss, campo, ',');
            produto.valorProduto = stof(campo);

            produtos.push_back(produto); // adiciona valores ao vetor

        }
        
        arquivo.close();
        return produtos;
    }

    void atualizarProduto(Produto atualizado) {

        ofstream temp("../temp.csv"); // passando nome de arquivo temporario
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

        remove(nomeArquivoEstoque.c_str()); // c_str - String com funcionalidades de C
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
    Carrinho carrinho;
    
    void opcoesMenu(string entrada, int opcoes) {
        int entradaInt;

        try {
           entradaInt = stoi(entrada);
        } catch (const invalid_argument& e) {
            throw invalid_argument("ERRO: Entrada invalida!");
        }

        if (entradaInt < 1 || entradaInt > opcoes) {
            throw invalid_argument("ERRO: Entrada invalida!");
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

    void atualizarProduto(Produto atualizado) {
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

    void adicionarProdutoCarrinho (Produto &produto, Carrinho &carr, string quantidade) {
        bool estaNoCarrinho = false;
        float quantidadeFloat;

        for (Produto prod : carr.produtosCarrinho) {
            if (prod.id == produto.id) estaNoCarrinho = true;
            break; 
        }

        if(estaNoCarrinho) {
            throw runtime_error("ERRO: Produto ja esta no carrinho!");
        };

        try {
            quantidadeFloat = stof(quantidade);
        } catch (const invalid_argument& e) {
            throw invalid_argument("ERRO: Entrada invalida!");
        }

        if (quantidadeFloat <= 0 || quantidadeFloat > produto.quantidadeProduto) {
            throw runtime_error("ERRO: Quantidade insuficiente!");
        } else {
            produto.quantidadeProduto = quantidadeFloat;
            carr.adicionarProduto(produto);
        }
    }

    void removerProdutoCarrinho (Produto produto, Carrinho &carr) {
        bool estaNoCarrinho;

        for (Produto prod : carr.produtosCarrinho) {
            if (prod.id == produto.id) estaNoCarrinho = true; 
            break;
        }

        if(!estaNoCarrinho) {
            throw runtime_error("ERRO: Produto nao esta no carrinho!");
        } else {
            carr.removerProduto(produto.id);
        }
    }
};

struct Interacao {

    Validacoes validar;
    Estoque estoque;
    Carrinho carrinho;

    void listarProdutos(Estoque& estoque) {

    vector<Produto> produtos = estoque.listarProdutos();
        for (Produto produto : produtos) {
            cout << left << setw(11) << produto.id << setw(25) << produto.nomeProduto << setw(8) << produto.quantidadeProduto << setw(15) << produto.valorProduto << endl;
        }
    }

    void menuPrincipal() {
        string entradaUsuario;
        
        cout << "_______________________________________________\n"
             << "                                               \n"
             << "                MENU PRINCIPAL                 \n"
             << "_______________________________________________\n"
             << "                                               \n"
             << "               1) Administrador                \n"
             << "                                               \n"
             << "               2) Cliente                      \n"
             << "                                               \n"
             << "               3) Sair do Programa             \n"
             << "                                               \n"
             << "_______________________________________________\n";
        
        while (true) {
            cout  << "Escolha a opcao: ";
            try {
                cin >> entradaUsuario;
                validar.opcoesMenu(entradaUsuario, 3);
                system("cls"); // limpa o terminal

                int entradaUsuarioInt = stoi(entradaUsuario);
                switch (entradaUsuarioInt)
                {
                case 1:
                    menuAdministrador();
                    break;
                
                case 2:
                    menuProdutos();
                    break;
                case 3:
                    cout << "Obrigado por tudo!";
                    exit(0); 
                }
                break;
            } 
            catch (const invalid_argument& e) {
                cout << e.what() << endl; // retorna de onde veio o erro, resetando o programa
            }
        }
    } 

    void menuAdministrador(){

        string entradaUsuario;

        cout << "_______________________________________________\n" 
             << "                                               \n" 
             << "                ADMINISTRADOR                  \n" 
             << "_______________________________________________\n" 
             << "                                               \n" 
             << "               1) Login                        \n" 
             << "                                               \n" 
             << "               2) Cadastrar                    \n" 
             << "                                               \n" 
             << "               3) Menu principal               \n" 
             << "                                               \n" 
             << "_______________________________________________\n\n";
         while (true) {
            cout  << "Ecolha a opcao: ";
            try {
                cin >> entradaUsuario;
                validar.opcoesMenu(entradaUsuario, 3);
                system("cls");

                int entradaUsuarioInt = stoi(entradaUsuario);
                switch (entradaUsuarioInt)
                {
                case 1:
                    menuLoginAmd();
                    break;
                
                case 2:
                    menuCadastroAdm();
                    break;
                case 3:
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

    void menuLoginAmd(){

        Administrador administrador;
        
        cout << "____________________LOGIN______________________\n"; 
        while (true)  {
            try {
                cout << "Nome de usuario: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, administrador.nomeUsuario);

                cout << "Senha: ";
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
            cout << "___________________CADASTRAR ____________________\n";
               
            try {
                cout << "Nome de usuario: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, administrador.nomeUsuario);

                cout << "Senha: ";
                cin >> administrador.senha;

                cout << "Confirme a senha: ";
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
             << "             1) Atualizar produto              \n" 
             << "                                               \n" 
             << "             2) Cadastrar produto              \n" 
             << "                                               \n" 
             << "             3) Remover produto                \n" 
             << "                                               \n" 
             << "             4) Menu principal                 \n" 
             << "_______________________________________________\n\n";
        
        while (true) {
            cout << "Escolha a opcao: ";
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

        cout << "_______________ATUALIZAR PRODUTO________________\n";
        listarProdutos(estoque);
        cout << "________________________________________________\n"
             << " - Digite o ID do produto para remover          \n"
             << " - Digite 0 para voltar para o menu principal   \n"
             << "________________________________________________\n";

        while (true) {
            try {
                cout << ": ";
                cin >> entradaUsuario;

                if (entradaUsuario == "0") return;

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
            cout << left << setw(25) << "1)NOME" 
                << setw(12) << "2)QUANT" 
                << setw(15) << "3)VALOR" 
                << endl;

            cout << left << setw(25) << atualizado.nomeProduto 
                << setw(12) << atualizado.quantidadeProduto 
                << setw(15) << atualizado.valorProduto 
                << endl;

            cout << "________________________________________________\n"
                 << " - Digite o que deseja alterar no produto       \n"
                 << " - Digite 0 para voltar                         \n"
                 << "________________________________________________\n\n";
            cout << ": ";

            cin >> entradaUsuario;

            if (entradaUsuario == "0") break; // sai do menu de atualização

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
                    cout << "Informe o novo nome: ";
                    cin >> atualizado.nomeProduto;
                    cout << "Nome atualizado com sucesso!" << endl;
                    system("cls");
                    break;

                case 2:
                    while (true) {
                        cout << "Informe a nova quantidade: ";
                        string quantidade;
                        cin >> quantidade;
                        try {
                            float quantidadeFloat = stof(quantidade);
                            atualizado.quantidadeProduto = quantidadeFloat;
                            cout << "Quantidade atualizada com sucesso!" << endl;
                            system("cls");
                            break;
                        } catch (const invalid_argument&) {
                            cerr << "ERRO: Entrada invalida" << endl;
                        }
                    }
                    break;

                case 3:
                    while (true) {
                        cout << "Informe o novo valor: ";
                        string valor;
                        cin >> valor;
                        try {
                            float valorFloat = stof(valor);
                            atualizado.valorProduto = valorFloat;
                            cout << "Valor atualizado com sucesso!" << endl;
                            system("cls");
                            break;
                        } catch (const invalid_argument&) {
                            cerr << "ERRO: Entrada invalida" << endl;
                        }
                    }
                    break;
            }

            // tenta validar o produto atualizado
            try {
                validar.atualizarProduto(atualizado);
            } catch(const exception& e) {
                cerr << e.what() << endl;
            }
        }
    }

    void menuCadastrarProduto() {

        Produto produto;
        string quantidade;
        string valor;

        cout << "_______________CADASTRAR PRODUTO________________\n";

        while (true) {
            try {
                cout << "Informe o nome do produto: ";
                cin >> produto.nomeProduto;

                while (true) {
                    cout << "Informe a quantidade: ";
                    cin >> quantidade;

                    try {
                        float quantidadeFloat = stof(quantidade);
                        produto.quantidadeProduto = quantidadeFloat;
                        break;
                    } catch(const invalid_argument& e) {
                        cerr << "ERRO: Entrada invalida" << '\n';
                    }
                    
                }
                while (true) {
                    cout << "Informe o valor: ";
                    cin >> valor;

                    try {
                        float valorFloat = stof(valor);
                        produto.valorProduto = valorFloat;
                        break;
                    } catch(const invalid_argument& e) {
                        cerr << "ERRO: Entrada invalida" << '\n';
                    }
                    
                }
                validar.cadastrarProduto(produto);
                system("cls");
                cout << "Produto cadastrado com sucesso!" << endl;
                return;
            }
            catch(const runtime_error& e) {
                cerr << e.what() << endl;
            } 
        }
        
    }

    void menuRemoverProduto() {

        Produto produto;
        string entradaUsuario;
        
        while (true) {
            cout << "_________________REMOVER PRODUTO________________\n";
            listarProdutos(estoque);
            cout << "________________________________________________\n"
                 << " - Digite o ID do produto para remover          \n"
                 << " - Digite 0 para voltar                         \n"
                 << "________________________________________________\n\n";

            try {

                cout << ":";
                cin >> entradaUsuario;

                if (entradaUsuario == "0") menuAdministrador();

                produto = validar.buscarProduto(entradaUsuario);

                cout << "Tem certeza que deseja remover: " << produto.nomeProduto << endl;
                cout << "1)Sim" << endl << "2)Nao" << endl;

                while (true) {
                    cout << ":";
                    cin >> entradaUsuario;
    
                    if (entradaUsuario == "1") {
                        validar.removerProduto(produto.id);
                        cout << "Produto removido com sucesso!" << endl;
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
    
    void menuProdutos() {

        string entradaUsuario;

        cout << "_________________________________________________\n" 
             << "                                                 \n" 
             << "                    PRODUTOS                     \n" 
             << "_________________________________________________\n\n"
             << left << setw(11) << "ID" << setw(25) << "NOME" << setw(8) << "QUANT" << setw(15) << "VALOR" << endl;
        listarProdutos(estoque);
        
        cout << "_________________________________________________\n"
             << "                                                 \n"
             << "         1) Adicionar produto ao carrinho       \n"
             << "                                                 \n"
             << "         2) Remover produto do carrinho          \n"
             << "                                                 \n"
             << "         3) Ver carrinho                         \n"
             << "                                                 \n"
             << "         4) Finalizar compra                     \n"
             << "                                                 \n"
             << "         5) Menu principal                       \n"
             << "_________________________________________________\n\n";

        int entradaUsuarioInt;

        while (true) {
            try {
                cout  << "Escolha a opcao: ";
                cin >> entradaUsuario;

                validar.opcoesMenu(entradaUsuario, 5);
                entradaUsuarioInt = stoi(entradaUsuario);

                break;
            } 
            catch (const invalid_argument& e) {
                cout << e.what() << endl;
                continue;
            }
        }
            
        switch (entradaUsuarioInt) {

            case 1:
                while (true) {
                    string id, quantidade;

                    try {
                        cout << "Informe o ID do produto para adicionar: ";
                        cin >> id;
                        Produto produto = validar.buscarProduto(id);

                        cout << "Informe a quantidade: ";
                        cin >> quantidade;
                        
                        validar.adicionarProdutoCarrinho(produto, carrinho, quantidade);
                        
                        system("cls");
                        cout << "Produto adicionado ao carrinho!" << endl;

                        break;

                    }
                    catch(const exception& e) {
                        cerr << e.what() << endl;
                    }
                }
                break;
            
            case 2: {
                string id;
                cout << "Informe o ID do produto para remover: ";
                cin >> id;
                try {
                    Produto produto = validar.buscarProduto(id);

                    validar.removerProdutoCarrinho(produto, carrinho); // passa a referência

                    system("cls");
                    cout << "Produto removido do carrinho!" << endl;

                } catch(const exception& e) {
                    cerr << e.what() << endl;
                }
                break;
            }

            case 3:
                cout << "__________________CARRINHO______________________\n"
                     << "                                                \n"
                     << " PRODUTO    |    QUANTIDADE                     \n";
                     
                for (Produto produto : carrinho.produtosCarrinho) {
                    cout << produto.nomeProduto << "        " << produto.quantidadeProduto << endl;
                }
                
                break;

            case 4:
                menuFinalizarCompra();
                break;
            
            case 5:
                return;
                break;
        }
        
    }

    void menuFinalizarCompra() {

        string entradaUsuario;

        cout << "_______________________________________________\n"
             << "                                               \n"
             << "              METODOS DE PAGAMENTO             \n"
             << "_______________________________________________\n"
             << "                                               \n"
             << "                 1) A vista                    \n"
             << "                                               \n"
             << "                 2) Cartao                     \n"
             << "                                               \n"
             << "                 3) Voltar                     \n"
             << "_______________________________________________\n\n";   

        while (true) {
            cout << "Escolha a opcao: ";
            
            try {
                cin >> entradaUsuario;
                validar.opcoesMenu(entradaUsuario, 3);
                int entradaUsuarioInt = stoi(entradaUsuario);

                switch (entradaUsuarioInt) {
                case 1:
                    cout << "Obrigado pela compra!" << endl;
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
        interacao.menuProdutos();
    }
}