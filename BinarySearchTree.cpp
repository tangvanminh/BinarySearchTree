// BinarySearchTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
template<class T>
class BinarySearchTree
{
public:
    class Node;
private:
    Node* root;
public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    //Helping function
    void addRec(Node*& current, T value) {
        if (current == NULL) {
            Node* temp = new Node(value);
            current = temp;
            return;
        }
        if (value > current->value) {
            addRec(current->pRight, value);
            return;
        }
        addRec(current->pLeft, value);
        return;
    }

    void add(T value) {
        //TODO
        addRec(this->root, value);
        return;
    }

    void deleteNodeRec(Node* &current, T value) {
        if (current == NULL) return;
        if (current->value < value) {
            deleteNodeRec(current->pRight, value);
            return;
        }
        if (current->value > value) {
            deleteNodeRec(current->pLeft, value);
            return;
        }
        if (current->pLeft == NULL) {
            Node* dltPtr = current;
            current = current->pRight;
            delete dltPtr;
            return;
        }
        if (current->pRight == NULL) {
            Node* dltPtr = current;
            current = current->pLeft;
            delete dltPtr;
            return;
        }
        Node* dltPtr = current->pRight;
        while (dltPtr->pLeft != NULL) {
            dltPtr = dltPtr->pLeft;
        }
        current->value = dltPtr->value;
        deleteNodeRec(current->pRight, dltPtr->value);
        return;
    }

    void deleteNode(T value) {
        //TODO
        deleteNodeRec(this->root, value);
        return;
    }
    string inOrderRec(Node* root) {
        stringstream ss;
        if (root != nullptr) {
            ss << inOrderRec(root->pLeft);
            ss << root->value << " ";
            ss << inOrderRec(root->pRight);
        }
        return ss.str();
    }

    T getMin() {
        //TODO: return the minimum values of nodes in the tree.
        Node* temp = this->root;
        while (temp->pLeft != NULL) {
            temp = temp->pLeft;
        }
        return temp->value;
    }

    T getMax() {
        //TODO: return the maximum values of nodes in the tree.
        Node* temp = this->root;
        while (temp->pRight != NULL) {
            temp = temp->pRight;
        }
        return temp->value;
    }

    bool find(T i) {
        // TODO: return true if value i is in the tree; otherwise, return false.
        Node* current = this->root;
        while (current != NULL) {
            if (current->value < i) current = current->pRight;             
            else if (current->value > i) current = current->pLeft;
            else return true;
        }
        return false;
    }

    T sumRec(Node* current, T l, T r) {
        if (current == NULL) return 0;
        if (current->value > r) return sumRec(current->pLeft, l, r);
        if (current->value < l) return sumRec(current->pRight, l, r);
        return current->value + sumRec(current->pLeft, l, r) + sumRec(current->pRight, l ,r);
    }

    T sum(T l, T r) {
        // TODO: return the sum of all element in the tree has value in range [l,r].
        return sumRec(this->root, l, r);
    }

    string inOrder() {
        return inOrderRec(this->root);
    }

    vector<int> levelAlterTraverse() {
        // STUDENT ANSWER
        Node* current = root;
        vector<int> result;
        if (current == NULL) return result;
        stack<Node*> reverse;
        queue<Node*> nodePipe;
        result.push_back(current->value);
        reverse.push(current);
        int level = 1; // 0 is root
        while (reverse.size() + nodePipe.size() != 0) {
            if (level % 2 == 1) {
                while (!reverse.empty()) {
                    nodePipe.push(reverse.top()->pRight);
                    nodePipe.push(reverse.top()->pLeft);
                    reverse.pop();
                }
            }
            else {
                while (!reverse.empty()) {
                    nodePipe.push(reverse.top()->pLeft);
                    nodePipe.push(reverse.top()->pRight);
                    reverse.pop();
                }
            }

            while (!nodePipe.empty()) {
                if (nodePipe.front() == NULL) nodePipe.pop();
                else {
                    result.push_back(nodePipe.front()->value);
                    reverse.push(nodePipe.front());
                    nodePipe.pop();
                }
            }
            level++;
        }
        return result;
    }

    void traverseCount(Node* root, int const k, int& count, int& result) {
        if (root == NULL) return;
        if (k >= count) {

            traverseCount(root->pLeft, k, count, result);
            if (count == k) {
                result = root->value;
                count++;
                return;
            }
            count++;
            if (count == k) {
                result = root->value;
                count++;
                return;
            }
            traverseCount(root->pRight, k, count, result);
            if (count == k) {
                result = root->value;
                count++;
                return;
            }
        }
        return;
    }

    int kthSmallest(int k) {
        // STUDENT ANSWER
        int count = 0;
        int result = 0;
        traverseCount(this->root, k, count, result);
        return result;
    }

    class Node
    {
    private:
        T value;
        Node* pLeft, * pRight;
        friend class BinarySearchTree<T>;
    public:
        Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
};



int main()
{
    int values[] = { 6, 9, 2, 13, 0, 20 };
    BinarySearchTree<int> bst;
    for (int i = 0; i < 6; ++i) {
        bst.add(values[i]);
    }
    
    cout << bst.kthSmallest(4);

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
