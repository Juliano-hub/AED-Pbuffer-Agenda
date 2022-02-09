#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct dados{
    char nome[20];
    int telefone;
}dados;

typedef struct Nodo{
    dados dado;
    struct Nodo *pProx;
    struct Nodo *pAnt;
}Nodo;

typedef struct inicio{
    Nodo *pLast;
    Nodo *pIni;
}inicio;

int menu();
inicio* criaLista();
Nodo* criaNodo();
void adicionar(inicio *p, Nodo *AUX);
Nodo* buscar(inicio *p);
void ordernar_telefone(inicio *p);
void ordernar_nome(inicio *p);
void remover(inicio *p, Nodo *AUX);
void printar(inicio *p);
void freeAgenda(inicio *p);

int main(){
    inicio *lista;
    Nodo *AUX;

    int escolhaAUX; 
    int escolha=0;
    lista = criaLista();


    for(;;){

        escolha = menu();

        switch(escolha){
            case 1:
                AUX = criaNodo();

                adicionar(lista, AUX);
            break;

            case 2:
                AUX = buscar(lista);
                if(AUX != NULL){
                    printf("\n-----Dado encontrado:");
                    printf("\nNome:%s", AUX->dado.nome);
                    printf("\nTelefone:%d\n", AUX->dado.telefone);
                }
            break;

            case 3:
                escolhaAUX = -1;
                while(escolhaAUX <= 0 || escolhaAUX > 2){
                    printf("-----Ordernar por:\n");
                    printf("1-Nome\n");
                    printf("2-Telefone\n");
                    scanf("%d", &escolhaAUX);
                }

                if(escolhaAUX == 2){
                    ordernar_telefone(lista);
                }
                if(escolhaAUX == 1){
                    ordernar_nome(lista);
                }

            break;

            case 4:
                AUX = buscar(lista);

                if(AUX != NULL){
                    remover(lista, AUX);
                }
            break;

            case 5:
                printar(lista);
            break;

            case 6:

            break;

            default:
                printf("\nOp nao encontrada!\n");
            break;
        }

    if(escolha == 6){
        freeAgenda(lista);
        break;
    }

    }

    return 0;
}

int menu(){
    int escolha;
    printf("1-Adicionar\n");
    printf("2-Buscar\n");
    printf("3-Ordernar\n");
    printf("4-Apagar\n");
    printf("5-Listar\n");
    printf("6-Sair\n");
    scanf("%d", &escolha);

    return escolha;
}

inicio* criaLista(){
    inicio *AUX;
    AUX = (inicio*) malloc(sizeof(inicio));

    if(AUX == NULL){
        printf("\nNao foi possivel fazer o malloc!\n");
    }
    
    AUX->pIni = NULL;
    AUX->pLast = NULL;

    return (inicio*) AUX;
}

Nodo* criaNodo(){
    Nodo *AUX;

    AUX = (Nodo*) malloc(sizeof(Nodo));
    printf("Digite um nome:");
    scanf("%s", &AUX->dado.nome);
    printf("Digite uma telefone:");
    scanf("%d", &AUX->dado.telefone);

    AUX->pProx = NULL;
    AUX->pAnt = NULL;
    return (Nodo*) AUX;
}

void adicionar(inicio *p, Nodo *AUX){
    Nodo *inicio_AUX;
    Nodo *anterior_AUX;

    // adiciona no inicio caso for vazio a primeira vez
    if(p->pIni == NULL){
        p->pIni = AUX;

        p->pIni->pAnt = NULL;
        p->pIni->pProx = NULL;

        p->pLast = p->pIni;
        
        return;
    }

    // seta o ponteiro final como inicial
    p->pLast = p->pIni;

    inicio_AUX = p->pIni;
    anterior_AUX = inicio_AUX;

    // inicio_AUX aponta para o primeiro elemento

    // enquanto o próximo conteudo n for NULL para ADD no fim, ele passa para o próximo conteúdo
    while(inicio_AUX->pProx != NULL){
        inicio_AUX = inicio_AUX->pProx;
        inicio_AUX->pAnt = anterior_AUX;

        anterior_AUX = anterior_AUX->pProx;
        p->pLast = p->pLast->pProx;
    }

    // ADD o conteudo do nodo AUX no próximo elemento

    inicio_AUX->pProx = AUX;
    inicio_AUX = inicio_AUX->pProx;
    inicio_AUX->pAnt = anterior_AUX;

    p->pLast = p->pLast->pProx;

    return;
}

