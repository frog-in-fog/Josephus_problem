#include <iostream>
#include <ctime>

enum direction{
    clockwise,
    counterclockwise
};


template <typename T>
struct Node{
    T data;
    Node *next, *prev;
};

class StepException
{
public:
    StepException(std::string message): message{message}{}
    std::string getMessage() const {return message;}
private:
    std::string message;
};

template<typename T>
class circular_linked_list{
    Node<T> *head, *tail;
public:
    void setHead(Node<T> *head) {
        circular_linked_list::head = head;
    }

    void setTail(Node<T> *tail) {
        circular_linked_list::tail = tail;
    }

public:
    Node<T> *getHead() const {
        return head;
    }

    Node<T> *getTail() const {
        return tail;
    }

private:
    int count;
public:
    //constructor
    circular_linked_list();

    //copy constructor
    circular_linked_list(const circular_linked_list<T>&l);

    //move constructor
    circular_linked_list(circular_linked_list<T>&& l) = default;

    //destructor
    ~circular_linked_list();

    //get count of list elements
    int getCount();

    //get element of list
    Node<T>* getElem(int);

    //delete list
    void delAll();

    //delete element
    void del(int pos);

    //delete node
    void delNode(Node<T>* node);

    //insert element
    void insert(int pos);

    //add to tail aka push_back
    void addTail(T n);

    //add to head aka push_front
    void addHead(T n);

    //print the list
    void print();

    //print element of list
    void print(int pos);

    //operator =
    circular_linked_list<T>& operator = (const circular_linked_list<T>&l);

    //operator =
    circular_linked_list<T>& operator = (circular_linked_list<T>&&l) = default;

    //operator +
    circular_linked_list<T> operator + (const circular_linked_list<T>&);

    bool operator == (const circular_linked_list<T>&);
    bool operator != (const circular_linked_list<T>&);
    bool operator <= (const circular_linked_list<T>&);
    bool operator >= (const circular_linked_list<T>&);
    bool operator < (const circular_linked_list<T>&);
    bool operator > (const circular_linked_list<T>&);

    //reverse list
    circular_linked_list<T> operator - ();
};

template<typename T>
circular_linked_list<T>::circular_linked_list() {
    head = nullptr;
    tail = nullptr;
    count = 0;
}

template<typename T>
circular_linked_list<T>::circular_linked_list(const circular_linked_list<T> & l) {
    head = nullptr;
    tail = nullptr;
    count = 0;

    Node<T> *temp = l.head;

    do{
        addTail(temp->data);
        temp = temp->next;
    }
    while(temp != l.head);
}

template<typename T>
circular_linked_list<T>::~circular_linked_list<T>() {
    delAll();
}

template<typename T>
void circular_linked_list<T>::addHead(T n) {
    auto *temp = new Node<T>;

    if (count == 0){
        temp->next = temp;
        temp->prev = temp;
        head = tail = temp;
    }

    temp->prev = tail;
    temp->data = n;
    temp->next = head;
    tail->next = temp;

    if (head != nullptr){
        head->prev = temp;
    }

    if (count != 0 ) {
        head = temp;
    }

    count++;
}

template<typename T>
void circular_linked_list<T>::addTail(T n) {
    auto *temp = new Node<T>;

    if (count == 0){
        temp->next = temp;
        temp->prev = temp;
        head = tail = temp;
    }

    temp->next = head;
    temp->data = n;
    temp->prev = tail;
    head->prev = temp;

    if (tail != nullptr){
        tail->next = temp;
    }

    if (count != 0) {
        tail = temp;
    }

    count++;
}

template<typename T>
void circular_linked_list<T>::insert(int pos) {
    if (pos <  0 || pos > count - 1){
        std::cout << "Incorrect position" << std::endl;
        return;
    }

    if (pos == count - 1){
        T data;
        std::cout << "Input new data: ";
        std::cin>>data;
        addTail(data);
        return;
    } else if (pos == 0){
        T data;
        std::cout << "Input new data: ";
        std::cin>>data;
        addHead(data);
        return;
    }

    int i = 0;

    Node<T> *Ins = head;

    while(i < pos){
        Ins = Ins->next;
        i++;
    }

    Node<T> *prevIns = Ins->prev;

    auto *temp = new Node<T>;

    std::cout<<"Input new data: ";
    std::cin>>temp->data;

    if (prevIns != nullptr && count != 1){
        prevIns->next = temp;
    }

    temp->next = Ins;
    temp->prev = prevIns;
    Ins->prev = temp;

    count++;
}

