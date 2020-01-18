#ifndef CPPBF_H
#define CPPBF_H

#include <array>
#include <algorithm>

namespace cppbf {
namespace detail {

template <std::size_t DataSize, std::size_t OutputSize, typename Program, typename Input>
constexpr auto execute(Program program, Input input) {
    std::array<char, DataSize> data = {0};
    std::array<char, OutputSize> output = {0};
    auto output_it = output.begin();
    auto data_it = data.begin();
    auto input_it = input.begin();

    std::size_t loops = 0;
    for (auto it = program.begin(); it != program.end(); ++it) {
        if (*it == '>') {
            ++data_it;
        } else if (*it == '<') {
            --data_it;
        } else if (*it == '+') {
            ++*data_it;
        } else if (*it == '-') {
            --*data_it;
        } else if (*it == '.' ) {
            *output_it++ = *data_it;
        } else if (*it == ',') {
            *data_it = *input_it++;
        } else if (*it == '[') {
            if (*data_it == 0) {
                /* Go forward to the matching ']' */
                loops = 1;
                while (loops != 0) {
                    ++it;
                    if (*it == '[') {
                        loops++;
                    } else if (*it == ']') {
                        loops--;
                    }
                }
            }
        } else if (*it == ']') {
            if (*data_it != 0) {
                /* Go backward to the matching '[' */
                loops = 1;
                while (loops != 0) {
                    --it;
                    if (*it == ']') {
                        loops++;
                    } else if (*it == '[') {
                        loops--;
                    }
                }
            }
        }
    }
    *output_it = 0;
    return output;
}

template <std::size_t DataSize, std::size_t OutputSize, std::size_t ProgramSize, std::size_t InputSize>
constexpr auto bf_impl(std::array<char, ProgramSize> program_array, std::array<char, InputSize> input_array) {
    return execute<DataSize, OutputSize>(program_array, input_array);
}

template <typename InputIt, typename OutputIt>
constexpr OutputIt constexpr_copy(InputIt first, InputIt last, OutputIt out_first) {
    while (first != last) {
        *out_first++ = *first++;
    }
    return out_first;
}

template <typename Output>
constexpr std::size_t find_null(Output output) {
    auto it = output.begin();
    auto last = output.end();
    for (; it != last; ++it) {
        if (*it == 0) {
            return it - output.begin();
        }
    }
    return output.size();
}

template <typename Char, Char ...chars>
constexpr auto operator_bf() {
    auto program = {chars...};
    std::array<char, 0> input_array = {};
    std::array<char, sizeof...(chars)> program_array = {0};
    constexpr_copy(program.begin(), program.end(), program_array.begin());

    return bf_impl<30000, 1000>(program_array, input_array);
}

} // namespace detail

template <typename Char, Char ...chars>
constexpr auto operator""_bf() {
    constexpr auto output = detail::operator_bf<Char, chars...>();
    constexpr auto end = detail::find_null(output);
    std::array<char, end> shrinked_output = {0};
    detail::constexpr_copy(output.begin(), output.begin() + end, shrinked_output.begin());
    return shrinked_output;
}

template <typename Char, Char ...chars>
struct BrainfuckWithInput {};

template <typename Char, Char ...chars>
constexpr auto operator""_bfi() {
    return BrainfuckWithInput<Char, chars...>{};
}

template <typename Char, Char ...chars, std::size_t N>
constexpr auto operator<<(BrainfuckWithInput<Char, chars...>, const char(&input)[N]) {
    auto program = {chars...};
    std::array<char, sizeof...(chars)> program_array = {0};
    std::array<char, N> input_array = {0};

    detail::constexpr_copy(program.begin(), program.end(), program_array.begin());
    detail::constexpr_copy(input, input + N, input_array.begin());

    return detail::bf_impl<30000, 1000>(program_array, input_array);
}

template <std::size_t DataSize=30000, std::size_t OutputSize=1000, std::size_t ProgramSize, std::size_t InputSize>
constexpr auto bf(const char(&program)[ProgramSize], const char(&input)[InputSize]) {
    std::array<char, ProgramSize> program_array = {0};
    std::array<char, InputSize> input_array = {0};

    detail::constexpr_copy(program, program + ProgramSize, program_array.begin());
    detail::constexpr_copy(input, input + InputSize, input_array.begin());

    return detail::bf_impl<DataSize, OutputSize>(program_array, input_array);
}

template <std::size_t DataSize=30000, std::size_t OutputSize=1000, std::size_t ProgramSize>
constexpr auto bf(const char(&program)[ProgramSize]) {
    std::array<char, ProgramSize> program_array = {0};
    std::array<char, 0> input_array = {};

    detail::constexpr_copy(program, program + ProgramSize, program_array.begin());
    detail::constexpr_copy(program, program + ProgramSize, program_array.begin());

    return detail::bf_impl<DataSize, OutputSize>(program_array, input_array);
}

} // namespace cppbf

#endif // CPPBF_H
