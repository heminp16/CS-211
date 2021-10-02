#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct bstNode BST;
struct bstNode {
    int key;
    int val;
    struct bstNode* l_child;
    struct bstNode* r_child;
};
// Add new data to the BST using recursion

void bstNodeInsert (BST **root, int key ) {
    if (*root==NULL) {
        *root = malloc(sizeof(BST));
        //**root->l_child = NULL;
        //**root->r_child = NULL;
        //**root->key = key;
        **root= (BST){
            .key= key,
            .l_child=NULL,
            .r_child= NULL,
        };
    return;
    }
    if (key <(*root)->key){
        bstNodeInsert(&(*root)->l_child, key);
    }
    else if (key==(*root)->key){ //lecture 46:00 min 
    } else{
    bstNodeInsert(&(*root)->r_child, key);
    }
}
//void Rev_Trav (BST* root);

//    if(root== NULL);
//        return;
//    Rev_Trav(root->r_child);
//    print (" %d ", root->key);
//    Rev_Trav( root->l_child);
//}
void Rev_Trav(BST *root){
    if (root==NULL){
        return;
    }
    Rev_Trav(root->r_child);
    printf(" %d ", root->key);
    Rev_Trav( root->l_child);
}
void clear(BST **root){
    if(*root== NULL)
    {
        return;
    }
    clear(&(*root)->l_child);
    clear(&(*root)->r_child);
    free(*root);
}

int main(int argc, char* argv[])
{
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    //struct bstNode* root = NULL;
    BST* parse(const char *path){
        BST *root= NULL;
        int key;
        //char buff[256];
        while ( fscanf(fp, "%d", &key)!=EOF ) {
            bstNodeInsert(&root, key);
        }
    

    fclose(fp);
    return root;
    }
    BST *root= parse(argv[1]);
    Rev_Trav(root);
    puts ("\n");
    clear(&root);
    return 0;

}
    

   // struct bstNode* root = newBST(1); //it was NULL changed it
    //build tree
    //root->l_child = newBST(2);
    //root->r_child = newBST(3);
    //root->l_child->l_child = newBST(4);
    //root->l_child->r_child = newBST(5);
    //Rev_Trav(root);


// numbers from list inserted into BST

//input: 8,3,6,1,10,4,14,7,13 
//output in descending order: 14, 13, 10, 8, 7, 6, 4, 3, 1.
// ./bstReverseOrder tests/test1.txt


//     8
//  3    10
// 1  6     14
//   4 7  13



