

**CSI 488 – Algoritmos e Estruturas de Dados I**

**Trabalho Prático 2**

**Prof. Mateus Ferreira Satler**

**DECSI – ICEA - UFOP**

**Descrição**

O trabalho consiste na implementação de um Sistema de Votação usando **ÁRVORES BINÁRIAS DE BUSCA (ABB)**.

Imagine que um grupo de pessoas irá participar de uma eleição. Para votar e ser votado, e necessário ter um número

de título de eleitor válido (o número de título pode ser um inteiro simples). Além disso, qualquer pessoa pode ser

eleita para a função. Nesta votação, uma pessoa pode **votar em alguém** ou, a qualquer momento, decidir **retirar seu**

**voto** por qualquer que seja o motivo. Contudo, apenas um voto por pessoa pode estar armazenado no sistema num

dado momento.

Essas verificações podem ser feitas da seguinte forma:

•

•

Criar uma ABB para armazenar os números de todos os títulos válidos.

Criar outra ABB para armazenar os números de todos os títulos que já votaram até o momento.

Para evitar redundância de dados (informações iguais armazenadas em locais diferentes), o cadastro dos votantes

deverá ser feito em uma estrutura separada que será **referenciada** pelas árvores (\*info). Utilize as estruturas abaixo:

**typedef struct** Info\_Est {

**int** titulo\_eleitor;

**char** Nome[50];

**int** voto;

}Info;

**typedef struct** No\_Est {

**Info** \*info;

struct No\_Est \*esq;

struct No\_Est \*dir;

}No;

No \*arvoreTitulos;

No \*arvoreVotos;

**Observação:** Não permita que sejam cadastrados dois números de título de eleitor iguais. Ao final do programa,

libere todos os endereços de memória alocados.

**Funcionalidades Esperadas**

Seu programa deve conter um **menu** com as seguintes opções:

**1. Cadastrar um título:** insere o título e nome na árvore de títulos válidos (se esse não estiver lá)

**2. Descadastrar um título:** retira o título da árvore de títulos válidos (se esse estiver lá) e apaga os dados.

**3. Iniciar nova votação:** inicializa/esvazia a ABB que guarda os títulos que já votaram.

**4. Votar:** lê o número do título e o voto. Se o número é válido e se ainda não votou, atualiza a ABB que armazena

os títulos de quem já votou e computa o voto (em quem votou). Se o número não é válido ou já votou, emite

mensagem de erro.

**5. Retirar voto:** lê o número do título e verifica se já votou. Se já votou, retira o título e o voto. Caso contrário,

emite mensagem de erro.

Página **1** de **2**





**6. Mostrar resultado parcial das eleições** (títulos e nomes dos votados e quantidade de votos de cada um),

ordenados de forma decrescente em relação ao **número de votos.**

**7. Listar todos os números de títulos e nomes** das pessoas que já votaram.

**8. Liberar todas as estruturas** e **encerrar o programa**.
