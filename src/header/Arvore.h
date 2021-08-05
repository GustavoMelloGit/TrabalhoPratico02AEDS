typedef struct Info_Est {
    int titulo_eleitor;
    char Nome[50];
    int voto;
}Info;
typedef struct No_Est {
    Info *info;
    struct No_Est *esq;
    struct No_Est *dir;
}No;

No *arvoreTitulos;
No *arvoreVotos;

void mostraMenu();
void criarArvore(No **);
void limpaArvore(No *);
void contaVotos(No *);
void insereTitulo(No **, Info *);
void criaInfo();
void votar(Info *);
void preOrderRec (No* no);
void sucessor(No *, No **);
int pesquisa (No*, Info *);
int retira(No **, Info);
Info* pesquisaTitulo(No *, int);
