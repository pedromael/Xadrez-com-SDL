#include "../cab/desenhar.h"

void desenhar_peca(SDL_Renderer* renderizador, pecas* p) {
    int size = ALTURA / 8; // Tamanho de cada quadrado
    int pieceSize = size / 2; // Tamanho das peças (metade do quadrado)
    SDL_Rect rect;
    rect.w = pieceSize;
    rect.h = pieceSize;

    // Define a cor da peça com base no lado
    if (p->status) {
        if (p->lado == 0) { // Peças brancas
            SDL_SetRenderDrawColor(renderizador, 255, 255, 255, 255); // Branco
        } else { // Peças pretas
            SDL_SetRenderDrawColor(renderizador, 0, 0, 0, 255); // Preto
        }

        // Centraliza a peça no quadrado
        rect.x = p->x * size + (size - pieceSize) / 2; // Centraliza horizontalmente
        rect.y = p->y * size + (size - pieceSize) / 2; // Centraliza verticalmente
        SDL_RenderFillRect(renderizador, &rect);

        // Renderiza o número correspondente à peça
        char number[3];
        snprintf(number, sizeof(number), "%d", p->tipo); // Converte o tipo em string
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, number, (p->lado == 0) ? (SDL_Color){0, 0, 0, 255} : (SDL_Color){255, 255, 255, 255});
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderizador, textSurface);

        // Define a posição do texto
        SDL_Rect textRect;
        textRect.x = rect.x + pieceSize / 4; // Centraliza o texto no quadrado
        textRect.y = rect.y + pieceSize / 4; // Centraliza verticalmente
        textRect.w = textSurface->w;
        textRect.h = textSurface->h;

        // Renderiza o texto
        SDL_RenderCopy(renderizador, textTexture, NULL, &textRect);

        // Libera a superfície e a textura
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
}