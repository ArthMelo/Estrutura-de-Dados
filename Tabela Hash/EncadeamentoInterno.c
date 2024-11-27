//Tabela Hash com encadeamento interno sem área de colisão e sem coalescência
//arthurmb@dcc.ufrj.br

#include <stdio.h>
#include <stdlib.h>

typedef struct hash_no {
    int chave; 
    int prox; 
} hash_no;

void iniciarTabelaHash(hash_no *tabela, int tam) {
    for (int i = 0; i < tam; i++) {
        tabela[i].chave = -1; 
        tabela[i].prox = -1; 
    }
}

int funcaoHash(int chave, int mod) {
    return chave % mod;
}

void inserir(int chave, hash_no *tabela, int mod) {
    int pos = funcaoHash(chave, mod);

    if (tabela[pos].chave == -1) {
        tabela[pos].chave = chave;
    } else {
        int chaveExistente = tabela[pos].chave;
        if (funcaoHash(chaveExistente, mod) != pos) {
            tabela[pos].chave = chave;
            chave = chaveExistente; 
        }

        for (int i = pos; i < mod; i++) {
            if (tabela[i].chave == -1) {
                tabela[i].chave = chave;
                tabela[i].prox = -1;

                int atual = pos;
                while (tabela[atual].prox != -1) {
                    atual = tabela[atual].prox;
                }
                tabela[atual].prox = i;
                return;
            }
        }
        for (int i = 0; i < pos; i++) {
            if (tabela[i].chave == -1) {
                tabela[i].chave = chave;
                tabela[i].prox = -1;

                int atual = pos;
                while (tabela[atual].prox != -1) {
                    atual = tabela[atual].prox;
                }
                tabela[atual].prox = i;
                return;
            }
        }
    }
}

void imprimeTabela(hash_no *tabela, int mod) {
    for (int i = 0; i < mod; i++) {
        printf("%d\n", tabela[i].chave);
    }
}

void remover(int chave, hash_no *tabela, int mod) {
    int pos = funcaoHash(chave, mod);
    int atual = pos, anterior = -1;

    while (atual != -1) {
        if (tabela[atual].chave == chave) {
            if (anterior == -1) {
                if (tabela[atual].prox != -1) {
                    int prox = tabela[atual].prox;
                    tabela[atual].chave = tabela[prox].chave;
                    tabela[atual].prox = tabela[prox].prox;

                    tabela[prox].chave = -1;
                    tabela[prox].prox = -1;
                } else {
                    tabela[atual].chave = -1;
                }
            } else {
                tabela[anterior].prox = tabela[atual].prox;
                tabela[atual].chave = -1;
                tabela[atual].prox = -1;
            }
            return;
        }
        anterior = atual;
        atual = tabela[atual].prox;
    }
}

int main(void) {
    int mod, num;
    char indice;

    scanf("%d", &mod);
    hash_no tabelaHash[mod];

    iniciarTabelaHash(tabelaHash, mod);

    while (scanf(" %c %d", &indice, &num) != EOF) {
        if (indice == 'i') {
            inserir(num, tabelaHash, mod);
        } else if (indice == 'l') {
            imprimeTabela(tabelaHash, mod);
        } else if (indice == 'r') {
            remover(num, tabelaHash, mod);
        } else {
            break;
        }
    }

    return 0;
}
