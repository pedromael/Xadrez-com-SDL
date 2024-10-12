#include "../cab/verificadores.h"

void verificar_jogadas_disponiveis() {
    // Limpa jogadas anteriores
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            jogadas_disponiveis[i][j] = false;
        }
    }

    if (peca_selecionada) {
        int direcao = peca_selecionada->lado == 0 ? -1 : 1; // Direção do movimento
        int novaY = peca_selecionada->y + direcao;

        // Movimento para frente
        if (novaY >= 0 && novaY < 8) {
            // Verifica se o quadrado à frente está livre
            bool quadradoLivre = true;
            for (int i = 0; i < 32; i++) {
                if (peca[i].x == peca_selecionada->x && peca[i].y == novaY && peca[i].status) {
                    quadradoLivre = false;
                    break;
                }
            }
            if (quadradoLivre) {
                jogadas_disponiveis[novaY][peca_selecionada->x] = true; // Marca a posição para frente
            }
        }

        // Captura (diagonal)
        for (int dx = -1; dx <= 1; dx += 2) { // -1 e 1 para esquerda e direita
            int novaX = peca_selecionada->x + dx;
            if (novaX >= 0 && novaX < 8 && novaY >= 0 && novaY < 8) {
                // Verifica se há uma peça adversária na posição
                for (int i = 0; i < 32; i++) {
                    if (peca[i].x == novaX && peca[i].y == novaY && peca[i].status && peca[i].lado != peca_selecionada->lado) {
                        jogadas_disponiveis[novaY][novaX] = true; // Marca a captura
                        break;
                    }
                }
            }
        }
    }
}