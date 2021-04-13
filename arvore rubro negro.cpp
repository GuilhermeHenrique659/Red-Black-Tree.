#include<bits/stdc++.h>
#define RED 1
#define BLACK 0

typedef struct No *apontador;
struct No
{
    int chave;
    int cor;
    apontador esq;
    apontador dir;
    apontador pai;
} No;

apontador raiz = NULL;
apontador nodonull = NULL;



apontador cria_nodo(int k, apontador esq, apontador dir, apontador pai)
{
    apontador p;
    p = (struct No*)malloc(sizeof(*p));
    p->chave = k;
    p->esq = esq;
    p->dir = dir;
    p->pai = pai;
    return p;
}

void inicializa(void)
{
    nodonull = cria_nodo(0, NULL, NULL, NULL);
    nodonull->cor = BLACK;
    raiz = nodonull;
}

apontador left_rotate(apontador r, apontador p)
{
    apontador y = p->dir;
    p->dir = y->esq;
    if (y->esq != nodonull)
        y->esq->pai = p;
    y->pai = p->pai;
    if (p->pai == nodonull)
        r = y;
    else if (p == p->pai->esq)
        p->pai->esq = y;
    else
        p->pai->dir = y;
    y->esq = p;
    p->pai = y;
    return r;
}

apontador right_rotate(apontador r, apontador p)
{
    apontador y = p->esq;
    p->esq = y->dir;
    if (y->dir != nodonull)
        y->dir->pai = p;
    y->pai = p->pai;
    if (p->pai == nodonull)
        r = y;
    else if (p == p->pai->esq)
        p->pai->esq = y;
    else
        p->pai->dir = y;
    y->dir = p;
    p->pai = y;
    return r;
}

apontador RB_insert_fixup(apontador r, apontador p)
{
    apontador y;
    while (p->pai->cor == RED )
    {
        if (p->pai == p->pai->pai->esq)
        {
            y = p->pai->pai->dir;
            if (y->cor == RED)
            {
                p->pai->cor = BLACK;
                y->cor = BLACK;
                p->pai->pai->cor = RED;
                p = p->pai->pai;
            }
            else
            {
                if (p == p->pai->dir)
                {
                    p = p->pai;
                    r = left_rotate(r, p);
                }
                else
                {
                    p->pai->cor = BLACK;
                    p->pai->pai->cor = RED;
                    r = right_rotate(r, p->pai->pai );
                }
            }
        }
        else
        {
            y = p->pai->pai->esq;
            if (y->cor == RED)
            {
                p->pai->cor = BLACK;
                y->cor = BLACK;
                p->pai->pai->cor = RED;
                p = p->pai->pai;
            }
            else
            {
                if (p == p->pai->esq)
                {
                    p = p->pai;
                    r = right_rotate(r, p);
                }
                else
                {
                    p->pai->cor = BLACK;
                    p->pai->pai->cor = RED;
                    r = left_rotate(r, p->pai->pai);
                }
            }
        }
    }
    r->cor = BLACK;
    return r;
}

apontador insere(apontador t, int k)
{
    apontador novo = cria_nodo(k, nodonull, nodonull, nodonull);

    apontador x = t;
    apontador paix = nodonull;
    while (x != nodonull)
    {
        paix = x;
        if (k < x->chave)
            x = x->esq;
        else
            x = x->dir;
    }
    novo->pai = paix;
    if (paix == nodonull)
        t = novo;
    else if (k < paix->chave)
        paix->esq = novo;
    else
        paix->dir = novo;
    novo->cor = RED;
    t =  RB_insert_fixup(t, novo);
    return t;
}

apontador busca(apontador p, int k)
{
    if (p == nodonull)
        return nodonull;
    if (p->chave == k)
        return p;
    else if (k < p->chave)
        return busca (p->esq, k);
    else
        return busca (p->dir, k);
}

apontador RB_transplant(apontador t, apontador u, apontador v)
{
    if(u->pai==nodonull)
        t = v;
    else if (u==u->pai->esq)
        u->pai->esq = v;
    else u->pai->dir = v;
    v->pai = u->pai;
    return t;
}

apontador tree_minimun(apontador x)
{
    while(x->esq!=nodonull)
        x = x->esq;
    return x;
}

