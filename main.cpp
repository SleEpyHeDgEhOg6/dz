#include <iostream>
#include <initializer_list>
#include <fstream>

struct Node {
    int data; //хранимое значение
    Node* left; //указатель на левое поддерево
    Node* right; //указателб на правое поддерево

    Node(int v) : data(v), left(nullptr), right(nullptr) {}
};

class BSTree {
private:
    Node* root;

    void delete_tree(Node* ot) { 
        if (ot) {
            delete_tree(ot->left);
            delete_tree(ot->right);
            delete ot;
        }
    }

    bool add_element(Node*& ty, int hg) { // функция добавления
        if (!ty) {
            ty = new Node(hg); //если пустой,то создаем новый 
            return true;
        }
        if (hg < ty->data) { //если значение меньше,то идем и добавляем в левое поддерево
            return add_element(ty->left, hg);
        } else if (hg > ty->data) {//если значение меньше,то идем и добавляем в правое поддерево
            return add_element(ty->right, hg);
        }
        return false; //если равно,то такое уже есть 
    }

    bool delete_element(Node*& ot, int w) { //функция удаления
        if (!ot) return false;//если пуст,то есть дошли до конца ветки,значит ничего не найдено

        if (w < ot->data) {//если искомое значение меньше,то ищем его в левом поддереве,а если больше, то вправом поддереве 
            return delete_element(ot->left, w);
        } else if (w > ot->data) {
            return delete_element(ot->right, w);
        } 
    }

    bool find_element(Node* ot, int t) { //функция поиска элемента
        if (!ot) return false;//если пуст,то есть дошли до конца ветки,значит ничего не найдено
        if (t < ot->data) {
            return find_element(ot->left, t);
        } else if (t > ot->data) {
            return find_element(ot->right, t);
        }
        return true; 
    }

    void print(Node* ot) {// функция вывода дерева в консоль
        if (ot) {
            print(ot->left);
            std::cout << ot->data << " ";
            print(ot->right);
        }
    }

    bool save_to_file(Node* ot, std::ofstream& file) {// функция сохранения в файл
        if (ot) {
            file << ot->data << " ";//записываем значение текущего элемента в файл
            save_to_file(ot->left, file);
            save_to_file(ot->right, file);
        }
    }

    bool load_from_file(Node*& ot, std::ifstream& file) { // функция загрузки из файла
        int k;
        while (file >> k) {
            add_element(ot, k);
        }
    }

public:
    BSTree() : root(nullptr) {}

    BSTree(std::initializer_list<int> list) : root(nullptr) {
        for (int value : list) {
            add_element(root, value);
        }
    }

    bool add_element(int value) {
        return add_element(root, value);
    }

    bool delete_element(int value) {
        return delete_element(root, value);
    }

    bool find_element(int value) {
        return find_element(root, value);
    }

    void print() {
        print(root);
        std::cout << std::endl;
    }

    bool save_to_file(const std::string& path) {
        std::ofstream file(path);
        if (!file.is_open()) return false;
        save_to_file(root, file);
        file.close();
        return true;
    }

    bool load_from_file(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) return false;
        load_from_file(root, file);
        file.close();
        return true;
    }

    ~BSTree() {
        delete_tree(root);
    }
};

int main() {
    BSTree tree;
    
    tree.add_element(50);
    tree.add_element(30);
    tree.add_element(70);
    tree.add_element(20);
    tree.add_element(40);
    tree.add_element(60);
    tree.add_element(80);
    
    std::cout << "Дерево после добавления: ";
    tree.print(); 
    
    int ol = 40;
    std::cout << "Элемент " << ol << (tree.find_element(ol) ? " найден" : " не найден") << std::endl;
    
    tree.delete_element(30);
    std::cout << "Дерево после удаления 30: ";
    tree.print();
    
    tree.save_to_file("tree_data.txt");
    std::cout << "Дерево сохранено в файл" << std::endl;
    
    BSTree newTree;
    newTree.load_from_file("tree_data.txt");
    std::cout << "Новое дерево после загрузки: ";
    newTree.print();
    
    BSTree initTree = {15, 10, 20, 5, 12, 17, 25};
    std::cout << "Дерево из initializer_list: ";
    initTree.print();
    
    return 0;
}
