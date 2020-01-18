# C++ Compile time Brainfuck interpreter
This library could be used to run a [Brainfuck](https://en.wikipedia.org/wiki/Brainfuck) program at compile time using user-defined string literal operator templates (gcc/clang extension) or a simple function.

## Examples

Simple hello world.
```cpp
constexpr auto hello_world = "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++."_bf;
// hello_world has std::array<char, N> type.
std::cout << std::string(hello_world.begin(), hello_world.end()) << std::endl;
```

Reverse input.
```cpp
constexpr auto reversed = "+[>,]+[<.-]"_bfi << "fbppc";
```

A branfuck interpreter that takes a brainfuck program as input.
http://www.hevanet.com/cristofd/brainfuck/dbfi.b
```cpp
constexpr auto bf_in_bf = bf<1000, 5>(
          ">>>+[[-]>>[-]++>+>+++++++[<++++>>++<-]++>>+>+>+++++[>++>++++++<<-]+>>>,<++[[>["
          "->>]<[>>]<<-]<[<]<+>>[>]>[<+>-[[<+>-]>]<[[[-]<]++<-[<+++++++++>[<->-]>>]>>]]<<"
          "]<]<[[<]>[[>]>>[>>]+[<<]<[<]<+>>-]>[>]+[->>]<<<<[[<<]<[<]+<<[+>+<<-[>-->+<<-[>"
          "+<[>>+<<-]]]>[<+>-]<]++>>-->[>]>>[>>]]<<[>>+<[[<]<]>[[<<]<[<]+[-<+>>-[<<+>++>-"
          "[<->[<<+>>-]]]<[>+<-]>]>[>]>]>[>>]>>]<<[>>+>>+>>]<<[->>>>>>>>]<<[>.>>>>>>>]<<["
          ">->>>>>]<<[>,>>>]<<[>+>]<<[+<<]<]",
          "+[>,]+[<.-]!abc");
```

### Try online
https://godbolt.org/z/VsiPME
