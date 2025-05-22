#include "binari.h"

#include <stdint.h>
#include <string.h>

// Static members

//// Allocate memory
static BTNode nodes[NODES_MAX_QTY];
static char url_text[URL_STRINGS_SIZE];

//// Pointers
BTNode btroot = {
    .tag = "",
    .handle = NULL,
    .left = NULL,
    .right = NULL};

static size_t node_qty = 0;
static size_t text_pos = 0;

static char *btnode_allocate_string(char *tag)
{
    // Check if it can allocate the tag
    size_t tag_len = strlen(tag);
    if (text_pos + tag_len >= URL_STRINGS_SIZE)
    {
        return NULL;
    }

    // Allocate tag
    char *alloc_pos = url_text + text_pos;
    strcpy(alloc_pos, tag);
    text_pos += tag_len + 1;

    return alloc_pos;
}

static BTNode *btnode_allocate(char *tag)
{
    // Check if it can allocate the node
    if (node_qty >= NODES_MAX_QTY)
    {
        return NULL;
    }

    // Allocate node
    BTNode *node = nodes + node_qty;

    // Allocate tag
    node->tag = btnode_allocate_string(tag);
    if (node->tag == NULL)
    {
        return NULL;
    }
    node_qty += 1;

    // Set root
    if (node_qty == 1)
    {
        btroot.left = node;
    }

    return node;
}

static void btnode_append(BTNode *parent, BTNode *child)
{
    if ((parent == NULL) || (child == NULL))
        return;

    if (parent->left == NULL) // Free space in the left
    {
        parent->left = child;
    }
    else // Searching a free space in the right
    {
        parent = parent->left;
        while (parent->right != NULL)
        {
            parent = parent->right;
        }
        parent->right = child;
    }
}

static BTNode *btnode_right_search(BTNode *root, char *tag)
{
    BTNode *node;
    for (node = root; node != NULL; node = node->right) // Right-side search
    {
        if (strcmp(tag, node->tag) == 0)
        {
            break;
        }
    }
    return node;
}

BTNode *btnode_create(const char *url, HandleFunctionType handle)
{
    // Check url size
    if (strlen(url) > URL_BUFFER_SIZE)
    {
        return NULL;
    }

    // Copy URL in destructive buffer
    char url_buffer[URL_BUFFER_SIZE] = {0};
    char *inner_safe_ptr = url_buffer;
    strcpy(url_buffer, url);

    //  Allocation
    BTNode *parent = &btroot;
    for (char *tag = strtok_r(url_buffer, "/", &inner_safe_ptr), *leftovers = strtok_r(NULL, "", &inner_safe_ptr);
         tag != NULL;
         tag = strtok_r(leftovers, "/", &inner_safe_ptr), leftovers = strtok_r(NULL, "", &inner_safe_ptr))
    {
        // Search if exists
        BTNode *node = btnode_right_search(parent->left, tag);
        
        if (node == NULL) // Creates a new node
        {
            node = btnode_allocate(tag);
            if (node == NULL)
            {
                // [Produce un error fatal]  <-------------------------------------- Importante!!!
            }
            btnode_append(parent, node);
        }

        if (leftovers == NULL) // last tag?
        {
            node->handle = handle;
        }

        parent = node;
    }

    return parent;
}

BTNode *btnode_search(const char *url)
{
    // Copy URL in destructive buffer
    char url_buffer[URL_BUFFER_SIZE];
    char *inner_safe_ptr = url_buffer;
    strcpy(url_buffer, url);

    BTNode *parent = &btroot;
    for (char *tag = strtok_r(url_buffer, "/", &inner_safe_ptr), *leftovers = strtok_r(NULL, "", &inner_safe_ptr);
         tag != NULL;
         tag = strtok_r(leftovers, "/", &inner_safe_ptr), leftovers = strtok_r(NULL, "", &inner_safe_ptr))
    {
        BTNode *node = btnode_right_search(parent->left, tag);
        if (node == NULL)
        {
            return NULL; // Not found
        }

        if (leftovers == NULL)
        {
            return node;
        }

        parent = node;
    }

    // Not foundm but also error
    return NULL;
}
