#ifndef ITEM_CARDAPIO_HPP
#define ITEM_CARDAPIO_HPP

#include <iostream>
#include <string>
using namespace std;

// Classe base para os itens do cardapio
class ItemCardapio {
protected:
    string nome;
    double preco;
public:
    ItemCardapio(string n, double p) : nome(n), preco(p) {}
    virtual void exibir() const {
        cout << nome << " - R$" << preco << endl;
    }
    string getNome() const { return nome; }
    double getPreco() const { return preco; }
    void setNome(string n) { nome = n; }
    void setPreco(double p) { preco = p; }
};

// Classe para representar um item de comida no cardapio
class Comida : public ItemCardapio {
public:
    Comida(string n, double p) : ItemCardapio(n, p) {}
};

#endif // ITEM_CARDAPIO_HPP
