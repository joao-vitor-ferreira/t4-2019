#include "Rbtree.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
void leftRotate(Rbtree tree, struct node *x){
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
}
void rightRotate(Rbtree tree, struct node *x){
    head *newHead = (head*)tree;
    
    struct node *y = x->left;
    x->left = y->right;
    if (y->right != newHead->null){
        y->right->parent = x;
    }

    if (y != newHead->null){
        y->parent = x->parent;
    }

    if (x->parent == newHead->null){
        newHead->root = y;
    } else if (x == (x->parent)->right){
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    if (x != newHead->null){
        x->parent = y;
    }
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
                    leftRotate(tree, z);
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
                leftRotate(tree, (z->parent)->parent);
            }
        }
        // if (z == newHead->root)
        //     break;
        
    }
    (newHead->root)->color = 'B';
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

    z->left = cabeca->null;
    z->right = cabeca->null;
    z->color = 'R';
    insertFixUp(tree, z);
    (cabeca->qtd)++;
    //     // chame insert FixUp para corrigir a propriedade da árvore vermelho-preta se
    //     // for violada devido à inserção.
}

/* FIM INSERE ELEMENTO */


/* DELETA ELEMENTO */

void rbtreeTransplant(Rbtree tree, PosicTree a, PosicTree b){
    head *newHead = (head*)tree;
    node *u = (node*)a, *v = (node*)b;
    if (u->parent == newHead->null)
        newHead->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

PosicTree getRbtreeMinValue(Rbtree tree, PosicTree pNo){
    head *newHead = (head*)tree;
    node *no = (node*)pNo;
    if (no->left == newHead->null)
        return no;
    getRbtreeMinValue(tree, no->left);
}

int getQtdRbtree(Rbtree tree){
    head *newHead = (head*)tree;
    return newHead->qtd;
}

void deleteFixUp(Rbtree tree, PosicTree p){
    head *newHead = (head*)tree;
    node *x = (node*)p, *w;
    
    while (x != newHead->null && x->color == 'B'){
        if (x == x->parent->left)
            w = x->parent->right;
        else
            w = x->parent->left;
        if (w->color == 'R'){
            w->color = 'B';
            x->parent->color = 'R';
            leftRotate(tree, x->parent);
            w = x->parent->right;
        }
        if (w->left->color == 'B' && w->right->color == 'B'){
            w->color = 'R';
            x = x->parent;
        } else if (w->right->color == 'B'){
            w->left->color = 'B';
            w->color = 'R';
            rightRotate(tree, w);
            w = x->parent->right;
        }
    }
}

void removeRbtree(Rbtree tree, PosicTree pObj){
    head *newHead = (head*)tree;
    node *z = (node*)pObj, *y, *x;
    y = z;
    char y_cor_original = y->color;
    if (z->left == newHead->null){
        x = z->right;
        rbtreeTransplant(tree, z, z->right);
    } else if (z->right == newHead->null){
        x = z->left;
        rbtreeTransplant(tree, z, z->left);
    } else {
        y = getRbtreeMinValue(tree, z->right);
        y_cor_original = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else {
            rbtreeTransplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbtreeTransplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if (y_cor_original == 'B')
        deleteFixUp(tree, x);
    (newHead->qtd)--;
}

// void removeRbtree(Rbtree tree, PosicTree pObj){
//     struct node *x, *y, *w, *ppObj;
//     ppObj = (node*)pObj;
//     head *cabeca = (head*)tree;
//     int x_esquerda;
//     if (ppObj == cabeca->null)
//         return;
//     if (ppObj->left == cabeca->null && ppObj->right == cabeca->null) {

//         y = cabeca->null;
//         x = cabeca->null;
//         x->parent = ppObj->parent;
//         if (ppObj->parent != cabeca->null && ppObj->parent->left == ppObj)
//             x_esquerda = 1;
//         else
//             x_esquerda = 0;
        
//     } else if (ppObj->left == cabeca->null && ppObj->right != cabeca->null) {

//         y = ppObj->right;
//         x = ppObj->right;
//         x->parent = ppObj->parent;
//         x_esquerda = 0;
//     } else if (ppObj->left != cabeca->null && ppObj->right == cabeca->null) {
//         y = ppObj->left;
//         x = ppObj->left;
//         x->parent = ppObj->parent;
//         x_esquerda = 1;
//     } else {
//         y = ppObj->right;
//         while (y->left != cabeca->null)
//             y = y->left;
//         x = y->right;
//         if (y != ppObj->right) {
//             y->left = ppObj->left;
//             y->right = ppObj->right;
//             y->left->parent = y;
//             y->right->parent = y;
//             x->parent = y->parent;
//             x->parent->left = x;
//             x_esquerda = 1;
//         } else {
//             x->parent = y;
//             y->left = ppObj->left;
//             ppObj->left->parent = y;
//             x_esquerda = 0;
//         }
//     }

//     if (ppObj->parent != cabeca->null) {
//         if (ppObj->parent->left == ppObj)
//             ppObj->parent->left = y;
//         else
//             ppObj->parent->right = y;
//     } else {
//         (cabeca->root) = y;
//     }

//     if (y != cabeca->null) {
//         y->parent = ppObj->parent;
//     }

	
//     if (ppObj->color == 'R' && (y->color == 'R' || y == cabeca->null))
//         return;
//     else if (ppObj->color == 'R' && y->color == 'B') {
//         y->color = 'R';
//     } else if (ppObj->color == 'B' && y->color == 'R') {
//         y->color = 'B';
//         return;
//     }

//     while (x != (cabeca->root)) {
//         if (x_esquerda)
//             w = x->parent->right;
//         else
//             w = x->parent->left;
        
//         if (x->color == 'R') {
//             x->color = 'B';
//             return;
//         } else {
//             if (w->color == 'R') {
//                 w->color = 'B';
//                 x->parent->color = 'R';
//                 if (x_esquerda) {
//                     leftRotate(cabeca->root, x->parent);
//                     w = x->parent->right;
//                 } else {
//                     rightRotate(cabeca->root, x->parent);
//                     w = x->parent->left;
//                 }
//             }
			
//             if (w->color == 'B') {
//                 if (w->left->color == 'B' && w->right->color == 'B') {
//                     w->color = 'R';
//                     x = x->parent;
//                     x_esquerda = x->parent == cabeca->null ? 0 : x == x->parent->left;
//                     if (x->color == 'R') {
//                         x->color = 'B';
//                         return;
//                     }
//                     continue;
//                 } else if (x_esquerda && w->left->color == 'R' && w->right->color == 'B'
//                         || !x_esquerda && w->right->color == 'R' && w->left->color == 'B') {
//                     w->color = 'R';
//                     if (x_esquerda) {
//                         w->left->color = 'B';
//                         rightRotate(cabeca->root, w);
//                         w = x->parent->right;
//                     } else {
//                         w->right->color = 'B';
//                         leftRotate(cabeca->root, w);
//                         w = x->parent->left;
//                     }
//                 }
//                 w->color = x->parent->color;
//                 x->parent->color = 'B';
//                 if (x->parent->left == x) {
//                     w->right->color = 'B';
//                     leftRotate(cabeca->root, x->parent);
//                 } else {
//                     w->left->color = 'B';
//                     rightRotate(cabeca->root, x->parent);
//                 }
//                 return;
//             }
//         }
//     }
    
   
// }


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


// double funcAbs(double value){
	
// 	if (value < 0.0)
// 		return value*(-1);
// 	return value;
// }

// /*comparação de numeros de ponto flutuante*/

// int doubleEquals(double a, double b){
// 	double dif = a - b;
// 	// printf("dif : %f\n", dif);
// 	dif = funcAbs(dif);
// 	if (dif < 0.00001)
// 		return 1;
// 	return 0;
	
// }

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
    } else if (a->x >= b->x){
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

void printNodeSvg(FILE *svg, Rbtree tree, PosicTree root, double width, double height, double x_ant, double y_ant, int es, InfoElement func){
    head *newHead = (head*)tree;
    node *no = (node*)root;
    char cor[20];
    int lar = 6, a, b;
    if (posicTreeVazio(tree, root))
        return;
    printNodeSvg(svg, tree, getRbtreeLeft(tree, root), width - (es)/2, (height + 100), (width + 1)*lar, height, es/2, func);  
    printNodeSvg(svg, tree, getRbtreeRight(tree, root), width + (es)/2, (height + 100), (width + 1)*lar, height, es/2, func);
    if(no->color == 'R')
        strcpy(cor, "red");
    else
        strcpy(cor, "black");    
    fprintf(svg, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke-width=\"4\" stroke=\"darkgreen\" />\n", (width + 1.0)*lar, height, x_ant, y_ant);
    fprintf(svg, "<circle cx = \"%f\" cy = \"%f\" r = \"10\" fill = \"%s\" stroke=\"%s\" stroke-width=\"1\" fill-opacity = \"1\"/>\n", (width + 1.0)*lar, height, cor, cor);
    if (func != NULL)
        fprintf(svg, "<text x=\"%f\" y=\"%f\" font-family= \"Verdana\" font-size=\"7\" fill = \"yellow\">%s</text>\n", (width + 1.0)*lar, height ,func(getObjRbtree(tree, no)));
}

int funcLog2(int value){
    int i = 2, j = 1;
    while(1){
        if (value <= i){
            return i;
        }
        j++;
        i = pow(2, j);
    }
    return 2;
}
void printTreeSvg(FILE *svg, Rbtree tree, InfoElement func){
    head *newHead = (head*)tree;
    node *atual = (node*)newHead->root;
    int width = getMaxWidth(tree), height = getMaxHeight(tree), es;
    if (width%2 == 1){
        width++;
    }
    if (height%2==1){
        height++;
    }
    width *= funcLog2(height);
    printf("%d\n", funcLog2(height));
    es = width;
    printNodeSvg(svg, tree, getRoot(tree), width, 30, (width + 1)*(4), 30, es, func);
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

typedef void (*SvgTree)(FILE **, Item);

void printSvgRbtree(Rbtree tree, PosicTree root, FILE *svg, SvgTree func){
    if (posicTreeVazio(tree, root))
        return;
    printSvgRbtree(tree, getRbtreeLeft(tree, root), svg, func);
    printSvgRbtree(tree, getRbtreeRight(tree, root), svg, func);
    func(&svg, getObjRbtree(tree, root));
}

// int main() {
//     int i, count = 0;
//     Rbtree head = createTree();
//     Forma coisa;
//     PosicTree p1;
//     FILE *arq;
//     for (i=0; i<200; ++i){
//         // printf("1\n");
//         coisa = createForma(random()/100000000.123,random()/100000000.43412);
// 		insertRbtree(head,coisa, cmpData);
//         // printf("3\n");
//     }
//     // printf("sss %d\n", countt(head));
//     // getchar();
//     arq = fopen("./testes/saida/c1/arv.svg", "w");
//     if (arq == NULL){
//         printf("se...\n");
//         return 0;
//     }
        
//     fprintf(arq, "<svg>\n");    
//     printTreeSvg(arq, head);
//     fprintf(arq, "</svg>\n");    
//     // getchar();
//     fclose(arq);
//     // getchar();
//     // printf("antes\n");
//     removeRbtree(head, getRbtreeLeft(head, getRbtreeLeft(head, getRoot(head))));
//     removeRbtree(head, getRoot(head));
//     getchar();
//     printTree(head);
//     // deletaTudo(head, getRoot(head), &count);
//     // deletaTudo(head, getRoot(head));
//     // printf("depois\n");
//     // getchar();

//     // for (i=0; i<5; ++i){
//     //     coisa = createForma(random()/100000000.123,random()/100000000.43412);
        
//     // }
    
//     // printTree(head);
//     // printf("\n");

//     // printf("Quantidade de elementos: %d\n",qtdRbtree(head));
//     // printf("Maxima largura: %d \n", getMaxWidth(head));
//     // printf("Maxima altura: %d \n", getMaxHeight(head));
    
//     // freeTree(getRoot(head));
    

//     free(head);
//     return 0;
// }
