#include <iostream>
#include <string>

struct No { // No da arvore binária
    std::string nome;
    No* esquerda;
    No* direita;

    No(std::string nome) : nome(nome), esquerda(nullptr), direita(nullptr) {}
};

No* inserir(No* raiz, std::string nome) {
    if (raiz == nullptr) return new No(nome);

    if (nome < raiz->nome) raiz->esquerda = inserir(raiz->esquerda, nome);
    else if (nome > raiz->nome) raiz->direita = inserir(raiz->direita, nome);

    return raiz;
}

bool buscar(No* raiz, std::string alvo) {
    if (raiz == nullptr) return false;

    if (alvo == raiz->nome) return true;
    else if (alvo < raiz->nome) return buscar(raiz->esquerda, alvo);
    else return buscar(raiz->direita, alvo);
}

void apagarArvore(No* raiz) {
    if (raiz == nullptr) return;

    apagarArvore(raiz->esquerda);
    apagarArvore(raiz->direita);
    delete raiz;
}

int main() {
    No* raiz = nullptr;

    // Inserir os membros da Sociedade do Anel na árvore binária
    raiz = inserir(raiz, "Aragorn");
    raiz = inserir(raiz, "Boromir");
    raiz = inserir(raiz, "Frodo");
    raiz = inserir(raiz, "Gimli");
    raiz = inserir(raiz, "Gandalf");
    raiz = inserir(raiz, "Legolas");
    raiz = inserir(raiz, "Sam");

    std::string nomeBusca;
    std::cout << "\nDigite o nome do membro que deseja buscar: ";
    std::cin >> nomeBusca;

    if (buscar(raiz, nomeBusca)) {
        std::cout << nomeBusca << " foi encontrado na Sociedade do Anel!\n" << std::endl;
    } else {
        std::cout << nomeBusca << " nao faz parte da Sociedade do Anel.\n" << std::endl;
    }

    apagarArvore(raiz); // Libera memoria alocada para arvore binaria

    return 0;
}
