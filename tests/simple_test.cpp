#include "cppbf.hpp"

template <std::size_t N, std::size_t M>
constexpr bool compare(const std::array<char, N> &output, const char (&expected)[M]) noexcept {
    for (std::size_t i = 0; i < M - 1; ++i) {
        if (output[i] != expected[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    using namespace cppbf;
    /* Simple hello world */
    constexpr auto hello_world = "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++."_bf;
    static_assert(compare(hello_world, "Hello World!"));

    /* Reverse input */
    constexpr auto reversed = "+[>,]+[<.-]"_bfi << "desrever";
    static_assert(compare(reversed, "reversed"));

    /* Same but using bf() function */
    constexpr auto reversed2 = bf("+[>,]+[<.-]", "desrever");
    static_assert(compare(reversed2, "reversed"));

    /* A branfuck interpreter that takes a brainfuck program as input.
     * http://www.hevanet.com/cristofd/brainfuck/dbfi.b
     */
    constexpr auto bf_in_bf = bf<1000, 5>(
        ">>>+[[-]>>[-]++>+>+++++++[<++++>>++<-]++>>+>+>+++++[>++>++++++<<-]+>>>,<++[[>["
        "->>]<[>>]<<-]<[<]<+>>[>]>[<+>-[[<+>-]>]<[[[-]<]++<-[<+++++++++>[<->-]>>]>>]]<<"
        "]<]<[[<]>[[>]>>[>>]+[<<]<[<]<+>>-]>[>]+[->>]<<<<[[<<]<[<]+<<[+>+<<-[>-->+<<-[>"
        "+<[>>+<<-]]]>[<+>-]<]++>>-->[>]>>[>>]]<<[>>+<[[<]<]>[[<<]<[<]+[-<+>>-[<<+>++>-"
        "[<->[<<+>>-]]]<[>+<-]>]>[>]>]>[>>]>>]<<[>>+>>+>>]<<[->>>>>>>>]<<[>.>>>>>>>]<<["
        ">->>>>>]<<[>,>>>]<<[>+>]<<[+<<]<]",
        "+[>,]+[<.-]!abc");
    static_assert(compare(bf_in_bf, "cba"));

}
