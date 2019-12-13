#include "Rbtree.h"

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
}head;


/* DECLARACAO LOCAL PARA TIRAR IMPLICIDADE */
void inorder(struct node *root);
int counterTree(struct node *root);
struct node* deleteNode(struct node* sroot, int data);

/* UTILITY FUNCTIONS */
/* Compute the "height" of a tree -- the number of 
    nodes along the longest path from the root node 
    down to the farthest leaf node.*/
int height(struct node* node);
/* Get width of a given level */
int getWidth(struct node* root, int level);

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
    newHead->qtd = 0;
    newHead->root = NULL;
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
void LeftRotate(struct node **root,struct node *x) {
    if (!x || !x->right)
        return ;
    //y ponteiro armazenado do filho certo de x
    struct node *y = x->right;

    //armazena o ponteiro esquerdo da subárvore esquerda como filho direito de x
    x->right = y->left;

    //atualizar o ponteiro pai da direita de x
    if (x->right != NULL)
        x->right->parent = x;

    //atualizar o ponteiro pai de y
    y->parent = x->parent;

    // se o pai de x for nulo, faça y como raiz da árvore
    if (x->parent == NULL)
        (*root) = y;

    // armazene y no local de x
    else if (x == x->parent->left)
        x->parent->left = y;
    else    x->parent->right = y;

    // faça x como filho esquerdo de y
    y->left = x;

    //atualizar ponteiro pai de x
    x->parent = y;
}
void rightRotate(struct node **root,struct node *y){
    if (!y || !y->left)
        return ;
    struct node *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent =y->parent;
    if (x->parent == NULL)
        (*root) = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
}
void insertFixUp(struct node **root,struct node *z){
    // itere até z não ser a raiz e a cor pai de z ser vermelha
    while (z != *root && z != (*root)->left && z != (*root)->right && z->parent->color == 'R'){
        struct node *y;

        // Encontre o tio e guarde o tio em y
        if (z->parent && z->parent->parent && z->parent == z->parent->parent->left)
            y = z->parent->parent->right;
        else
            y = z->parent->parent->left;

        // Se o tio for VERMELHO, faça o seguinte
        // (i) Mude a cor do pai e do tio como PRETO
        // (ii) Alterar a cor dos avós como VERMELHO
        // (iii) Mover z para avô
        if (!y)
            z = z->parent->parent;
        else if (y->color == 'R'){
            y->color = 'B';
            z->parent->color = 'B';
            z->parent->parent->color = 'R';
            z = z->parent->parent;
        }

        // Tio é preto, existem quatro casos (LL, LR, RL and RR)
        else{
            // Caso Esquerda-Esquerda (LL), faça o seguinte
            // (i) Troque a cor dos pais e avós
            // (ii) Girar à direita avô
            if (z->parent == z->parent->parent->left &&
                z == z->parent->left){

                char ch = z->parent->color ;
                z->parent->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                rightRotate(root,z->parent->parent);
            }

            // Caso Esquerda-Direita (LR), faça o seguinte
            // (i) Troque a cor do nó atual e dos avós
            // (ii) Girar pai à esquerda
            // (iii) Girar à direita Grand Parent
            if (z->parent && z->parent->parent && z->parent == z->parent->parent->left &&
                z == z->parent->right){

                char ch = z->color ;
                z->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                LeftRotate(root,z->parent);
                rightRotate(root,z->parent->parent);
            }

            // Caso Direito-Direito (RR), faça o seguinte
            // (i) Troque a cor dos pais e avós
            // (ii) Girar à esquerda avô
            if (z->parent && z->parent->parent &&
                z->parent == z->parent->parent->right &&
                z == z->parent->right){

                char ch = z->parent->color ;
                z->parent->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                LeftRotate(root,z->parent->parent);
            }

            // Caso Direita-Esquerda (RL), faça o seguinte
            // (i) Troque a cor do nó atual e dos avós
            // (ii) Girar pai à direita
            // (iii) Girar à esquerda Grand Parent
            if (z->parent && z->parent->parent && z->parent == z->parent->parent->right &&
                z == z->parent->left){
                
                char ch = z->color ;
                z->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                rightRotate(root,z->parent);
                LeftRotate(root,z->parent->parent);
            }
        }
    }
    (*root)->color = 'B'; // mantém a raiz sempre preta
}
struct node * minValueNode(struct node* node){
    struct node* current = node; 
  
    // vai rodando pra esquerda até achar o menor valor (filho) 
    while (current && current->left != NULL) 
        current = current->left; 
  
