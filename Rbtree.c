#include "Rbtree.h"
#include <stdlib.h>
#include <string.h>
#include "Calculos.h"

typedef struct forma{
    double x,y;
}forma;

typedef struct node{
    Item data;
    double x,y;
    char color;
    struct node *left, *right, *parent;
}node;

typedef struct head{
    int qtd;
    struct node *root;
    node *null;
}head;


/* DECLARACAO LOCAL PARA TIRAR IMPLICIDADE */
void inorder(Rbtree tree, struct node *root);
int counterTree(Rbtree tree, struct node *root);
struct node* deleteNode(Rbtree tree, struct node* root, int data);

/* UTILITY FUNCTIONS */
/* Compute the "height" of a tree -- the number of 
    nodes along the longest path from the root node 
    down to the farthest leaf node.*/
int height(Rbtree tree, struct node* node);
/* Get width of a given level */
int getWidth(Rbtree tree, struct node* root, int level);

/* Function to get the maximum width of a binary tree*/
int getMaxWidth(Rbtree tree);
int getMaxHeight(Rbtree tree);
// struct node* deleteNode(struct node* root, int data);
/* FIM DECLARACAO LOCAL */


/* FUNCOES AUXILIARES */
Rbtree createTree(){
    head *newHead;
    node *root;
    newHead = (head*)malloc(sizeof(head));
    newHead->null = (node*)malloc(sizeof(node));
    (newHead->null)->color = 'B';
    (newHead->null)->data = NULL;
    (newHead->null)->left = newHead->null;
    (newHead->null)->right = newHead->null;
    (newHead->null)->parent = newHead->null;
    (newHead->null)->x = 0;
    (newHead->null)->y = 0;
    newHead->qtd = 0;
    newHead->root = newHead->null;
    return newHead;
}
Forma createForma(double x, double y){
    forma *newForma;
    newForma = (forma*)malloc(sizeof(forma));
    newForma->x = x;
    newForma->y = y;
    return newForma;
}

PosicTree getRoot(Rbtree tree){
    head *newHead = (head*)tree;
    return newHead->root;
}

PosicTree getRbtreeNull(Rbtree tree){
    head *newHead = (head*)tree;
    return newHead->null;
}

PosicTree getRbtreeLeft(Rbtree tree, PosicTree p){
    head *newHead = (head*)tree;
    node *no = (node*)p;
    return (PosicTree)no->left;
}

PosicTree getRbtreeRight(Rbtree tree, PosicTree p){
    head *newHead = (head*)tree;
    node *no = (node*)p;
    return (PosicTree)no->right;
}

