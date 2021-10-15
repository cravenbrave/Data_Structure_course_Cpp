#include <memory>
#include <cassert>
#include <iostream>
#include <string>

namespace cs2c
{

    template <typename T>
    class Bag
    {
    public:
        class Node
        {
        private:
            T value_;
            Node *left_, right_;
            Node(const T &value) : value_(value), left_(nullptr), right_(nullptr) {}

        public:
            ~Node()
            {
                delete left_;
                delete right_;
                left_ = nullptr;
                right_ = nullptr;
            }
            // left getter
            Node *left()
            {
                return left_;
            }
            // right getter
            Node *right()
            {
                return right_;
            }

            const T &value() const
            {
                return value_;
            }

            friend class Bag<T>;
        };

    private:
        Node* root_;
        int size_;

        int count(Node *cur, const T &value) const
        {
            if (cur == nullptr)
            {
                return 0; // return 0 since nullptr cannot have the value
            }
            else if (value == cur->value_)
            {
                return count(cur->left_, value) + count(cur->right_, value) + 1;
            }
            else if (value < cur->value_)
            {
                return count(cur->left_, value);
            }
            else
            {
                return count(cur->right_, value);
            }
        }

        // Remove the node with the greatest value in the left subtree and return a
        // unique_ptr to it.
        static std::unique_ptr<Node> extract_greatest_in_left_subtree(Node *cur)
        {
            std::unique_ptr<Node> greatest;
            Node *c, *largestNode;
            largestNode = cur;
            for (c = cur; c->right_.get() != nullptr; c = c->right_.get())
            {
                if (c->value_ > largestNode->value_)
                {
                    largestNode = c;
                }
            }
            greatest.reset(largestNode);
            // std::cout << "hereL " << largestNode->value_ << std::endl;
            return greatest;
        }

        // Remove the node with the smallest value in the right subtree and return a
        // unique_ptr to it.
        static std::unique_ptr<Node> extract_least_in_right_subtree(Node *cur)
        {
            std::unique_ptr<Node> least;
            Node *c, *leastNode;
            leastNode = cur;
            for (c = cur; c->left_.get() != nullptr; c = c->left_.get())
            {
                if (leastNode->value_ > c->value_)
                {
                    leastNode = c;
                }
            }
            least.reset(leastNode);
            std::cout << "hereS " << leastNode->value_ << std::endl;
            return least;
        }

        int remove(Node *prev, Node *cur, const T &value)
        {
            if (cur == nullptr)
            {
                return 0; // base case
            }
            else if (value == cur->value_)
            {
                // We need to remove cur and any children nodes with the same value...
                int num_removed = (remove(cur, cur->left_.get(), value) +
                                   remove(cur, cur->right_.get(), value));

                // Find a replacement leaf node, unless cur is a leaf.
                std::unique_ptr<Node> replacement;
                if (cur->left_ == nullptr && cur->right_ == nullptr)
                {
                }
                else if (cur->left_ == nullptr)
                {
                    replacement = extract_least_in_right_subtree(cur->right_.get());
                }
                else if (cur->right_ == nullptr)
                {
                    replacement = extract_greatest_in_left_subtree(cur->left_.get());
                }
                else
                { //if it has two children, pick the largest element on the left
                    replacement = extract_least_in_right_subtree(cur->right_.get());
                    //    replacement->left_ = extract_greatest_in_left_subtree(cur);
                }

                // If there is a replacement, then move cur's children to the replacement
                if (replacement != nullptr)
                {
                    std::cout << "______Here_____" << std::endl;
                    // print(0,replacement.get());
                    // std::cout << "______Here_____" << std::endl;
                    // assert(replacement->left_ == nullptr);
                    // assert(replacement->right_ == nullptr);
                    // replacement->left_.reset(cur->left_.release());
                    // replacement->right_.reset(cur->right_.release());
                }

                // Make cur's parent node (prev) point to the replacement
                if (prev == nullptr)
                {
                    root_.reset(replacement.release());
                }
                else if (prev->left_.get() == cur)
                {
                    prev->left_.reset(replacement.release());
                }
                else
                { // if (prev->right_.get() == cur)
                    prev->right_.reset(replacement.release());
                }
                assert(replacement == nullptr);
                --size_;
                return num_removed + 1;
            }
            else if (value < cur->value_)
            {
                return remove(cur, cur->left_.get(), value);
            }
            else
            { // if (value > cur->value_)
                return remove(cur, cur->right_.get(), value);
            }
        }

        void print(int depth, Node *cur)
        {
            if (cur->left_.get() != nullptr)
            {
                print(depth + 1, cur->left_.get());
            }
            for (int i = 0; i < depth; i++)
            {
                std::cout << "~ ";
            }
            std::cout << cur->value_ << std::endl;
            if (cur->right_.get() != nullptr)
            {
                print(depth + 1, cur->right_.get());
            }
        }

    public:
        Bag() : size_(0) {}

        void insert(const T &value)
        {
            std::unique_ptr<Node> *cur;
            for (cur = &root_;
                 cur->get() != nullptr;
                 cur = value < (*cur)->value_ ? &(*cur)->left_ : &(*cur)->right_)
                ;
            cur->reset(new Node(value)); // actually insert the value
            ++size_;
        }

        int remove(const T &value)
        {
            return remove(nullptr, root_.get(), value);
        }

        int count(const T &value) const
        {
            return count(root_.get(), value);
        }

        bool contains(const T &value) const
        {
            return count(value) != 0;
        }

        int size()
        {
            return size_;
        }

        Node *root()
        {
            return root_.get();
        }

        void print()
        {
            if (root() != nullptr)
            {
                print(0, root());
            }
        }
    };

} // namespace cs2c