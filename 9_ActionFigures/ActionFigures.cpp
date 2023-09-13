#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <list>

class ActionFigure {
    private:
        int indice;
        std::string nome;
        int raridade;

    public:
        // Construtor com parâmetros
        ActionFigure(int indice, std::string nome, int raridade):
            indice(indice), nome(nome), raridade(raridade) {}

        // Métodos de obtenção (get)
        int getIndice() const {
            return indice;
        }

        std::string getNome() const {
            return nome;
        }

        int getRaridade() const {
            return raridade;
        }
        
        // Função para trocar dois ActionFigures
        void trocar(ActionFigure& outro) {
            std::swap(indice, outro.indice);
            std::swap(nome, outro.nome);
            std::swap(raridade, outro.raridade);
        }
};

// Função de ordenação InsertionSort
void InsertionSort(std::list<ActionFigure>& lista) {
    for (auto it = std::begin(lista); it != std::end(lista); ++it) {
        ActionFigure chave = *it;
        auto jt = it;

        while (jt != std::begin(lista) && chave.getRaridade() < std::prev(jt)->getRaridade()) {
            *jt = *std::prev(jt); // Move o elemento para a direita
            jt--;
        }

        *jt = chave; // Insere a chave na posição correta
    }
}

int main () {
    std::ifstream arquivoLeitura("colecao.txt");

    // Tratamento para erro na abertura
    if (!arquivoLeitura.is_open()) {
        std::cout << "Nao foi possivel abrir o arquivo.\n";
        return 1;
    }

    // Manipulacao dos Arquivos
    std::string linha;
    std::list<ActionFigure> listaElementos;

    while (std::getline(arquivoLeitura, linha)) {
        // Encontra a posição do separador '.'
        size_t ponto = linha.find('.');
        // Verifica se o ponto foi encontrado
        if (ponto != std::string::npos) {
            // Separa a linha em indice e descricao
            int indice = stoi(linha.substr(0, ponto));
            std::string descricao = linha.substr(ponto + 1);

            // Encontra a posição do separador '-'
            size_t traco = descricao.find('-');
            // Verifica se o traco foi encontrado
            if (traco != std::string::npos) {
                // Separa a descricao em nome e raridade
                std::string nome = descricao.substr(0, traco);
                std::string auxRaridade = descricao.substr(traco + 1);

                // Encontra a posição do separador ':'
                size_t pos = auxRaridade.find(':');
                // Verifica se o ':' foi encontrado
                if (pos != std::string::npos) {
                    // Separa a raridade
                    int raridade = stoi(auxRaridade.substr(pos + 1));

                    // Cria um objeto ActionFigure e adiciona à lista
                    listaElementos.push_back(ActionFigure(indice, nome, raridade));
                }
            }
        }
    }

    std::list<ActionFigure> listaElementosCopia = listaElementos;

    // Ordenacao
    InsertionSort(listaElementos);

    std::list<ActionFigure> listaOrdenada = listaElementos;

    int menu = 0;
    while (menu < 1 || menu > 2) {
        std::cout << "\nMENU\n";
        std::cout << "Digite a funcao desejada:" << std::endl;
        std::cout << "'1' para inserir nova Action Figure." << std::endl;
        std::cout << "'2' para verificar lista por insersao e ordenada." << std::endl;
        std::cin >> menu;
    }

    if (menu == 1) {
        std::ofstream arquivoOrdenado("colecao.txt", std::ios::app);
        if (!arquivoOrdenado.is_open()) {
            std::cout << "Nao foi possivel abrir o arquivo.\n";
            return 1;
        }

        int indice;
        std::string nome;
        int raridade = 1;
        std::cout << "Informe os dados do novo Action Figure: " << std::endl;
        std::cout << "Informe o indice: ";
        std::cin >> indice;
        std::cout << "Informe o nome e descricao se necessario: ";

        // Ignora os espaços em branco no nome
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, nome);

        std::cout << "Informe a raridade: ";
        std::cin >> raridade;

        // Converter inteiros em strings
        std::string indiceStr = std::to_string(indice);
        std::string raridadeStr = std::to_string(raridade);

        // Concatenar as strings
        std::string personagem = "\n" + indiceStr + ". " + nome + " - Raridade: " + raridadeStr;
        arquivoOrdenado << personagem;
        
        arquivoOrdenado.close();
    } else {
        // Impressao dados no terminal
        std::cout << "\nAction Figure por Insercao:" << std::endl;
        while (!listaElementosCopia.empty()) {
            const ActionFigure &elemento = listaElementosCopia.front();
            std::cout << elemento.getIndice() << "." << elemento.getNome() << "- Raridade: " << elemento.getRaridade() << std::endl;
            listaElementosCopia.pop_front(); // Remove o elemento da frente da lista
        }

        std::cout << "\nAction Figure Ordenada por Raridade:" << std::endl;
        while (!listaElementos.empty()) {
            const ActionFigure &elemento = listaElementos.front();
            std::cout << elemento.getIndice() << "." << elemento.getNome() << "- Raridade: " << elemento.getRaridade() << std::endl;
            listaElementos.pop_front(); // Remove o elemento da frente da lista
        }

        // Manipuilacao arquivo Ordenado
        std::ofstream arquivoOrdenado("arqOrdenado.txt", std::ios::out);
        while (!listaOrdenada.empty()) {
            const ActionFigure &elemento = listaOrdenada.front();
            arquivoOrdenado << elemento.getIndice() << "." << elemento.getNome() << "- Raridade: " << elemento.getRaridade() << std::endl;
            listaOrdenada.pop_front(); // Remove o elemento da frente da lista
        }
        arquivoOrdenado.close();
    }

    arquivoLeitura.close();
}