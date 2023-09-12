#include <iostream>
#include <fstream>
#include <list>
#include <string>

// Estrutura para representar uma encarnação do Doctor
struct Doctor {
    int regeneration;
    std::string nome;
    int ano;
};

// Função para comparar Doctors pela regeneração
bool compareDoctors(const Doctor& a, const Doctor& b) {
    return a.regeneration < b.regeneration;
}

int main() {
    std::ifstream arquivoLeitura("encarnacoes.txt");
    if (!arquivoLeitura.is_open()) {
        std::cout << "Nao foi possivel abrir o arquivo.\n";
        return 1;
    }

    // Manipular arquivo .txt e preencher a lista
    std::string linha;
    std::list<Doctor> encarnacoes;
    while (std::getline(arquivoLeitura, linha)) {
        // Encontre a posição do separador '-'
        size_t ponto = linha.find('.');
        if (ponto != std::string::npos) {
            // Separe a linha em encarnacao e descricao
            int indice = stoi(linha.substr(0, ponto));
            std::string auxDescricao = linha.substr(ponto + 1);

            // Encontre a posição do separador '-'
            size_t traco = auxDescricao.find('-');
            
            // Verifique se o separador '-' foi encontrado
            if (traco != std::string::npos) {
                // Separe a linha em nome e descricao
                std::string nome = auxDescricao.substr(0, traco);
                int ano = stoi(auxDescricao.substr(traco + 1));

                Doctor encarnacao;
                encarnacao.regeneration = indice;
                encarnacao.nome = nome;
                encarnacao.ano = ano;
                encarnacoes.push_back(encarnacao);
            }
        }
    }
    arquivoLeitura.close();

    // Ordenar a lista com base no número da encarnação
    encarnacoes.sort(compareDoctors);

    // Solicitar identificação da encarnação para busca
    int buscarEncarnacao = 0;
    while (buscarEncarnacao < 1)
    {
        std::cout << "Digite o numero da encarnacao que voce deseja buscar: ";
        std::cin >> buscarEncarnacao;
    }

    // Implementar a busca binária
    bool found = false;
    int left = 1;
    int right = encarnacoes.size();
    while (left <= right) {
        int mid = left + (right - left) / 2;
        auto iterator = encarnacoes.begin();
        std::advance(iterator, mid - 1);

        if (iterator->regeneration == buscarEncarnacao) {
            found = true;
            std::cout << "Doctor encontrado:" << iterator->nome << "- " << iterator->ano << "\n\n";
            break;
        } else if (iterator->regeneration < buscarEncarnacao) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (!found) std::cout << "\nDoctor nao encontrado.\n" << std::endl;
    return 0;
}
