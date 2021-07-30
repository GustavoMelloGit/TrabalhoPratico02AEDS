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

void criaArvoreVazia(No **);
void insercao(No **, Info*);
void insereTitulo(No **, Info *);
void criaInfo();
void preOrderRec (No* no);
void mostraMenu();
int pesquisa (No*, Info *) ;