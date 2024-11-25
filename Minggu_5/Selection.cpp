#include "Check.h"
#include "MenuLokal.h"
#include "Node.h"
#include "limits"
#include <chrono>

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

#define duration(a)                                                            \
  std::chrono::duration_cast<std::chrono::nanoseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()
int pep = 0;
bool value = false;
class Selection {
private:
  Node *next;
  Node *front;
  Node *rear;
  int angka;

public:
  Selection() : front(nullptr), rear(nullptr) {}
  void Membersihkan() {
    while (front != nullptr) {
      Node *temp = front;
      front = front->getNext();
      delete temp;
    }
    rear = nullptr;
    angka = 0;
    std::cout << "Semua Node sudah terbersihkan" << std::endl;
  }
  void hintSortSelection() {
    if (front == nullptr) {
      cout << "List Kosong";
      return;
    }

    Node *sortedFront = nullptr;
    Node *sortedRear = nullptr;
    int step = 1;

    while (front != nullptr) {

      cout << "Current list: ";
      Node *temp = front;
      while (temp != nullptr) {
        cout << temp->getValue() << " ";
        temp = temp->getNext();
      }
      cout << "\n";

      // Find the minimum node
      Node *minNode = front;
      Node *prevMin = nullptr;
      Node *current = front;
      Node *prev = nullptr;
      pep++;
      while (current != nullptr) {
        std::cout << "\nPerulangan Ke - " << pep;
        pep++;
        std::cout << "\nStep " << step << ":\n";
        if (current->getValue() < minNode->getValue()) {
          minNode = current;
          prevMin = prev;
        }
        prev = current;
        current = current->getNext();
      }

      cout << "Minimum value found: " << minNode->getValue() << "\n";

      // Remove minNode from the unsorted list
      if (prevMin == nullptr) {
        front = front->getNext();
      } else {
        prevMin->setNext(minNode->getNext());
      }

      // Add minNode to the sorted list
      minNode->setNext(nullptr);
      if (sortedFront == nullptr) {
        sortedFront = sortedRear = minNode;
      } else {
        sortedRear->setNext(minNode);
        sortedRear = minNode;
      }

      cout << "Sorted list so far: ";
      temp = sortedFront;
      while (temp != nullptr) {
        cout << temp->getValue() << " ";
        temp = temp->getNext();
      }
      cout << "\n";

      step++;
    }

    // Update the front and rear of the main list
    front = sortedFront;
    rear = sortedRear;

    cout << "\nFinal sorted list: ";
    Node *temp = front;
    while (temp != nullptr) {
      cout << temp->getValue() << " ";
      temp = temp->getNext();
    }
    cout << "\n";
  }
  void sortSelection(bool showhint = false) {
    value = false;
    if (showhint) {
      hintSortSelection();
    }
    if (front == nullptr) {
      cout << "List Kosong";
      return;
    }

    Node *sortedFront = nullptr;
    Node *sortedRear = nullptr;

    while (front != nullptr) {

      // Find the minimum node
      Node *minNode = front;
      Node *prevMin = nullptr;
      Node *current = front;
      Node *prev = nullptr;

      while (current != nullptr) {
        if (current->getValue() < minNode->getValue()) {
          minNode = current;
          prevMin = prev;
        }
        prev = current;
        current = current->getNext();
      }

      // Remove minNode from the unsorted list
      if (prevMin == nullptr) {
        front = front->getNext();
      } else {
        prevMin->setNext(minNode->getNext());
      }

      // Add minNode to the sorted list
      minNode->setNext(nullptr);
      if (sortedFront == nullptr) {
        sortedFront = sortedRear = minNode;
      } else {
        sortedRear->setNext(minNode);
        sortedRear = minNode;
      }
    }

    // Update the front and rear of the main list
    front = sortedFront;
    rear = sortedRear;
  }
  void Mengacak(int angka) {

    if (front != 0 && !value) {
      value = true;
      mengacak_pilih(angka);
    }
    if (front != 0 && value) {
      Check check;
      check.ClearSystem();
      std::cout << "anda sudah melakukan pengacakan!";
    }
    if (front == 0) {
      std::cout << "Melakukan Pengisian Angka\n"
                << "Content Sekarang : " << front << endl;
      for (int i = 1; i < angka + 1; i++) {
        Node *newNode = new Node(i);
        if (rear == nullptr) {
          front = rear = newNode;
        } else {
          rear->setNext(newNode);
          rear = newNode;
        }
      }
    }
  }
  void mengacak_manual(int angka) {

    int value = 0;
    for (int i = 1; i < angka + 1; i++) {
      std::cout << "Index" << "[" << i << "] :";
      std::cin >> value;
      Node *newNode = new Node(value);
      if (rear == nullptr) {
        front = rear = newNode;
      } else {
        rear->setNext(newNode);
        rear = newNode;
      }
    }
    return;
  }
  void mengacak_pilih(int angka) {
    if (front == nullptr) {
      cout << "List Kosong!";
      return;
    }

    if (angka <= 0) {
      cout << "No elements to select from!";
      return;
    }

    for (int i = 0; i < angka; i++) {
      int randomIndex = rand() % angka;

      Node *prev1 = nullptr, *prev2 = nullptr;
      Node *node1 = front, *node2 = front;
      int pos1 = 0, pos2 = 0;

      while (node1 != nullptr && pos1 != i) {
        prev1 = node1;
        node1 = node1->getNext();
        pos1++;
      }
      while (node2 != nullptr && pos2 != randomIndex) {
        prev2 = node2;
        node2 = node2->getNext();
        pos2++;
      }

      if (node1 == nullptr || node2 == nullptr) {
        cout << "Invalid indices for swapping." << endl;
        return;
      }

      if (prev1 != nullptr)
        prev1->setNext(node2);
      else
        front = node2;

      if (prev2 != nullptr)
        prev2->setNext(node1);
      else
        front = node1;

      Node *temp = node1->getNext();
      node1->setNext(node2->getNext());
      node2->setNext(temp);

      if (node1->getNext() == nullptr)
        rear = node1;
      if (node2->getNext() == nullptr)
        rear = node2;

      cout << "Swapped elements at indices " << i << " and " << randomIndex
           << endl;
    }
    cin.get();
  }

