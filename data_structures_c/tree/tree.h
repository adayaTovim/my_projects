#ifndef __TREE_H__
#define __TREE_H__
#include "ADTDef.h"  /* error header  ????*/

typedef struct Node Node;
typedef struct Tree Tree;

typedef enum
{
	PRE_ORDER,
	IN_ORDER,
	POST_ORDER
} TreeTraverse;

/*descraption: creat new tree.
  input: nothing.
  output: ptr to the tree; 
  errores: if aloocation faild return NULL.
*/
Tree* TreeCreate();

/*descraption: destroy all allocation in the tree.
  input: ptr to tree.
  output: nothing.
  errores: nothing.*/
void TreeDestroy(Tree* _tree);

/*descraption: insert data to tree.
  input: ptr to root and data for enter.
  output: if data inserted return ERR_OK.
  errores: if allocation fail return ERR_ALLOCATION_FAILED.
  if ptr to root is NULL return ERR_NOT_INITIALIZED.
  if data for enter is duplicate return ERR_DUPLICATE.*/ 
ADTErr TreeInsert(Tree* _tree, int _data);

/*descraption: check if data found in tree.
  input: ptr to root and data for found.
  output: if data found return TRUE, else rutern FALSE.
  errores: if ptr to root is Null return FALSE.*/
int TreeIsDataFound(Tree* _tree, int _data);

/*descraption: print all data from tree.
  input: ptr to root.
  output: print data to standart output.
  errores:nothing;
*/
void TreePrint(Tree* _tree, TreeTraverse _traverseMode);

int isFullTree(Tree* _tree);

int AreSimilarTree(Tree* _tree1, Tree* _tree2);

int CalcTreeLevel(Tree* _tree);

int MirrorTree(Tree* _tree);

#endif
