#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char estado[50];
    int codigo;
    char nome[100];
    unsigned long int populacao;
    float area;
    double pib;
    int pontosTuristicos;
    float densidadePopulacional;
    double pibPerCapita;
    float superPoder;
} Carta;

// Funções auxiliares
float calcularDensidade(unsigned long int populacao, float area) {
    return populacao / area;
}

double calcularPIBPerCapita(double pib, unsigned long int populacao) {
    return pib / populacao;
}

float calcularSuperPoder(Carta c) {
    float inversoDensidade = 1.0f / c.densidadePopulacional;
    return (float)c.populacao + c.area + (float)c.pib + (float)c.pontosTuristicos +
           (float)c.pibPerCapita + inversoDensidade;
}

void preencherCarta(Carta *c, const char *estado, int codigo, const char *nome, unsigned long int pop, float area, double pib, int pts) {
    strcpy(c->estado, estado);
    c->codigo = codigo;
    strcpy(c->nome, nome);
    c->populacao = pop;
    c->area = area;
    c->pib = pib;
    c->pontosTuristicos = pts;

    c->densidadePopulacional = calcularDensidade(c->populacao, c->area);
    c->pibPerCapita = calcularPIBPerCapita(c->pib, c->populacao);
    c->superPoder = calcularSuperPoder(*c);
}

// Função para exibir o menu de atributos
void exibirMenu(int ignorar) {
    printf("\nEscolha um atributo:\n");
    if (ignorar != 1) printf("1 - População\n");
    if (ignorar != 2) printf("2 - Área\n");
    if (ignorar != 3) printf("3 - PIB\n");
    if (ignorar != 4) printf("4 - Pontos Turísticos\n");
    if (ignorar != 5) printf("5 - Densidade Populacional\n");
    if (ignorar != 6) printf("6 - PIB per Capita\n");
    if (ignorar != 7) printf("7 - Super Poder\n");
}

// Função para obter o valor de um atributo como float
float obterValorPorAtributo(Carta c, int opcao) {
    switch (opcao) {
        case 1: return (float)c.populacao;
        case 2: return c.area;
        case 3: return (float)c.pib;
        case 4: return (float)c.pontosTuristicos;
        case 5: return c.densidadePopulacional;
        case 6: return (float)c.pibPerCapita;
        case 7: return c.superPoder;
        default: return -1;
    }
}

// Função para exibir o nome do atributo
const char* nomeAtributo(int opcao) {
    switch (opcao) {
        case 1: return "População";
        case 2: return "Área";
        case 3: return "PIB";
        case 4: return "Pontos Turísticos";
        case 5: return "Densidade Populacional";
        case 6: return "PIB per Capita";
        case 7: return "Super Poder";
        default: return "Desconhecido";
    }
}

// Comparação com dois atributos
void compararCartasAvancado(Carta c1, Carta c2, int attr1, int attr2) {
    float valor1_c1 = obterValorPorAtributo(c1, attr1);
    float valor2_c1 = obterValorPorAtributo(c1, attr2);
    float valor1_c2 = obterValorPorAtributo(c2, attr1);
    float valor2_c2 = obterValorPorAtributo(c2, attr2);

    int v1 = (attr1 == 5) ? (valor1_c1 < valor1_c2) : (valor1_c1 > valor1_c2);
    int v2 = (attr2 == 5) ? (valor2_c1 < valor2_c2) : (valor2_c1 > valor2_c2);

    float soma1 = valor1_c1 + valor2_c1;
    float soma2 = valor1_c2 + valor2_c2;

    printf("\n--- Resultado da Comparação ---\n");
    printf("Carta 1: %s\n", c1.nome);
    printf("Carta 2: %s\n", c2.nome);

    printf("\nAtributo 1 (%s): %.2f x %.2f => %s venceu\n", nomeAtributo(attr1), valor1_c1, valor1_c2,
           v1 ? c1.nome : c2.nome);

    printf("Atributo 2 (%s): %.2f x %.2f => %s venceu\n", nomeAtributo(attr2), valor2_c1, valor2_c2,
           v2 ? c1.nome : c2.nome);

    printf("\nSoma dos atributos:\n%s: %.2f\n%s: %.2f\n", c1.nome, soma1, c2.nome, soma2);

    printf("\nResultado Final: ");
    if (soma1 > soma2)
        printf("%s venceu a rodada!\n", c1.nome);
    else if (soma2 > soma1)
        printf("%s venceu a rodada!\n", c2.nome);
    else
        printf("Empate!\n");
}

int main() {
    Carta carta1, carta2;

    // Pré-cadastro (você pode modificar ou adaptar para leitura manual)
    preencherCarta(&carta1, "Brasil", 1, "Brasil", 210000000, 8515767.0f, 2200000000000.0, 30);
    preencherCarta(&carta2, "Argentina", 2, "Argentina", 45000000, 2780000.0f, 500000000000.0, 20);

    int escolha1 = 0, escolha2 = 0;

    // Menu de seleção do primeiro atributo
    while (escolha1 < 1 || escolha1 > 7) {
        exibirMenu(0);
        printf("Escolha o primeiro atributo: ");
        scanf("%d", &escolha1);
        if (escolha1 < 1 || escolha1 > 7)
            printf("Opção inválida. Tente novamente.\n");
    }

    // Menu de seleção do segundo atributo (sem repetir o primeiro)
    while (escolha2 < 1 || escolha2 > 7 || escolha2 == escolha1) {
        exibirMenu(escolha1);
        printf("Escolha o segundo atributo (diferente do primeiro): ");
        scanf("%d", &escolha2);
        if (escolha2 == escolha1)
            printf("Atributo já escolhido. Selecione outro.\n");
        else if (escolha2 < 1 || escolha2 > 7)
            printf("Opção inválida. Tente novamente.\n");
    }

    // Comparar as cartas
    compararCartasAvancado(carta1, carta2, escolha1, escolha2);

    return 0;
}
