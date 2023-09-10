#include <iostream>
#include <fstream>
#include <string>
#include <list>

class Feiticos {
    private:
        int indice;
        std::string nome;
        std::string descricao;
    public:
        // Construtor com parâmetros
        Feiticos(int indice, std::string nome, std::string descricao) : indice(indice), nome(nome), descricao(descricao) {}

        // Métodos de configuração (set)
        void setIndice(const int &newIndice) {
            indice = newIndice;
        }

        // Métodos de obtenção (get)
        int getIndice() const {
            return indice;
        }

        std::string getNome() const {
            return nome;
        }

        std::string getDescricao() const {
            return descricao;
        }
};

void BubbleSort(std::list<Feiticos> &feiticos) {
    bool trocou;
    do {
        trocou = false;
        for (auto i = feiticos.begin(); std::next(i) != feiticos.end(); i++) {
            if (i->getNome() > std::next(i)->getNome()) {
                std::swap(*i, *std::next(i));
                trocou = true;
            }
        }
    } while (trocou);
}

int main () {
    // Abertura do arquivo
    std::ifstream arquivoLeitura("Feiticos.txt");
    if (!arquivoLeitura.is_open()) {
        std::cout << "Nao foi possivel abrir o arquivo.\n";
        return 1;
    }

    // Manipulacao do Arquivo
    std::string linha;
    std::list<Feiticos> listaFeiticos;
    while (std::getline(arquivoLeitura, linha)) {
        // Encontre a posição do separador '.'
        size_t ponto = linha.find('.');

        // Verifique se o separador '.' foi encontrado
        if (ponto != std::string::npos) {
            // Separe a linha em nome e descricao
            int indice = stoi(linha.substr(0, ponto));
            std::string auxFeitico = linha.substr(ponto + 1);

            // Encontre a posição do separador '-'
            size_t traco = auxFeitico.find('-');
            
            // Verifique se o separador '-' foi encontrado
            if (traco != std::string::npos) {
                // Separe a linha em nome e descricao
                std::string nome = auxFeitico.substr(0, traco);
                std::string descricao = auxFeitico.substr(traco + 1);

                // Cria um objeto Heroi e adiciona a lista
                listaFeiticos.push_back(Feiticos(indice, nome, descricao));
            }
        }
    }
    arquivoLeitura.close();

    // Ordenacao
    BubbleSort(listaFeiticos);

    // Manipuilacao arquivo Ordenado
    std::ofstream arquivoEscrita("Feiticos.txt", std::ios::out);
    if (!arquivoEscrita.is_open()) {
        std::cout << "Nao foi possivel abrir o arquivo.\n";
        return 1;
    }

    while (!listaFeiticos.empty()) {
        const Feiticos &elemento = listaFeiticos.front();
        arquivoEscrita << elemento.getNome() << '-' << elemento.getDescricao() << std::endl;
        listaFeiticos.pop_front(); // Remove o elemento da frente da lista
    }

    arquivoEscrita.close();

    std::cout << "\nArquivo Feiticos ordenado com sucesso!" << std::endl;
}