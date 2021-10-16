#ifndef BST_MAP_H_
#define BST_MAP_H_

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::pair;
using std::vector;

template <typename Key, typename Value>
class BinarySearchTree
{
    struct Node
    {
        Key key;
        Value value;
        Node *left, *right;
        Node(const Key &key) : key(key), left(nullptr), right(nullptr) {}
        Node(const Key &key, const Value &value) : value(value), key(key), left(nullptr), right(nullptr) {}

        void print(int depth)
        {
            if (left != nullptr)
            {
                left->print(depth + 1);
            }
            for (int i = 0; i < depth; i++)
            {
                cout << "  ";
            }
            cout << key << ": " << value << endl;
            if (right != nullptr)
            {
                right->print(depth + 1);
            }
        }

        bool contains(const Key &k)
        {
            if (key == k)
            {
                return true;
            }
            else if (k < key)
            {
                if (left == nullptr)
                {
                    return false;
                }
                else
                {
                    return left->contains(k);
                }
            }
            else //v > value
            {
                if (right == nullptr)
                {
                    return false;
                }
                else
                {
                    return right->contains(k);
                }
            }
        }

        bool insert(const Key &new_key, const Value &new_value)
        {
            if (new_key == key)
            {
                return false;
            }
            else if (new_key < key)
            { // Need to insert to the left
                if (left == nullptr)
                {
                    left = new Node(new_key, new_value);
                    return true;
                }
                else
                {
                    return left->insert(new_key, new_value);
                }
            }
            else
            { // if (new_value > value)  Need to insert to the right
                if (right == nullptr)
                {
                    right = new Node(new_key, new_value);
                    return true;
                }
                else
                {
                    return right->insert(new_key, new_value);
                }
            }
        }

        Value &operator[](const Key &k)
        {
            if (k == key)
            {
                return value;
            }
            else if (k < key)
            {
                if (left == nullptr)
                {
                    left = new Node(k);
                    return left->value;
                }
                else
                {
                    return (*left)[k];
                }
            }
            else //if (k > key)
            {
                if (right == nullptr)
                {
                    right = new Node(k);
                    return right->value;
                }
                else
                {
                    return (*right)[k];
                }
            }
        }
        //helper function to find the largest node in the left subtree
        const Node *largest_node()
        {
            Node *largest;
            for (largest = this; largest->right != nullptr; largest = largest->right)
            {
            }
            return largest;
        }
        static int _erase(const Key &k, Node **node_ptr)
        {
            //const ptr, but can change what it points to
            Node *node = *node_ptr;
            if (node == nullptr)
            {
                return 0;

            } //move to the node key == k
            else if (k < node->key)
            {
                return _erase(k, &node->left);
            }
            else if (k > node->key)
            {
                return _erase(k, &node->right);
            }
            else //when find key == k
            {
                //if the node we want to delete is leaf
                if (node->left == nullptr && node->right == nullptr)
                {
                    *node_ptr = nullptr;
                    delete node;
                    return 1;
                } //if node has one child
                else if (node->left == nullptr)
                {
                    *node_ptr = node->right;
                    delete node;
                    return 1;
                }
                else if (node->right == nullptr)
                {
                    *node_ptr = node->left;
                    delete node;
                    return 1;
                }
                else
                { //if node has two children
                    const Node *largest = node->left->largest_node();
                    //copy largest key and value to node, then find largest subtress's largest node
                    node->key = largest->key;
                    node->value = largest->value;
                    return _erase(node->key, &node->left);
                }
            }
        }
    };

public:
    Node *root;
    BinarySearchTree() : root(nullptr) {}

    ~BinarySearchTree()
    {
        delete root;
    }
    class Iterator
    {
        vector<Node *> stack;

    public:
        // constructor
        Iterator() {}
        Iterator(Node *root)
        {
            for (Node *cur = root; cur != nullptr; cur = cur->left)
            {
                stack.push_back(cur);
            }
        }
        // compare (!=)
        bool operator!=(const Iterator &rhs) const
        {
            return stack != rhs.stack;
        }
        // dereference (*)
        pair<Key, Value> operator*() const
        {
            Node *top = stack.back();
            return pair<Key, Value>(top->key, top->value);
        }
        // increment (++)
        Iterator &operator++()
        {
            Node *cur = stack.back()->right;
            stack.pop_back();
            for (; cur != nullptr; cur = cur->left)
            {
                stack.push_back(cur);
            }
            return *this;
        }

        // This is for demo purposes only, to show how Iterator works.
        void print_stack_keys()
        {
            for (const Node *cur : stack)
            {
                cout << cur->key << ' ';
            }
            cout << endl;
        }
    };
    void print()
    {
        if (root != nullptr)
        {
            root->print(0);
        }
    }

    bool insert(const Key &key, const Value &value)
    {
        if (root == nullptr)
        {
            root = new Node(key, value);
            return true;
        }
        else
        {
            return root->insert(key, value);
        }
    }

    bool contains(const Key &key)
    {
        if (root == nullptr)
        {
            return false;
        }
        else
        {
            return root->contains(key);
        }
    }

    Value &operator[](const Key &key)
    {
        if (root == nullptr)
        {
            root = new Node(key);
            return root->value;
        }
        else
        {
            return (*root)[key];
        }
    }

    int erase(const Key &key)
    {
        if (!contains(key))
        {
            return 0;
        }
        return Node::_erase(key, &root);
    }
};
#endif /* BST_H_ */