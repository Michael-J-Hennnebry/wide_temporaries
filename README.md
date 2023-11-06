# NAME
wide_temporaries

# SYNOPSIS
#include "wide_temporaries.hh"  
...  
mjh::wide_temporaries<narrow_t, wide_t>  
is a class for floating pointing point computation.

# DESCRIPTION
mjh::wide_temporaries is a class template  
that wraps a specified floating point type,  
but causes computations to be done in another floating point type,  
also specified.
The mechanism is simple.  
The class holds a narrow_t datum,
but will only convert to wide_t.  
Both must be floating point types.
wide_t must be at least as wide as narrow_t.

For completeness, four assignment operators are defined,  
but deprecated as defeating the purpose of wide_temporaries.

# LIMITATIONS
Though precisely the size of a narrow_t,  
a mjh::wide_temporaries<narrow_t, wide_t> is neither a narrow_t nor a wide_t.  
Other than copying, there is no valid way to pass an array of  
wide_temporaries to a function expecting an array of narrow_t.  
Other than copying, there is no valid way to pass an array of  
narrow_t to a function expecting an array of wide_temporaries.  
There are invalid ways that are pretty much guaranteed to work.  
Similar issues arise with other aggregates.

# EXAMPLES
The code in the examples directory is not needed to use wide_tempories.hh .  
To use it, from some directory, which is not terribly important:  
.../wide_temporaries/example/configure.sh  
make syntax  # compiles and links syntax.cc, but does not run it.  
make run     # compiles and links dot.cc and runs ./dot  

# HISTORY
Before C++ and when C was new,
computation on floats was done in double precision.
Usually, but not always, this had a salutary effect on accuracy.
Also, it was convenient for code that ran on a PDP-11.
Intel 80486s and some Motorolas had only 80-bit floating point registers
and floating point arithmetic was done in an even wider format than double.

When C was first codified by ANSI and ISO,
computing with a wider floating point type
than that of either operand was forbidden,
but some platforms,
e.g. those with only 80-bit floating point registers, did it anyway.
Eventually processors got more floating point registers,
but not more 80-bit registers.
They did 32-bit and 64-bit arithmetic on the new registers.
On most platforms involving these processors,
now the vast majority with hardware floating point,
floating point arithmetic is done with the precision indicated by operands.

As William Kahan has pointed out, that is often not the best.
See William Kahan's "On the Cost of Floating-Point Computation
Without Extra-Precise Arithmetic" at
https://people.eecs.berkeley.edu/~wkahan/Qdrtcs.pdf

The decision stuck even though ANSI and ISO relented with C99.
Often it is useful to perform arithmetic
with a greater precision than any operand.
In such cases, one would like to hold off on using a narrow
type until necessary to store a result in that size memory location.
Some platforms still have this behavior built in.
In such cases, it is not optional and has sometimes
been done badly enough to produce strange anomolies:
The result was not deterministic.
Following along and doing the calculations by hand was
not possible without looking at the compiler output.

There are important differences between
built-in widening and using wide_temporaries.
With built-in widening, the type remains the narrow type,
even though the calculation is done in the wide type.
With built-in widening, in the expression sqrt(x*y),
the sqrt selected will correspond to the narrow type.
The result will subtly depend on the ABI and possibly
on the details of the implementation of sqrt.
With wide_temporaries, x*y will have the wide
type and the sqrt will be selected accordingly.

There are additional subtleties when wide_temporaries
and built-in widening are both in play.
If wide_temporaries' wide type is subject to built-in widening,
one can have the same sort of anomalies as without wide_temporaries.
One way to avoid this is to use float_t or double_t
for the wide type instead of float or double.
It is possible that even long double might
be widened to some implementation-defined type.
I know of no platform that does so.

mjh::wide_temporaries<double, double_t>
has some advantages over just using the built-in widening.
Arithmetic expressions involving it have a well-defined type: double_t .
Register spills will be to the correct amount of main memory,
avoiding related anamolous beavior.
Functions will receive values appropriate for the argument types.
