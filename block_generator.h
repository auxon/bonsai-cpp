#ifndef BONSAI_BLOCKCHAIN_BLOCK_GENERATOR_H
#define BONSAI_BLOCKCHAIN_BLOCK_GENERATOR_H

#include <rxcpp/rx.hpp>
#include <memory>
#include <bonsai-cpp/block.h>

namespace bonsai {
namespace blockchain {

template<typename T>
class BlockGenerator {
public:
    static rxcpp::observable<std::shared_ptr<IBlock<T>>> Generate(
        rxcpp::observable<std::shared_ptr<IBlock<T>>> genesis,
        std::function<rxcpp::observable<std::shared_ptr<IBlock<T>>>(rxcpp::observable<std::shared_ptr<IBlock<T>>>)> function);
};

} // namespace blockchain
} // namespace bonsai

#endif // BONSAI_BLOCKCHAIN_BLOCK_GENERATOR_H