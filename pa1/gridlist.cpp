// File:        gridlist.cpp
// Date:        2020-01-18 00:11
// Description: Contains partial implementation of GridList class
//              CPSC 221 2019W2 PA1
//              Function bodies to be completed by yourselves
//
// ADD YOUR FUNCTION IMPLEMENTATIONS IN THIS FILE
//

#include "gridlist.h"
#include "gridlist_given.cpp"

// Creates a PNG of appropriate pixel dimensions according to the GridList's structure
//   and colours each pixel according the each GridNode's Block data.
// The fully coloured PNG is returned.
PNG GridList::Render() const{
  PNG image;
  //check if this is the last node in the image
  if(northwest != NULL){
    //Resize the graph
    int nodeDimension = (northwest->data).Dimension();
    image.resize(dimx * nodeDimension, dimy * nodeDimension);
    
    //Start to render
    int counter = 0;
    GridNode *curr = northwest;
    (curr->data).Render(image, 0, 0);

    while (curr->next != NULL){
      curr = curr->next;
      counter++;
      int upper = counter / dimx * nodeDimension;
      int left = counter % dimx * nodeDimension;
      (curr->data).Render(image, upper, left);
    }
  }

  return image;
}

// Allocates a new GridNode containing bdata and
//   attaches it to end of this list.
// Be careful of the special case of inserting into an empty list.
void GridList::InsertBack(const Block& bdata){
  GridNode *newNode = new GridNode(bdata);
  if (Length() == 0){
    northwest = newNode;
    southeast = newNode;
  }
  //insert the new node at the end of the linked list
  else{
    newNode->prev = southeast;
    southeast->next = newNode;
    southeast = newNode;
  }
}

bool GridList::IsEdgeCondition(int op1, int op2, int op3, int op4){
  if ((op1 < 2) || (op2 < 1) || (op3 != op4)){
    return true;
  }
  return false;
}

// if this list has an odd number of column blocks, then the right side will have more blocks
// PRE:  this list and inner are not the same physical list
//       this list must have at least two column blocks
//       inner list must have at least one column block
//       inner list must have the same vertical resolution, vertical block dimension, and block size
// POST: this list has nodes of the entire inner list in between the left and right halves of this list
//         and inner list becomes empty
//       otherwise both lists are not modified
// THIS MUST BE ACHIEVED USING POINTER REASSIGNMENTS.
// DO NOT ALLOCATE OR DELETE ANY NODES IN THIS FUNCTION.
void GridList::Sandwich_H(GridList& inner){
  
  if(IsEdgeCondition(dimx, inner.dimx, dimy, inner.dimy)){return;}

  int currMid = dimx / 2 - 1;
  //make sure left < right
  int innerDimx = inner.dimx;
  int counter = 0;
  int innerCounter;
  GridNode *curr = northwest;
  GridNode *other = inner.northwest;
  while (curr->next != NULL){
    if (counter % dimx == currMid){
      innerCounter = 0;
      while (innerCounter < innerDimx){
        GridNode *temp = other;
        //keep track of other's head
        other = other->next;
        //move other to the next node
        temp->prev = curr;
        temp->next = curr->next;
        curr->next->prev = temp;
        curr->next = temp;
        //insert temp into the row
        curr = curr->next;
        innerCounter++;
      }
    }
    curr = curr->next;
    ++counter;
  }
  dimx += inner.dimx;
  //increase dimx by 1
  inner.dimx = 0;
  inner.dimy = 0;
  inner.southeast = NULL;
  inner.northwest = NULL;
  //delete inner linked list
}

// inner list must have the same horizontal resolution, horizontal block dimension, and block size
// if this list has an odd number of row blocks, then the bottom side will have more blocks
// PRE:  this list and inner are not the same physical list
//       this list must have at least two row blocks
//       inner list must have at least one row block
//       inner list must have same horizontal resolution, horizontal block dimension, and block size
// POST: this list has nodes of the entire inner list in between the upper and lower halves of this list
//         and inner list becomes empty
//       otherwise both lists are not modified
// THIS MUST BE ACHIEVED USING POINTER REASSIGNMENTS.
// DO NOT ALLOCATE OR DELETE ANY NODES IN THIS FUNCTION.
void GridList::Sandwich_V(GridList& inner)
{
  if(IsEdgeCondition(dimy, inner.dimy, dimx, inner.dimx)){return;}

  int currMid = dimy / 2 * dimx - 1;
  int counter = 0;
  GridNode *curr = northwest;
  while (curr->next != NULL){
    if (counter == currMid){
      inner.southeast->next = curr->next;
      inner.northwest->prev = curr;
      curr->next->prev = inner.southeast;
      curr->next = inner.northwest;
    }
    curr = curr->next;
    ++counter;
  }
  dimy += inner.dimy;
  inner.dimx = 0;
  inner.dimy = 0;
  inner.southeast = NULL;
  inner.northwest = NULL;
}


// PRE:  this list and otherlist have the same pixel dimensions, block dimensions, and block size
// POST: this list and otherlist are checkered with each other's nodes
//       each list's dimensions remain the same
// THIS MUST BE ACHIEVED USING POINTER REASSIGNMENTS.
// DO NOT ALLOCATE OR DELETE ANY NODES IN THIS FUNCTION.
void GridList::CheckerSwap(GridList& otherlist)
{
  int dimension = (northwest->data).Dimension();
  int counter = 0;
  GridNode *curr = northwest;
  GridNode *other = otherlist.northwest;
  while (curr->next != NULL)
  {
    curr = curr->next;
    other = other->next;
    counter++;
    int upper = counter / dimx * dimension;
    int left = counter % dimx * dimension;
    if ((upper + left) % 2 == 1){
      if (curr->next != NULL){
        curr->next->prev = other;
        other->next->prev = curr;
      }
      curr->prev->next = other;
      other->prev->next = curr;
      GridNode *temp = curr->prev;
      curr->prev = other->prev;
      other->prev = temp;
      temp = curr->next;
      curr->next = other->next;
      other->next = temp;
    }
  }
}

// POST: this list has the negative effect applied selectively to GridNodes to form
//         a checkerboard pattern.
//       The northwest block is normal (does not have the negative effect applied).
// Ensure that the checkering looks correct for both odd and even horizontal block dimensions
void GridList::CheckerN(){
  if (northwest != NULL){
    int counter = 0;
    GridNode *curr = northwest;
    while (curr->next != NULL){
      curr = curr->next;
      counter++;
      int upper = counter / dimx;
      int left = counter % dimx;
      if ((upper + left) % 2 == 1){
        curr->data.Negative();
      }
    }
  }
}

// Deallocates any dynamic memory associated with this list
//   and re-initializes this list to an empty state
void GridList::Clear(){
   if (!IsEmpty()){
    GridNode* curr = northwest;
    while (curr->next!= NULL){
      curr = curr->next;
      delete curr->prev;
      curr->prev = NULL;
    }
  }
}

// Allocates new nodes into this list as copies of all nodes from otherlist
void GridList::Copy(const GridList& otherlist){
  dimx = otherlist.dimx;
  dimy = otherlist.dimy;
  GridNode *curr = otherlist.northwest->next;
  while (curr != otherlist.northwest){
    InsertBack(curr->data);
    curr = curr->next;
  }
}