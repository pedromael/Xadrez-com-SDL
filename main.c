#include "cab/index.h"
#include "cab/verificadores.h"
#include "cab/desenhar.h"

pecas peca[32]; // 16 peças brancas + 16 peças pretas = 32
pecas* peca_selecionada = NULL; // Para armazenar a peça selecionada
bool jogadas_disponiveis[8][8] = {false}; // Matriz para armazenar jogadas disponíveis
TTF_Font* font = NULL;

void mover_peca(int novaX, int novaY) {
    if (peca_selecionada) {
        // Verifica se o movimento é válido
        if (jogadas_disponiveis[novaY][novaX]) {
            // Se houver uma peça adversária na nova posição, "captura" ela
            for (int i = 0; i < 32; i++) {
                if (peca[i].x == novaX && peca[i].y == novaY && peca[i].status) {
                    peca[i].status = false; // Remove a peça adversária
                    break;
                }
            }
            // Move a peça selecionada
            peca_selecionada->x = novaX;
            peca_selecionada->y = novaY;
        }
        peca_selecionada = NULL; // Reseta a peça selecionada
    }
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init(); // Inicializa a biblioteca TTF
    font = TTF_OpenFont("files/Roboto-Black.ttf", 24);
    SDL_Window* janela = SDL_CreateWindow("Xadrez", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGURA, ALTURA, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderizador = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);

    // Inicializa as peças
    for (size_t j = 0; j < 8; j++) {
        // Peões brancos na linha 1
        peca[j].tipo = 1; // Peão
        peca[j].status = true;
        peca[j].lado = 0; // Branco
        peca[j].x = j; 
        peca[j].y = 1; 

        // Peões pretos na linha 6
        peca[j + 8].tipo = 1; // Peão
        peca[j + 8].status = true;
        peca[j + 8].lado = 1; // Preto
        peca[j + 8].x = j; 
        peca[j + 8].y = 6; 
    }

    // Tipos para peças principais
    int pieceTypes[8] = {2, 3, 4, 5, 6, 4, 3, 2}; // Tipos para outras peças
    for (size_t i = 0; i < 8; i++) {
        // Peças brancas na linha 0
        peca[i + 16].tipo = pieceTypes[i];
        peca[i + 16].status = true;
        peca[i + 16].lado = 0; // Branco
        peca[i + 16].x = i; 
        peca[i + 16].y = 0; 

        // Peças pretas na linha 7
        peca[i + 24].tipo = pieceTypes[i];
        peca[i + 24].status = true;
        peca[i + 24].lado = 1; // Preto
        peca[i + 24].x = i; 
        peca[i + 24].y = 7; 
    }

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false; // Sai do loop quando a janela é fechada
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) { // Verifica se é o botão esquerdo do mouse
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;

                    // Converte as coordenadas do mouse para as coordenadas do tabuleiro
                    int squareSize = ALTURA / 8;
                    int x = mouseX / squareSize;
                    int y = mouseY / squareSize;

                    if (peca_selecionada == NULL) {
                        // Seleciona a peça
                        for (int i = 0; i < 32; i++) {
                            if (peca[i].x == x && peca[i].y == y && peca[i].status) {
                                peca_selecionada = &peca[i];
                                verificar_jogadas_disponiveis();
                                break;
                            }
                        }
                    } else {
                        // Tenta mover a peça selecionada
                        if (x >= 0 && x < 8 && y >= 0 && y < 8) {
                            mover_peca(x, y);
                        }
                        peca_selecionada = NULL; // Reseta a seleção
                    }
                }
            }
        }

        // Limpa a janela
        SDL_SetRenderDrawColor(renderizador, 255, 255, 55, 255);
        SDL_RenderClear(renderizador);

        // Desenha o grid
        int size = ALTURA / 8; // Tamanho de cada quadrado
        SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255); // Cor preta para linhas do grid
        for (size_t i = 0; i <= 8; i++) {
            SDL_RenderDrawLine(renderizador, 0, size * i, ALTURA, size * i); // Linhas horizontais
            SDL_RenderDrawLine(renderizador, size * i, 0, size * i, ALTURA); // Linhas verticais
        }

        // Desenha o quadrado selecionado
        if (peca_selecionada) {
            SDL_Rect selectedSquare;
            selectedSquare.x = peca_selecionada->x * size;
            selectedSquare.y = peca_selecionada->y * size;
            selectedSquare.w = size;
            selectedSquare.h = size;

            SDL_SetRenderDrawColor(renderizador, 0, 255, 0, 128); // Verde semi-transparente
            SDL_RenderFillRect(renderizador, &selectedSquare); // Desenha o quadrado selecionado
        }

        // Desenha as jogadas disponíveis
        SDL_SetRenderDrawColor(renderizador, 255, 0, 0, 128); // Vermelho semi-transparente
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (jogadas_disponiveis[i][j]) {
                    SDL_Rect moveSquare;
                    moveSquare.x = j * size;
                    moveSquare.y = i * size;
                    moveSquare.w = size;
                    moveSquare.h = size;
                    SDL_RenderFillRect(renderizador, &moveSquare); // Desenha as áreas disponíveis
                }
            }
        }

        // Desenha as peças
        for (size_t i = 0; i < 32; i++) { // Alterado para 32 peças
            desenhar_peca(renderizador, &peca[i]);
        }

        SDL_RenderPresent(renderizador);
        SDL_Delay(16); // Controle de taxa de quadros
    }

    TTF_CloseFont(font); // Libera a fonte
    TTF_Quit();
    SDL_DestroyRenderer(renderizador); // Limpeza
    SDL_DestroyWindow(janela);
    SDL_Quit();

    return 0;
}
