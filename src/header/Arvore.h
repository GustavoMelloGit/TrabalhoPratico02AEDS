typedef struct Info_Est {
    int titulo_eleitor;
    char Nome[50];
    int voto;
    int votoRecebido;
}Info;
typedef struct No_Est {
    Info *info;
    struct No_Est *esq;
    struct No_Est *dir;
}No;

No *arvoreTitulos;
No *arvoreVotos;
No *arvoreCandidatos;

void mostraMenu();

void criarArvore(No **);

void limpaArvore(No *);

void contaVotos(No *);

void insereTitulo(No **, Info *);

void insereVoto(No **, Info *);

void criaInfo();

void votar(Info *);

void imprimeVotos(No *);

void preOrderRec(No *);

void sucessor(No *, No **);

int pesquisa(No *, Info *);

int retira(No **, Info);

int contemTitulo(No *, int);

Info *pesquisaTitulo(No *, int);
