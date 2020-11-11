#pragma once

#include "Chain_hash_table.h"
#include "Sbox_hash.h"

template<typename T>
struct Identity_hash_table : Chain_hash_table<T>
{
    using Chain_hash_table<T>::Chain_hash_table;
    hashcode_t hash(std::string const&) const override;
};

template<typename T>
hashcode_t Identity_hash_table<T>::hash(std::string const& s) const
{
    hashcode_t ret = 0;
    size_t limit = std::min<size_t>(s.length(), 8);

    for (size_t i = 0; i < limit; ++i) {
        ret |= ((hashcode_t)(unsigned char) s[i]) << (i * 8);
    }

    return ret;
};


template<typename T>
struct One_byte_hash_table : Chain_hash_table<T>
{
    using Chain_hash_table<T>::Chain_hash_table;
    hashcode_t hash(std::string const&) const override;
};

template<typename T>
hashcode_t One_byte_hash_table<T>::hash(std::string const& s) const
{
    hashcode_t ret = 0;

    for (char c : s) {
        ret ^= (unsigned char) c;
    }

    return ret;
};
template<typename T>
struct polynomial_rolling : Chain_hash_table<T>
{
    using Chain_hash_table<T>::Chain_hash_table;
    hashcode_t hash(std::string const& s) const override;
};

//hash(s)=s[0]+s[1]⋅p+s[2]⋅p2+...+s[n−1]⋅pn−1 mod m
template<typename T>
hashcode_t polynomial_rolling<T>::hash(std::string const& s) const
{
    hashcode_t ret = 0;
    //31 for only lowercase letters of the English alphabet
    //53 for both
    const int p = 31;//a prime number roughly equal to the number of characters in the input alphabet.
    //the probability of two random strings colliding is about 1/m
    const int m = 1e9 + 9;// large prime number
    long long p_pow = 1;

    for (char c : s) {
        //a->1 b->2...z->26
        ret = (ret + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }

    return ret;
};
template<typename T>
struct Eight_bytes_hash_table : Chain_hash_table<T>
{
    using Chain_hash_table<T>::Chain_hash_table;
    hashcode_t hash(std::string const& s) const override;
};

template<typename T>
hashcode_t Eight_bytes_hash_table<T>::hash(std::string const& s) const
{
    hashcode_t ret = 0;

    size_t shift = 0;
    size_t limit = s.size() / 8 * 8;

    for (size_t i = 0; i < limit; ++i) {
        ret ^= (hashcode_t)(unsigned char)s[i] << (shift * 8);
        shift = (shift + 1) % 8;
    }

    return ret;
};


template<typename T>
class Simple_mix_hash_table : public Chain_hash_table<T>
{
public:
    explicit Simple_mix_hash_table
            (
            size_t nbuckets = Hash_table_base<T>::default_nbuckets,
            hashcode_t mixer = 3,
            hashcode_t start = 0
            )
            :
            Chain_hash_table<T>(nbuckets),
            mixer_(mixer),
            start_(start)
    { }

    hashcode_t hash(std::string const& s) const override;

private:
    hashcode_t mixer_;
    hashcode_t start_;
};

template<typename T>
hashcode_t Simple_mix_hash_table<T>::hash(std::string const& s) const
{
    hashcode_t ret = start_;

    for (char c : s) {
        ret ^= (unsigned char) c;
        ret *= mixer_;
    }

    return ret;
};


template<typename T>
class Sbox_hash_table : public Chain_hash_table<T>
{
public:
    explicit Sbox_hash_table(size_t nbuckets = Hash_table_base<T>::default_nbuckets)
            : Chain_hash_table<T>(nbuckets)
    { }

    hashcode_t hash(std::string const& s) const override;

private:
    Sbox_hash hash_;
};

template<typename T>
hashcode_t Sbox_hash_table<T>::hash(std::string const& s) const
{
    return hash_(s);
}
