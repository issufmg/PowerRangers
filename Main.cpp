#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <limits>
#include "ItemCardapio.hpp"
#include "Pedido.hpp"
#include "Cardapio.hpp"
#include "Mesas.hpp"
#include "Estoque.hpp"
#include "ConclusaoPedidos.hpp"
#include "GerenciadorPedidos.hpp"

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Função para listar configurações existentes no diretório atual
void listarConfiguracoes(vector<string>& configuracoes) {
    configuracoes.clear(); // Limpa o vetor antes de listar
    cout << "\n=== Configurações Disponíveis ===\n";

    ifstream arquivoIndex("configuracoes.txt");
    if (arquivoIndex.is_open()) {
        string linha;
        int numero = 1;
        while (getline(arquivoIndex, linha)) {
            configuracoes.push_back(linha);
            cout << numero << ". " << linha << endl;
            numero++;
        }
        arquivoIndex.close();
    }
    else {
        cout << "Nenhuma configuração encontrada.\n";
    }
}


// Função para adicionar uma configuração ao arquivo de índice
void salvarNoIndice(const string& nomeArquivo) {
    ofstream arquivoIndex("configuracoes.txt", ios::app);
    if (arquivoIndex.is_open()) {
        arquivoIndex << nomeArquivo << endl;
        arquivoIndex.close();
    }
    else {
        cout << "Erro ao atualizar o índice de configurações.\n";
    }
}