template<typename T>
void circular_linked_list<T>::delNode(Node<T> *node) {
    Node<T> *next, *prev;
    prev = node->prev;
    next = node->next;
    if (prev != nullptr && count != 1) {
        prev->next = node->next;
    }
    if (next != nullptr && count != 1) {
        next->prev = node->prev;
    }

    if (head == node) {
        head = next;
    }
    if (tail == node) {
        tail = prev;
    }

    delete node;
    count--;
}

template<typename T>
void circular_linked_list<T>::del(int pos) {

    if(pos < 0 || pos > count - 1)
    {
        std::cout << "Incorrect position \n";
        return;
    }

    int i = 0;

    Node<T> *del = head;

    while(i < pos){
        del = del->next;
        i++;
    }

    Node<T> *prevDel = del->prev;
    Node<T> *afterDel = del->next;

    if (prevDel != nullptr && count != 1){
        prevDel->next = afterDel;
    }
    if (afterDel != nullptr && count != 1){
        afterDel->prev = prevDel;
    }

    if (pos == 0){
        head = afterDel;
    }
    if (pos == count - 1){
        tail = prevDel;
    }

    delete del;
    count--;
}

template<typename T>
void circular_linked_list<T>::print(int pos) {
    if(pos < 0 || pos > count - 1){
        std::cout << "Incorrect position \n";
        return;
    }
    Node<T> *temp;

    if (pos <= count / 2){
        temp = head;
        int i = 0;

        while (i < pos){
            temp = temp->next;
            i++;
        }
    } else {
        temp = tail;
        int i = 1;

        while (i <= count - 1 - pos){
            temp = temp->prev;
            i++;
        }
    }

    std::cout<< pos << "element: " << temp->data << std::endl;
}

template<typename T>
void circular_linked_list<T>::print() {
    if (count != 0){
        Node<T> *temp = head;
        std::cout<<"( ";
        while(temp->next != head){
            std::cout<< temp->data << ", ";
            temp = temp->next;
        }

        std:: cout << temp->data << " )\n";
    }
}

template<typename T>
void circular_linked_list<T>::delAll() {
    while(count != 0){
        del(0);
    }
}

template<typename T>
int circular_linked_list<T>::getCount() {
    return count;
}

template<typename T>
Node<T> *circular_linked_list<T>::getElem(int pos) {
    Node<T> *temp = head;

    if (pos < 0 || pos > count - 1){
        std::cout << "incorrect position" << std::endl;
        return nullptr;
    }

    int i = 0;

    while(i < pos && temp != nullptr){
        temp = temp->next;
        i++;
    }

    if (temp == nullptr){
        return nullptr;
    } else {
        return temp;
    }
}

template<typename T>
circular_linked_list<T> &circular_linked_list<T>::operator = (const circular_linked_list<T> & l) {
    if (this == &l){
        return *this;
    }

    this->~circular_linked_list<T>();

    Node<T> *temp = l.head;

    do{
        addTail(temp->data);
        temp = temp->next;
    }
    while(temp != l.head);

    return *this;
}

template<typename T>
circular_linked_list<T> circular_linked_list<T>::operator+(const circular_linked_list<T> &l) {
    circular_linked_list<T> result(*this);

    Node<T> *temp = l.head;

    do {
        result.addTail(temp->data);
        temp = temp->next;
    }
    while(temp != l.head);

    return result;
}

template<typename T>
bool circular_linked_list<T>::operator==(const circular_linked_list<T> & l) {
    if (count != l.count){
        return false;
    }

    Node<T> *t1, *t2;

    t1 = head;
    t2 = l.head;

    do{
        if (t1->data != t2->data){
            return false;
        }
        t1 = t1->next;
        t2 = t2->next;
    }
    while(t1 != head);

    return true;
}

template<typename T>
bool circular_linked_list<T>::operator!=(const circular_linked_list<T> & l) {
    return *this != l;
}

template<typename T>
bool circular_linked_list<T>::operator>=(const circular_linked_list<T> & l) {
    if (count > l.count){
        return true;
    }

    if (*this == l){
        return true;
    }

    return false;
}

template<typename T>
bool circular_linked_list<T>::operator<=(const circular_linked_list<T> & l) {
    if (count < l.count){
        return true;
    }

    if (*this == l){
        return true;
    }

    return false;
}

template<typename T>
bool circular_linked_list<T>::operator>(const circular_linked_list<T> & l) {
    return count > l.count;
}

template<typename T>
bool circular_linked_list<T>::operator<(const circular_linked_list<T> & l) {
    return count < l.count;

}

