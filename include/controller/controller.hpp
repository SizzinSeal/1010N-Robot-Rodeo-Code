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
template <typename in, typename out> class AbstractController {
    public:
        virtual out step(in) = 0;
};
