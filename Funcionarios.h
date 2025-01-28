#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H

#include <iostream>

class Funcionarios {
public:
    virtual void exibirPermissoes() const = 0;
    virtual void executarFuncao(int opcao) const = 0;
    virtual ~Funcionarios() = default;
};

class Recepcionista : public Funcionarios {
public:
    void exibirPermissoes() const override {
        std::cout << "Selecione:\n";
        std::cout << "1. Acesso a mesas disponíveis\n";
        std::cout << "2. Alocar clientes\n";
    }

    void executarFuncao(int opcao) const override {
        switch (opcao) {
        case 1:
            std::cout << "Exibindo mesas disponíveis...\n";
            break;
        case 2:
            std::cout << "Alocando clientes...\n";
            break;
        default:
            std::cout << "Opção inválida para Recepcionista.\n";
        }
    }
};

class Garcom : public Funcionarios {
public:
    void exibirPermissoes() const override {
        std::cout << "Selecione:\n";
        std::cout << "1. Acesso a mesas ocupadas\n";
        std::cout << "2. Fazer pedido\n";
        std::cout << "3. Ver itens da conta\n";
        std::cout << "4. Fechar conta\n";
    }

    void executarFuncao(int opcao) const override {
        switch (opcao) {
        case 1:
            std::cout << "Exibindo mesas ocupadas...\n";
            break;
        case 2:
            std::cout << "Fazendo pedido...\n";
            break;
        case 3:
            std::cout << "Exibindo itens da conta...\n";
            break;
        case 4:
            std::cout << "Fechando conta...\n";
            break;
        default:
            std::cout << "Opção inválida para Garçom.\n";
        }
    }
};

class Gerente : public Funcionarios {
public:
    void exibirPermissoes() const override {
        std::cout << "Selecione\n";
        std::cout << "1. Acesso a mesas disponíveis\n";
        std::cout << "2. Alocar clientes\n";
        std::cout << "3. Acesso a mesas ocupadas\n";
        std::cout << "4. Fazer pedido\n";
        std::cout << "5. Ver itens da conta\n";
        std::cout << "6. Fechar conta\n";
    }

    void executarFuncao(int opcao) const override {
        switch (opcao) {
        case 1:
            std::cout << "Exibindo mesas disponíveis...\n";
            break;
        case 2:
            std::cout << "Alocando clientes...\n";
            break;
        case 3:
            std::cout << "Exibindo mesas ocupadas...\n";
            break;
        case 4:
            std::cout << "Fazendo pedido...\n";
            break;
        case 5:
            std::cout << "Exibindo itens da conta...\n";
            break;
        case 6:
            std::cout << "Fechando conta...\n";
            break;
        default:
            std::cout << "Opção inválida para Gerente.\n";
        }
    }
};

#endif
