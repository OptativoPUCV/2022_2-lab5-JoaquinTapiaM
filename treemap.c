#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * t = (TreeMap*)calloc(1,sizeof(TreeMap));
    t->root = NULL;
    t->current = NULL;
    t->lower_than = lower_than;
    return t;
}


//3.- Implemente la función void insertTreeMap(TreeMap * tree, void* key, void * value). Esta función inserta un nuevo dato (key,value) en el árbol y hace que el current apunte al nuevo nodo.
//Para insertar un dato, primero debe realizar una búsqueda para encontrar donde debería ubicarse. Luego crear el nuevo nodo y enlazarlo. Si la clave del dato ya existe retorne sin hacer nada (recuerde que el mapa no permite claves repetidas).

void insertTreeMap(TreeMap * tree, void* key, void * value) {
    TreeNode * newNode = createTreeNode(key, value);
    //si el arbol esta vacio
    if(tree->root==NULL){
      tree->root = newNode;
      tree->current = newNode;
    }
    
    //en caso de no estar vacio
    TreeNode * aux = tree->root;
    while(aux!=NULL){
      if(tree->lower_than(key, aux->pair->key)){
        if(aux->left == NULL){
          aux->left = newNode;
          newNode->parent = aux;
          tree->current = newNode;
          return;
        }
        aux = aux->left;
        }
      if(tree->lower_than(aux->pair->key, key)){
        if(aux->right == NULL){
          aux->right  = newNode;
          newNode->parent = aux;
          tree->current = newNode;
          return;
        }
        aux = aux->right;
      }
      if(is_equal(tree, aux->pair->key, key)){
        return;
      }
    }
  
}


//4.- Implemente la función TreeNode * minimum(TreeNode * x). Esta función retorna el **nodo con la mínima clave** ubicado en el subárbol con raiz x. Para obtener el nodo tiene que, a partir del nodo x, irse por la rama izquierda hasta llegar al final del subárbol. Si x no tiene hijo izquierdo se retorna el mismo nodo.

TreeNode * minimum(TreeNode * x){
    if(x->left == NULL){
      return x;
    }
    TreeNode * aux = x->left;
    while(aux!=NULL){
      if(aux->left == NULL){
        return aux;
      }
      aux = aux->left;
    }
    return NULL;
}

//5.- Implemente la función void removeNode(TreeMap * tree, TreeNode* node). Esta función elimina el nodo *node* del árbol *tree*. Recuerde que para eliminar un node existen 3 casos:
//**Nodo sin hijos:** Se anula el puntero del padre que apuntaba al nodo
//**Nodo con un hijo:** El padre del nodo pasa a ser padre de su hijo
//**Nodo con dos hijos:** Descienda al hijo derecho y obtenga el menor nodo del subárbol (con la función minimum). Reemplace los datos (key,value) de *node* con los del nodo "minimum". Elimine el nodo minimum (para hacerlo puede usar la misma función *removeNode*).


void removeNode(TreeMap * tree, TreeNode* node) {
  TreeNode * aux = node->parent;
  //caso sin hijos
  if(node->left == NULL && node->right == NULL){
    if(tree->lower_than(node->pair->key,aux->pair->key)){
      aux->left = NULL;
      return;
    }
    if(tree->lower_than(aux->pair->key, node->pair->key)){
      aux->right = NULL;
      return;
    }
  }
  //caso con 1 hijo
  if(node->left == NULL && node->right != NULL){
    if(tree->lower_than(node->pair->key,aux->pair->key)){
      aux->left = node->right;
      node->right->parent = aux;
      return;
    }
    if(tree->lower_than(aux->pair->key, node->pair->key)){
      aux->right = node->right;
      node->right->parent = aux;
      return;
    }
  }
  if(node->right == NULL && node->left != NULL){
    if(tree->lower_than(node->pair->key,aux->pair->key)){
      aux->left = node->left;
      node->left->parent = aux;
      return;
    }
    if(tree->lower_than(aux->pair->key, node->pair->key)){
      aux->right = node->left;
      node->left->parent = aux;
      return;
    }
  }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}



//2.- Implemente la función Pair* searchTreeMap(TreeMap* tree, void* key), la cual busca el nodo con clave igual a key y retorna el **Pair** asociado al nodo. Si no se encuentra la clave retorna NULL.
//Recuerde hacer que el current apunte al nodo encontrado.


Pair * searchTreeMap(TreeMap * tree, void* key) {
    if(tree->root==NULL){
      return NULL;
    }
    
    TreeNode * new = tree->root;

    while(new!=NULL){
      //actual es menor que key ingresada
      if(tree->lower_than(new->pair->key, key)){
        if(new->right == NULL){
          return NULL;
        }
        new = new->right;
      }

      if(tree->lower_than(key, new->pair->key)){
        if(new->left == NULL){
          return NULL;
        }
        new = new->left;
      }
      
      if(is_equal(tree, new->pair->key, key)){
        tree->current = new;
        return new->pair;
      }

      if(new->left == NULL && new->right == NULL){
        return NULL;
      }
    }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