PosicTree getRbtreeParent(Rbtree tree, PosicTree p){
    head *newHead = (head*)tree;
    node *no = (node*)p;
    return (PosicTree)no->parent;    
}
void LeftRotate(Rbtree tree, struct node *x){
    head *newHead = (head*)tree;
    struct node *y = x->right;
    x->right = y->left;
    if (y->left != newHead->null){
        y->left->parent = x;
    }
    if (y != newHead->null){
        y->parent = x->parent;
    }
    if (x->parent == newHead->null){
        newHead->root = y;
    } else if(x == (x->parent)->left){
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;

    if (x != newHead->null){
        x->parent = y;
    }

    // if (x != newHead->null || x->right != newHead->null)
    //     return ;
    // //y ponteiro armazenado do filho certo de x
    // struct node *y = x->right;

    // //armazena o ponteiro esquerdo da subárvore esquerda como filho direito de x
    // x->right = y->left;

    // //atualizar o ponteiro pai da direita de x
    // if (x->right != newHead->null)
    //     x->right->parent = x;

    // //atualizar o ponteiro pai de y
    // y->parent = x->parent;

    // // se o pai de x for nulo, faça y como raiz da árvore
    // if (x->parent == newHead->null)
    //     (newHead->root) = y;

    // // armazene y no local de x
    // else if (x == x->parent->left)
    //     x->parent->left = y;
    // else    x->parent->right = y;

    // // faça x como filho esquerdo de y
    // y->left = x;

    // //atualizar ponteiro pai de x
    // x->parent = y;
}
void rightRotate(Rbtree tree, struct node *x){
    head *newHead = (head*)tree;
    
    struct node *y = x->left;
    x->left = y->right;
    if (y->right != newHead->null){
        (y->right)->parent = x;
    }

    if (y != newHead->null){
        y->parent = x->parent;
    }

    if (x->parent == newHead->null){
        newHead->root = y;
    } else if (x == (x->parent)->right){
        (x->parent)->right = y;
    } else {
        (x->parent)->left = y;
    }
    y->right = x;
    if (x != newHead->null){
        x->parent = y;
    }

    // if (y != newHead->null || y->left != newHead->null)
    //     return ;
    // if (y != newHead->null || y->left != newHead->null)
    //     return;
    // struct node *x = y->left;
    // y->left = x->right;
    // if (x->right != newHead->null)
    //     x->right->parent = y;
    // x->parent =y->parent;
    // if (x->parent == newHead->null)
    //     (newHead->root) = x;
    // else if (y == y->parent->left)
    //     y->parent->left = x;
    // else y->parent->right = x;
    // x->right = y;
    // y->parent = x;
}
void insertFixUp(Rbtree tree, struct node *z){
    struct node *y, *x;
    head *newHead = (head*)tree;
    while((z->parent)->color == 'R'){
        if (z->parent == ((z->parent)->parent)->left){
            y = ((z->parent)->parent)->right;
            if (y->color == 'R'){
                (z->parent)->color = 'B';
                y->color = 'B';
                ((z->parent)->parent)->color = 'R';
                z = (z->parent)->parent;
            } else {
                if (z == (z->parent)->right){
                    z = z->parent;
                    LeftRotate(tree, z);
                }
                (z->parent)->color = 'B';
                ((z->parent)->parent)->color = 'R';
                rightRotate(tree, (z->parent)->parent);
            }
        } else {
            y = ((z->parent)->parent)->left;
            if (y->color == 'R'){
                (z->parent)->color = 'B';
                y->color = 'B';
                ((z->parent)->parent)->color = 'R';
                z = (z->parent)->parent;
            } else {
                if (z == (z->parent)->left){
                    z = z->parent;
                    rightRotate(tree, z);
                }
                (z->parent)->color = 'B';
                ((z->parent)->parent)->color = 'R';
                LeftRotate(tree, (z->parent)->parent);
            }
        }
        if (z == newHead->root)
            break;
        
    }
    (newHead->root)->color = 'B';
    
    // struct node **root = &(newHead->root);
    // // itere até z não ser a raiz e a cor pai de z ser vermelha
    // while (z != *root && z != (*root)->left && z != (*root)->right && z->parent->color == 'R'){
    //     struct node *y;

    //     // Encontre o tio e guarde o tio em y
    //     if (z->parent && z->parent->parent && z->parent == z->parent->parent->left)
    //         y = z->parent->parent->right;
    //     else
    //         y = z->parent->parent->left;

    //     // Se o tio for VERMELHO, faça o seguinte
    //     // (i) Mude a cor do pai e do tio como PRETO
    //     // (ii) Alterar a cor dos avós como VERMELHO
    //     // (iii) Mover z para avô
    //     if (!y)
    //         z = z->parent->parent;
    //     else if (y->color == 'R'){
    //         y->color = 'B';
    //         z->parent->color = 'B';
    //         z->parent->parent->color = 'R';
    //         z = z->parent->parent;
    //     }

    //     // Tio é preto, existem quatro casos (LL, LR, RL and RR)
    //     else{
    //         // Caso Esquerda-Esquerda (LL), faça o seguinte
    //         // (i) Troque a cor dos pais e avós
    //         // (ii) Girar à direita avô
    //         if (z->parent == z->parent->parent->left &&
    //             z == z->parent->left){

    //             char ch = z->parent->color ;
    //             z->parent->color = z->parent->parent->color;
    //             z->parent->parent->color = ch;
    //             rightRotate(tree, root,z->parent->parent);
    //         }

    //         // Caso Esquerda-Direita (LR), faça o seguinte
    //         // (i) Troque a cor do nó atual e dos avós
    //         // (ii) Girar pai à esquerda
    //         // (iii) Girar à direita Grand Parent
    //         if (z->parent && z->parent->parent && z->parent == z->parent->parent->left &&
    //             z == z->parent->right){

    //             char ch = z->color ;
    //             z->color = z->parent->parent->color;
    //             z->parent->parent->color = ch;
    //             LeftRotate(tree, z->parent);
    //             rightRotate(tree, z->parent->parent);
    //         }

    //         // Caso Direito-Direito (RR), faça o seguinte
    //         // (i) Troque a cor dos pais e avós
    //         // (ii) Girar à esquerda avô
    //         if (z->parent && z->parent->parent &&
    //             z->parent == z->parent->parent->right &&
    //             z == z->parent->right){

    //             char ch = z->parent->color ;
    //             z->parent->color = z->parent->parent->color;
    //             z->parent->parent->color = ch;
    //             LeftRotate(tree, root,z->parent->parent);
    //         }

    //         // Caso Direita-Esquerda (RL), faça o seguinte
    //         // (i) Troque a cor do nó atual e dos avós
    //         // (ii) Girar pai à direita
    //         // (iii) Girar à esquerda Grand Parent
    //         if (z->parent && z->parent->parent && z->parent == z->parent->parent->right &&
    //             z == z->parent->left){
                
    //             char ch = z->color ;
    //             z->color = z->parent->parent->color;
    //             z->parent->parent->color = ch;
    //             rightRotate(tree, root,z->parent);
    //             LeftRotate(tree, root,z->parent->parent);
    //         }
    //  }
    // }
    // (*root)->color = 'B'; // mantém a raiz sempre preta
}

struct node * minValueNode(Rbtree tree, struct node *node){
    head *newHead = (head*)tree;
    struct node* current = node; 
  
    // vai rodando pra esquerda até achar o menor valor (filho) 
    while (current && current->left != newHead->null) 
        current = current->left; 
  
    return current; 
}
int getMaxWidth(Rbtree tree){ 
  int maxWidth = 0;    
  int width; 
  struct node *root = ((head *)tree)->root;
  int h = height(tree, root); 
  int i; 
    
  /* Pega a largura de cada nivel, e compara para pegar o maior */
  for(i=1; i<=h; i++){ 
    width = getWidth(tree, root, i); 
    if(width > maxWidth) 
      maxWidth = width; 
  }
    
  return maxWidth; 
}  
int getWidth(Rbtree tree, struct node* root, int level){
    head *newHead = (head*)tree;
  if(root == newHead->null) 
    return 0; 
    
  if(level == 1) 
    return 1; 
              
  else if (level > 1) 
    return getWidth(tree, root->left, level-1) +  
             getWidth(tree, root->right, level-1); 
}
int getMaxHeight(Rbtree tree){
    struct node *root = ((head *)tree)->root;
    return height(tree, root);
}
int height(Rbtree tree, struct node* node){ 
    head *newHead = (head*)tree;
   if (node==newHead->null) 
     return 0; 
   else{ 
     int lHeight = height(tree, node->left); 
     int rHeight = height(tree, node->right);   
     return (lHeight > rHeight)? (lHeight+1): (rHeight+1); 
   } 
}
Item getObjRbtree(Rbtree tree, PosicTree p){
    return ((node*)p)->data;
}
/* FIM FUNCOES AUXILIARES */


/* INSERE ELEMENTO */
void insertRbtree(Rbtree tree, Item data, RbtreeCompare comp){
    // Alocar memória para novo nó
    struct node *z = (struct node*)malloc(sizeof(struct node)), *x, *y;
    z->data = data;
    // z->x = x;
    // z->y = y;
    struct head *cabeca = (struct head *)tree;
    z->left = z->right = z->parent = cabeca->null;
    y = cabeca->null;
    x = cabeca->root;
    while(x != cabeca->null){
        y = x;
        if (comp(z->data, x->data) < 0){
            x = x->left;
            // printf("left\n");
        } else {
            x = x->right;
            // printf("right\n");
        }
    }
    z->parent = y;
    if (y == cabeca->null){
        cabeca->root = z;
    } else {
        if (comp(z->data, y->data) < 0){
            // printf("left TT\n");
            y->left = z;
        } else {
            y->right = z;
            // printf("right TT\n");
        }
    }
    if (z->parent == cabeca->null){
        z->color = 'B';
    }
    // if ((z->parent)->parent == cabeca->null){
    //     printf("achei\n");
    //     return;
    // }

    z->left = cabeca->null;
    z->right = cabeca->null;
    z->color = 'R';
    insertFixUp(tree, z);
    (cabeca->qtd)++;
    // ' //se root for nulo, faça z como root
    // (cabeca->qtd)++;
    // if (root == cabeca->null){
    //     z->color = 'B';
    //     cabeca->root = z;

    // }
    // else{
    //     struct node *y = cabeca->null;
    //     struct node *x = root;

    //     // Siga as etapas de inserção padrão do BST para inserir primeiro o nó
    //     while (x != cabeca->null){
    //         y = x;
    //         if (z->x < x->x)
    //             x = x->left;
    //         else if (z->x > x->x)
    //             x = x->right;
    //         else{
    //             if(z->y < x->y)
    //                 x = x->left;
    //             else
    //                 x = x->right;
    //         }
            
    //     }
    //     z->parent = y;

    //     if(y->x < z->x)
    //         y->right = z;
    //     else if(y->x > z->x)
    //         y->left = z;
    //     else{
    //         if(y->y < z->y)
    //             y->right = z;
    //         else
    //             y->left = z;
    //     }
    //     z->color = 'R';

    //}
    //     // chame insert FixUp para corrigir a propriedade da árvore vermelho-preta se
    //     // for violada devido à inserção.
}

/* FIM INSERE ELEMENTO */


/* DELETA ELEMENTO */

void removeRbtree(Rbtree tree, PosicTree pObj){
    struct node *x, *y, *w, *ppObj;
    ppObj = (node*)pObj;
    head *cabeca = (head*)tree;
    int x_esquerda;
    if (ppObj == cabeca->null)
        return;
    if (ppObj->left == cabeca->null && ppObj->right == cabeca->null) {

        y = cabeca->null;
        x = cabeca->null;
        x->parent = ppObj->parent;
        if (ppObj->parent != cabeca->null && ppObj->parent->left == ppObj)
            x_esquerda = 1;
        else
            x_esquerda = 0;
        
    } else if (ppObj->left == cabeca->null && ppObj->right != cabeca->null) {

        y = ppObj->right;
        x = ppObj->right;
        x->parent = ppObj->parent;
        x_esquerda = 0;
    } else if (ppObj->left != cabeca->null && ppObj->right == cabeca->null) {
        y = ppObj->left;
        x = ppObj->left;
        x->parent = ppObj->parent;
        x_esquerda = 1;
    } else {
        y = ppObj->right;
        while (y->left != cabeca->null)
            y = y->left;
        x = y->right;
        if (y != ppObj->right) {
            y->left = ppObj->left;
            y->right = ppObj->right;
            y->left->parent = y;
            y->right->parent = y;
            x->parent = y->parent;
            x->parent->left = x;
            x_esquerda = 1;
        } else {
            x->parent = y;
            y->left = ppObj->left;
            ppObj->left->parent = y;
            x_esquerda = 0;
        }
    }

    if (ppObj->parent != cabeca->null) {
        if (ppObj->parent->left == ppObj)
            ppObj->parent->left = y;
        else
            ppObj->parent->right = y;
    } else {
        (cabeca->root) = y;
    }

    if (y != cabeca->null) {
        y->parent = ppObj->parent;
    }

	
    if (ppObj->color == 'R' && (y->color == 'R' || y == cabeca->null))
        return;
    else if (ppObj->color == 'R' && y->color == 'B') {
        y->color = 'R';
    } else if (ppObj->color == 'B' && y->color == 'R') {
        y->color = 'B';
        return;
    }

    while (x != (cabeca->root)) {
        if (x_esquerda)
            w = x->parent->right;
        else
            w = x->parent->left;
        
        if (x->color == 'R') {
            x->color = 'B';
            return;
        } else {
            if (w->color == 'R') {
                w->color = 'B';
                x->parent->color = 'R';
                if (x_esquerda) {
                    LeftRotate(cabeca->root, x->parent);
                    w = x->parent->right;
                } else {
                    rightRotate(cabeca->root, x->parent);
                    w = x->parent->left;
                }
            }
			
            if (w->color == 'B') {
                if (w->left->color == 'B' && w->right->color == 'B') {
                    w->color = 'R';
                    x = x->parent;
                    x_esquerda = x->parent == cabeca->null ? 0 : x == x->parent->left;
                    if (x->color == 'R') {
                        x->color = 'B';
                        return;
                    }
                    continue;
                } else if (x_esquerda && w->left->color == 'R' && w->right->color == 'B'
                        || !x_esquerda && w->right->color == 'R' && w->left->color == 'B') {
                    w->color = 'R';
                    if (x_esquerda) {
                        w->left->color = 'B';
                        rightRotate(cabeca->root, w);
                        w = x->parent->right;
                    } else {
                        w->right->color = 'B';
                        LeftRotate(cabeca->root, w);
                        w = x->parent->left;
                    }
                }
                w->color = x->parent->color;
                x->parent->color = 'B';
                if (x->parent->left == x) {
                    w->right->color = 'B';
                    LeftRotate(cabeca->root, x->parent);
                } else {
                    w->left->color = 'B';
                    rightRotate(cabeca->root, x->parent);
                }
                return;
            }
        }
    }
    
   
}


// void delete(Rbtree tree, int data){
//     head *root = (head*)tree;
//     deleteNode(tree, root->root, data);
// }
// struct node* deleteNode(Rbtree tree, struct node* root, int data) {
//     head *newHead = (head*)tree;
//     // caso base 
//     if (root == newHead->null)
//         return root;
//     // nó com apenas um filho ou nenhum filho
//     if (root->left == newHead->null){
//         struct node *temp = root->right; 
//         free(root); 
//         return temp; 
//     } 
//     else if (root->right == newHead->null) { 
//         struct node *temp = root->left; 
//         free(root); 
//         return temp; 
//     }
//     // nó com dois filhos: obtenha o sucessor inorder (menor
//     // na subárvore direita)
//     struct node* temp = minValueNode(tree, root->right); 

//     // Copie o conteúdo do sucessor da ordem de entrada para este nó
//     root->data = temp->data; 

//     // Excluir o sucessor da ordem de entrada
//     root->right = deleteNode(tree, temp,data); 
//     return root; 
// }

// void freeTree(struct node *root) {
//     if (root == NULL)
//         return;
//     freeTree(root->left);
//     deleteNode(root,root->data);

//     freeTree(root->right);
// }
/* FIM DELETA ELEMENTO */


/* IMPRESSAO DA ARVORE*/
void printTree(Rbtree tree){
    head *root = (head *)tree;
    inorder(tree, root->root);
}
void inorder(Rbtree tree, struct node *root) {
    head *newHead = (head *)tree;
    if (root == newHead->null){
        // printf("arvore vazia\n");
        return;
    }
    inorder(tree, root->left);
    printf("%.2lf cor %C\n", ((forma *)root->data)->x,root->color);
    inorder(tree, root->right);
    printf("%.2lf cor %C\n", ((forma *)root->data)->x,root->color);
}
/* FIM DA IMPRESSAO DA ARVORE*/


/* CONTADOR DE ELEMENTOS*/
// int qtdRbtree(Rbtree tree){
//     head *newHead = (head *)tree;
//     return newHead->qtd;
// }

int posicTreeVazio(Rbtree tree, PosicTree p){
    head *cabeca = (head*)tree;
    node *no = (node*)p;
    if (no == cabeca->null)
        return 1;
    else 
        return 0;
}

PosicTree getNullTree(Rbtree tree){
    head *cabeca = (head*)tree;
    return cabeca->null;
}

int qtdRbtree(Rbtree tree){
    head *root = (head *)tree;
    return counterTree(tree, root->root);
}
int counterTree(Rbtree tree, struct node *root) {
    head *newHead = (head *)tree;
    if(root == newHead->null)      
        return 0;  
    if(root->left == newHead->null && root->right == newHead->null)  
        return 1;
    else
        return 1 + counterTree(tree, root->left) + counterTree(tree, root->right);  
}

void freeTree(Rbtree tree){
    head *cabeca = (head*)tree;
    if (cabeca->null != NULL)
        free(cabeca->null);
    if (cabeca != NULL)
        free(cabeca);
}
/* FIM CONTADOR ELEMENTOS*/


double funcAbs(double value){
	
	if (value < 0.0)
		return value*(-1);
	return value;
}

/*comparação de numeros de ponto flutuante*/

int doubleEquals(double a, double b){
	double dif = a - b;
	// printf("dif : %f\n", dif);
	dif = funcAbs(dif);
	if (dif < 0.00001)
		return 1;
	return 0;
	
}

int cmpData(Item x, Item y){
    forma *a = (forma*)x;
    forma *b = (forma*)y;
    // printf("a %f b %f\n", a->x, b->x);
    if (doubleEquals(a->x, b->x)){
        if (a->y >= b->y){
            return 1;
        } else {
            return -1;
        }
    } else if (a->x > b->x){
        return 1;
    } else {
        return -1;
    }
    
}

int cp(Rbtree tree, PosicTree at, int a){
    head *newHead = (head*)tree;
    node *no = (node*)at;    
    if (posicTreeVazio(tree, at))
        return a+0;
    a = cp(tree, getRbtreeLeft(tree, at), a);
    a = cp(tree, getRbtreeRight(tree, at), a);

    return a+1;
}

int countt(Rbtree tree){
    head *newHead = (head*)tree;
    int c = cp(tree, newHead->root, 0);
    return c;
}

void printNodeSvg(FILE *svg, Rbtree tree, PosicTree root, int width, int height, double x_ant, double y_ant, int *es){
    head *newHead = (head*)tree;
    node *no = (node*)root;
    char cor[20];
    int lar = 15;
    if (posicTreeVazio(tree, root))
        return;
    if (*es){
        printNodeSvg(svg, tree, getRbtreeLeft(tree, root), width -1, height + 40, width*(lar+0.1), height*(1.1), es);
    } else {
        if (no == newHead->root)
            printNodeSvg(svg, tree, getRbtreeLeft(tree, root), width - 1, height + 40, width*(lar+0.1), height*(1.1), es);
        else
            printNodeSvg(svg, tree, getRbtreeLeft(tree, root), width, height + 40, width*(lar+0.1), height*(1.1), es);
    }
    if (no == newHead->root)
        *es = 0;
    if (*es){
        if (no == newHead->root)
            printNodeSvg(svg, tree, getRbtreeRight(tree, root), width + 1, height + 40, width*(lar+0.1), height*(1.1), es);
        else
            printNodeSvg(svg, tree, getRbtreeRight(tree, root), width, height + 40, width*(lar+0.1), height*(1.1), es);
    } else {
        printNodeSvg(svg, tree, getRbtreeRight(tree, root), width + 1, height + 40, width*(lar+0.1), height*(1.1), es);
    }
    if(no->color == 'R')
        strcpy(cor, "red");
    else
        strcpy(cor, "black");
    printf("%d\n", lar);
    fprintf(svg, "<circle cx = \"%f\" cy = \"%f\" r = \"5\" fill = \"%s\" stroke=\"%s\" stroke-width=\"1\" fill-opacity = \"1\"/>\n", width*(lar+0.1), height*(1.1), cor, cor);
    fprintf(svg, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke-width=\"4\" stroke=\"darkgreen\" />\n", width*(lar+0.1), height*(1.1), x_ant, y_ant);
    if (no == newHead->root){
        fprintf(svg, "<text x=\"%f\" y=\"%f\" font-family= \"Verdana\"  font-size=\"40\">root</text>\n", width*(lar+0.1) + 10, height*(1.1));
        printf("aki\n");
        *es = 0;
    }
}

void printTreeSvg(FILE *svg, Rbtree tree){
    head *newHead = (head*)tree;
    node *atual = (node*)newHead->root;
    int width = getMaxWidth(tree), height = getMaxHeight(tree), es = 1;
    
    printNodeSvg(svg, tree, getRoot(tree), width/2 + 1, 30, (width/2 + 1)*(10), 30*(1.1), &es);
}

void deletaTudo(Rbtree tree, PosicTree root, int *count){
    head *newHead = (head*)tree;
    node *atual = (node*)root;
    if (posicTreeVazio(tree, root))
        return;
    deletaTudo(tree, atual->left, count);
    deletaTudo(tree, atual->right, count);
    removeRbtree(tree, atual);
    (*count)++;
    printf("%d\n", *count);
}

int main() {
    int i, count = 0;
    Rbtree head = createTree();
    Forma coisa;
    PosicTree p1;
    FILE *arq;
    for (i=0; i<200; ++i){
        // printf("1\n");
        coisa = createForma(random()/100000000.123,random()/100000000.43412);
		insertRbtree(head,coisa, cmpData);
        // printf("3\n");
    }
    // printf("sss %d\n", countt(head));
    // getchar();
    arq = fopen("./testes/saida/c1/arv.svg", "w");
    if (arq == NULL){
        printf("se...\n");
        return 0;
    }
        
    fprintf(arq, "<svg>\n");    
    printTreeSvg(arq, head);
    fprintf(arq, "</svg>\n");    
    // getchar();
    fclose(arq);
    // getchar();
    // printf("antes\n");
    // deletaTudo(head, getRoot(head), &count);
    // deletaTudo(head, getRoot(head));
    // printf("depois\n");
    // getchar();

    // for (i=0; i<5; ++i){
    //     coisa = createForma(random()/100000000.123,random()/100000000.43412);
        
    // }
    
    // printTree(head);
    // printf("\n");

    // printf("Quantidade de elementos: %d\n",qtdRbtree(head));
    // printf("Maxima largura: %d \n", getMaxWidth(head));
    // printf("Maxima altura: %d \n", getMaxHeight(head));
    
    // freeTree(getRoot(head));
    

    free(head);
    return 0;
}
