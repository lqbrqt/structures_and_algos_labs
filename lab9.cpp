#include <iostream>
#include <string>

template <typename T>
struct Node{
    Node(T value){
        this->value = value;
    }

    T value;
    Node* left = NULL;
    Node* right = NULL;
    Node* parent = NULL;
};

template <typename T>
class BinaryTree{

public:

    void insert(T value){
        if(this->root == NULL){
            this->root = new Node<T>(value);
            return;
        }

        Node<T>* parentNode = this->getParentNode(value);

        if(parentNode->value == value){
            return;
        }

        if(parentNode->value > value){
            parentNode->left = new Node<T>(value);
            parentNode->left->parent = parentNode;
        }else{
            parentNode->right = new Node<T>(value);
            parentNode->right->parent = parentNode;

        }
    }

    Node<T>* getMinNode(){
        Node<T>* tmpNode = this->root;

        while (tmpNode->left){
            tmpNode = tmpNode->left;
        }

        return tmpNode;
    }

    Node<T>* getMaxNode(){
        Node<T>* tmpNode = this->root;

        while (tmpNode->right){
            tmpNode = tmpNode->right;
        }

        return tmpNode;
    }

    Node<T>* getNodeByValue(T value){
        Node<T>* parentNode = this->getParentNode(value);

        if(parentNode->value > value && parentNode->left->value == value){
            return parentNode->left;
        }else if(parentNode->value < value && parentNode->right->value == value){
            return parentNode->right;
        }else{
            return NULL;
        }
    }

    void removeByPointer(Node<T>* toDelete){
        Node<T>* parentNode = toDelete->parent;

        if(parentNode->value > toDelete->value){
            parentNode->left = NULL;

            Node<T>* newParentNodeForLHS = this->getParentNode(toDelete->left->value);
            if(newParentNodeForLHS->value > toDelete->left->value){
                newParentNodeForLHS->left = toDelete->left;
                if(toDelete->left){
                    toDelete->left->parent = newParentNodeForLHS;
                }
            }else{
                newParentNodeForLHS->right = toDelete->left;
                if(toDelete->right){
                    toDelete->right->parent = newParentNodeForLHS;
                }
            }

            Node<T>* newParentNodeForRHS = this->getParentNode(toDelete->right->value);
            if(newParentNodeForRHS->value > toDelete->right->value){
                newParentNodeForRHS->left = toDelete->right;
            }else{
                newParentNodeForRHS->right = toDelete->right;
            }
        }

        free(toDelete);
    }

    bool removeByValue(T toDeleteValue){
        Node<T>* parentNode = this->getParentNode(toDeleteValue)->parent;
        if(parentNode->value > toDeleteValue){
            if(!parentNode->left){
                return false;
            }else{
                this->removeByPointer(parentNode->left);
                return true;
            }
        }else{
            if(!parentNode->right){
                return false;
            }else{
                this->removeByPointer(parentNode->right);
                return true;
            }
        }
    }

    void printTree(){
        if(root)
        this->printTree("", this->root, true);
    }


private:

    Node<T>* getParentNode(T value){
        Node<T>* tmpNode = this->root;

        while (true){
            if(tmpNode->value > value){
                if(tmpNode->left){
                    tmpNode = tmpNode->left;
                }else{
                    return tmpNode;
                }
            }else if(tmpNode->value < value){
                if(tmpNode->right){
                    tmpNode = tmpNode->right;
                }else{
                    return tmpNode;
                }
            }
            else{
                return tmpNode;
            }
        }
    }

    void printTree(const std::string& prefix, const Node<T>* node, bool isLeft){

        if (node != nullptr)
        {
            std::cout << prefix;

            std::cout << "+--";

            std::cout << node->value << std::endl;

            printTree(prefix + (isLeft ? "|   " : "    "), node->left, true);
            printTree(prefix + (isLeft ? "|   " : "    "), node->right, false);

        }

    }

    Node<T>* root = NULL;

};

int main(){
    BinaryTree<int> tree;

    for(int i = 0; i < 10; ++i){
        int in;
        std::cin >> in;
        tree.insert(in);
    }

    tree.printTree();

    tree.removeByValue(24);

    tree.printTree();
}