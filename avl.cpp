#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

struct node {
    int value, height, size;
    node *left = nullptr, *right = nullptr;

    node(int value, int height, int size) {
        this->value = value;
        this->height = height;
        this->size = size;
    }
};

int height(node *x) {
    if (x == nullptr) return 0;
    return x->height;
}

int size(node *x) {
    if (x == nullptr) return 0;
    return x->size;
}

void update(node *x) {
    x->size = 1 + size(x->left) + size(x->right);
    x->height = 1 + max(height(x->left), height(x->right));
}

int dif(node *x) {
    return height(x->left) - height(x->right);
}

node *rot_left(node *x) {
    node *y = x->right;
    x->right = y->left;
    y->left = x;
    update(x), update(y);
    return y;
}

node *rot_right(node *x) {
    node *y = x->left;
    x->left = y->right;
    y->right = x;
    update(x), update(y);
    return y;
}

node *balance(node *x) {
    if (dif(x) > 1) {
        if (dif(x->left) < 0) x->left = rot_left(x->left);
        x = rot_right(x);
    } else if (dif(x) < -1) {
        if (dif(x->right) > 0) x->right = rot_right(x->right);
        x = rot_left(x);
    }
    update(x);
    return x;
}

node *get_min(node *x) {
    if (x->left == nullptr) return x;
    return get_min(x->left);
}

node *remove_min(node *x) {
    if (x->left == nullptr) return x->right;
    x->left = remove_min(x->left);
    return balance(x);
}

bool contains(node *x, int v) {
    if (x == nullptr) return false;
    else if (v < x->value) return contains(x->left, v);
    else if (v > x->value) return contains(x->right, v);
    return true;
}

node *insert(node *x, int v) {
    if (x == nullptr) return new node(v, 0, 1);
    if (v < x->value) x->left = insert(x->left, v);
    else x->right = insert(x->right, v);
    return balance(x);
}

node *remove(node *x, int v) {
    if (x == nullptr) return x;
    if (v < x->value) x->left = remove(x->left, v);
    else if (v > x->value) x->right = remove(x->right, v);
    else {
        if (x->left == nullptr) return x->right;
        else if (x->right == nullptr) return x->left;
        else {
            node *y = x;
            x = get_min(y->right);
            x->right = remove_min(y->right);
            x->left = y->left;
        }
    }
    return balance(x);
}

node *find(node *x, int v) {
    if (x == nullptr) return x;
    int k = size(x->left);
    if (v < k) return find(x->left, v);
    else if (v > k) return find(x->right, v - k - 1);
    return x;
}

int get_index(node *x, int v) {
    if (x == nullptr) return 0;
    if (v <= x->value) return get_index(x->left, v);
    else return 1 + size(x->left) + get_index(x->right, v);
}

void traverse(node *x) {
    if (x == nullptr) return;
    traverse(x->left);
    cout << x->value << " ";
    traverse(x->right);
}