  void display() {
    Check check;
    Node *current = front;
    check.ClearSystem();
    if (front == nullptr) {

      cout << "Queue is empty!" << endl;
      return;
    }
    cout << "Queue contents: ";
    while (current != nullptr) {
      cout << current->getValue() << " ";
      current = current->getNext();
    }
    return;
  }
};

int main() {
  int value = 0;
  bool g = false;
  bool simpan1 = false, simpan2 = false;
  Selection selection;
  std::vector<std::string> options2 = {"Hint", "Random", "Bersihkan", "Back"};
  Check check;
  check.ClearSystem();
  do {
    std::vector<std::string> options = {"Selection", "Peraturan", "Display",
                                        "Exit"};
    Menu menu(options);
    int choice = menu.run();
    switch (choice) {
    case 0: {
      if (!g) {
        menu.reset_for_input();
        cout << "Masukkan jumlah index yang diinginkan: \n";
        while (!(std::cin >> value)) {
          std::cout << value;
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cout << "Invalid input. Silahkan masukkan Angka: ";
        }
        g = true;
        menu.init_for_menu();
      }

      menu.reset_for_input();
      if (simpan2) {
        selection.Mengacak(value);
        cin.get();
      } else {
        selection.mengacak_manual(value);
      }
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      char response;
      Check check;
      check.ClearSystem();
      std::cout << "Melakukan Sorting! / y/n \n";
      std::cin >> response;
      switch (response) {
      case 'y': {

        auto t1 = high_resolution_clock::now();
        selection.sortSelection(simpan1);
        auto t2 = high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1)
                .count();
        std::cout << "Durasi : " << duration << "Milidetik" << "\n";
        cin.get();
      }
      case 'n':
        break;
      }
      menu.init_for_menu();
      break;
    }
    case 1: {
      bool exitSubMenu = false;
      while (!exitSubMenu) {
        Check check;
        Menu menu(options2);
        int subChoice = menu.run();
        switch (subChoice) {
        case 0: // Hints
          simpan1 = !simpan1;
          options2[0] = simpan1 ? "Hint [*]" : "Hint";
          break;
        case 1: // Random
          simpan2 = !simpan2;
          options2[1] = simpan2 ? "Random [*]" : "Random";
          break;
        case 2: // Bersihkan
          selection.Membersihkan();
          g = false; // Reset g so that the user can input a new value
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cin.get();
          menu.init_for_menu();
          break;
        case 3:
          exitSubMenu = true;
          break;
        }
        if (!exitSubMenu) {
          check.ClearSystem();
        }
      }
      break;
    }
    case 2:
      menu.reset_for_input();
      selection.display();
      std::cout << "\nPress Enter to continue...";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin.get();
      menu.init_for_menu();
      break;
    case 3:
      exit(0);
    default:
      break;
    }
  } while (true);
}
