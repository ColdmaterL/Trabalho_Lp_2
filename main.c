#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct lista{
    char nome[7];  // id
    int ini;  // endereço onde começa
    int fim;  // endereço onde termina
    int freeant;  // espaço disponivel antes
    int freedps;  // espaço disponivel depois
    struct lista *prox;
}lista;


int *iniciaHeap(int *v, int num){
    int i;
    v = (int *) malloc(sizeof(int)*num);
    for(i = 0; i < num; i++)
        v[i] = true;
    return v;
}


int verificaExiste(lista *l, char *na_wa){
    while(l != NULL){
        if(strcmp(l->nome, na_wa) == 0)
            return 1;
        else
            l = l->prox;
    }
    return 0;
}


lista *firstFit(lista *l, int *vet, int tam, int tamheap, char *na_wa){
    int i;
    lista *aux1, *aux2, *aux3;
    if(l == NULL){  // se a lista estiver vazia
        l = (lista *) malloc(sizeof(lista));
        strcpy(l->nome, na_wa);
        l->ini = 0;
        l->fim = tam - 1;
        l->freeant = 0;
        l->freedps = tamheap - tam;
        l->prox = NULL;
        for(i = 0; i < tam; i++)
            vet[i] = false;
    }
    else{
        if(l->prox == NULL){  // se ha somente um elemento
            if(l->freeant >= tam){
                aux1 = (lista *) malloc(sizeof(lista));
                strcpy(aux1->nome, na_wa);
                aux1->ini = 0;
                aux1->fim = tam - 1;
                aux1->freeant = 0;
                aux1->freedps = l->freeant - tam;
                l->freeant = aux1->freedps;
                aux1->prox = l;
                for(i = 0; i <= tam; i++)
                    vet[i] = false;
                return aux1;
            }
            else if(l->freedps >= tam){
                aux1 = (lista *) malloc(sizeof(lista));
                strcpy(aux1->nome, na_wa);
                aux1->ini = l->fim + 1;
                aux1->fim = l->fim + tam;
                aux1->freeant = 0;
                aux1->freedps = l->freedps - tam;
                aux1->prox = l->prox;
                l->freedps = 0;
                l->prox = aux1;
                for(i = aux1->ini; i <= aux1->fim; i++)
                    vet[i] = false;
                return l;
            }
            else
                printf("Nao ha espaçoes disponiveis\n");
        }
        else{
            aux1 = l;
            if(aux1->freeant >= tam){
                aux1 = (lista *) malloc(sizeof(lista));
                strcpy(aux1->nome, na_wa);
                aux1->ini = 0;
                aux1->fim = tam - 1;
                aux1->freeant = 0;
                aux1->freedps = l->freeant - tam;
                l->freeant = aux1->freedps;
                aux1->prox = l;
                for(i = 0; i <= tam; i++)
                    vet[i] = false;
                return aux1;
            }
            aux2 = l->prox;
            while(aux2 != NULL){
                if(aux2->freeant >= tam){
                    aux3 = (lista *) malloc(sizeof(lista));
                    strcpy(aux3->nome, na_wa);
                    aux3->ini = aux1->fim;
                    aux3->fim = aux3->ini + tam;
                    aux3->freeant = 0;
                    aux3->freedps = aux1->freedps - tam;
                    aux3->prox = aux1->prox;
                    aux1->freedps = 0;
                    aux1->prox = aux3;
                    aux2->freeant = aux3->freedps;
                    for(i = aux3->ini; i <= aux3->fim; i++)
                        vet[i] = false;
                    return l;
                }
                else if(aux2->freedps >= tam){
                    aux3 = (lista *) malloc(sizeof(lista));
                    strcpy(aux3->nome, na_wa);
                    aux3->ini = aux2->fim + 1;
                    aux3->fim = aux2->fim + tam;
                    aux3->freeant = 0;
                    aux3->freedps = aux2->freedps - tam;
                    aux2->freedps = 0;
                    aux3->prox = aux2->prox;
                    aux2->prox = aux3;
                    for(i = aux3->ini; i <= aux3->fim; i++)
                        vet[i] = false;
                    if(aux3->prox != NULL){
                        aux3 = aux3->prox;
                        aux3->freeant = aux3->freeant - tam;
                    }
                    return l;
                }
                else if(aux2->prox == NULL){
                    printf("Nao existem espacos disponiveis.\n");
                }
                aux1 = aux1->prox;
                aux2 = aux2->prox;
            }
        }
    }
    return l;
}


