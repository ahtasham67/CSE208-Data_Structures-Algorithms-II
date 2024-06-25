#include "2105067_problem2.cpp"

int main()
{
  Map myMap;
  freopen("in.txt", "r", stdin);
  while (1)
  {
    string str1;
    cin >> str1;

    if (str1 == "F")
    {
      int a;
      cin >> a;
      if (myMap.find(a))
      {
        cout << a << " Found" << endl;
      }
      else
      {
        cout << a << " Not Found" << endl;
      }
    }
    else if (str1 == "I")
    {
      int a;
      string s;
      cin >> a >> s;
      if (myMap.find(a))
      {
        myMap.erase(a);
        myMap.insert(a, s);
        myMap.printTree();
      }
      else
      {
        myMap.insert(a, s);
        myMap.printTree();
      }
    }
    else if (str1 == "E")
    {
      int val;
      cin >> val;
      if (myMap.find(val))
      {
        myMap.erase(val);
        myMap.printTree();
      }
      else
        cout << val << " not found" << endl;
    }
    else if (str1 == "Itr")
    {
      myMap.printInOrder();
    }
    else if (str1 == "S")
    {
      cout << myMap.size() << endl;
    }
    else if (str1 == "Em")
    {
      if (myMap.empty())
        cout << "yes" << endl;
      else
        cout << "no" << endl;
    }
    else if (str1 == "Clr")
    {
      myMap.clear();
    }
    else
      break;
  }
  return 0;
}