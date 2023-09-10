#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <chrono>
#include <list>

class Heroi {
    private:
        int indice;
        std::string nome;

    public:
        // Construtor com parâmetros
        Heroi(int indice, std::string nome):
            indice(indice), nome(nome) {}

        // Métodos de configuração (set)
        void setIndice(const int &newIndice) {
            indice = newIndice;
        }

        void setTexto(const std::string &newNome) {
            nome = newNome;
        }

        // Métodos de obtenção (get)
        int getIndice() const {
            return indice;
        }

        std::string getNome() const {
            return nome;
        }
};

std::list<Heroi> listaHerois;

// QuickSort para ordenação alfabética
void QuickSortAlfabetico(std::list<Heroi>& lista) {
    if (lista.size() <= 1) {
        return; // A lista já está ordenada ou está vazia
    }

    Heroi pivot = lista.front();
    std::list<Heroi> menores, iguais, maiores;

    for (const Heroi& elemento : lista) {
        if (elemento.getNome() < pivot.getNome()) {
            menores.push_back(elemento);
        } else if (elemento.getNome() == pivot.getNome()) {
            iguais.push_back(elemento);
        } else {
            maiores.push_back(elemento);
        }
    }

    QuickSortAlfabetico(menores);
    QuickSortAlfabetico(maiores);

    lista.clear();
    lista.insert(lista.end(), menores.begin(), menores.end());
    lista.insert(lista.end(), iguais.begin(), iguais.end());
    lista.insert(lista.end(), maiores.begin(), maiores.end());
}

bool buscaBinaria(std::string nomeHeroi) {
    // Inicialização de ponteiros de inicio e fim da lista.
    auto inicio = listaHerois.begin();
    auto fim = listaHerois.end();

    // Realiza a busca binaria.
    while (inicio != fim) {
        auto meio = std::next(inicio, std::distance(inicio, fim) / 2);

        if (nomeHeroi == meio->getNome()) {
            return true; // Heroi encontrado
        } else if (nomeHeroi < meio->getNome()) {
            fim = meio; // Continue a busca na metade inferior
        } else {
            inicio = std::next(meio); // Continue a busca na metade superior
        }
    }

    return false; // Herói não encontrado
}

int main () {
    // Abertura do arquivo
    std::ifstream arquivoLeitura("Herois.txt");
    if (!arquivoLeitura.is_open()) {
        std::cout << "Nao foi possivel abrir o arquivo.\n";
        return 1;
    }

    // Manipulacao dos Arquivos
    std::string linha;
    std::list<Heroi> listaHerois;

    while (std::getline(arquivoLeitura, linha)) {
        // Encontre a posição do separador '.'
        size_t pos = linha.find('.');

        // Verifique se o ponto foi encontrado
        if (pos != std::string::npos) {
            // Separe a linha em indice e texto
            int indice = stoi(linha.substr(0, pos));
            std::string nome = linha.substr(pos + 1);

            // Cria um objeto Heroi e adiciona à lista
            listaHerois.push_back(Heroi(indice, nome));
        }
    }

    int qtdHerois = listaHerois.size();

    // Ordenacao
    QuickSortAlfabetico(listaHerois);

    // Manipuilacao arquivo Ordenado
    std::ofstream arquivoEscrita("Herois.txt", std::ios::out);
    if (!arquivoEscrita.is_open()) {
        std::cout << "Nao foi possivel abrir o arquivo.\n";
        return 1;
    }

    while (!listaHerois.empty()) {
        const Heroi &elemento = listaHerois.front();
        arquivoEscrita << elemento.getIndice() << "." << elemento.getNome() << std::endl;
        listaHerois.pop_front(); // Remove o elemento da frente da lista
    }

    arquivoLeitura.close();

    // Impressao dados no terminal
    int operacao = 0;
    while (operacao != 1 && operacao != 2)
    {
        std::cout << "\nVoce deseja pesquisar um Heroi? Digite:\n";
        std::cout << "'1' para SIM.\n";
        std::cout << "'2' para NAO.\n";
        std::cin >> operacao;
    }

    if (operacao == 1) {
        std::cout << "Digite o nome do heroi: ";
        std::string nomeHeroi;
        std::cin >> nomeHeroi;

        // Busca binaria
        if(!buscaBinaria(nomeHeroi)) {
            std::cout << std::endl << nomeHeroi << " esta na lista." << std::endl;
        } else {
            std::cout << std::endl << nomeHeroi << " nao existe na lista." << std::endl;
            std::cout << "\nVoce deseja adicionar " << nomeHeroi << " na lista? Digite:\n";
            std::cout << "'1' para SIM.\n";
            std::cout << "'2' para NAO.\n";
            std::cin >> operacao;

            if (operacao==1) {
                arquivoEscrita << qtdHerois+1 << ". " << nomeHeroi << std::endl;
                std::cout << "Heroi adicionado a lista com sucesso!" << std::endl;
            } else {
                std::cout << "\nArquivo Heroi ordenado com sucesso!" << std::endl;
            }
        }

        arquivoEscrita.close();
    } else {
        std::cout << "\nArquivo Heroi ordenado com sucesso!" << std::endl;
    }
}