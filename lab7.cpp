#include <iostream>

template<typename T>
struct node{
public:
    node(T value){
        this->value = value;
    }

    node<T>* next;
    T value;
};

template<typename T>
struct Queue {
public:
    virtual bool isEmpty() = 0;

    virtual void pushBack(T value) = 0;

    virtual T pop() = 0;

    virtual void clear() = 0;

    virtual void print() = 0;
};

template<typename T>
class PtrQueue : Queue<T>{
public:
    node<T> *head = NULL;
    node<T> *tail = NULL;

    int elementsCount = 0;

    bool isEmpty() override{
        if(elementsCount == 0){
            return true;
        }
        return false;
    }

    void pushBack(T value) override{

        if(elementsCount == 0){
            this->head = new node<T>(value);
            this->tail = this->head;
            this->tail->next = this->head;
            elementsCount++;
            return;
        }

        this->tail->next = new node<T>(value);

        this->tail = this->tail->next;
        this->tail->next = this->head;


        elementsCount++;

    }


    T pop() override{
        node<T>* tmpNode = head->next;

        T tmp = this->head->value;
        free(this->head);
        this->head = tmpNode;
        this->tail->next = this->head;

        elementsCount--;

        if(elementsCount == 0){
            this->head = NULL;
            this->tail = NULL;
        }

        return tmp;
    }

    void clear() override{
        while(!isEmpty()){
            this->pop();
        }
    }

    void print() override{
        std::cout << "ELEMENTS: ";
        if(this->tail == NULL && this->head == NULL){
            std::cout << std::endl;

            return;
        }
        node<T>* currentNode = this->head;
        do{
            std::cout << currentNode->value << ' ';
            currentNode = currentNode->next;
        }while (currentNode!=this->head);
        std::cout << std::endl;
    }
};

template<typename T>
class ArrayQueue : Queue<T> {
public:

    ArrayQueue(int size){
        this->size = size;
        this->data = new T[size];
    }

    bool isEmpty() override{
        if(endPos == 0){
            return true;
        }
        return false;
    }

    void pushBack(T value) override{

        data[endPos] = value;
        endPos++;


    }

    T pop() override{

        T value = data[0];
        for(int i = 0; i < endPos - 1; i++){
            data[i] = data[i+1];
        }

        endPos--;
        return value;

    }

    void clear() override{
        while(!isEmpty()){
            this->pop();
        }
    }

    void print() override{
        std::cout << "ELEMENTS: ";
        for (int i = 0; i < endPos; ++i){
            std::cout << data[i] << ' ';
        }
        std::cout << std::endl;
    }


private:
    int size = 0;
    int endPos = 0;

    T* data;
};

int main() {
    {
        PtrQueue<int> queue;
        for (int i = 0; i < 10; i++) {
            queue.pushBack(i);
        }

        queue.print();
        std::cout << queue.pop() << std::endl;
        queue.pushBack(55);

        queue.print();
        queue.clear();
        std::cout << queue.isEmpty() << std::endl;
        queue.print();


    }
    {
        ArrayQueue<int> queue(10);
        for (int i = 0; i < 10; i++) {
            queue.pushBack(i);
        }

        queue.print();
        std::cout << queue.pop() << std::endl;
        queue.print();
        queue.pushBack(55);
        queue.print();
        queue.clear();
        std::cout << queue.isEmpty() << std::endl;
        queue.print();

    }

    return 0;
}