// Função para criar uma nova configuração
void criarConfiguracao() {
    string nomeArquivo;
    int quantidadeMesas;

    cout << "Digite o nome da nova configuração (sem extensão): ";
    cin.ignore();
    getline(cin, nomeArquivo);
    nomeArquivo += ".txt";

    cout << "Digite a quantidade de mesas para o restaurante: ";
    while (!(cin >> quantidadeMesas) || quantidadeMesas <= 0) {
        cout << "Entrada inválida! Digite um número positivo: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    ofstream arquivo(nomeArquivo);
    if (arquivo.is_open()) {
        arquivo << "Quantidade de Mesas: " << quantidadeMesas << endl;
        arquivo << "=== Mesas ===\n";
        for (int i = 0; i < quantidadeMesas; ++i) {
            arquivo << "Mesa " << i + 1 << ": Vazia\n";
        }
        arquivo.close();
        cout << "Configuração salva em: " << nomeArquivo << endl;
        salvarNoIndice(nomeArquivo);
    }
    else {
        cout << "Erro ao criar o arquivo de configuração.\n";
    }
}

// Função para carregar uma configuração existente
bool carregarConfiguracao(string& nomeArquivo) {
    vector<string> configuracoes;
    listarConfiguracoes(configuracoes);

    if (configuracoes.empty()) {
        cout << "Nenhuma configuração disponível para carregar.\n";
        return false; // Indica falha no carregamento
    }

    int escolha;
    cout << "Digite o número da configuração a carregar: ";
    while (!(cin >> escolha) || escolha < 1 || escolha > configuracoes.size()) {
        cout << "Opção inválida! Digite um número entre 1 e " << configuracoes.size() << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    nomeArquivo = configuracoes[escolha - 1]; // Obtém o nome do arquivo correspondente
    cout << "Carregando configuração: " << nomeArquivo << endl;
    return true; // Indica sucesso no carregamento
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void menuCardapio(Cardapio& cardapio) {
    int opcao;
    do {
        cout << "\n=== Gerenciamento do Cardápio ===\n";
        cout << "1. Adicionar Item\n";
        cout << "2. Listar Itens\n";
        cout << "3. Remover Item\n";
        cout << "4. Alterar Item\n";
        cout << "0. Voltar\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        string nome;
        double preco;
        switch (opcao) {
        case 1:
            cout << "Digite o nome do item: ";
            cin.ignore();
            getline(cin, nome);
            cout << "Digite o preço do item: ";
            cin >> preco;
            cardapio.adicionarItem(new Comida(nome, preco));
            break;
        case 2:
            cardapio.listarItens();
            break;
        case 3:
            cout << "Digite o nome do item a remover: ";
            cin.ignore();
            getline(cin, nome);
            cardapio.removerItem(nome);
            break;
        case 4:
            cout << "Digite o nome do item a alterar: ";
            cin.ignore();
            getline(cin, nome);
            cardapio.alterarItem(nome);
            break;
        case 0:
            cout << "Voltando ao menu principal...\n";
            break;
        default:
            cout << "Opção inválida, tente novamente.\n";
        }
    } while (opcao != 0);
}

void menuMesas(GerenciadorMesas& restaurante) {
    int opcao, numeroMesa = 0;
    do {
        cout << "\n=== Gerenciamento de Mesas ===\n";
        cout << "1. Mostrar status das mesas\n";
        cout << "2. Ocupar uma mesa\n";
        cout << "3. Liberar uma mesa\n";
        cout << "0. Voltar\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
        case 1:
            restaurante.mostrarStatusMesas();
            break;
        case 2:
            cout << "Digite o número da mesa a ocupar: ";
            cin >> numeroMesa;
            restaurante.ocuparMesa(numeroMesa);
            break;
        case 3:
            cout << "Digite o número da mesa a liberar: ";
            cin >> numeroMesa;
            restaurante.liberarMesa(numeroMesa);
            break;
        case 0:
            cout << "Voltando ao menu principal...\n";
            break;
        default:
            cout << "Opção inválida! Tente novamente.\n";
        }
    } while (opcao != 0);
}

void menuPedidos(GerenciadorPedidos& gerenciador) {
    int opcao, mesa;
    string garcom;

    do {
        cout << "\n=== Gerenciamento de Pedidos ===\n";
        cout << "1. Adicionar Pedido\n";
        cout << "2. Editar Pedido\n";
        cout << "3. Mostrar Pedido\n";
        cout << "4. Mostrar Pedidos\n";
        cout << "0. Voltar\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
        case 1:
            cout << "Número da mesa: ";
            cin >> mesa;
            cout << "Nome do garçom: ";
            cin.ignore();
            getline(cin, garcom);
            gerenciador.adicionarPedido(mesa, garcom);
            break;
        case 2:
            cout << "Número da mesa: ";
            cin >> mesa;
            gerenciador.editarPedido(mesa);
            break;
        case 3:
            cout << "Número da mesa: ";
            cin >> mesa;
            gerenciador.mostrarPedido(mesa);
            break;
        case 4:
            gerenciador.mostrarPedidos();
            break;
        case 0:
            cout << "Voltando ao menu principal...\n";
            break;
        default:
            cout << "Opção inválida, tente novamente.\n";
        }
    } while (opcao != 0);
}

void menuEstoque(Estoque& estoque) {
    int opcao;
    do {
        cout << "\n=== Gerenciamento do Estoque ===\n";
        cout << "1. Adicionar Quantidade de Item\n";
        cout << "2. Remover Quantidade de Item\n";
        cout << "3. Listar Estoque\n";
        cout << "4. Ver Quantidade Total\n";
        cout << "0. Voltar\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        string nome;
        int quantidade;
        switch (opcao) {
        case 1:
            cout << "Digite o nome do item para adicionar ao estoque: ";
            cin.ignore();
            getline(cin, nome);
            cout << "Digite a quantidade: ";
            cin >> quantidade;
            estoque.adicionarItem(nome, quantidade);
            break;
        case 2:
            cout << "Digite o nome do item para remover do estoque: ";
            cin.ignore();
            getline(cin, nome);
            cout << "Digite a quantidade: ";
            cin >> quantidade;
            estoque.removerItem(nome, quantidade);
            break;
        case 3:
            estoque.listarEstoque();
            break;
        case 4:
            cout << "Quantidade total no estoque: " << estoque.quantidadeTotal() << " unidades.\n";
            break;
        case 0:
            cout << "Voltando ao menu principal...\n";
            break;
        default:
            cout << "Opção inválida, tente novamente.\n";
        }
    } while (opcao != 0);
}




void menuConclusaoPedidos(ConclusaoPedidos& conclusao) {
    int opcao;
    do {
        cout << "\n=== Conclusão de Pedidos ===\n";
        cout << "1. Concluir Pedido\n";
        cout << "2. Mostrar Pedidos Concluídos\n";
        cout << "0. Voltar ao Menu Principal\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
        case 1:
            conclusao.concluirPedido(); // Chama a função para concluir um pedido
            break;
        case 2:
            conclusao.carregarPedidosConcluidos(); // Exibe pedidos concluídos salvos
            break;
        case 0:
            cout << "Voltando ao menu principal...\n";
            break;
        default:
            cout << "Opção inválida. Tente novamente.\n";
        }
    } while (opcao != 0);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void menuPrincipal(GerenciadorMesas& restaurante, GerenciadorPedidos& gerenciadorPedidos, Estoque& estoque, Cardapio& cardapio, ConclusaoPedidos& conclusao) {
    int opcao;
    do {
        cout << "\n=== Sistema de Gestão para Restaurantes ===\n";
        cout << "1. Gerenciar Cardápio\n";
        cout << "2. Gerenciar Estoque\n";
        cout << "3. Controle de Mesas\n";
        cout << "4. Gerenciar Pedidos\n";
        cout << "5. Concluir Pedidos\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
        case 1:
            menuCardapio(cardapio);
            break;
        case 2:
            menuEstoque(estoque);
            break;
        case 3:
            menuMesas(restaurante);
            break;
        case 4:
            menuPedidos(gerenciadorPedidos);
            break;
        case 5:
            menuConclusaoPedidos(conclusao);
            break;
        case 0:
            cout << "Saindo do sistema...\n";
            break;
        default:
            cout << "Opção inválida, tente novamente.\n";
            break;
        }
    } while (opcao != 0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void menuGarcom(GerenciadorMesas& restaurante, GerenciadorPedidos& gerenciadorPedidos, ConclusaoPedidos& conclusao) {
    int opcao;
    do {
        cout << "\n=== Menu do Garçom ===\n";
        cout << "1. Controle de Mesas\n";
        cout << "2. Gerenciar Pedidos\n";
        cout << "3. Concluir Pedidos\n";
        cout << "0. Voltar ao Menu Principal\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
        case 1:
            menuMesas(restaurante);
            break;
        case 2:
            menuPedidos(gerenciadorPedidos);
            break;
        case 3:
            menuConclusaoPedidos(conclusao);
            break;
        case 0:
            cout << "Voltando ao Menu Principal...\n";
            break;
        default:
            cout << "Opção inválida, tente novamente.\n";
        }
    } while (opcao != 0);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void menuRecepcionista(GerenciadorMesas& restaurante) {
    int opcao;
    do {
        cout << "\n=== Menu do Recepcionista ===\n";
        cout << "1. Controle de Mesas\n";
        cout << "2. Mostrar Status das Mesas\n";
        cout << "0. Voltar ao Menu Principal\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
        case 1:
            menuMesas(restaurante);
            break;
        case 2:
            restaurante.mostrarStatusMesas();
            break;
        case 0:
            cout << "Voltando ao Menu Principal...\n";
            break;
        default:
            cout << "Opção inválida, tente novamente.\n";
        }
    } while (opcao != 0);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void menuCozinheiro(GerenciadorPedidos& gerenciadorPedidos, Estoque& estoque) {
    int opcao;
    do {
        cout << "\n=== Menu do Cozinheiro ===\n";
        cout << "1. Visualizar Pedidos Pendentes\n";
        cout << "2. Gerenciar Estoque\n";
        cout << "0. Voltar ao Menu Principal\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
        case 1:
            gerenciadorPedidos.mostrarPedidos();
            break;
        case 2:
            menuEstoque(estoque);
            break;
        case 0:
            cout << "Voltando ao Menu Principal...\n";
            break;
        default:
            cout << "Opção inválida, tente novamente.\n";
        }
    } while (opcao != 0);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void menuFuncionario(string nomeArquivo) {
    GerenciadorMesas restaurante(nomeArquivo, false); // Não exibe mesas ao carregar
    GerenciadorPedidos gerenciadorPedidos(nomeArquivo);
    Estoque estoque(nomeArquivo);
    Cardapio cardapio(nomeArquivo);
    ConclusaoPedidos conclusao(gerenciadorPedidos, restaurante, nomeArquivo);

    int opcao;
    do {
        cout << "\n=== Selecione o Tipo de Funcionário ===\n";
        cout << "1. Gerente\n";
        cout << "2. Cozinheiro\n";
        cout << "3. Garçom\n";
        cout << "4. Recepcionista\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
        case 1:
            cout << "Bem-vindo, Gerente!\n";
            menuPrincipal(restaurante, gerenciadorPedidos, estoque, cardapio, conclusao);
            break;
        case 2:
            cout << "Bem-vindo, Cozinheiro!\n";
            menuCozinheiro(gerenciadorPedidos, estoque);
            break;
        case 3:
            cout << "Bem-vindo, Garçom!\n";
            menuGarcom(restaurante, gerenciadorPedidos, conclusao);
            break;
        case 4:
            cout << "Bem-vindo, Recepcionista!\n";
            menuRecepcionista(restaurante);
            break;
        case 0:
            cout << "Saindo do sistema...\n";
            break;
        default:
            cout << "Opção inválida, tente novamente.\n";
        }
    } while (opcao != 0);
}



// Menu inicial para selecionar ou criar configurações
void menuInicial() {
    int opcao;
    string nomeArquivo;
    vector<string> configuracoes;

    do {
        cout << "\n=== Menu Inicial ===\n";
        cout << "1. Listar Configurações Existentes\n";
        cout << "2. Criar Nova Configuração\n";
        cout << "3. Carregar Configuração Existente\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
        case 1:
            listarConfiguracoes(configuracoes);
            break;
        case 2:
            criarConfiguracao();
            break;
        case 3:
            if (carregarConfiguracao(nomeArquivo)) { // Verifica se o carregamento foi bem-sucedido
                menuFuncionario(nomeArquivo);       // Redireciona para o menu de funcionários
            }
            else {
                cout << "Falha ao carregar configuração. Tente novamente.\n";
            }
            break;
        case 0:
            cout << "Saindo do sistema...\n";
            break;
        default:
            cout << "Opção inválida, tente novamente.\n";
        }
    } while (opcao != 0);
}






///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    string nomeArquivo;
    menuInicial();
    if (!nomeArquivo.empty()) {
        menuFuncionario(nomeArquivo);
    }
    return 0;
}
