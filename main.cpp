#include <iostream>


template<class T>
class Iterator;

template<class T>
class List;

template<class T>
class Node {
    T value;
    Node *next = nullptr;

public:
    explicit Node(T value) {
        this->value = value;
    }

    void setNext(Node *next) {
        this->next = next;
    }

    Node *getNext() {
        return next;
    }

    T getValue() {
        return value;
    }
};

template<class T>
class Iterator {
    friend class List<T>;

protected:
    Node<T> *node;
    const List<T> *list;
public:
    Iterator(const List<T> *list, Node<T> *node) : node(node), list(list) {
    }

    int operator*() { return node->getValue(); }

    bool operator!=(const Iterator &iter) const {
        return !(*this == iter);
    }

    bool operator==(const Iterator &iter) const {
        return list == iter.list && node == iter.node;
    }

    Iterator next() const {
        if (node != nullptr)
            return {list, node->getNext()};
        return *this;
    }

    Iterator &operator++() {
        if (node != nullptr)
            node = node->getNext();
        return *this;
    }
};

template<class T>
class List {
private:
    Node<T> *first = nullptr;
    Node<T> *last = nullptr;

public:
    int size = 0;

    void add(T value) {
        if (size == 0) {
            first = new Node<T>(value);
            last = first;
        } else {
            last->setNext(new Node<T>(value));
            last = last->getNext();
        }
        size++;
    }

    bool isEmpty() {
        return first == nullptr;
    }

    void toString() {
        if (isEmpty()) return;
        Node *tmp = first;
        while (tmp) {
            std::cout << tmp->getValue() << " ";
            tmp = tmp->getNext();
        }
        std::cout << std::endl;
    }

    Iterator<T> begin() const {
        return {this, first};
    }

    Iterator<T> end() const {
        return Iterator<T>(this, last).next();
    }

    List<T> filter(bool (*ptr)(T)) {
        List newList = List();
        Node<T> *tmp = first;
        while (tmp) {
            if (ptr(tmp->getValue())) {
                newList.add(tmp->getValue());
            }
            tmp = tmp->getNext();
        }
        return newList;
    }

    template<class T, class V>
    List<V> map(V (*ptr)(T)) {
        List<V> newList = List();
        Node<T> *tmp = first;
        while (tmp) {
            newList.add(ptr(tmp->getValue()));

            tmp = tmp->getNext();
        }
        return newList;
    }
};


int main() {

    List<int> list = List<int>();
    list.add(1);
    list.add(2);
    list.add(6);
    list.add(10);
    list.add(0);
    list.add(-19);

    auto lambda = [](int j) { return std:: string ("ja"); };

 //   List<const char *> newList = list.map(lambda);

     List<int> newList =list.filter([](int j) { return j % 2 == 0; });
//            .map([](std::string j) { return "new " + j;})
//            ;

    for (int it : newList) {
        std::cout << it << " ";
    }

    std::cout << std::endl;

    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }

    return 0;
}
