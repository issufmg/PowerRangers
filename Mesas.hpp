#ifndef MESAS_HPP
#define MESAS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

class GerenciadorMesas {
private:
    vector<bool> mesas; // true para ocupada, false para vazia
    int totalMesas;
    string nomeArquivo;

    // Funcao auxiliar para obter entrada numerica segura
    int obterEntradaNumerica(string mensagem) {
        int valor;
        cout << mensagem;
        while (!(cin >> valor) || valor <= 0) {
            cout << "Entrada invalida! Digite um numero positivo: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        return valor;
    }

    // Funcao para carregar o estado das mesas a partir do arquivo
    void carregarEstadoMesas() {
        ifstream arquivo(nomeArquivo);
        if (arquivo.is_open()) {
            string linha;
            bool encontrouQuantidade = false;

            while (getline(arquivo, linha)) {
                // Remove espacos extras
                linha.erase(0, linha.find_first_not_of(" \t"));
                linha.erase(linha.find_last_not_of(" \t") + 1);

                if (linha.find("Quantidade de Mesas:") != string::npos) {
                    try {
                        totalMesas = stoi(linha.substr(linha.find(":") + 1));
                        if (totalMesas < 2) {
                            cout << "Erro: O numero de mesas deve ser no minimo 2.\n";
                            totalMesas = 2; // Define o minimo de mesas
                        }
                        mesas.resize(totalMesas, false);
                        encontrouQuantidade = true;
                    }
                    catch (...) {
                        cout << "Erro ao interpretar a quantidade de mesas.\n";
                    }
                }
                else if (linha.find("Mesa") != string::npos) {
                    try {
                        size_t numMesa = stoi(linha.substr(5, linha.find(":") - 5));
                        if (numMesa <= mesas.size()) {
                            mesas[numMesa - 1] = (linha.find("Ocupada") != string::npos);
                        }
                        else {
                            cout << "Erro: Numero de mesa invalido. Linha ignorada: " << linha << endl;
                        }
                    }
                    catch (...) {
                        // Comentado para nao exibir mensagens desnecessarias
                    }
                }
                else {
                    // Comentado para nao exibir mensagens desnecessarias
                }
            }

            if (!encontrouQuantidade) {
                cout << "Erro: Configuracao nao contem a quantidade de mesas.\n";
            }

            arquivo.close();
        }
        else {
            cout << "Erro ao abrir o arquivo de configuracao.\n";
        }
    }

public:
    // Construtor que carrega a configuracao de um arquivo
    GerenciadorMesas(string arquivoConfig, bool exibirStatus = false) : nomeArquivo(arquivoConfig) {
        carregarEstadoMesas();
        if (exibirStatus) { // Exibe mesas apenas se solicitado
            mostrarStatusMesas();
        }
    }

    // Exibe o status das mesas
    void mostrarStatusMesas() {
        cout << "Status das mesas:\n";
        for (size_t i = 0; i < mesas.size(); ++i) {
            cout << "Mesa " << i + 1 << ": " << (mesas[i] ? "Ocupada" : "Vazia") << endl;
        }
    }

    // Define uma mesa como ocupada
    void ocuparMesa(int numero) {
        if (numero >= 1 && numero <= totalMesas) {
            if (!mesas[numero - 1]) {
                mesas[numero - 1] = true;
                cout << "Mesa " << numero << " agora esta ocupada.\n";
                salvarEstadoMesas();
            }
            else {
                cout << "Mesa " << numero << " ja esta ocupada.\n";
            }
        }
        else {
            cout << "Numero de mesa invalido.\n";
        }
    }

    // Define uma mesa como vazia
    void liberarMesa(int numero) {
        if (numero >= 1 && numero <= totalMesas) {
            if (mesas[numero - 1]) {
                mesas[numero - 1] = false;
                cout << "Mesa " << numero << " agora esta vazia.\n";
                salvarEstadoMesas();
            }
            else {
                cout << "Mesa " << numero << " ja esta vazia.\n";
            }
        }
        else {
            cout << "Numero de mesa invalido.\n";
        }
    }

    // Funcao para salvar o estado das mesas no arquivo
    void salvarEstadoMesas() {
        ofstream arquivo(nomeArquivo);
        if (arquivo.is_open()) {
            arquivo << "Quantidade de Mesas: " << totalMesas << endl;
            arquivo << "=== Estado das Mesas ===\n";
            for (size_t i = 0; i < mesas.size(); ++i) {
                arquivo << "Mesa " << i + 1 << ": " << (mesas[i] ? "Ocupada" : "Vazia") << endl;
            }
            arquivo.close();
        }
        else {
            cout << "Erro ao salvar estado das mesas.\n";
        }
    }
};

#endif
