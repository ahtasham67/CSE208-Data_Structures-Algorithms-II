#include "2105067_problem1.cpp"

class Map
{
private:
  RedBlackTree tree;

public:

  void insert(int key, string value)
  {
    if (tree.searchTree(key))
    {
      tree.deleteNode(key);
      tree.insert(key, value);
    }
    else
    {
      tree.insert(key, value);
    }
  }

  void erase(int key)
  {
    if (tree.find(key))
    {
      tree.deleteNode(key);
    }
    else
    {
      cout << key << " not found" << endl;
    }
  }

  void clear()
  {
    if (tree.size() == 0)
    {
      cout << "unsuccessful" << endl;
    }
    else
    {
      tree.deleteTree();
      cout << "Successful" << endl;
    }
  }

  int size()
  {
    return tree.size();
  }


  bool empty()
  {
    return tree.isEmpty();
  }

  bool find(int key)
  {
    return tree.find(key);
  }

  void printInOrder()
  {
    tree.printInOrder();
  }


  void printTree()
  {
    tree.printTree();
  }
};