int encontraPior(int tam,  int *vet, int tamheap){  // se achar um espaço retorna a primeira posicao
    int i, pos = 0, posfin = 0, cont = 0, contm = 0;
    for(i = 0; i < tamheap; i++){
        if(vet[i] == true){
            cont++;
        }
        else{
            cont = 0;
            pos = i + 1;
        }
        if(cont > contm){
            contm = cont;
            posfin = pos;
        }
        if(contm == tam)
            return posfin;
    }
    if(contm >= tam)
        return posfin;
    else
        return -1;
}


lista *worstFit(lista *l, int *vet, int tam, int tamheap, char *na_wa){
    int veri, i;
    lista *aux, *aux1, *aux2;
    veri = encontraPior(tam, vet, tamheap);
    if(veri != -1){
        if(l == NULL){  // se a lista estiver vazia
            l = (lista *) malloc(sizeof(lista));
            strcpy(l->nome, na_wa);
            l->ini = 0;
            l->fim = tam - 1;
            l->freeant = 0;
            l->freedps = tamheap - tam;
            l->prox = NULL;
            for(i = 0; i < tam; i++)
                vet[i] = false;
        }
        else{
            aux = (lista *) malloc(sizeof(lista));
            strcpy(aux->nome, na_wa);
            aux->ini = veri;
            aux->fim = veri + tam - 1;
            if(l->ini > aux->ini){
                aux->freeant = 0;
                aux->freedps = l->freeant - tam;
                aux->prox = l;
                for(i = aux->ini; i < tam; i++)
                    vet[i] = false;
                return aux;
            }
            else{
                aux1 = l;
                aux2 = l->prox;
                if(aux2 != NULL){
                    if(aux2->prox == NULL){
                        aux1 = aux1->prox;
                        aux2 = NULL;
                    }
                    else{
                        while(aux2->ini  < aux->ini){
                            aux1 = aux1->prox;
                            aux2 = aux2->prox;
                        }
                    }
                }
                if(aux2 != NULL){
                    aux->freeant = 0;
                    aux->freedps = aux1->freedps - tam;
                    aux1->freedps = 0;
                    aux2->freeant = aux->freedps;
                    aux1->prox = aux;
                    aux->prox = aux2;
                }
                else{
                    aux->freeant = 0;
                    aux->freedps = aux1->freedps - tam;
                    aux1->freedps = 0;
                    aux1->prox = aux;
                    aux->prox = NULL;
                }
                for(i = aux->ini; i <= aux->fim; i++)
                    vet[i] = false;
            }
        }
    }
    else{
        printf("Nao ha espacos disponiveis.\n");
    }
    return l;
}


lista *deletar(lista *l, char *na_wa, int *vet){
    lista *aux, *aux1;
    int i;
    if(l == NULL){
        printf("Lista Vazia.\n");
    }
    else if(strcmp(l->nome, na_wa) == 0){  // é o primeiro elemento
        for(i = l->ini; i <= l->fim; i++)
            vet[i] = true;
        aux = l;
        if(l->prox != NULL){
            l = l->prox;
            l->freeant = l->freeant + (aux->fim - aux->ini + 1) ;
        }
        else{
            free(aux);
            return NULL;
        }
        free(aux);
    }
    else{
        aux1 = l;
        aux = l->prox;
        while(strcmp(aux->nome, na_wa) != 0){
            aux1 = aux1->prox;
            aux = aux->prox;
        }
        for(i = aux->ini; i <= aux->fim; i++)
            vet[i] = true;
        aux1->freedps = aux1->freedps + aux->freedps + (aux->fim - aux->ini + 1 );
        aux1->prox = aux->prox;
        if(aux1->prox != NULL){
            aux1 = aux1->prox;
            aux1->freeant = aux1->freeant + (aux->fim - aux->ini + 1 );
        }
        free(aux);
    }
    return l;
}


