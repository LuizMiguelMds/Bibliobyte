#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <conio.h>
#include <string.h>
#include <ctype.h> 

enum COLORS {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
};

enum BACKGROUND_COLORS {
    _BLACK = 0,
    _BLUE = 16,
    _GREEN = 32,
    _CYAN = 48,
    _RED = 64,
    _MAGENTA = 80,
    _BROWN = 96,
    _LIGHTGRAY = 112,
    _DARKGRAY = 128,
    _LIGHTBLUE = 144,
    _LIGHTGREEN = 160,
    _LIGHTCYAN = 176,
    _LIGHTRED = 192,
    _LIGHTMAGENTA = 208,
    _YELLOW = 224,
    _WHITE = 240
};

enum AreasConhecimento{BIOMEDICAS, EXATAS, HUMANAS};

typedef struct{
  int codigo;
  char titulo[100];
  char autor[100];
  char editora[100];
  enum AreasConhecimento area;
  int quantidade_acervo;
  int quantidade_disponivel;
} Livro;

void TextColor(int letras, int fundo) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), letras + fundo);
}

void ResetColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE | _BLACK);
}

void linhaCol(int lin, int col) {
    COORD coord;
    coord.X = col - 1;
    coord.Y = lin - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Fun√ß√£o para desenhar uma caixa (box) no console
void box(int lin1, int col1, int lin2, int col2) {
    const char HORIZONTAL = 196; // ‚îÄ
    const char VERTICAL = 179;   // ‚îÇ
    const char TOP_LEFT = 218;   // ‚îå
    const char TOP_RIGHT = 191;  // ‚îê
    const char BOTTOM_LEFT = 192;// ‚îî
    const char BOTTOM_RIGHT = 217;// ‚îò

    int i;

    // Linhas horizontais
    for (i = col1; i <= col2; i++) {
        linhaCol(lin1, i);
        printf("%c", HORIZONTAL);
        linhaCol(lin2, i);
        printf("%c", HORIZONTAL);
    }

    // Linhas verticais
    for (i = lin1; i <= lin2; i++) {
        linhaCol(i, col1);
        printf("%c", VERTICAL);
        linhaCol(i, col2);
        printf("%c", VERTICAL);
    }

    // Cantos
    linhaCol(lin1, col1);
    printf("%c", TOP_LEFT);
    linhaCol(lin1, col2);
    printf("%c", TOP_RIGHT);
    linhaCol(lin2, col1);
    printf("%c", BOTTOM_LEFT);
    linhaCol(lin2, col2);
    printf("%c", BOTTOM_RIGHT);
}

void exibirCabecalho() {
    system("cls");
    printf("                                     .-'''-.                                                    \n");
    printf("                        .---.       '   _    \\                                                  \n");
    printf("/|        .--./|        |   |.--. /   /` '.   \\ /|                               __.....__      \n");
    printf("||        |__|||        |   ||__|.   |     \\  ' ||    .-.          .-        .-''         '.    \n");
    printf("||        .--.||        |   |.--.|   '      |  '||     \\ \\        / /  .|   /     .-''\"'-.  `.  \n");
    printf("||  __    |  |||  __    |   ||  |\\    \\     / / ||  __  \\ \\      / / .' |_ /     /________\\   \\ \n");
    printf("||/'__ '. |  |||/'__ '. |   ||  | `.   ` ..' /  ||/'__ '.\\ \\    / /.'     ||                  | \n");
    printf("|:/`  '. '|  ||:/`  '. '|   ||  |    '-...-'`   |:/`  '. '\\ \\  / /'--.  .-'\\    .-------------' \n");
    printf("||     | ||  |||     | ||   ||  |               ||     | | \\ `  /    |  |   \\    '-.____...---. \n");
    printf("||\\    / '|__|||\\    / '|   ||__|               ||\\    / '  \\  /     |  |    `.             .'  \n");
    printf("|/\\'..' /     |/\\'..' / '---'                   |/\\'..' /   / /      |  '.'    `''-...... -'    \n");
    printf("'  `'-'`      '  `'-'`                          '  `'-'`|`-' /       |   /                       \n");
    printf("                                                         '..'        `'-'                        \n");
    printf("=================================================================================================\n");
}

void menuLogin() {
    char usuario[20], senha[20];
    const char usuarioCorreto[] = "admin";
    const char senhaCorreta[] = "1234";
    int tentativas = 3; // N√∫mero de tentativas permitidas

    while (tentativas > 0) {
        system("cls");
        exibirCabecalho(); // Exibe o cabe√ßalho no topo
        printf("========== MENU DE LOGIN ==========\n");
        printf("Usuario: ");
        scanf("%s", usuario);
        printf("Senha: ");
        scanf("%s", senha);

        if (strcmp(usuario, usuarioCorreto) == 0 && strcmp(senha, senhaCorreta) == 0) {
            printf("\nLogin bem-sucedido!\n");
            Sleep(1000); // Pausa de 1 segundo antes de continuar
            return; // Sai da fun√ß√£o de login e continua no programa
        } else {
            tentativas--;
            printf("\nUsuario ou senha incorretos! Tentativas restantes: %d\n", tentativas);
            Sleep(2000); // Pausa de 2 segundos para mostrar o erro
        }
    }

    // Se esgotar as tentativas, encerra o programa
    printf("\nNumero de tentativas excedido. Encerrando o programa...\n");
    exit(0);
}

// Fun√ß√£o para criar um menu
int menu(int lin1, int col1, int qtd, char lista[][40]) {
    int opc = 1;
    int lin2, col2, linha, i, tamMaxitem, tecla;

    tamMaxitem = strlen(lista[0]);

    for (i = 1; i < qtd; i++) {
        if (strlen(lista[i]) > tamMaxitem) {
            tamMaxitem = strlen(lista[i]);
        }
    }

    lin2 = lin1 + (qtd * 2 + 2);
    col2 = col1 + tamMaxitem + 4;

    TextColor(WHITE, _BLUE);
    setlocale(LC_ALL, "C");
    box(lin1, col1, lin2, col2);
    setlocale(LC_ALL, "");

    while (1) {
        linha = lin1 + 2;
        for (i = 0; i < qtd; i++) {
            if (i + 1 == opc)
                TextColor(BLACK, _LIGHTGREEN);
            else
                TextColor(WHITE, _BLUE);

            linhaCol(linha, col1 + 2);
            printf("%s", lista[i]);
            linha += 2;
        }

        linhaCol(1, 1);
        tecla = getch();

        // Controle do menu com as setas do teclado
        if (tecla == 80) { // Seta para baixo
            opc++;
            if (opc > qtd) opc = 1;
        } else if (tecla == 72) { // Seta para cima
            opc--;
            if (opc < 1) opc = qtd;
        } else if (tecla == 13) { // Enter
            return opc;
        }
    }
}

int validarCodigoLivro(char *codigoEntrada, FILE *arquivo) {
    // Verificar se a entrada esta vazia
    if (codigoEntrada == NULL || codigoEntrada[0] == '\n') {
        printf("Entrada invalida.\n");
        return 0;
    }

    // Remover newline se presente
    codigoEntrada[strcspn(codigoEntrada, "\n")] = 0;

    // Verificar se a entrada contem apenas digitos
    for (int i = 0; codigoEntrada[i] != '\0'; i++) {
        if (!isdigit(codigoEntrada[i])) {
            printf("Erro: O codigo deve conter apenas numeros!\n");
            return 0;
        }
    }

    // Converter para inteiro
    int codigo = atoi(codigoEntrada);

    // Verificar se o codigo ja existe no arquivo
    rewind(arquivo);
    Livro livroExistente;
    while (fread(&livroExistente, sizeof(Livro), 1, arquivo) == 1) {
        if (livroExistente.codigo == codigo) {
            printf("Erro: Ja existe um livro com este codigo!\n");
            return 0;
        }
    }

    return codigo;
}

// Funcao para o submenu de "Cadastrar Novo Livro"
void cadastrarLivro() {
    system("cls");
    exibirCabecalho();
    printf("Voce selecionou: Cadastrar Novo Livro\n");
    
    Livro novoLivro;
    FILE *arquivo = fopen("biblioteca.bin", "ab+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    printf("--- CADASTRAR NOVO LIVRO ---\n");

    // Variaveis para validacao
    char codigoEntrada[20];
    int codigoValidado = 0;

    // Loop controlado para validacao do codigo
do {
    printf("Digite o codigo do livro (apenas numeros): ");
    
    // Limpar buffer antes de ler
    fflush(stdin);       
    
    // Ler entrada
    if (fgets(codigoEntrada, sizeof(codigoEntrada), stdin) == NULL) {
        printf("\nErro na leitura do codigo.\n");
        continue;
    }
    
    // Tentar validar o codigo
    codigoValidado = validarCodigoLivro(codigoEntrada, arquivo);
    
    // Adicionar mensagem de confirmaÁ„o se o codigo for valido
    if (codigoValidado != 0) {
        printf("Codigo validado com sucesso!(pressione 'Enter' para prosseguir)", codigoValidado);
    }

} while (codigoValidado == 0);

    // Atribuir codigo validado
    novoLivro.codigo = codigoValidado;

    // Resto do codigo de cadastro permanece igual
    getchar(); // Limpar buffer adicional
    

    printf("Digite o titulo do livro: ");
    fgets(novoLivro.titulo, sizeof(novoLivro.titulo), stdin);
    novoLivro.titulo[strcspn(novoLivro.titulo, "\n")] = 0;

    printf("Digite o autor: ");
    fgets(novoLivro.autor, sizeof(novoLivro.autor), stdin);
    novoLivro.autor[strcspn(novoLivro.autor, "\n")] = 0;

    printf("Digite a editora: ");
    fgets(novoLivro.editora, sizeof(novoLivro.editora), stdin);
    novoLivro.editora[strcspn(novoLivro.editora, "\n")] = 0;

// Validacao da area
int escolhaArea = 0;
int areaValida = 0;

while (!areaValida) {
    // Menu para selecao de area
    printf("Selecione a area:\n");
    printf("1. Exatas\n");
    printf("2. Humanas\n");
    printf("3. Biomedicas\n");
    printf("Escolha a area (1-3): ");
    
    // Ler a escolha
    if (scanf("%d", &escolhaArea) != 1) {
        // Limpar entrada invalida
        while (getchar() != '\n');
        printf("Entrada invalida. Digite um numero entre 1 e 3.\n");
        continue;
    }

    // Limpar buffer
    while (getchar() != '\n');

    // Verificar se a escolha est· no intervalo v·lido
    if (escolhaArea >= 1 && escolhaArea <= 3) {
        areaValida = 1;
    } else {
        printf("Opcao invalida. Escolha um numero entre 1 e 3.\n");
    }
}

// Atribuir area baseado na escolha
switch(escolhaArea) {
    case 1: novoLivro.area = EXATAS; break;
    case 2: novoLivro.area = HUMANAS; break;
    case 3: novoLivro.area = BIOMEDICAS; break;
}

// ValidaÁ„o da quantidade no acervo
int quantidadeAcervo = 0;
int quantidadeValida = 0;

while (!quantidadeValida) {
    printf("Digite a quantidade no acervo: ");
    
    // Ler a quantidade
    if (scanf("%d", &quantidadeAcervo) != 1) {
        // Limpar entrada invalida
        while (getchar() != '\n');
        printf("Entrada invalida. Digite um numero inteiro.\n");
        continue;
    }

    // Limpar buffer
    while (getchar() != '\n');

    // Verificar se a quantidade e valida (nao negativa)
    if (quantidadeAcervo >= 0) {
        quantidadeValida = 1;
    } else {
        printf("Quantidade invalida. Digite um numero maior ou igual a zero.\n");
    }
}

// Atribuir quantidade
novoLivro.quantidade_acervo = quantidadeAcervo;
novoLivro.quantidade_disponivel = quantidadeAcervo;

fwrite(&novoLivro, sizeof(Livro), 1, arquivo);
fclose(arquivo);

printf("Livro cadastrado com sucesso!\n");
system("pause");
}

// Funcao para o submenu de "Consultar Livros"
void consultarLivros() {
  char continuar;
  do{
    system("cls");
    exibirCabecalho();
    printf("Voce selecionou: Consultar Livros\n");
    
    FILE *arquivo = fopen("biblioteca.bin", "rb");
    Livro livro;
    int encontrados = 0;

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        system("pause");
        return;
    }

    printf("--- CONSULTAR LIVROS ---\n");
    printf("1. Consultar livro por codigo\n");
    printf("2. Listar livros por area\n");
    printf("3. Quantidade total de livros\n");
    printf("4. Listar todos os livros\n");
    printf("Escolha uma opcao: ");

    int opcao;
    scanf("%d", &opcao);
    getchar(); // Limpar buffer

    switch(opcao) {
        case 1: {
            int codigo;
            printf("Digite o codigo do livro: ");
            scanf("%d", &codigo);

            while (fread(&livro, sizeof(Livro), 1, arquivo) == 1) {
                if (livro.codigo == codigo) {
                    printf("\nDisponibilidade: %d\n", livro.quantidade_disponivel);
                    printf("\nDados completos do livro:\n");
                    printf("Codigo: %d\n", livro.codigo);
                    printf("Titulo: %s\n", livro.titulo);
                    printf("Autor: %s\n", livro.autor);
                    printf("Editora: %s\n", livro.editora);

                    // Conversao do enum para string
                    char *areaStr;
                    switch(livro.area) {
                        case EXATAS: areaStr = "Exatas"; break;
                        case HUMANAS: areaStr = "Humanas"; break;
                        case BIOMEDICAS: areaStr = "Biomedicas"; break;
                    }
                    printf("area: %s\n", areaStr);

                    printf("Quantidade no Acervo: %d\n", livro.quantidade_acervo);
                    printf("Quantidade Disponivel: %d\n", livro.quantidade_disponivel);
                    encontrados++;
                    break;
                }
            }

            if (encontrados == 0) {
                printf("Livro n√£o encontrado.\n");
            }
            break;
        }
        case 2: {
            printf("Selecione a area:\n");
            printf("1. Exatas\n");
            printf("2. Humanas\n");
            printf("3. Biomedicas\n");
            printf("Escolha a area (1-3): ");

            int escolhaArea;
            scanf("%d", &escolhaArea);

            enum AreasConhecimento areaEscolhida;
            switch(escolhaArea) {
                case 1: areaEscolhida = EXATAS; break;
                case 2: areaEscolhida = HUMANAS; break;
                case 3: areaEscolhida = BIOMEDICAS; break;
                default: 
                    printf("Opcao invalida.\n");
                    fclose(arquivo);
                    system("pause");
                    return;
            }

            while (fread(&livro, sizeof(Livro), 1, arquivo) == 1) {
                if (livro.area == areaEscolhida) {
                    printf("\nCodigo: %d\n", livro.codigo);
                    printf("Titulo: %s\n", livro.titulo);
                    printf("Disponivel: %d\n", livro.quantidade_disponivel);
                    encontrados++;
                }
            }

            if (encontrados == 0) {
                printf("Nenhum livro encontrado na area especificada.\n");
            }
            break;
        }
        case 3: {
            int totalLivros = 0;
            while (fread(&livro, sizeof(Livro), 1, arquivo) == 1) {
                totalLivros += livro.quantidade_acervo;
            }
            printf("Quantidade total de livros na biblioteca: %d\n", totalLivros);
            break;
        }
        case 4: {
          system("cls");
                printf("--- LISTA COMPLETA DE LIVROS ---\n");
                rewind(arquivo); // Reset file pointer to beginning
                while (fread(&livro, sizeof(Livro), 1, arquivo) == 1) {
                    // Convers√£o do enum para string
                    char *areaStr;
                    switch(livro.area) {
                        case EXATAS: areaStr = "Exatas"; break;
                        case HUMANAS: areaStr = "Humanas"; break;
                        case BIOMEDICAS: areaStr = "Biomedicas"; break;
                    }

                    printf("\nCodigo: %d\n", livro.codigo);
                    printf("Titulo: %s\n", livro.titulo);
                    printf("Autor: %s\n", livro.autor);
                    printf("Editora: %s\n", livro.editora);
                    printf("Area: %s\n", areaStr);
                    printf("Quantidade no Acervo: %d\n", livro.quantidade_acervo);
                    printf("Quantidade Disponivel: %d\n", livro.quantidade_disponivel);
                    encontrados++;
                }

                if (encontrados == 0) {
                    printf("Nenhum livro cadastrado.\n");
                }
      break;
    }
        default:
            printf("Opcao invalida.\n");
    }

    fclose(arquivo);

    printf("\nDeseja continuar consultando? (S/N): ");
    scanf(" %c", &continuar);
    } while (continuar == 'S' || continuar == 's');
}

// Funcao para o submenu de "Alterar Livro"
void alterarLivro() {
    system("cls");
    exibirCabecalho();
    printf("Voce selecionou: Alterar Livro\n");
    
    FILE *arquivo = fopen("biblioteca.bin", "r+b");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        system("pause");
        return;
    }
	
	//listar codigos existentes
	Livro livro;
    int codigos[100], total_codigos = 0;
    rewind(arquivo);
    while (fread(&livro, sizeof(Livro), 1, arquivo) == 1) {
        codigos[total_codigos++] = livro.codigo;
    }

    printf("--- ALTERAR LIVRO ---\n");
    printf("Codigos cadastrados: ");
    for (int i = 0; i < total_codigos; i++) {
        printf("%d%s", codigos[i], (i < total_codigos - 1) ? ", " : "\n");
    }

    int codigo, encontrado = 0;

    printf("Digite o codigo do livro que deseja alterar: ");
    scanf("%d", &codigo);

  rewind(arquivo);
    while (fread(&livro, sizeof(Livro), 1, arquivo) == 1) {
        if (livro.codigo == codigo) {
            encontrado = 1;

            //tive que converter areaConhecimento para string para ele fazer a leitura
            char *areaAtual;
            switch(livro.area) {
                case BIOMEDICAS: areaAtual = "Biomedicas"; break;
                case EXATAS: areaAtual = "Exatas"; break;
                case HUMANAS: areaAtual = "Humanas"; break;
            }

            printf("\nInformacoes atuais do livro:\n");
            printf("Titulo: %s\n", livro.titulo);
            printf("Autor: %s\n", livro.autor);
            printf("Editora: %s\n", livro.editora);
            printf("Area Atual: %s\n", areaAtual);
            printf("Quantidade no Acervo: %d\n", livro.quantidade_acervo);
            printf("Quantidade Disponivel: %d\n", livro.quantidade_disponivel);

            printf("\nDigite os novos dados (deixe em branco para manter atual):\n");
            getchar(); // Limpar buffer

            char temp[100];

            printf("Novo titulo: ");
            fgets(temp, sizeof(temp), stdin);
            if (strlen(temp) > 1) {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(livro.titulo, temp);
            }

            printf("Novo autor: ");
            fgets(temp, sizeof(temp), stdin);
            if (strlen(temp) > 1) {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(livro.autor, temp);
            }

            printf("Nova editora: ");
            fgets(temp, sizeof(temp), stdin);
            if (strlen(temp) > 1) {
                temp[strcspn(temp, "\n")] = 0;
                strcpy(livro.editora, temp);
            }

			printf("Nova Area (1-Biomedicas, 2-Exatas, 3-Humanas): ");
			int escolhaArea;
			scanf("%d", &escolhaArea);

			// ValidaÁ„o da ·rea
			while (escolhaArea < 1 || escolhaArea > 3) {
    			printf("Opcao invalida. Digite 1 para Biomedicas, 2 para Exatas ou 3 para Humanas: ");
    			scanf("%d", &escolhaArea);
				}

			switch(escolhaArea) {
    			case 1: livro.area = BIOMEDICAS; break;
    			case 2: livro.area = EXATAS; break;
    			case 3: livro.area = HUMANAS; break;
			}

            printf("Nova quantidade no acervo: ");
            scanf("%d", &livro.quantidade_acervo);

            printf("Nova quantidade disponivel: ");
            scanf("%d", &livro.quantidade_disponivel);

            // Voltar para posicao anterior para sobrescrever
            fseek(arquivo, -sizeof(Livro), SEEK_CUR);
            fwrite(&livro, sizeof(Livro), 1, arquivo);

            printf("\nLivro alterado com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Livro com codigo %d nao encontrado.\n", codigo);
    }

    fclose(arquivo);
    system("pause");
}

// Funcao para o submenu de "Excluir Livro"
void excluirLivro() {
    system("cls");
    exibirCabecalho();
    printf("Voce selecionou: Excluir Livro\n");
    FILE *arquivo = fopen("biblioteca.bin", "rb");
    FILE *arquivoTemp = fopen("temp_biblioteca.bin", "wb");

    if (arquivo == NULL || arquivoTemp == NULL) {
        printf("Erro ao abrir os arquivos!\n");
        if (arquivo) fclose(arquivo);
        if (arquivoTemp) fclose(arquivoTemp);
        system("pause");
        return;
    }

    // Primeiro, listar todos os codigos cadastrados
    Livro livro;
    int codigos[100], total_codigos = 0;

    while (fread(&livro, sizeof(Livro), 1, arquivo) == 1) {
        codigos[total_codigos++] = livro.codigo;
    }

    printf("--- EXCLUIR LIVRO ---\n");
    printf("Codigos cadastrados: ");
    for (int i = 0; i < total_codigos; i++) {
        printf("%d%s", codigos[i], (i < total_codigos - 1) ? ", " : "\n");
    }

    int codigo, encontrado = 0;
    printf("Digite o codigo do livro que deseja excluir: ");
    scanf("%d", &codigo);

    // Rewind para voltar ao inicio do arquivo
    rewind(arquivo);

    while (fread(&livro, sizeof(Livro), 1, arquivo) == 1) {
        if (livro.codigo == codigo) {
            // Converter area para string para exibicao
            char *areaStr;
            switch(livro.area) {
                case BIOMEDICAS: areaStr = "Biomedicas"; break;
                case EXATAS: areaStr = "Exatas"; break;
                case HUMANAS: areaStr = "Humanas"; break;
            }

            // Confirmacao de exclusao
            printf("\nInformacoes do livro a ser excluido:\n");
            printf("Codigo: %d\n", livro.codigo);
            printf("Titulo: %s\n", livro.titulo);
            printf("Autor: %s\n", livro.autor);
            printf("Editora: %s\n", livro.editora);
            printf("Area: %s\n", areaStr);
            printf("Quantidade no Acervo: %d\n", livro.quantidade_acervo);
            printf("Quantidade Disponivel: %d\n", livro.quantidade_disponivel);

            char confirmacao;
            printf("\nTem certeza que deseja excluir este livro? (S/N): ");
            scanf(" %c", &confirmacao);

            encontrado = 1;

            if (confirmacao == 'S' || confirmacao == 's') {
                // Nao copia o livro para o arquivo temporario (efetivamente excluindo)
                printf("Livro excluido com sucesso!\n");
            } else {
                // Copia o livro para o arquivo temporario
                fwrite(&livro, sizeof(Livro), 1, arquivoTemp);
                printf("Exclus√£o cancelada.\n");
            }
        } else {
            // Copia outros livros para o arquivo temporario
            fwrite(&livro, sizeof(Livro), 1, arquivoTemp);
        }
    }

    // Fechar arquivos
    fclose(arquivo);
    fclose(arquivoTemp);

    // Substituir arquivo original
    remove("biblioteca.bin");
    rename("temp_biblioteca.bin", "biblioteca.bin");

    if (!encontrado) {
        printf("Livro com codigo %d nao encontrado.\n", codigo);
    }

    system("pause");
}

void EmprestimoDevolucaoLivro() {
    system("cls");
    exibirCabecalho();
    FILE *arquivo = fopen("biblioteca.bin", "r+b");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        system("pause");
        return;
    }

    // Listar codigos cadastrados
    Livro livro;
    int codigos[100], total_codigos = 0;
    rewind(arquivo);
    while (fread(&livro, sizeof(Livro), 1, arquivo) == 1) {
        codigos[total_codigos++] = livro.codigo;
    }

    printf("--- EMPRESTIMO/DEVOLUCAO DE LIVRO ---\n");
    printf("Codigos cadastrados: ");
    for (int i = 0; i < total_codigos; i++) {
        printf("%d%s", codigos[i], (i < total_codigos - 1) ? ", " : "\n");
    }

int opcao;
do {
    printf("\nEscolha a operacao:\n");
    printf("0. Sair\n");
    printf("1. Emprestimo\n");
    printf("2. Devolucao\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    // ValidaÁ„o da opÁ„o
    if (opcao < 0 || opcao > 2) {
        printf("\nOpcao invalida. Por favor, escolha 0, 1 ou 2.\n");
        while (getchar() != '\n'); // Limpa buffer de entrada
    }
} while (opcao < 0 || opcao > 2);

// Se escolher sair, pode retornar ao menu principal
if (opcao == 0) {
    return; // ou continue; dependendo da estrutura do seu cÛdigo
}

    // codigo do livro
    int codigo;
    printf("Digite o codigo do livro: ");
    scanf("%d", &codigo);

    // Variaveis de controle
    int encontrado = 0;
    long posicao = 0;

    // Reposicionar no inicio do arquivo
    rewind(arquivo);

    // Buscar livro
    while (fread(&livro, sizeof(Livro), 1, arquivo) == 1) {
        if (livro.codigo == codigo) {
            encontrado = 1;
            posicao = ftell(arquivo) - sizeof(Livro);

            // Informacoes do livro
            char *areaStr;
            switch(livro.area) {
                case BIOMEDICAS: areaStr = "Biomedicas"; break;
                case EXATAS: areaStr = "Exatas"; break;
                case HUMANAS: areaStr = "Humanas"; break;
            }

            printf("\nLivro encontrado:\n");
            printf("Titulo: %s\n", livro.titulo);
            printf("Area: %s\n", areaStr);
            printf("Quantidade Disponivel: %d\n", livro.quantidade_disponivel);
            printf("Quantidade Total no Acervo: %d\n", livro.quantidade_acervo);

            //  emprestimo e devolucao
            switch(opcao) {
                case 1: // Emprestimo
                    if (livro.quantidade_disponivel > 0) {
                        livro.quantidade_disponivel--;
                        printf("\nEmprestimo realizado com sucesso!\n");
                    } else {
                        printf("\nNao ha, exemplares disponiveis para emprestimo.\n");
                        encontrado = 0;
                    }
                    break;

                case 2: // Devolucao
                    if (livro.quantidade_disponivel < livro.quantidade_acervo) {
                        livro.quantidade_disponivel++;
                        printf("\nDevolucao realizada com sucesso!\n");
                    } else {
                        printf("\nTodos os exemplares Ja estao no acervo.\n");
                        encontrado = 0;
                    }
                    break;

                default:
                    printf("\nOpcao invalida.\n");
                    encontrado = 0;
            }

            // Se operacao valida, atualizar arquivo
            if (encontrado) {
                fseek(arquivo, posicao, SEEK_SET);
                fwrite(&livro, sizeof(Livro), 1, arquivo);
            }

            break;
        }
    }

    // Livro nao encontrado
    if (!encontrado) {
        printf("\nLivro com codigo %d nao encontrado.\n", codigo);
    }

    fclose(arquivo);
    system("pause");
}

int main() {
    int opc;
    char lista[6][40] = {"Cadastrar Novo Livro", "Consultar Livros", "Alterar Livro", "Excluir", "Emprestimo/Devolucao", "Sair/Encerrar programa"};

    setlocale(LC_ALL, "");

    menuLogin();

    while (1) {
        exibirCabecalho(); // Exibe o cabecalho
        opc = menu(15, 6, 6, lista); // Exibe o menu principal

        switch (opc) {
            case 1:
                cadastrarLivro();
                ResetColor();
                break;
            case 2:
                consultarLivros();
                ResetColor();
                break;
            case 3:
                alterarLivro();
                ResetColor();
                break;
            case 4:
                excluirLivro();
                ResetColor();
                break;
            case 5:
              EmprestimoDevolucaoLivro();
              ResetColor();
              break;
            case 6:
                linhaCol(30, 25);
                printf("Encerrando o programa...\n");
                exit(0);
                ResetColor();
                break;
        }
    }

    ResetColor();
    return 0;
}

