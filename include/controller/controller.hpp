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
template <typename In, typename Out> class AbstractController {
    public:
        /**
         * @brief Update the controller
         *
         * @param in the input to the controller
         *
         * @return out the output of the controller
         */
        virtual Out update(In input) = 0;
};
