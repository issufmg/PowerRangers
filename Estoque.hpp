#ifndef ESTOQUE_HPP
#define ESTOQUE_HPP

#include <iostream>
#include <map>
#include <string>
#include <fstream>
using namespace std;

class Estoque {
private:
    map<string, int> estoque;
    string arquivoConfiguracao;

public:
    Estoque() : arquivoConfiguracao("") {}

    Estoque(const string& arquivo) : arquivoConfiguracao(arquivo) {
        carregarEstoque();
    }

    void adicionarItem(const string& nome, int quantidade) {
        estoque[nome] += quantidade;
        salvarEstoque();
    }

    void removerItem(const string& nome, int quantidade) {
        if (estoque.find(nome) != estoque.end() && estoque[nome] >= quantidade) {
            estoque[nome] -= quantidade;
            if (estoque[nome] == 0) {
                estoque.erase(nome);
            }
            salvarEstoque();
        }
    }

    void listarEstoque() const {
        for (const auto& item : estoque) {
            cout << item.first << ": " << item.second << " unidades\n";
        }
    }

    int quantidadeTotal() const {
        int total = 0;
        for (const auto& item : estoque) {
            total += item.second;
        }
        return total;
    }

    void salvarEstoque() {
        ofstream arquivo(arquivoConfiguracao, ios::app);
        if (!arquivo) return;

        arquivo << "\n=== Estoque ===\n";
        for (const auto& item : estoque) {
            arquivo << item.first << ";" << item.second << "\n";
        }
        arquivo.close();
    }

    void carregarEstoque() {
        ifstream arquivo(arquivoConfiguracao);
        if (!arquivo) return;

        string linha;
        while (getline(arquivo, linha)) {
            // Logica para carregar itens do estoque
        }
    }
};

#endif // ESTOQUE_HPP
