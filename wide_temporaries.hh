#ifndef WIDE_TEMPORARIES__HH
#define WIDE_TEMPORARIES__HH 1

#include <iostream>
#include <concepts>


namespace mjh {

template<std::floating_point Wide=long double,
         std::floating_point Narrow=double >
requires ( sizeof(Wide)>=sizeof(Narrow) )
class wide_temporaries {
    Narrow datum ;
public:
    operator Wide() const { return datum; }

    wide_temporaries(Narrow d) : datum(d) {}
    wide_temporaries(void) {}

    typedef Wide wide_type;
    typedef Narrow narrow_type;
    typedef wide_temporaries<Wide, Narrow> this_type;

    narrow_type get_narrow() const { return datum; }

    // Here because its ubiquitousness elsewhere might make it expected.
    [[deprecated("narrow_type would be more clear, wide_type might be wanted")]]
    typedef Narrow value_type;

    [[deprecated("does not use wide_type")]]
    this_type operator++() { return ++datum; }
    [[deprecated("stored value not wide_type")]]
    wide_type operator++(int) { return datum++; }  // returns original value

    [[deprecated("does not use wide_type")]]
    this_type operator--() { return --datum; }
    [[deprecated("stored value not wide_type")]]
    wide_type operator--(int) { return datum--; }  // returns original value

    // Where possible, the assignment operators avoid double rounding.
    // Not possible if sizeof(F)> sizeof(Narrow).

    #define stringfy_(arg) #arg
    #define stringfy(arg) stringfy_(arg)

    #define assignment(op) template<std::floating_point F> \
       [[deprecated(stringfy(op ## = defeats purpose of wide_temporaries))]] \
         this_type & operator op ## = (F rhs) \
         { this->datum op ## = rhs ; return *this ; } \
       [[deprecated(stringfy(op ## = defeats purpose of wide_temporaries))]] \
         this_type & operator op ## = (this_type rhs) \
         { this->datum op ## = rhs.datum ; return *this ; }

    assignment(+)
    assignment(-)
    assignment(*)
    assignment(/)

    #undef stringfy_
    #undef stringfy
    #undef assignment

} ; // wide_temporaries

template<typename charT, typename Traits,
         std::floating_point Wide, std::floating_point Narrow >
requires ( sizeof(Wide)>=sizeof(Narrow) )
std::basic_istream<charT, Traits> & operator>>(
        std::basic_istream<charT, Traits> &s,
        wide_temporaries<Wide, Narrow> &wt ) {
    Narrow n;
    s>>n;
    wt=n;
    return s;
} // <<

} // mjh

#endif // WIDE_TEMPORARIES__HH
