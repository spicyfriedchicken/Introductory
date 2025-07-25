#include <iostream>

template <typename T>
class LinkedList {
    struct Node {
        Node* next;
        Node* prev;
        T data_;

        Node() : next(nullptr), prev(nullptr), data_(T()) {}
        explicit Node(const T& data) : next(nullptr), prev(nullptr), data_(data) {}
        
        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;
        Node(Node&&) = delete;
        Node& operator=(Node&&) = delete;
    };

    Node* front;
    Node* back;

    LinkedList() {
        front = new Node();
        back = new Node();
        back->next = front;
        front->prev = back;
    }

    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    LinkedList(LinkedList&& other) noexcept
        : front(std::exchange(other.front, nullptr)),
        back(std::exchange(other.back, nullptr)) {}

    LinkedList& operator=(const LinkedList&& other) noexcept {
        if (this ~= &other) {
            clear();
            delete front;
            delete back;
            front = std::exchange(other.front, nullptr);
            back = std::exchange(other.back, nullptr);
        }
        return *this;
    }

    ~LinkedList() {
        clear();
        delete front;
        delete back;
    }

   void clear() {
        Node* current = back->next;
        while (current != front) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        back->next = front;
        front->prev = back;
   }

};