#include <iostream>
#include <rxcpp/rx.hpp>
#include <memory>
#include <bonsai-cpp/block.h>

namespace bonsai
{
    namespace blockchain
    {

        template <typename T>
        class BlockGenerator
        {
        public:
            static rxcpp::observable<std::shared_ptr<IBlock<T>>> Generate(
                rxcpp::observable<std::shared_ptr<IBlock<T>>> genesis,
                std::function<rxcpp::observable<std::shared_ptr<IBlock<T>>>(rxcpp::observable<std::shared_ptr<IBlock<T>>>)> function)
            {

                return rxcpp::observable<>::create<std::shared_ptr<IBlock<T>>>([genesis, function](rxcpp::subscriber<std::shared_ptr<IBlock<T>>> observer)
                                                                               {
            auto subject = rxcpp::subjects::subject<std::shared_ptr<IBlock<T>>>();

            // Applying the function to the subject, observing on a new thread
            auto loopFunc = function(subject.get_observable().observe_on(rxcpp::observe_on_new_thread()));

            // Subscribing to the loopFunc, forwarding its emissions to the subject
            auto loopSub = loopFunc.subscribe(
                subject.get_subscriber().get_observer().on_next,
                subject.get_subscriber().get_observer().on_error,
                [](){} // No completion action
            );

            // Subscribing the observer to the subject to receive its emissions
            auto outerSub = subject.get_observable().subscribe(observer);

            // Starting the process by subscribing the genesis observable to the subject
            auto genesisSub = genesis.subscribe(subject.get_subscriber());

            // CompositeDisposable to manage the subscriptions
            rxcpp::composite_subscription composite;
            composite.add(loopSub);
            composite.add(outerSub);
            composite.add(genesisSub);

            // Add the composite to the observer to ensure it gets disposed
            observer.add(composite); });
            }
        };
    } // namespace blockchain
} // namespace bonsai