#include "Various_hashes.h"
#include "Sbox_hash.h"

#include <catch.hxx>

Sbox_hash const hash1, hash2;
char const* const message1 = "Hello, world";
char const* const message2 = "Hello, world!";

TEST_CASE("Deterministic")
{
    CHECK(hash1(message1) == hash1(message1));
    CHECK(hash1(message2) == hash1(message2));
    CHECK(hash2(message1) == hash2(message1));
    CHECK(hash2(message2) == hash2(message2));
}

// Could fail, but very unlikely...
TEST_CASE("DifferentStrings")
{
    CHECK(hash1(message1) != hash1(message2));
    CHECK(hash2(message1) != hash2(message2));
}

// Could fail, but very unlikely...
TEST_CASE("DifferentFunctions")
{
    CHECK(hash1(message1) != hash2(message1));
    CHECK(hash1(message2) != hash2(message2));
}


/*
 * 17.a.1
 *
 * telephone
 * telegraph
 * telescope
 *
 * telescope
 * microscope
 * arthroscope
 *
 * good for first, bad for second:
 * hash function takes the last character
 *
 * bad for first, good for second
 * hash function takes the first character
 *
 * good for both
 * hash function takes the fifth character
 *
 * 17.a.3
 *
 * unsigned char hash1(unsigned char c) {
  return c;
}

unsigned char hash2(unsigned char c) {
  return 255-c;
}


 unsigned char hash3(unsigned char c) {
  return c | 1;
}

1 ^ 0 = 1
 unsigned char hash4(unsigned char c) {
  return c ^ 255;
}
1 ^ 1 = 0
unsigned char hash5(unsigned char c) {
  return c ^ c;
}


 | x | y | x ^ y |
|---|---|-------|
| 0 | 0 | 0     |
| 0 | 1 | 1     |
| 1 | 0 | 1     |
| 1 | 1 | 0     |



 17.a.4
 substitution-box hashing
 we're going to take sets of bits that come in and the hash code
 then substitute them for random other bits that we're gonna set up

 */


