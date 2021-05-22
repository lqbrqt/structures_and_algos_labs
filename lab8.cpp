#include <iostream>

template<typename T>
struct node{
public:
    node(T value){
        this->value = value;
    }

    node<T>* next;
    node<T>* prev;


    T value;
};

template<typename T>
struct List {
public:
    virtual bool isEmpty() {}

    virtual void insert(T value, int position) {}
    virtual void push_back(T value) {}
    virtual void push_front(T value) {}

    virtual void remove(int position) {};

    virtual void clear(){};

    virtual void print(){};
};

template<typename T>
class PtrList : List<T>{
public:
    node<T> *head = NULL;
    node<T> *tail = NULL;

    int elementsCount = 0;

    bool isEmpty() override{
        if(head == tail && head == NULL){
            return true;
        }
        return false;
    }

    void push_back(T value) override{

        if(elementsCount == 0){
            this->head = new node<T>(value);
            this->head->next = NULL;
            this->head->prev = NULL;


            this->tail = this->head;
            elementsCount++;
            return;
        }

        node<T>* tmpNode = this->tail;
        tmpNode->next = NULL;
        tmpNode->prev = this->tail;

        this->tail = tmpNode;

        elementsCount++;

    }

    void push_front(T value) override{

        if(elementsCount == 0){
            this->head = new node<T>(value);
            this->head->next = NULL;
            this->head->prev = NULL;


            this->tail = this->head;
            elementsCount++;
            return;
        }

        node<T>* tmpNode = new node<T>(value);
        tmpNode->next = this->head;
        tmpNode->prev = NULL;
        this->head->prev = tmpNode;
        this->head = tmpNode;

        elementsCount++;

    }

    void remove(int position) override{

        if(position == 0) {
            this->pop_front();
            return;
        }
        if(position == elementsCount - 1) {
            this->pop_back();
            return;
        }

        node<T>* tmpNode = head;
        for(int i = 0; i < position; ++i){
            tmpNode = tmpNode->next;
        }

        node<T>* toDelete = tmpNode;
        toDelete->next->prev = toDelete->prev;
        toDelete->prev->next = toDelete->next;

        free(toDelete);
        elementsCount--;
    }

    void pop_front(){

        if(elementsCount == 1){
            free(head);
            head = NULL;
            tail = NULL;
            elementsCount--;
            return;
        }

        node<T>* nextNode = head->next;
        free(head);
        head = nextNode;
        head->prev = NULL;
        elementsCount--;
    }

    void pop_back(){

        if(elementsCount == 1){
            free(head);
            head = NULL;
            tail = NULL;
            elementsCount--;
            return;
        }

        node<T>* toDelete = this->tail;
        toDelete->prev->next = NULL;
        this->tail = toDelete->prev;
        free(toDelete);

    }

    void insert(int position, T value) override{

        if(position == 0){
            push_back(value);
        }

        node<T>* tmpNode = head;
        for(int i = 0; i < position; ++i){
            tmpNode = tmpNode->next;
        }

        node<T>* newNode = new node<T>(value);
        newNode->next = tmpNode;
        newNode->prev = tmpNode->prev;
        tmpNode->prev->next = newNode;
        tmpNode->prev = newNode;

        elementsCount++;
    }

    void clear() override{
        while(!isEmpty()){
            this->pop_front();
        }
    }
    void print() override{
        std::cout << "ELEMENTS: ";
        node<T>* currentNode = this->head;
        for (int i = 0; i < elementsCount; ++i){
            std::cout << currentNode->value << ' ';
            currentNode = currentNode->next;
        }
        std::cout << std::endl;
    }
};

template<typename T>
class ArrayList : List<T> {
public:

    ArrayList(int size){
        this->size = size;
        this->data = new T[size];
    }

    bool isEmpty() override{
        if(elementsCount == 0){
            return true;
        }
        return false;
    }

    void push_back(T value) override{

        elementsCount++;
        data[endPos] = value;
        endPos++;

    }

    void push_front(T value) override{

        for(int i = endPos; i >= startPos; i--){
            data[i+1] = data[i];
            swapCount++;
        }

        data[startPos] = value;
        elementsCount++;
        endPos++;

    }

    void remove(int position) override{
        T out = data[position];

        for(int i = position; i <= endPos; i++){
            data[i] = data[i+1];
            swapCount++;
        }

        elementsCount--;
        endPos--;

    }

    void clear() override{
        while(!isEmpty()){
            this->remove(0);
        }
    }

    void insert(int position, T value) override{
        for(int i = endPos; i >= position; i--){
            data[i+1] = data[i];
            swapCount++;
        }
        endPos++;
        elementsCount++;
        data[position] = value;
    }

    void print() override{
        std::cout << "ELEMENTS: ";
        for (int i = startPos; i < elementsCount; ++i){
            std::cout << data[i] << ' ';
        }
        std::cout << std::endl;
    }

    int elementsCount = 0;
    int swapCount = 0;

private:
    int size = 0;
    int startPos = 0;
    int endPos = 0;

    T* data;
};

int main() {
    {
        PtrList<int> list;
        for (int i = 0; i < 10; i++) {
            list.push_front(i);
        }

        list.print();
        list.remove(2);
        list.print();
        list.insert(2, 55);
        list.print();
        list.clear();
        std::cout << list.isEmpty() << std::endl;
        list.print();


    }
    {
        ArrayList<int> list(10);
        for (int i = 0; i < 10; i++) {
            list.push_front(i);
        }

        list.print();
        list.remove(2);
        list.print();
        list.insert(2, 55);
        list.print();
        list.clear();
        std::cout << list.isEmpty() << std::endl;
        list.print();

        std::cout << list.swapCount << std::endl;




    }

    return 0;
}
