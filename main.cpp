#include <iostream>
#include "Funcionarios.h"

void exibirMenu() {
    std::cout << "Selecione o tipo de funcionário:\n";
    std::cout << "1. Recepcionista\n";
    std::cout << "2. Garçom\n";
    std::cout << "3. Gerente\n";
    std::cout << "Digite o número correspondente: ";
}

int main() {
    int tipoFuncionario;

    exibirMenu();
    std::cin >> tipoFuncionario;

    if (std::cin.fail() || tipoFuncionario < 1 || tipoFuncionario > 3) {
        std::cout << "Opção inválida! Encerrando o programa.\n";
        return 1;
    }

    Funcionarios* funcionario = nullptr;

    switch (tipoFuncionario) {
        case 1:
            funcionario = new Recepcionista();
            break;
        case 2:
            funcionario = new Garcom();
            break;
        case 3:
            funcionario = new Gerente();
            break;
    }

    funcionario->exibirPermissoes();

    std::cout << "\nDigite o número da função que deseja executar: ";
    int funcao;
    std::cin >> funcao;

    if (std::cin.fail()) {
        std::cout << "Entrada inválida! Encerrando o programa.\n";
        delete funcionario;
        return 1;
    }

    funcionario->executarFuncao(funcao);

    delete funcionario;

    return 0;
}
