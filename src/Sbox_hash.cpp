#include "Sbox_hash.h"

#include <chrono>
#include <random>

using namespace std;

static auto construct_randomness_engine()
{
    random_device rd;
    // always use the same random seed here so the
    // avalanche testing code always gets the same sbox
    auto time = static_cast<random_device::result_type>(0);
    return mt19937_64(rd() ^ time);
}

Sbox_hash::Sbox_hash()
{
    auto rng = construct_randomness_engine();
    uniform_int_distribution<uint64_t> dist;
    //iterating over evert entry in the array
    //picks a random number, store it into the array
    //array becomes a mapping to randomness
    //every index in the array has some random bits in it
    for (auto& n : sbox_) n = dist(rng);
}

uint64_t Sbox_hash::operator()(string const& s) const
{
    uint64_t hash = 0;

    for (char c : s) {
        //a character to some particular set of random bits found in the box field
        //we always choose the same set of random bits
        // a way yo consistently scramble bits
        hash ^= sbox_[(unsigned char)c];
        hash *= 3;
    }

    return hash;
}

