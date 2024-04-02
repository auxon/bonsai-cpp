#pragma once
#include <memory>

namespace bonsai
{
    namespace blockchain
    {
        template <typename T>
        class IBlock
        {
            Block(T value);
            Block(T value, std::shared_ptr<IBlock<T>> parent);
            Block(T Value, std::shared_ptr<IBlock<T>> parent, std::shared_ptr<IBlock<T>> child);
        private:
            std::shared_ptr<IBlock<T>> parent;
            std::shared_ptr<IBlock<T>> child;
        public:
            virtual ~IBlock() = default;
            virtual std::shared_ptr<IBlock<T>> getParent() const = 0;
            virtual void setParent(std::shared_ptr<IBlock<T>> parent) = 0;
            virtual std::shared_ptr<IBlock<T>> getChild() const = 0;
            virtual void setChild(std::shared_ptr<IBlock<T>> child) = 0;
        };
    };
};
