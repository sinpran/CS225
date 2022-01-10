/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <iostream>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    if (curDim < 0 || curDim >= Dim)
      return false;
    if(first[curDim]==second[curDim])
          return first<second;
    return (first[curDim] < second[curDim]);
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    double curDistance = 0, potDistance = 0;
    for(int i=0; i<Dim;i++){
           curDistance += ((target[i]-currentBest[i])*(target[i]-currentBest[i]));
           potDistance += ((target[i]-potential[i])*(target[i]-potential[i]));
    }
    if(curDistance == potDistance)
      return potential < currentBest;
    return potDistance < curDistance;
}

template <int Dim>
unsigned KDTree<Dim>::quickSelectLocation(vector<Point<Dim>>& list, int dimension, unsigned left, unsigned right, unsigned pivotIndex){
      Point<Dim> pivotValue = list[pivotIndex];
      Point<Dim> temp = list[pivotIndex];
      list[pivotIndex] = list[right];
      list[right] = temp;
      unsigned storeIndex = left;
      for(unsigned i = left;i<right;i++){
        if(smallerDimVal(list[i],pivotValue,dimension)){
          temp = list[storeIndex];
          list[storeIndex] = list[i];
          list[i] = temp;
          storeIndex++;
        }
      }
      temp = list[storeIndex];
      list[storeIndex] = list[right];
      list[right] = temp;
      return storeIndex;
}

template <int Dim>
Point<Dim>& KDTree<Dim>::quickSelect(vector<Point<Dim>>& list, int dimension, unsigned left, unsigned right, unsigned k){
      if(left == right)
        return list[left];
      unsigned pivotIndex = k;
      pivotIndex = quickSelectLocation(list,dimension,left,right,pivotIndex);
      if(k==pivotIndex)
        return list[k];
      else if(k<pivotIndex)
        return quickSelect(list, dimension, left, pivotIndex-1, k);
      else
        return quickSelect(list, dimension, pivotIndex+1, right, k);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::ctorHelper(vector<Point<Dim>>& points_, int dimension, unsigned left, unsigned right){
    if(points_.empty()||left<0||right>=points_.size()||right<0||left>=points_.size())
      return NULL;
    if(left>right)
      return NULL;
    unsigned median_idx = (left+right)/2;
    KDTreeNode* subroot_ = new KDTreeNode(quickSelect(points_,dimension%Dim,left,right,median_idx));
    size+=1;
    dimension++;
    subroot_->left = ctorHelper(points_,dimension,left,median_idx-1);
    subroot_->right = ctorHelper(points_,dimension,median_idx+1,right);
    return subroot_;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    size = 0;
    vector<Point<Dim>> points;
    points.assign(newPoints.begin(), newPoints.end());
    root = ctorHelper(points, 0, 0, points.size()-1);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
    copy(this->root, other.root);
    size = other.size;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
      if (this != NULL)
        destroy(root);
      copy(this->root, rhs.root);
      size = rhs.size;
      return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
      destroy(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const {
    return findNearestNeighbor(root, query, 0);  // Use helper function
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(KDTreeNode * subroot, const Point<Dim>& query, int dimension) const {
    Point<Dim> currentBest = subroot->point;
    bool flag;
    if (subroot->left == NULL && subroot->right == NULL)
      return subroot->point;
    if (smallerDimVal(query, subroot->point, dimension)) {
        if (subroot->left == NULL)
            currentBest = findNearestNeighbor(subroot->right, query, (dimension + 1) % Dim);
        else
            currentBest = findNearestNeighbor(subroot->left, query, (dimension + 1) % Dim);
        flag = true;
    }
    else {
        if (subroot->right == NULL)
            currentBest = findNearestNeighbor(subroot->left, query, (dimension + 1) % Dim);
        else
            currentBest = findNearestNeighbor(subroot->right, query, (dimension + 1) % Dim);
        flag = false;
    }
    if (shouldReplace(query, currentBest, subroot->point))
      currentBest = subroot->point;

    double radius = 0;
    for (int i = 0; i < Dim; i++) {
        radius += (query[i] - currentBest[i]) * (query[i] - currentBest[i]);
    }
    double split_distance = subroot->point[dimension] - query[dimension];
    split_distance = split_distance * split_distance;

    if (split_distance <= radius) {
        KDTreeNode * need_to_check = flag ? subroot->right : subroot->left;
        if (need_to_check != NULL) {
            Point<Dim> otherBest = findNearestNeighbor(need_to_check, query, (dimension + 1) % Dim);
            if (shouldReplace(query, currentBest, otherBest))
              currentBest = otherBest;
        }
    }
    return currentBest;
}

template <int Dim>
void KDTree<Dim>::destroy(KDTreeNode * subroot) {
    if (subroot == NULL)
      return;
    if (subroot->left != NULL)
      destroy(subroot->left);
    if (subroot->right != NULL)
      destroy(subroot->right);
    delete subroot;
    subroot = NULL;
}

template <int Dim>
void KDTree<Dim>::copy(KDTreeNode * subroot, KDTreeNode * othersubroot) {
    subroot = new KDTreeNode();
    subroot->point = othersubroot->point;
    copy(subroot->left, othersubroot->left);
    copy(subroot->right, othersubroot->right);
}