template<typename T>
circular_linked_list<T> circular_linked_list<T>::operator-() {
    circular_linked_list<T> result;

    Node<T> *temp = head;

    do{
        result.addHead(temp->data);
        temp = temp->next;
    }
    while(temp != head);

    return result;
}

//solving Josephus problem
template<typename T>
std::pair<int, T> Josephus_problem(circular_linked_list<T> cll, direction dir, unsigned step) {

    if (step == 0){
        throw StepException("Step is equal 0");
    }

    if (step == 1) {
        return dir == clockwise ?
               std::make_pair(cll.getCount() - 1, cll.getElem(cll.getCount() - 1)->data) :
               std::make_pair(0, cll.getElem(0)->data);
    }

    auto posList = new circular_linked_list<int>;
    for (int i = 0; i < cll.getCount(); i++){
        posList->addTail(i);
    }

    Node<T> *front, *back, *posPointer, *posPointerBack;

    front = dir == clockwise ? cll.getHead() : cll.getTail();
    back = dir == clockwise ? cll.getHead() : cll.getTail();
    posPointer = dir == clockwise ? posList->getHead() : posList->getTail();
    posPointerBack = dir == clockwise ? posList->getHead() : posList->getTail();

    while (cll.getCount() > 1) {
        for (int i = 1; i < step; i++) {
            back = front;
            front = dir == clockwise ? front->next : front->prev;
            posPointerBack = posPointer;
            posPointer = dir == clockwise ? posPointer->next : posPointer->prev;
        }
        cll.delNode(front);
        posList->delNode(posPointer);
        front = dir == clockwise ? back->next : back->prev;
        posPointer = dir == clockwise ? posPointerBack->next : posPointerBack->prev;
    }
    int pos = posPointer->data;
    posList->delAll();

    return std::make_pair(pos, front->data);
}

void check_circular_linked_list_working(){
    circular_linked_list<int> L;

    const int n = 10;
    int a[n] = {0,1,2,3,4,5,6,7,8,9};

    // We add elements at even indexes in the head,
    // on odd numbers - in the tail
    for(int i = 0; i < n; i++)
        if(i % 2 == 0)
            L.addHead(a[i]);
        else
            L.addTail(a[i]);

    // printing the list
    std::cout << "List L:\n";
    std::cout<<"Elements in list: "<<L.getCount()<<std::endl;
    L.print();

    std::cout << std::endl;

    int pos;
    std::cout << "Input position: ";
    std::cin>>pos;
    // inserting element in index
    L.insert(pos);
    // Распечатка списка
    std::cout << "List L:\n";
    std::cout<<"Elements in list: "<<L.getCount()<<std::endl;
    L.print();

    // printing 2nd and 8th elements
    L.print(2);
    L.print(8);

    circular_linked_list<int> T;

    // copying the list
    T = L;
    // print the copy
    std::cout << "List T:\n";
    std::cout<<"Elements in list: "<<L.getCount()<<std::endl;
    T.print();

    // Add two lists (first is reversed)
    std::cout << "List Sum:\n";
    circular_linked_list<int> Sum = -L + T;
    std::cout<<"Elements in list: "<<Sum.getCount()<<std::endl;
    // print the list
    Sum.print();

    std::cout << "Deleting demonstration"<<std::endl;
    std::cout << "Input position: ";
    std::cin>>pos;
    Sum.del(pos);
    std::cout<<"List after deleting element with index = "<<pos<<std::endl;
    std::cout<<"Elements in list: "<<Sum.getCount()<<std::endl;
    Sum.print();
}

void check_josephus_problem_solving(){
    srand(time(NULL));
    unsigned size, step;
    std::cout<<"Enter the number of elements: ";
    std::cin>>size;

    std::cout<<"Enter the step value: ";
    std::cin>>step;


    auto cll = new circular_linked_list<int>;
    for (int i = 0; i < size; i++){
        cll->addTail(rand()%10);
    }

    std::cout<<"List: "<<std::endl;
    cll->print();
    try {
        auto pairClockWise = Josephus_problem(*cll, clockwise, step);
        std::cout << "Josephus position clockwise: (" << pairClockWise.first << ", " << pairClockWise.second << ")" << std::endl;

        auto pairCounterClockWise = Josephus_problem(*cll, counterclockwise, step);
        std::cout << "Josephus position counter clockwise: (" << pairCounterClockWise.first << ", " << pairCounterClockWise.second << ")" << std::endl;
    } catch (const StepException &se) {
        std::cout << se.getMessage() << std::endl;
    }
}

int main(){

    //check_circular_linked_list_working();
    check_josephus_problem_solving();



    return 0;
}