apontador RB_Remove_fix(apontador T, apontador x)
{
    apontador w;
    while (x != T && x->cor == BLACK)
    {
        if (x == x->pai->esq)
        {
            w = x->pai->dir;
            if (w->cor == RED)
            {
                w->cor = BLACK;
                x->pai->cor = RED;
                T = left_rotate (T, x->pai);
                w = x->pai->dir;
            }
            if (w->esq->cor == BLACK && w->dir->cor == BLACK)
            {
                w->cor = RED;
                x = x->pai;
            }
            else if (w->dir->cor == BLACK)
            {
                w->esq->cor = BLACK;
                w->cor = RED;
                T = right_rotate (T, w);
                w = x->pai->dir;
            }
            w->cor = x->pai->cor;
            x->pai->cor = BLACK;
            w->dir->cor = BLACK;
            T = left_rotate (T, x->pai);
            x = T;
        }
        else
        {
            w = x->pai->esq;
            if (w->cor == RED)
            {
                w->cor = BLACK;
                x->pai->cor = RED;
                T = right_rotate (T, x->pai);
                w = x->pai->esq;
            }
            if (w->dir->cor == BLACK && w->esq->cor == BLACK)
            {
                w->cor = RED;
                x = x->pai;
            }
            else if (w->esq->cor == BLACK)
            {
                w->dir->cor = BLACK;
                w->cor = RED;
                T = left_rotate (T, w);
                w = x->pai->esq;
            }
            w->cor = x->pai->cor;
            x->pai->cor = BLACK;
            w->esq->cor = BLACK;
            T = right_rotate (T, x->pai);
            x = T;
        }
    }
    x->cor = BLACK;
    return T;
}

apontador remover(apontador t,apontador z)
{
    apontador y;
    apontador x;
    y = z;
    int y_cor_origin = y->cor;
    if(z->esq == nodonull)
    {
        x = z->dir;
        t = RB_transplant(t,z,z->dir);
    }
    else if(z->dir == nodonull)
    {
        x = z->esq;
        t = RB_transplant(t, z, z->esq);
    }
    else
    {
        y = tree_minimun(z->dir);
        y_cor_origin = y->cor;
        x = y->dir;
        if(y->pai == z)
            x->pai = y;
        else
        {
            t = RB_transplant(t, y, y->dir);
            y->dir = z->dir;
            y->dir->pai = y;
        }
        t = RB_transplant(t,z,y);
        y->esq = z->esq;
        y->esq->pai = y;
        y->cor = z->cor;
    }
    if(y_cor_origin == BLACK)
        t=RB_Remove_fix(t, x);
    return t;
}


void preOrder(apontador p, int h)
{
    if (p == nodonull)
        return;
    else if( p != nodonull)
    {
        if (p->cor == BLACK)
            printf("Chave: %d | Cor: BLACK | H(%d) | Filho de %d \n", p->chave, h, p->pai->chave);
        else
            printf("Chave: %d | Cor: RED   | H(%d) | Filho de %d \n", p->chave, h, p->pai->chave);
        preOrder(p->esq, h+1);
        preOrder(p->dir, h+1);
    }
}
void inOrder(apontador p, int h)
{
    if( p == nodonull)
        return;
    else
    {
        inOrder(p->esq, h+1);
        if (p->cor == BLACK)
            printf("Chave: %d | Cor: BLACK | H(%d) | Filho de %d \n", p->chave, h, p->pai->chave);
        else
            printf("Chave: %d | Cor: RED   | H(%d) | Filho de %d \n", p->chave, h, p->pai->chave);
        inOrder(p->dir, h+1);
    }
}
void posOrdem(apontador p, int h)
{
    if( p == nodonull)
        return;
    else if(p != nodonull)
    {
        posOrdem(p->esq, h+1);
        posOrdem(p->dir, h+1);
        if (p->cor == BLACK)
            printf("Chave: %d | Cor: BLACK | H(%d) | Filho de %d \n", p->chave, h, p->pai->chave);
        else
            printf("Chave: %d | Cor: RED   | H(%d) | Filho de %d \n", p->chave, h, p->pai->chave);
    }
}

void libere(apontador p)
{
    if(p==nodonull)
        return;
    libere(p->esq);
    libere(p->dir);
    free(p);
}
int main()
{
    apontador aux;
    int op, chave, show_op;
    inicializa();
    while(1)
    {
        printf("1-inserir\n2-remover\n3-mostrar\n4-sair\n");
        scanf("%d", &op);
        if(op==1)
        {
            scanf("%d", &chave);
            raiz = insere(raiz, chave);
            printf("chave inserida\n");
            system("cls");
        }
        else if(op==2)
        {
            scanf("%d", &chave);
            aux = busca(raiz, chave);
            raiz = remover(raiz, aux);
            if(aux != nodonull)
                printf("a chave foi removida\n");
            else
                printf("esta chave nao existe\n");
            system("cls");
        }
        else if(op==3)
        {
            printf("1-preOrder\n2-inOrder\n3-posOrder\n4-limpar\n");
            scanf("%d", &show_op);
            if(show_op == 1)
                preOrder(raiz,0);
            else if(show_op == 2)
                inOrder(raiz,0);
            else if(show_op == 3)
                posOrdem(raiz, 0);
            else if(show_op == 4)
                system("cls");
        }
        else if(op==4)
            break;
    }
    libere(raiz);
    libere(nodonull);
    return 0;
}
