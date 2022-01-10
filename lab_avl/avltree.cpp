/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

 using namespace std;

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here

    Node* temp = t->right;
    t->right = temp->left;
    temp->left = t;

    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t = temp;
    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here

    Node* temp = t->left;
    t->left = temp->right;
    temp->right = t;

    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
    t = temp;
    t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here

    if(subtree == NULL)
      return;

    int bal = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);

    if (bal == -2){
      int balLeft = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
      if(balLeft < 0)
        rotateRight(subtree);
      else
        rotateLeftRight(subtree);
    }
    else if (bal == 2){
      int balRight = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
      if(balRight > 0)
        rotateLeft(subtree);
      else
        rotateRightLeft(subtree);
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code
    if(subtree == NULL){
      Node* newNode = new Node(key, value);
      subtree = newNode;
    }
    else if (key < subtree->key){
      insert(subtree->left, key, value);
      rebalance(subtree);
    }
    else if (key > subtree->key){
      insert(subtree->right, key, value);
      rebalance(subtree);
    }
    else if (key == subtree->key){
      subtree->value = value;
      return;
    }
    subtree->height = 1 + max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* before = subtree->left;
            while(before->right != NULL){
              before = before->right;
            }
            subtree->key = before -> key;
            subtree ->value = before->value;
            remove(subtree->left, before->key);
        } else {
            /* one-child remove */
            // your code here
            Node* temp;
            if(subtree->right == NULL)
              temp = subtree->left;
            else
              temp = subtree->right;
            *subtree = *temp;
            delete temp;
            temp = NULL;
        }
        // your code here
    }
    subtree->height = 1 + max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
    rebalance(subtree);
}
