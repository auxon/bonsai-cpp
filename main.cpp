#pragma once
#include <rxcpp/rx.hpp>
#include <bonsai-cpp/block.h>
#include <bonsai-cpp/block_generator.h>
#include <iostream>
#include <memory>

int main() {

auto genesisBlock = rxcpp::observable<>::create<Block<int>>([](rxcpp::subscriber<Block<int>> s){
            auto block1 = std::make_shared<Block<int>>(1);
            auto block2 = std::make_shared<Block<int>>(2);
            s.on_next(block1);
            s.on_next(block2);
            s.on_completed();
    });

            auto nextBlockFunction = [](std::shared_ptr<IBlock<int>> prevBlock) -> std::shared_ptr<IBlock<int>> {
                auto newBlock = std::make_shared<IBlock<int>>();
                newBlock->setParent(prevBlock);
                return newBlock;
            };
            auto blockchain = bonsai::blockchain::BlockGenerator<int>::Generate(genesisBlock, nextBlockFunction);
            blockchain.subscribe(
                [](const std::shared_ptr<IBlock<int>>& block) {
                    // Process each block
                    std::cout << "Received a block" << std::endl;
                },
                []() {
                    // OnCompleted
                    std::cout << "Blockchain generation completed" << std::endl;
                }
            );

            return 0;
        };