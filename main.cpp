//
//  main.cpp
//  Binary Search Tree
//
//  Created by Ira Xavier Porchia on 6/3/20.
//  Copyright © 2020 Ira Xavier Porchia. All rights reserved.
//

#include <iostream>
using namespace std;

const int MAX = 100;
class node;
class BST;

template <class T>
class Queue{
private:
    int _head;
    int _tail;
public:
    T _data[MAX];

    Queue():
    _head(0), _tail(0){}

    bool isEmpty(){
        return _tail == _head;
    }

    bool isFull(){
        return (_tail + 1) % MAX == _head;
    }

    T dequeue(){
        if (isEmpty()) {
            return 0;
        }
        T i = _data[_head];
        _head = (_head + 1) % MAX;
        return i;
    }

    void enqueue(node* value){
        if (isFull()) {
            return;
        }
        _data[_tail] = value;
        _tail = (_tail + 1) % MAX;
    }

    T head(){
        return _data[_head];
    }

};

struct Trunk
{
    Trunk *prev;
    string str;

    Trunk(Trunk *prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

// Helper function to print branches of the binary tree
void showTrunks(Trunk *p)
{
    if (p == nullptr)
        return;

    showTrunks(p->prev);

    cout << p->str;
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
class node{
    friend class BST;
private:
    int _data;
    node *_left;
    node *_right;
public:
    node(int data):
    _data(data), _left(nullptr), _right(nullptr){}
    
    void preOrder();
    
    void inOrder();
    
    void postOrder();
    
    void levelOrder(node *root);
    
    int search(int data);
    
    void DeleteMin(node *root);
    
    node *minElement(node *root);
    
};

class BST{
private:
    node *_root;
public:
    BST():
    _root(nullptr){}
    
    ~BST(){
        if(_root == nullptr){
            return;
        }
        if(_root->_left != nullptr){
            delete _root->_left;
            _root->_left = nullptr;
        }
        if(_root->_right != nullptr){
            delete _root->_right;
            _root->_right = nullptr;
        }
        delete _root;
        _root = nullptr;
    }
    
    node *root();
    
    node *insert(node *root, int data);
    
    void preOrder();
    
    void inOrder();
    
    void postOrder();
    
    void levelOrder(node *root);
    
    void printTree(node *root, Trunk *prev, bool isLeft);
    
    int search(int data);
    
    node *Delete(node *root, int data);
    
    void DeleteMin(node *root);
    
    node *minElement(node *root);
    
};
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
node *BST::root(){
    return _root;
}

node *BST::insert(node *root, int data){
    if(root == nullptr){
        root = new node(data);
        _root = root;
        return root;
    }
    if(root->_data > data){
        root->_left = insert(root->_left, data);
    }else if(root->_data <= data){
        root->_right = insert(root->_right, data);
    }
    _root = root;
    return root;
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void BST::printTree(node *root, Trunk *prev, bool isLeft)
{
    if (root == nullptr)
        return;

    string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);

    printTree(root->_left, trunk, true);

    if (!prev)
        trunk->str = "---";
    else if (isLeft)
    {
        trunk->str = ".---";
        prev_str = "   |";
    }
    else
    {
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << root->_data << endl;

    if (prev)
        prev->str = prev_str;
    trunk->str = "   |";

    printTree(root->_right, trunk, false);
}

void BST::preOrder(){
    if (_root != nullptr){
        _root->preOrder();
    }
}

void node::preOrder(){
    cout << _data << " ";
    if(_left != nullptr){
        _left->preOrder();
    }
    if(_right != nullptr){
        _right->preOrder();
    }
}

void BST::inOrder(){
    if (_root != nullptr){
        _root->inOrder();
    }
}

void node::inOrder(){
    if(_left != nullptr){
        _left->inOrder();
    }
    cout << _data << " ";
    if(_right != nullptr){
        _right->inOrder();
    }
}

void BST::postOrder(){
    if (_root != nullptr){
        _root->postOrder();
    }
}

void node::postOrder(){
    if(_left != nullptr){
        _left->postOrder();
    }
    if(_right != nullptr){
        _right->postOrder();
    }
    cout << _data << " ";
}

void BST::levelOrder(node *root){
    if(_root != nullptr){
        _root->levelOrder(_root);
    }
}

void node::levelOrder(node *root){
    Queue<node*> queue;
    queue.enqueue(root);
    while(!queue.isEmpty()){
        node *presentNode = queue.dequeue();
        cout << presentNode->_data << " ";
        if(presentNode->_left != nullptr){
            queue.enqueue(presentNode->_left);
        }
        if(presentNode->_right != nullptr){
            queue.enqueue(presentNode->_right);
        }
    }
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
int BST::search(int data){
    if(_root == nullptr){
        cout << "Number is not in there." << endl << endl;
        return -1;
    }
    return _root->search(data);
}

int node::search(int data){
    bool i = false;
    if(data == _data){
        i = true;
        cout << "Value found: " << data << endl << endl;
        return data;
    }else if(data < _data){
        _left->search(data);
    }else if(data > _data){
        _right->search(data);
    }else{
        cout << "Number is not in there." << endl << endl;
    }
    if(i == true){
        return data;
    }
    return -1;
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
node *BST::Delete(node *root, int data){
    if(root == nullptr){
        cout << "Number is not in there." << endl << endl;
        return root;
    }
    if(data < root->_data){
        root->_left = Delete(root->_left, data);
    }else if(data > root->_data){
        root->_right = Delete(root->_right, data);
    }else{
        if(root->_left != nullptr && root->_right != nullptr){
            node *temp = root;
            node *replace = minElement(temp->_right);
            root->_data = replace->_data;
            root->_right = Delete(root->_right, replace->_data);
        }else if(root->_left != nullptr){
            root = root->_left;
        }else if(root->_right != nullptr){
            root = root->_right;
        }else{
            root = nullptr;
        }
    }
    return root;
}

void BST::DeleteMin(node *root){
    if(_root->_left == nullptr){
        _root = _root->_right;
        return;
    }
    _root->DeleteMin(root);
}

void node::DeleteMin(node *root){
    node *p = root->_left;
    node *q = root;
    while(p->_left != nullptr){
        q = p;
        p = p->_left;
    }
    q->_left = p->_right;
    
}

node *BST::minElement(node *root){
    if(root == nullptr || (root->_left == nullptr && root->_right == nullptr)){
        return root;
    }
    return root->minElement(root);
}

node *node::minElement(node *root){
    if(root->_left == nullptr){
        return root;
    }
    node *p = root;
    while(p->_left != nullptr){
        p = p->_left;
    }
    return p;
}


//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
int main(int argc, const char * argv[]) {
    BST tree1;
    tree1.insert(tree1.root(), 25);
    tree1.insert(tree1.root(), 20);
    tree1.insert(tree1.root(), 30);
    tree1.insert(tree1.root(), 22);
    tree1.insert(tree1.root(), 28);
    tree1.insert(tree1.root(), 23);
    tree1.insert(tree1.root(), 27);
    tree1.preOrder();
    cout << endl << endl;
    tree1.inOrder();
    cout << endl << endl;
    tree1.postOrder();
    cout << endl << endl;
    tree1.levelOrder(tree1.root());
    cout << endl << endl;
    tree1.search(20);
    tree1.printTree(tree1.root(), nullptr, false);
    cout << endl << endl;
//    tree1.minElement(tree1.root());
//    cout << endl << endl;
//    tree1.DeleteMin(tree1.root());
//    cout << endl << endl;
    tree1.Delete(tree1.root(), 28);
    cout << endl << endl;
    tree1.printTree(tree1.root(), nullptr, false);
    cout << endl << endl;
    return 0;
}
