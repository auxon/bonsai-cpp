#include <bonsai-cpp/block.h>

namespace bonsai
{
    namespace blockchain
    {

        template <typename T>
        class Block : public IBlock<T>
        {
        public:
            // Constructor that takes an int (or any T type) parameter
            Block(T value) : data(value) {
                // Constructor implementation
                // Initialize your Block with the given value
                this->data = value;
                this->parent = nullptr;
                this->child = nullptr;

            }

            Block(T value, std::shared_ptr<IBlock<T>> parent)
            {
                this->data = value;
                this->parent = parent;
                this->child = nullptr;
            }
            
            Block(T value, std::shared_ptr<IBlock<T>> parent, std::shared_ptr<IBlock<T>> child) : data(value), parent(parent), child(child) {
                // Constructor implementation
                // Initialize your Block with the given value
                this->data = value;
                this->parent = parent;
                this->child = child;
            }

            Block(const Block& other) : data(other.data), parent(other.parent), child(other.child) {
                // Copy constructor implementation
                // Copy the data, parent, and child from the other Block
                this->data = other.data;
                this->parent = other.parent;
                this->child = other.child;
            }

            // Implement IBlock methods and add Block-specific members here
            std::shared_ptr<IBlock<T>> getParent() const override
            {
                return parent;
            }
            void setParent(std::shared_ptr<IBlock<T>> parent) override
            {
                this->parent = parent;
            }
            std::shared_ptr<IBlock<T>> getChild() const override
            {
                return child;
            }
            void setChild(std::shared_ptr<IBlock<T>> child) override
            {
                this->child = child;
            }

        private:
            std::shared_ptr<IBlock<T>> parent;
            std::shared_ptr<IBlock<T>> child;
            T data; // Added to store the block's data
        };
    };
};