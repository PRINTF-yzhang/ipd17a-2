#pragma once

#include <array>
#include <climits>
#include <cstdint>
#include <string>

class Sbox_hash
{
public:
    Sbox_hash();
    uint64_t operator()(std::string const&) const;

private:
    //Char_bit. Number of Bits in a character.
    //processing the string one character at a time
    //left shift: computing the number of bits in the character
    static constexpr size_t size_ = 1 << CHAR_BIT;
    //fixed sized array size is known to compile time
    //256 unsigned integers
    std::array<uint64_t, size_> sbox_;
};
