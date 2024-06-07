#pragma once

/**
 * @brief Abstract controller class
 *
 * This is used to allow the user to define their own controllers to be used
 * with LemLib. It's templated to allow for any input/output type.
 *
 * @tparam in the type of the input
 * @tparam out the type of the output
 */
template <typename In, typename Out> class Controller {
    public:
        /**
         * @brief Update the controller
         *
         * @param in the input to the controller
         *
         * @return out the output of the controller
         */
        virtual Out update(In input) = 0;

        /**
         * @brief Reset the controller
         *
         * This is used to reset the controller to some initial state.
         */
        virtual void reset() = 0;

        /**
         * @brief Destroy the Controller object
         *
         */
        virtual ~Controller() {}
};