Nodo* buscar(inicio *p){
    Nodo *Vazio;
    Vazio = NULL;

    if(p->pIni == NULL){
        printf("-----Lista Vazia!\n");
        return (Nodo*) Vazio;
    }

    
    Nodo *inicio_AUX;
    char c[20];


    inicio_AUX = p->pIni;
    // inicio_AUX aponta para o primeiro elemento

    printf("\nDigite um nome:");
    scanf("%s", &c);

    while(strcmp(c, inicio_AUX->dado.nome) != 0){

        inicio_AUX = inicio_AUX->pProx;

        if(inicio_AUX == NULL){
            printf("-----Nome nao encontrado!\n");
        return (Nodo*) Vazio;
        }

    }

    return (Nodo*) inicio_AUX;
}

void ordernar_telefone(inicio *p){

    if(p->pIni == NULL){
    printf("-----Lista Vazia!\n");
    return;
    }

    Nodo *inicio_AUX;
    Nodo *AUX;
    dados AUX_AUX;

    for(inicio_AUX = p->pIni->pProx ; inicio_AUX != NULL ; inicio_AUX = inicio_AUX->pProx){
       for(AUX = p->pIni ; AUX != p->pLast ; AUX = AUX->pProx ){
           if(AUX->dado.telefone > AUX->pProx->dado.telefone){
               AUX_AUX = AUX->dado;
               AUX->dado = AUX->pProx->dado;
               AUX->pProx->dado = AUX_AUX;
           }
       }

    }

    printar(p);
}

void ordernar_nome(inicio *p){

    if(p->pIni == NULL){
    printf("-----Lista Vazia!\n");
    return;
    }

    Nodo *inicio_AUX;
    Nodo *AUX;
    dados AUX_AUX;

    for(inicio_AUX = p->pIni->pProx ; inicio_AUX != NULL ; inicio_AUX = inicio_AUX->pProx){
       for(AUX = p->pIni ; AUX != p->pLast ; AUX = AUX->pProx ){
           if( strcmp(AUX->dado.nome, AUX->pProx->dado.nome) > 0 ){
               AUX_AUX = AUX->dado;
               AUX->dado = AUX->pProx->dado;
               AUX->pProx->dado = AUX_AUX;
           }
       }

    }

    printar(p);
  
}

void remover(inicio *p, Nodo *AUX){
    Nodo *Remover;
    Nodo *inicio_AUX;

    // caso for o inicio
    if(AUX->pAnt == NULL){

        p->pIni->pProx = NULL;
        p->pIni->pAnt = NULL;
        p->pLast = NULL;
        p->pIni = NULL;
        free(AUX);
        return;
    }

    inicio_AUX = p->pIni;
    
    while(strcmp(inicio_AUX->dado.nome, AUX->dado.nome) != 0){
        inicio_AUX = inicio_AUX->pProx;
    }

    // caso for o final
    if(AUX->pProx == NULL){

        // seta o ponteiro do último sendo o penúltimo
        p->pLast = p->pLast->pAnt;

        Remover = AUX->pAnt;
        Remover->pProx = NULL;

        free(AUX);

        return;
    }

    // caso for o meio
    // seta o ponteiro do último sendo o penúltimo


    //p->pLast = p->pLast->pAnt;
    Remover = AUX->pAnt;
    Remover->pProx = AUX->pProx;
 
    Remover->pProx->pAnt = Remover;


    free(AUX);
    return;
}


void printar(inicio *p){
    if(p->pIni == NULL){
        printf("-----Lista Vazia!\n");
        return;
    }

    Nodo *inicio_AUX;

    inicio_AUX = p->pIni;
    // inicio_AUX aponta para o primeiro elemento

    printf("\n-----Lista\n");

    // enquanto o conteúdo não for NULL
    while(inicio_AUX != p->pLast){
        printf("nome: %s\n", inicio_AUX->dado.nome);
        printf("telefone: %d\n", inicio_AUX->dado.telefone);

        // ele passa para o próximo conteúdo
        inicio_AUX = inicio_AUX->pProx;
    }

    if(inicio_AUX != NULL){
        printf("nome: %s\n", inicio_AUX->dado.nome);
        printf("telefone: %d\n", inicio_AUX->dado.telefone);
    }
}


void freeAgenda(inicio *p){
	Nodo *aux;
	if(p->pIni == NULL  ){
        free(p);
        return;
    }
	
	if(p->pIni->pProx == NULL){		
		free(p->pIni);
        free(p);
		return;
	}

	for(aux = p->pIni->pProx; aux->pProx != NULL; aux = aux->pProx){
        free(aux->pAnt);
    }
	free(aux);
    free(p);
    
}


