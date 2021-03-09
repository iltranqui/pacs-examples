#A template class for derivatives of a function by finite differences#

This is an example of template (meta)programming to have a class that implements derivatives of any order of a function
approximating them by finite differencing. It is an example of recursion. In practice the N-th derivative of f is approximated
as the 1st derivative of the Nth-1 derivative, and so on recursively until we get to the 1st derivative, where I use a standard two point formula.

To get a more stable (and accurate) formula for higher order derivatives I alternate backward and
forward differences, but you can also use centered formula. Howver, beware that the standard three point formula for the second derivative is obtained
by chosing the backward or forward alternative, not the centered ones. With the algorithm I have implemented a centered second order derivative will use a stencil of five points, not three.

**What does this example show?**

- An example of use of recursion with templates;
- A use of the type traits `std::is_same<>` to check a type;
- The (c++17 extension) `if constexpr` construct, to select a conditioned branch **at compile time**. Without `if constexpr` and `std::is_same<>` we could have resorted to a metaprogramming technique called `tag dispatching` , see [here](www.fluentcpp.com/2018/04/27/tag-dispatching/). I have used tag dispatching in my `MyMat0` class for matrices to select the storage ordering;
- We also show how to make helper functions to create specific instances and simplify the use of the tool.


Derived from a code in *"Discovering Modern C++", P. Gottschiling, Addison Wesley, 2016.*
