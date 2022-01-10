/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1
    ListNode* head_ = NULL;
    ListNode* tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode * temp = head_;
  if(length_ == 0){
    return;
  }

  while(length_!=0){
    temp = head_->next;
    delete head_;
    head_ = temp;
    length_--;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  if (length_ == 0){
    tail_ = newNode;
    head_ = newNode;
    length_ =1;
    return;
  }
  if (head_ != NULL) {
    head_ -> prev = newNode;
    newNode -> next = head_;
    newNode -> prev = NULL;
    head_ = newNode;
  }
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = NULL;
  if (length_ == 0){
    tail_ = newNode;
    head_ = newNode;
    length_ =1;
    return;
  }
  if (tail_ != NULL) {
    tail_ -> next = newNode;
    newNode -> prev = tail_;
    tail_ = newNode;
  }
  length_++;

}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  if (start == NULL){
    return NULL;
  }
  if(splitPoint<1){
    return start;
  }

  if (length_ < splitPoint){
    return NULL;
  }

  ListNode * curr = start;

  for (int i = 0; i < splitPoint; i++) {
    if(curr->next != NULL)
      curr = curr->next;
  }
  if (curr != NULL) {
      curr->prev->next = NULL;
      tail_ = curr->prev;
      curr->prev = NULL;
      return curr;
  }
  return NULL;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three
  * elements in the list starting for the first three elements. If the
  * end of the list has a set of 1 or 2 elements, no rotation all be done
  * on the last 1 or 2 elements.
  *
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  if (length_ <= 2){
    return;
  }
  if(length_ >= 3){
    ListNode *node1 = head_;
    ListNode *node2 = head_->next;
    ListNode *node3 = head_->next->next;
    ListNode *nextNode = head_->next->next->next;

    node1->prev = node3;
    node1->next = nextNode;
    node2->prev = NULL;
    node2->next = node3;
    node3->prev = node2;
    node3->next = node1;
    nextNode->prev = node1;
    head_ = node2;

    node3 = head_->next->next;
    unsigned count = 0;
    while(node3 != NULL){
      node3 = node3->next;
      if (node3 == NULL){
        return;
      }
      count++;
      if (count == 3){
        node2 = node3->prev;
        node1 = node2->prev;
        ListNode *prevNode = node1->prev;
        ListNode *nextNode = node3->next;

        node1->prev = node3;
        node1->next = nextNode;
        node2->prev = prevNode;
        node2->next = node3;
        node3->prev = node2;
        node3->next = node1;
        prevNode->next = node2;
        if (nextNode != NULL)
          nextNode->prev = node1;
        count = 0;
        node3 = node1;
      }
    }
  }








  // ListNode * curr = head_;
  // unsigned count = 1;
  // while(curr->next != NULL){
  //   if (count == 3){
  //     ListNode *temp = curr->prev->prev;
  //     if(temp == head_){
  //       ListNode *node1 = head_;
  //       ListNode *node2 = head_->next;
  //       ListNode *node3 = head_->next->next;
  //       ListNode *nextNode = head_->next->next->next;
  //
  //       node1->prev = node3;
  //       node1->next = nextNode;
  //       node2->prev = NULL;
  //       node2->next = node3;
  //       node3->prev = node2;
  //       node3->next = node1;
  //       nextNode->prev = node1;
  //
  //       head_ = node2;
  //       count = 0;
  //     }
  //     else{
  //       ListNode *prevNode = curr->prev->prev->prev;
  //       ListNode *node1 = curr->prev->prev;
  //       ListNode *node2 = curr->prev;
  //       ListNode *node3 = curr;
  //       ListNode *nextNode = curr->next;
  //
  //       node1->prev = node3;
  //       node1->next = nextNode;
  //       node2->prev = prevNode;
  //       node2->next = node3;
  //       node3->prev = node2;
  //       node3->next = node1;
  //       nextNode->prev = node1;
  //       prevNode->next = node2;
  //
  //       count = 0;
  //     }
  //   }
  //   count++;
  //   curr = curr->next;
  // }

  // if(length_ >= 3){
  //   ListNode *temp = head_;
  //   ListNode *change = NULL;
  //   change = head_->next->next;
  //   temp->prev = head_->next;
  //   temp->next = change->next;
  //   change->prev = NULL;
  //   change->next = head_->next;
  // head_ = change;
  //   std::cout << temp->data << '\n';
  //   std::cout << change->data << '\n';
  //   std::cout << head_->next->data << '\n';
  //   std::cout << head_->next->data << '\n';
  //   std::cout << head_->next->next->data << '\n';
  //   ListNode * newNode = split(head_, 3);
  //   length_ = length_ -3;
  // //   tripleRotate();
  // // //  newNode
  // }
  // return;

}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  
  if (startPoint == endPoint){
    return;
  }

  ListNode *curr = startPoint;
  ListNode *temp = curr->next;
  ListNode *beforeStart = curr->prev;
  curr->next= endPoint->next;
  curr->prev = temp;
  curr = temp;

  while(curr != endPoint){
    temp = curr->next;
    curr->next = curr->prev;
    curr->prev = temp;
    curr = temp;
  }
  endPoint->next = endPoint->prev;
  endPoint->prev = beforeStart;

  if (head_ != startPoint){
    beforeStart->next = curr;
  }
  if (tail_ != endPoint){
    startPoint->next->prev = startPoint;
  }
  if (head_== startPoint){
    head_ = endPoint;
  }
  if (tail_ == endPoint){
    tail_ = startPoint;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2

  if (n > length_){
    reverse(head_, tail_);
  }
  if(n == length_){
    reverse(head_, tail_);
  }
  if (n < length_){
    int count =1;
    ListNode *curr = head_;
    ListNode *temp = curr;
    while(curr != NULL){
      curr = curr->next;
      if (curr->next == NULL){
        reverse(temp, curr);
        return;
      }
      count++;
      if (count == n){
        reverse(temp, curr);
        curr = temp->next;
        temp = curr;
        count =1;
      }
    }
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2

  if(first == NULL && second == NULL)
    return NULL;
//ListNode * Head;
  if (first->data < second->data){
    head_ = first;
    first = first->next;
  }
  else{
    head_ = second;
    second = second->next;
  }
  ListNode *temp = head_;
  while(first != NULL && second != NULL){
    if (second->data < first->data){
      temp->next = second;
      second->prev = temp;
      second = second->next;
    }
    else{
      temp->next = first;
      first->prev = temp;
      first = first->next;
    }
    temp = temp->next;
  }

  if(first == NULL && second != NULL){
    temp->next = second;
    second->prev = temp;
  }
  if(second == NULL && first != NULL){
    temp->next = first;
    first->prev = temp;
  }

  // ListNode *curr1 = first;
  // ListNode *curr2 = second;
  // ListNode *temp = curr2;
  // while(curr1 != NULL){
  //   while (curr2 != NULL){
  //     if(curr2->data < curr1->data && curr1->prev == NULL){
  //       temp= curr2->next;
  //       curr1->prev = curr2;
  //       curr2->next = curr1;
  //       curr2->prev = NULL;
  //       first = curr2;
  //       curr2 = temp;
  //     }
  //     if(curr1->data < curr2->data && curr1->next == NULL){
  //       temp= curr2->next;
  //       curr1->next = curr2;
  //       curr2->prev = curr1;
  //       curr2->next = NULL;
  //       curr2 = temp;
  //     }
  //     if(curr1->data < curr2->data && curr2->data < curr1->next->data){
  //       temp= curr2->next;
  //       curr1->next->prev = curr2;
  //       curr2->next = curr1->next;
  //       curr1->next = curr2;
  //       curr2->prev = curr1;
  //       curr2 = temp;
  //     }
  //     if(curr1->data == curr2->data){
  //       temp= curr2->next;
  //       curr1->prev->next = curr2;
  //       curr2->prev = curr1->prev;
  //       curr1->prev = curr2;
  //       curr2->next = curr1;
  //       curr2 = temp;
  //     }
  //     curr2 = curr2->next;
  //   }
  //   curr1 = curr1->next;
  // }
  //second = NULL;
  return head_;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (start->next == NULL)
    return start;
  ListNode *splitnode = split(start, chainLength/2);
  return merge(mergesort(start, chainLength/2), mergesort(splitnode, (chainLength%2) + (chainLength/2)));
}
