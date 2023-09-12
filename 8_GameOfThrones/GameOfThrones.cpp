#include <iostream>
#include <fstream>
#include <list>
#include <string>

struct Personagem {
    std::string nome;
};

int main() {
    std::ifstream arquivoLeitura("personagensGOT.txt");
    if (!arquivoLeitura.is_open()) {
        std::cout << "\nNao foi possivel abrir o arquivo.\n";
        return 1;
    }

    // Manipular arquivo .txt e preencher a lista
    std::string linha;
    std::list<Personagem> listPersonagens;
    while (std::getline(arquivoLeitura, linha)) {
        // Encontre a posição do separador '.'
        size_t ponto = linha.find('.');
        if (ponto != std::string::npos) {
            std::string nome = linha.substr(ponto + 1);

            Personagem objPersonagem;
            objPersonagem.nome = nome;
            listPersonagens.push_back(objPersonagem);
        }
    }
    arquivoLeitura.close();

    // Solicitar identificação do Stark para busca
    std::string buscarStark = "";
    std::cout << "\nDigite o nome do Stark que voce deseja buscar: ";
    std::cin >> buscarStark;

    // Implementar a busca binária
    for (const Personagem &p : listPersonagens) {
        if (p.nome.find(buscarStark) != std::string::npos) {
            std::cout << "\nStark encontrado:" << p.nome << "\n\n";
            return 0;
        }
    }

    std::cout << "\nStark nao encontrado.\n" << std::endl;
    return 0;
}