void espacos(lista *l){
    lista *aux;
    aux = l;
    if(aux->freeant > 0)
        printf("...");
        printf("%d", aux->ini);
    if(l != NULL){  // ver se a lista nao esta vazia
        while(aux != NULL){
            if(aux->freedps > 0){
                printf("%d", aux->fim);
                printf("...");
            }
            if(aux->prox == NULL && aux->freedps == 0){  // ultimo elemento
                printf("%d%d", aux->ini, aux->fim);
            }
            aux = aux->prox;
        }
    }
    else
        printf("Todos os espacos dispoiniveis.");
    printf("\n");
}


void liberaLista(lista *l){
    if(l != NULL){
        liberaLista(l->prox);
        free(l);
    }
}


void liberatudo(lista *l, int *vet){
    free(vet);
    liberaLista(l);
}


int main(){
    int *v, tamheap, tam, i;
    char command[20], name[7], *aux;
    lista *list = NULL, *auxlis;
    printf("Digite o tamanho do heap:");
    scanf("%d", &tamheap);
    system("cls");
    v = iniciaHeap(v, tamheap);
    while(strcmp(command, "exit") != 0){
        fflush(stdin);
        gets(command);
        aux = strtok(command, " ");
        if(strcmp(command, "new") == 0){  // new a 3
            aux = strtok(NULL, " ");  // a
            switch(verificaExiste(list, aux)){
                case 0:  // nao existe
                    strcpy(name, aux);  // name = a
                    aux = strtok(NULL, " ");  // 3
                    tam = atoi(aux);  // 3 vira int
                    list = firstFit(list, v, tam, tamheap, name);
                break;
                case 1:
                    printf("ERRO: elemento ja existente na lista.\n");
                    system("pause");
                break;
            }
        }
        if(strcmp(command, "worst") == 0){  // worst a 3
            aux = strtok(NULL, " ");  // a
            switch(verificaExiste(list, aux)){
                case 0:  // nao existe
                    strcpy(name, aux);  // name = a
                    aux = strtok(NULL, " ");  // 3
                    tam = atoi(aux);  // 3 vira int
                    list = worstFit(list, v, tam, tamheap, name);
                break;
                case 1:
                    printf("ERRO: elemento ja existente na lista.\n");
                    system("pause");
                break;
            }
        }
        else if(strcmp(command,"del") == 0){
            aux = strtok(NULL, " ");  // a
            switch(verificaExiste(list, aux)){
                case 0:
                    printf("O Elemento não existe na lista.\n");
                    system("pause");
                break;
                case 1:
                    list = deletar(list, aux, v);
                break;
            }
        }
        else if(strcmp(command,"show") == 0){
            for(i = 0; i < tamheap; i++){
                switch(v[i]){
                    case 0:
                        printf("%d false", i);
                    break;
                    case 1:
                        printf("%d true", i);
                    break;
                }
                printf("\n");
            }
        }
        else if(strcmp(command, "showlist") == 0){  // mostra a lista
            printf("\n");
            auxlis = list;
            while(auxlis != NULL){
                printf("nome:%s inicio:%d fim:%d qtdantes:%d qtddps:%d\n", auxlis->nome, auxlis->ini, auxlis->fim, auxlis->freeant, auxlis->freedps);
                auxlis = auxlis->prox;
            }
        }
        else if(strcmp(command,"space") == 0)  // limpa
            espacos(list);
        else if(strcmp(command,"clean") == 0)  // limpa
            system("cls");
    }
    liberatudo(list, v);
    return 0;
}
