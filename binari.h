#ifndef __BINARYTREE__
#define __BINARYTREE__

#define NODES_MAX_QTY (50U)
#define URL_STRINGS_SIZE (1024U)
#define URL_BUFFER_SIZE (128U)

typedef void (*HandleFunctionType)(void); // Change with the type of the handler

struct BTNodeStr;
typedef struct BTNodeStr BTNode;

struct BTNodeStr
{
    BTNode *left;   // Sons
    BTNode *right;  // Siblings
    char *tag;
    HandleFunctionType handle;
};

extern BTNode btroot;

BTNode *btnode_create(const char *url, HandleFunctionType handle);
BTNode *btnode_search(BTNode *root, char *url);

#endif