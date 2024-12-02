# Projeto Xadrez em C com SDL

Este é um projeto de xadrez desenvolvido em C utilizando a biblioteca SDL para a interface gráfica. O objetivo é criar um jogo de xadrez funcional e interativo, com uma interface amigável e regras do jogo implementadas.

## Características

- Implementação completa das regras do xadrez.
- Interface gráfica utilizando SDL.
- Suporte para dois jogadores locais.
- Sistema de detecção de xeque e xeque-mate.
- Representação visual do tabuleiro e das peças.
- Animações simples para movimentação das peças.

## Requisitos

Certifique-se de ter os seguintes softwares instalados no seu sistema:

- [SDL2](https://www.libsdl.org/download-2.0.php)
- Um compilador C (ex: GCC)
- [Make](https://www.gnu.org/software/make/)

## Instalação

1. Clone o repositório:
   ```bash
   git clone https://github.com/pedromael/Xadrez-com-SDL.git

2. Instale as dependências da SDL (se necessário):

sudo apt-get install libsdl2-dev libsdl2-image-dev


3. Compile o projeto usando o Makefile:

make


4. Execute o jogo:

./xadrez



Como Jogar

1. Inicie o jogo com o comando ./xadrez.


2. Use o mouse para selecionar e mover peças.


3. Siga as regras do xadrez tradicional.


4. O jogo termina em xeque-mate, empate ou desistência.



Estrutura do Projeto

.
├── src/                # Código fonte
│   ├── main.c          # Entrada principal do programa
│   ├── board.c         # Lógica do tabuleiro
│   ├── pieces.c        # Lógica das peças
│   ├── sdl_utils.c     # Utilitários para SDL
│   └── ...
├── include/            # Cabeçalhos do projeto
│   ├── board.h
│   ├── pieces.h
│   ├── sdl_utils.h
│   └── ...
├── assets/             # Imagens das peças e tabuleiro
├── Makefile            # Automação de compilação
└── README.md           # Documentação

Contribuição

Sinta-se à vontade para abrir issues ou pull requests para melhorar o projeto. Todas as contribuições são bem-vindas!

Licença

Este projeto é licenciado sob a MIT License. Você pode utilizá-lo livremente, mas sem garantias.

Créditos

Pedro Manuel - Desenvolvedor principal.

Biblioteca gráfica: SDL.

Ícones e imagens de xadrez: [Fonte dos assets, se aplicável].



---

Nota: Se você tiver alguma dúvida ou sugestão, entre em contato ou abra uma issue no repositório.
