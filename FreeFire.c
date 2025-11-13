#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM 10 // quantidade máxima de itens na mochila

// Estrutura para representar um item dentro da mochila
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Função que adiciona um novo item na mochila
void inserirItem(struct Item mochila[], int *qtd){
    if(*qtd >= TAM){
        printf("\n🚫 Mochila cheia! Você já tem %d itens.\n", TAM);
        return;
    }

    printf("\n--- 🪶 Cadastrar Novo Item ---\n");

    // leitura do nome
    printf("Nome do item: ");
    scanf(" %29[^\n]", mochila[*qtd].nome);

    // leitura do tipo
    printf("Tipo do item (arma, munição, cura...): ");
    scanf(" %19[^\n]", mochila[*qtd].tipo);

    // leitura da quantidade
    printf("Quantidade: ");
    scanf("%d", &mochila[*qtd].quantidade);

    (*qtd)++; // aumenta o contador de itens
    printf("\n✅ Item '%s' adicionado à mochila!\n", mochila[*qtd - 1].nome);

    // exibe o inventário após a inserção
    printf("\n--- Itens atuais na mochila ---\n");
    for(int i = 0; i < *qtd; i++){
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1,
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
    printf("-----------------------------------------\n");
}

// Função que lista todos os itens cadastrados
void listarItens(struct Item mochila[], int qtd){
    printf("\n--- 🎒 Mochila (%d/%d) ---\n", qtd, TAM);
    if(qtd == 0){
        printf("A mochila está vazia.\n");
    } else {
        for(int i = 0; i < qtd; i++){
            printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
                   i + 1,
                   mochila[i].nome,
                   mochila[i].tipo,
                   mochila[i].quantidade);
        }
    }
    printf("-----------------------------------------\n");
}

// Função que remove um item pelo nome
void removerItem(struct Item mochila[], int *qtd){
    if(*qtd == 0){
        printf("\n❌ A mochila está vazia. Nenhum item para remover.\n");
        return;
    }

    char nome[30];
    int achou = 0;

    printf("\n--- 🗑️ Remover Item ---\n");
    printf("Digite o nome do item que deseja remover: ");
    scanf(" %29[^\n]", nome);

    // procura o item na lista
    for(int i = 0; i < *qtd; i++){
        if(strcmp(mochila[i].nome, nome) == 0){
            // move todos os itens seguintes uma posição pra trás
            for(int j = i; j < *qtd - 1; j++){
                mochila[j] = mochila[j + 1];
            }
            (*qtd)--; // diminui a quantidade total
            achou = 1;
            printf("\n🗑️ Item '%s' removido com sucesso!\n", nome);
            break;
        }
    }

    if(!achou){
        printf("\n❓ Item '%s' não encontrado na mochila.\n", nome);
    }

    listarItens(mochila, *qtd); // mostra a mochila após a remoção
}

// Função que busca um item pelo nome (busca sequencial)
void buscarItem(struct Item mochila[], int qtd){
    if(qtd == 0){
        printf("\n⚠️ A mochila está vazia. Nenhum item para buscar.\n");
        return;
    }

    char nome[30];
    int achou = 0;

    printf("\n--- 🔍 Buscar Item ---\n");
    printf("Digite o nome do item que deseja procurar: ");
    scanf(" %29[^\n]", nome);

    // percorre todos os itens da mochila
    for(int i = 0; i < qtd; i++){
        if(strcmp(mochila[i].nome, nome) == 0){
            printf("\n✨ Item encontrado!\n");
            printf("-----------------------------------------\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("-----------------------------------------\n");
            achou = 1;
            break;
        }
    }

    if(!achou){
        printf("\n❓ Item '%s' não encontrado na mochila.\n", nome);
    }
}

// Função principal (menu do sistema)
int main(){
    struct Item mochila[TAM]; // vetor com os itens
    int qtd = 0;              // contador de quantos itens tem
    int opcao;                // opção escolhida pelo jogador

    // mensagem inicial do jogo
    printf("==========================================\n");
    printf("     🎮 MOCHILA DE LOOT - INVENTÁRIO      \n");
    printf("==========================================\n");

    // loop principal do programa
    do {
        // exibe o menu com as opções
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Cadastrar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item\n");
        printf("0. Sair do Jogo\n");
        printf("-----------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        // executa a função de acordo com a opção escolhida
        switch(opcao){
            case 1:
                inserirItem(mochila, &qtd);
                break;
            case 2:
                removerItem(mochila, &qtd);
                break;
            case 3:
                listarItens(mochila, qtd);
                break;
            case 4:
                buscarItem(mochila, qtd);
                break;
            case 0:
                printf("\n👋 Jogo encerrado. Até a próxima missão!\n");
                break;
            default:
                printf("\n❌ Opção inválida. Tente novamente.\n");
        }

    } while(opcao != 0); // o menu repete até o jogador escolher sair

    return 0; // fim do programa
}
