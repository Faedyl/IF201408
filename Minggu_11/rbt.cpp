#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

// Warna node
enum Color { RED, BLACK };

// Struktur Node
struct Node {
    char data;
    Color color;
    Node *left, *right, *parent;

    Node(char data) {
        this->data = data;
        left = right = parent = nullptr;
        color = RED; // Node baru selalu merah
    }
};

// Kelas Red-Black Tree
class RedBlackTree {
private:
    Node *root;

    // Fungsi untuk melakukan rotasi ke kiri
    void leftRotate(Node *&x) {
        Node *y = x->right;
        x->right = y->left;

        if (y->left != nullptr)
            y->left->parent = x;

        y->parent = x->parent;

        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    // Fungsi untuk melakukan rotasi ke kanan
    void rightRotate(Node *&x) {
        Node *y = x->left;
        x->left = y->right;

        if (y->right != nullptr)
            y->right->parent = x;

        y->parent = x->parent;

        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->right = x;
        x->parent = y;
    }

    // Fungsi untuk memperbaiki pohon setelah penyisipan
    void fixViolation(Node *&newNode) {
    Node *parent = nullptr;
    Node *grandparent = nullptr;

    while ((newNode != root) && (newNode->color == RED) && (newNode->parent != nullptr && newNode->parent->color == RED)) {
        parent = newNode->parent;
        grandparent = parent->parent;

        if (grandparent == nullptr) break; // Check if grandparent is valid

        if (parent == grandparent->left) {
            Node *uncle = grandparent->right;

            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                newNode = grandparent;
            } else {
                if (newNode == parent->right) {
                    leftRotate(parent);
                    newNode = parent;
                    parent = newNode->parent;
                }
                rightRotate(grandparent);
                swap(parent->color, grandparent->color);
                newNode = parent;
            }
        } else {
            Node *uncle = grandparent->left;

            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                newNode = grandparent;
            } else {
                if (newNode == parent->left) {
                    rightRotate(parent);
                    newNode = parent;
                    parent = newNode->parent;
                }
                leftRotate(grandparent);
                swap(parent->color, grandparent->color);
                newNode = parent;
            }
        }
    }
    root->color = BLACK;
}

    // Fungsi untuk melakukan pre-order traversal
    void preOrderHelper(Node *root) {
        if (root == nullptr)
            return;

        cout << root->data << " "; // Tampilkan key node dirinya sendiri
        preOrderHelper(root->left); // Rekursif ke node kiri
        preOrderHelper(root->right); // Rekursif ke node kanan
    }

    // Fungsi untuk melakukan in-order traversal
    void inOrderHelper(Node *root) {
        if (root == nullptr)
            return;

        inOrderHelper(root->left); // Rekursif ke node kiri
        cout << root->data << " "; // Tampilkan key node dirinya sendiri
        inOrderHelper(root->right); // Rekursif ke node kanan
    }

    // Fungsi untuk melakukan post-order traversal
    void postOrderHelper(Node *root) {
        if (root == nullptr)
            return;

        postOrderHelper(root->left); // Rekursif ke node kiri
        postOrderHelper(root->right); // Rekursif ke node kanan
        cout << root->data << " "; // Tampilkan key node dirinya sendiri
    }

    // Fungsi untuk menampilkan struktur pohon
    void displayHelper(Node *root, string indent, bool last) {
        if (root != nullptr) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "   ";
            } else {
                cout << "L----";
                indent += "|  ";
            }
            cout << root->data << "(" << (root->color == RED ? "RED" : "BLACK") << ")" << endl;
            displayHelper(root->left, indent, false);
            displayHelper(root->right, indent, true);
        }
    }


    // Fungsi untuk membersihkan pohon
    void clearHelper(Node *root) {
        if (root != nullptr) {
            clearHelper(root->left);
            clearHelper(root->right);
            delete root;
        }
    }

public:
    RedBlackTree() {
        root = nullptr;
    }

    // Fungsi untuk menyisipkan nilai ke dalam pohon
    void insert(char data) {
        Node *newNode = new Node(data);
        root = BSTInsert(root, newNode);
        fixViolation(newNode);
    }

    // Fungsi untuk menyisipkan node ke dalam BST
    Node* BSTInsert(Node* root, Node* newNode) {
        if (root == nullptr)
            return newNode;

        if (newNode->data < root->data) {
            root->left = BSTInsert(root->left, newNode);
            root->left->parent = root;
        } else if (newNode->data > root->data) {
            root->right = BSTInsert(root->right, newNode);
            root->right->parent = root;
        }

        return root;
    }

    // Fungsi untuk melakukan pre-order traversal
    void preOrder() {
        preOrderHelper(root);
        cout << endl;
    }

    // Fungsi untuk melakukan in-order traversal
    void inOrder() {
        inOrderHelper(root);
        cout << endl;
    }

    // Fungsi untuk melakukan post-order traversal
    void postOrder() {
        postOrderHelper(root);
        cout << endl;
    }

    // Fungsi untuk menampilkan struktur pohon
    void display() {
        if (root == nullptr) {
            cout << "Tree kosong." << endl;
        } else {
            displayHelper(root, "", true);
        }
    }

    // Fungsi untuk membersihkan pohon
    void clear() {
        clearHelper(root);
        root = nullptr;
    }

    // Destructor untuk membersihkan pohon saat objek dihapus
    ~RedBlackTree() {
        clear();
    }
};

// Fungsi utama
int main() {
    RedBlackTree tree;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Masukkan huruf acak ke dalam tree\n";
        cout << "2. Pre-order traversal\n";
        cout << "3. In-order traversal\n";
        cout << "4. Post-order traversal\n";
        cout << "5. Tampilkan Struktur Tree\n";
        cout << "6. Bersihkan Tree\n";
        cout << "7. Keluar\n";
        cout << "Pilih opsi (1-7): ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int subChoice;
                cout << "Sub-Opsi:\n";
                cout << "1. Input Manual\n";
                cout << "2. Input Acak\n";
                cout << "Pilih sub-opsi (1-2): ";
                cin >> subChoice;

                if (subChoice == 1) {
                    char key;
                    cout << "Masukkan huruf (A-Z): ";
                    cin >> key;
                    tree.insert(key);
                } else if (subChoice == 2) {
                    for (int i = 0; i < 10; ++i) {
                        char key = 'A' + rand() % 26; // Menghasilkan huruf acak dari A-Z
                        tree.insert(key);
                    }
                    cout << "10 huruf acak telah dimasukkan ke dalam tree.\n";
                } else {
                    cout << "Pilihan tidak valid.\n";
                }
                break;
            }
            case 2:
                cout << "Pre-order traversal: ";
                tree.preOrder();
                break;
            case 3:
                cout << "In-order traversal: ";
                tree.inOrder();
                break;
            case 4:
                cout << "Post-order traversal: ";
                tree.postOrder();
                break;
            case 5:
                cout << "Struktur Tree:\n";
                tree.display();
                break;
            case 6:
                tree.clear();
                cout << "Tree telah dibersihkan.\n";
                break;
            case 7:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan pilih lagi.\n";
        }
    } while (choice != 7);

    return 0;
}
               