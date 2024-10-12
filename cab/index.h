#ifndef INDEX_H
#define INDEX_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h> 
#include <stdbool.h>
#include <stdlib.h>

#define ALTURA 700
#define LARGURA 800

typedef struct {
    int x, y;     // Posição no tabuleiro
    int tipo;     // Tipo da peça (1 = peão, 2 = torre, etc.)
    int lado;     // Lado (0 = branco, 1 = preto)
    bool status;  // Status da peça (ativa/inativa)
} pecas;

extern pecas peca[32];
extern pecas* peca_selecionada;
extern bool jogadas_disponiveis[8][8];

#endif