#ifndef CONCLUSAO_PEDIDOS_HPP
#define CONCLUSAO_PEDIDOS_HPP

#include "GerenciadorPedidos.hpp"
#include "Mesas.hpp"
#include <iostream>
#include <fstream>

using namespace std;

class ConclusaoPedidos {
private:
    GerenciadorPedidos& gerenciadorPedidos;
    GerenciadorMesas& gerenciadorMesas;
    string arquivoConfiguracao;

public:
    ConclusaoPedidos(GerenciadorPedidos& pedidos, GerenciadorMesas& mesas, const string& arquivo)
        : gerenciadorPedidos(pedidos), gerenciadorMesas(mesas), arquivoConfiguracao(arquivo) {
    }

    void concluirPedido() {
        int numeroMesa;
        cout << "Digite o numero da mesa cujo pedido sera concluido: ";
        cin >> numeroMesa;

        if (gerenciadorPedidos.getPedidos().find(numeroMesa) == gerenciadorPedidos.getPedidos().end()) {
            cout << "Erro: Nenhum pedido encontrado para a mesa " << numeroMesa << ".\n";
            return;
        }

        Pedido pedido = gerenciadorPedidos.getPedidos()[numeroMesa];

        ofstream arquivo(arquivoConfiguracao, ios::app);
        if (arquivo.is_open()) {
            arquivo << "\n=== Pedido Concluido ===\n";
            arquivo << "Mesa " << numeroMesa << " - Garcom: " << pedido.garcom << "\n";
            for (const auto& item : pedido.itens) {
                arquivo << item.first << ": " << item.second << " unidade(s)\n";
            }
            arquivo.close();
        }
        else {
            cout << "Erro ao salvar o pedido concluido.\n";
            return;
        }

        gerenciadorPedidos.getPedidos().erase(numeroMesa);
        gerenciadorMesas.liberarMesa(numeroMesa);
        cout << "Pedido da mesa " << numeroMesa << " concluido com sucesso!\n";
    }

    void carregarPedidosConcluidos() {
        ifstream arquivo(arquivoConfiguracao);
        if (!arquivo) {
            cout << "Nenhum pedido concluido encontrado.\n";
            return;
        }

        string linha;
        bool lendoPedidosConcluidos = false;
        cout << "\n=== Pedidos Concluidos ===\n";
        while (getline(arquivo, linha)) {
            if (linha == "=== Pedido Concluido ===") {
                lendoPedidosConcluidos = true;
                continue;
            }
            if (lendoPedidosConcluidos) {
                cout << linha << endl;
            }
        }
        arquivo.close();
    }
};

#endif // CONCLUSAO_PEDIDOS_HPP