    return current; 
}
int getMaxWidth(Rbtree tree){ 
  int maxWidth = 0;    
  int width; 
  struct node *root = ((head *)tree)->root;
  int h = height(root); 
  int i; 
    
  /* Pega a largura de cada nivel, e compara para pegar o maior */
  for(i=1; i<=h; i++){ 
    width = getWidth(root, i); 
    if(width > maxWidth) 
      maxWidth = width; 
  }      
    
  return maxWidth; 
}  
int getWidth(struct node* root, int level){
  if(root == NULL) 
    return 0; 
    
  if(level == 1) 
    return 1; 
              
  else if (level > 1) 
    return getWidth(root->left, level-1) +  
             getWidth(root->right, level-1); 
}
int getMaxHeight(Rbtree tree){
    struct node *root = ((head *)tree)->root;
    return height(root);
}
int height(struct node* node){ 
   if (node==NULL) 
     return 0; 
   else{ 
     int lHeight = height(node->left); 
     int rHeight = height(node->right);   
     return (lHeight > rHeight)? (lHeight+1): (rHeight+1); 
   } 
}
Item getObjRbtree(Rbtree tree, PosicTree p){
    return ((node*)p)->data;
}
/* FIM FUNCOES AUXILIARES */


/* INSERE ELEMENTO */
void insertRbtree(Rbtree *tree, Item data,double x, double y){
    // Alocar memória para novo nó
    struct node *z = (struct node*)malloc(sizeof(struct node));
    z->data = data;
    z->x = x;
    z->y = y;
    z->left = z->right = z->parent = NULL;
    struct head *cabeca = (struct head *)*tree;
    struct node *root = cabeca->root;
     //se root for nulo, faça z como root
    (cabeca->qtd)++;
    if (root == NULL){
        z->color = 'B';
        cabeca->root = z;

    }
    else{
        struct node *y = NULL;
        struct node *x = root;

        // Siga as etapas de inserção padrão do BST para inserir primeiro o nó
        while (x != NULL){
            y = x;
            if (z->x < x->x)
                x = x->left;
            else if (z->x > x->x)
                x = x->right;
            else{
                if(z->y < x->y)
                    x = x->left;
                else
                    x = x->right;
            }
            
        }
        z->parent = y;

        if(y->x < z->x)
            y->right = z;
        else if(y->x > z->x)
            y->left = z;
        else{
            if(y->y < z->y)
                y->right = z;
            else
                y->left = z;
        }
        z->color = 'R';

        // chame insert FixUp para corrigir a propriedade da árvore vermelho-preta se
        // for violada devido à inserção.

        insertFixUp(&cabeca->root,z);
    }
}
/* FIM INSERE ELEMENTO */


/* DELETA ELEMENTO */
void delete(Rbtree tree, int data){
    head *root = (head*)tree;
    deleteNode(root->root,data);
}
struct node* deleteNode(struct node* root, int data) {
    // caso base 
    if (root == NULL)
        return root;
    // nó com apenas um filho ou nenhum filho
    if (root->left == NULL){
        struct node *temp = root->right; 
        free(root); 
        return temp; 
    } 
    else if (root->right == NULL) { 
        struct node *temp = root->left; 
        free(root); 
        return temp; 
    }
    // nó com dois filhos: obtenha o sucessor inorder (menor
    // na subárvore direita)
    struct node* temp = minValueNode(root->right); 

    // Copie o conteúdo do sucessor da ordem de entrada para este nó
    root->data = temp->data; 

    // Excluir o sucessor da ordem de entrada
    root->right = deleteNode(temp,data); 
    return root; 
}

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
    inorder(root->root);
}
void inorder(struct node *root) {
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%.2lf%C ", ((forma *)root->data)->x,root->color);

    inorder(root->right);
}
/* FIM DA IMPRESSAO DA ARVORE*/


/* CONTADOR DE ELEMENTOS*/
int qtdRbtree(Rbtree tree){
    head *root = (head *)tree;
    return counterTree(root->root);
}
int counterTree(struct node *root) {
    if(root == NULL)      
        return 0;  
    if(root->left == NULL && root->right == NULL)  
        return 1;
    else
        return 1 + counterTree(root->left) + counterTree(root->right);  
}
/* FIM CONTADOR ELEMENTOS*/

// int main() {
//     int i;
//     Rbtree head = createTree();
//     Forma coisa;
//     PosicTree p1;

//     for (i=0; i<5; ++i){
//         coisa = createForma(random()/100000000.123,random()/100000000.43412);
// 		insertRbtree(&head,coisa,random()/100000000.52154,random()/100000000.451);
//     }

//     for (i=0; i<5; ++i){
//         coisa = createForma(random()/100000000.123,random()/100000000.43412);
        
//     }

//     printTree(head);
//     printf("\n");

//     printf("Quantidade de elementos: %d\n",qtdRbtree(head));
//     printf("Maxima largura: %d \n", getMaxWidth(head));
//     printf("Maxima altura: %d \n", getMaxHeight(head));
    
//     // freeTree(getRoot(head));
    

//     free(head);
//     return 0;
// }