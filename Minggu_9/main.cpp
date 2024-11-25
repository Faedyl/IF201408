#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include "Node.cpp"
using namespace std;

class BinarySearchTree {
private:
    Node* root;

    Node* insert(Node* node, char key) {
        if (node == nullptr) return new Node(key);
        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        }
        return node;
    }

    void clear(Node* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    void preOrder(Node* node) {
        if (node == nullptr) return;
        cout << static_cast<char>(node->key) << " ";
        preOrder(node->left);
        preOrder(node->right);
    }

    void inOrder(Node* node) {
        if (node == nullptr) return;
        inOrder(node->left);
        cout << static_cast<char>(node->key)<< " ";
        inOrder(node->right);
    }

    void postOrder(Node* node) {
        if (node == nullptr) return;
        postOrder(node->left);
        postOrder(node->right);
        cout << static_cast<char>(node->key)<< " ";
    }

    void printTree(Node* node, string prefix = "", bool isLeft = true) {
        if (node == nullptr)
            return;

        cout << prefix;
        cout << (isLeft ? "|-- " : "`-- ");
        cout << static_cast<char>(node->key) << endl;

        string newPrefix = prefix + (isLeft ? "|   " : "    ");
        printTree(node->left, newPrefix, true);
        printTree(node->right, newPrefix, false);
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(char key) {
        root = insert(root, key);
    }

    void displayPreOrder() {
        clearScreen();
        cout << "Pre-order traversal: ";
        preOrder(root);
        cout << endl;
    }

    void displayInOrder() {
        clearScreen();
        cout << "In-order traversal: ";
        inOrder(root);
        cout << endl;
    }

    void displayPostOrder() {
        clearScreen();
        cout << "Post-order traversal: ";
        postOrder(root);
        cout << endl;
    }

    void displayTreeStructure() {
        clearScreen();
        cout << "\nStruktur Tree:\n";
        printTree(root);
    }

    void clearTree() {
        clear(root);
        root = nullptr;
    }

    ~BinarySearchTree() {
        clearTree();
    }

    void clearScreen() {
#ifdef _WIN32
        system("CLS");
#else
        system("clear");
#endif
    }
};

int main() {
    BinarySearchTree bst;
    int n;
    char key;
    char choice;

    do {
        cout << "\nPilih opsi:\n";
        cout << "1. Masukkan huruf acak ke dalam tree\n";
        cout << "2. Masukkan huruf manual ke dalam tree\n";
        cout << "3. Pre-order traversal\n";
        cout << "4. In-order traversal\n";
        cout << "5. Post-order traversal\n";
        cout << "6. Tampilkan Struktur Tree\n";
        cout << "7. Bersihkan Tree\n";
        cout << "8. Keluar\n";
        cout << "Masukkan pilihan Anda: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
          case '1':
                cout << "Masukkan jumlah huruf yang ingin dimasukkan: ";
                cin >> n;
                srand(time(0));
                cout << "Huruf yang dimasukkan ke dalam tree: ";
                for (int i = 0; i < n; i++) {
                    key = 'A' + rand() % 26; 
                    cout << key << " ";
                    bst.insert(key);
                }
                cout << endl;
                break; 
            case '2': {
    char continueInput;
    do {
        cout << "Masukkan sebuah huruf (atau '0' untuk kembali ke menu): ";
        string input;
        getline(cin, input);
        
        if (!input.empty()) {
            key = toupper(input[0]);
            if (key == '0') {
                cout << "Kembali ke menu utama.\n";
                break;
            } else if (isalpha(key)) {
                bst.insert(key);
                cout << "Huruf '" << key << "' telah dimasukkan ke dalam tree.\n";
                
                cout << "Ingin memasukkan huruf lagi? (y/n): ";
                string continueChoice;
                getline(cin, continueChoice);
                if (continueChoice.empty() || tolower(continueChoice[0]) != 'y') {
                    break;
                }
            } else {
                cout << "Input tidak valid. Mohon masukkan huruf saja.\n";
            }
        }
    } while (true);
    break;
} 
            case '3':
                bst.displayPreOrder();
                break;
            case '4':
                bst.displayInOrder();
                break;
            case '5':
                bst.displayPostOrder();
                break;
            case '6':
                bst.displayTreeStructure();
                break;
            case '7':
                bst.clearTree();
                cout << "Tree telah dibersihkan.\n";
                break;
            case '8':
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (choice != '8');

    return 0;
}