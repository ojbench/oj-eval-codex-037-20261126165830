#include <iostream>

namespace DoubleLinkList {

struct NODE {
    int data = 0;
    NODE* next = nullptr;
    NODE* pre = nullptr;
    explicit NODE(int value = 0) : data(value) {}
};

NODE* head = nullptr;
NODE* tail = nullptr;
int len = 0;

void Pre() {
    head = new NODE();
    tail = new NODE();
    head->next = tail;
    tail->pre = head;
    len = 0;
}

// Position len denotes the tail sentinel, allowing insertion at the end.
NODE* move(int i) {
    if (i < len / 2) {
        NODE* cur = head->next;
        for (int j = 0; j < i; ++j) cur = cur->next;
        return cur;
    }
    NODE* cur = tail;
    for (int j = len; j > i; --j) cur = cur->pre;
    return cur;
}

void insert(int i, int x) {
    NODE* right = move(i);
    NODE* node = new NODE(x);
    node->pre = right->pre;
    node->next = right;
    right->pre->next = node;
    right->pre = node;
    ++len;
}

void remove(int i) {
    NODE* node = move(i);
    node->pre->next = node->next;
    node->next->pre = node->pre;
    delete node;
    --len;
}

int Get_length() { return len; }

int Query(int i) {
    return i < 0 || i >= len ? -1 : move(i)->data;
}

void Print() {
    if (len == 0) {
        std::cout << -1 << '\n';
        return;
    }
    for (NODE* cur = head->next; cur != tail; cur = cur->next) {
        if (cur != head->next) std::cout << ' ';
        std::cout << cur->data;
    }
    std::cout << '\n';
}

void Clear() {
    while (head != nullptr) {
        NODE* next = head->next;
        delete head;
        head = next;
    }
    tail = nullptr;
    len = 0;
}

}  // namespace DoubleLinkList

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    if (!(std::cin >> n)) return 0;
    DoubleLinkList::Pre();
    for (int k = 0; k < n; ++k) {
        int op, p, x;
        std::cin >> op;
        switch (op) {
        case 0:
            std::cout << DoubleLinkList::Get_length() << '\n';
            break;
        case 1:
            std::cin >> p >> x;
            DoubleLinkList::insert(p, x);
            break;
        case 2:
            std::cin >> p;
            std::cout << DoubleLinkList::Query(p) << '\n';
            break;
        case 3:
            std::cin >> p;
            DoubleLinkList::remove(p);
            break;
        case 4:
            DoubleLinkList::Print();
            break;
        }
    }
    DoubleLinkList::Clear();
}
