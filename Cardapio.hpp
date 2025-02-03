#ifndef CARDAPIO_HPP
#define CARDAPIO_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "ItemCardapio.hpp" // Inclui as classes ItemCardapio e Comida

using namespace std;

// Classe para gerenciar o cardápio
class Cardapio {
private:
    vector<ItemCardapio*> itens;
    string arquivoConfiguracao; // Nome do arquivo de configuração

public:
    Cardapio(const string& arquivo) : arquivoConfiguracao(arquivo) {
        carregarCardapio();
    }

    ~Cardapio() {
        for (auto& item : itens) {
            delete item;
        }
    }

    void adicionarItem(ItemCardapio* item) {
        itens.push_back(item);
        salvarCardapio(); // Salva no arquivo sempre que um item é adicionado
        cout << "Item adicionado com sucesso!\n";
    }

    void listarItens() const {
        cout << "\n--- Itens no Cardápio ---\n";
        if (itens.empty()) {
            cout << "O cardápio está vazio.\n";
            return;
        }
        for (const auto& item : itens) {
            item->exibir();
        }
    }

    void removerItem(const string& nome) {
        for (auto it = itens.begin(); it != itens.end(); ++it) {
            if ((*it)->getNome() == nome) {
                delete* it;
                itens.erase(it);
                salvarCardapio(); // Atualiza o arquivo após a remoção
                cout << "Item removido com sucesso!\n";
                return;
            }
        }
        cout << "Item não encontrado!\n";
    }

    void alterarItem(const string& nome) {
        for (auto& item : itens) {
            if (item->getNome() == nome) {
                string novoNome;
                double novoPreco;
                cout << "Digite o novo nome: ";
                cin.ignore();
                getline(cin, novoNome);
                cout << "Digite o novo preço: ";
                cin >> novoPreco;
                item->setNome(novoNome);
                item->setPreco(novoPreco);
                salvarCardapio(); // Atualiza o arquivo após a alteração
                cout << "Item atualizado com sucesso!\n";
                return;
            }
        }
        cout << "Item não encontrado!\n";
    }

    // Função para salvar o cardápio no arquivo de configuração
    void salvarCardapio() {
        ofstream arquivo(arquivoConfiguracao, ios::app); // Abre no modo append
        if (!arquivo) {
            cout << "Erro ao salvar o cardápio no arquivo de configuração!\n";
            return;
        }
        arquivo << "\n=== Cardápio ===\n";
        for (const auto& item : itens) {
            arquivo << item->getNome() << ";" << item->getPreco() << "\n";
        }
        arquivo.close();
    }

    // Função para carregar o cardápio do arquivo de configuração
    void carregarCardapio() {
        ifstream arquivo(arquivoConfiguracao);
        if (!arquivo) {
            cout << "Arquivo de configuração não encontrado. Criando um novo.\n";
            return;
        }

        string linha;
        bool lendoCardapio = false;
        while (getline(arquivo, linha)) {
            if (linha == "=== Cardápio ===") {
                lendoCardapio = true;
                continue;
            }
            if (lendoCardapio) {
                size_t pos = linha.find(";");
                if (pos != string::npos) {
                    string nome = linha.substr(0, pos);
                    double preco = stod(linha.substr(pos + 1));
                    itens.push_back(new Comida(nome, preco));
                }
            }
        }
        arquivo.close();
    }
};

#endif // CARDAPIO_HPP
