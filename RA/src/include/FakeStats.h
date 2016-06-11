//
// Created by hongxu on 6/11/16.
//

#ifndef YAMA_FAKESTATS_H
#define YAMA_FAKESTATS_H

#include <string>


class FakeStats {
    unsigned value_;
    std::string const msg_;
public:

    unsigned value() {
        return value_;
    }

    explicit FakeStats(std::string msg) : value_(0u), msg_(msg) { }

    friend std::ostream& operator<<(std::ostream & ostream, FakeStats const& stats);

    FakeStats &operator=(unsigned Val) {
        value_ = Val;
        return *this;
    }

    FakeStats &operator++() {
        ++value_;
        return *this;
    }

    FakeStats &operator++(int) {
        value_++;
        return *this;
    }

    FakeStats &operator--() {
        --value_;
        return *this;
    }

    FakeStats &operator--(int) {
        value_--;
        return *this;
    }

    FakeStats &operator+=(const unsigned &V) {
        value_ += V;
        return *this;
    }

    FakeStats &operator-=(const unsigned &V) {
        value_ += V;
        return *this;
    }

    FakeStats &operator*=(const unsigned &V) {
        value_ *= V;
        return *this;
    }

    FakeStats &operator/=(const unsigned &V) {
        value_ /= V;
        return *this;
    }


};


#endif //YAMA_FAKESTATS_H
