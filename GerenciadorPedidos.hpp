#ifndef GERENCIADOR_PEDIDOS_HPP
#define GERENCIADOR_PEDIDOS_HPP

#include "Pedido.hpp"
#include <map>
#include <string>
#include <iostream>

class GerenciadorPedidos {
private:
    map<int, Pedido> pedidos;
    string arquivoConfiguracao;

public:
    GerenciadorPedidos() : arquivoConfiguracao("") {}

    GerenciadorPedidos(const string& arquivo) : arquivoConfiguracao(arquivo) {
        carregarPedidos();
    }

    map<int, Pedido>& getPedidos() {
        return pedidos;
    }

    void adicionarPedido(int numeroMesa, const string& garcom) {
        pedidos[numeroMesa] = Pedido(garcom);
    }

    void editarPedido(int numeroMesa) {
        if (pedidos.find(numeroMesa) == pedidos.end()) {
            cout << "Erro: Nenhum pedido associado a mesa " << numeroMesa << ".\n";
            return;
        }

        Pedido& pedido = pedidos[numeroMesa];
        int opcao;
        string nomeItem;
        int quantidade;

        do {
            cout << "\n1. Adicionar item\n2. Remover item\n3. Editar quantidade\n0. Finalizar edicao\n";
            cout << "Escolha uma opcao: ";
            cin >> opcao;

            switch (opcao) {
            case 1:
                cout << "Nome do item: ";
                cin.ignore();
                getline(cin, nomeItem);
                cout << "Quantidade: ";
                cin >> quantidade;
                pedido.adicionarItem(nomeItem, quantidade);
                break;
            case 2:
                cout << "Nome do item a remover: ";
                cin.ignore();
                getline(cin, nomeItem);
                pedido.removerItem(nomeItem);
                break;
            case 3:
                cout << "Nome do item a editar: ";
                cin.ignore();
                getline(cin, nomeItem);
                cout << "Nova quantidade: ";
                cin >> quantidade;
                pedido.editarQuantidade(nomeItem, quantidade);
                break;
            case 0:
                cout << "Edicao finalizada.\n";
                break;
            default:
                cout << "Opcao invalida.\n";
            }
        } while (opcao != 0);
    }

    void mostrarPedido(int numeroMesa) {
        if (pedidos.find(numeroMesa) == pedidos.end()) {
            cout << "Erro: Nenhum pedido associado a mesa " << numeroMesa << ".\n";
            return;
        }
        pedidos[numeroMesa].mostrarPedido();
    }

    void mostrarPedidos() {
        cout << "Mesas com pedidos abertos:\n";
        for (const auto& pedido : pedidos) {
            cout << "- Mesa " << pedido.first << " (Garcom: " << pedido.second.garcom << ")\n";
        }
    }

    void carregarPedidos() {
        // Implementacao futura para carregar pedidos de um arquivo
    }
};

#endif // GERENCIADOR_PEDIDOS_HPP
