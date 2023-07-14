#include <iostream>
#include "bin_tree.h"
#include <string>

int main() {
    std::cout << "Create a binary tree: \n";
    BinTree<int, std::string> tree;
    tree.add(1, "One");
    tree.add(2, "two");
    tree.add(3, "three");
    tree.add(0, "Zero");
    tree.add(10, "Ten");
    tree.add(1, "One");
    tree.add(1, "One");
    tree.add(10, "Ten");
    tree.print();
    std::cout << "Lets see if the tree contains key 5: "
              << (tree.contains(5) ? "Yes" : "No") << std::endl;
    std::cout << "Well, lets add 5 to the tree:\n";
    tree.add(5, "five");
    std::cout << "Let's see if it contains now: "
              << (tree.contains(5) ? "Yes" : "No") << std::endl;
    std::cout << "We want to be sure: " << std::endl;
    tree.print();
    std::cout << "Looks like it's to many ones here. Let's delete them:\n";
    tree.remove(1);
    tree.print();
    return 0;
}
