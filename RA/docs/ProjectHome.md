# Introduction #

The goal of this project is to implement an inter-procedural range analysis algorithm that scales up to programs with millions of lines of code. Contrary to many previous techniques, we handle comparisons between variables without resorting to relational lattices or expensive algorithms. We achieve path sensitiveness by using Bodik's [Extended Static Single Assignment](http://dl.acm.org/citation.cfm?id=349342) form as the intermediate representation. We show that by processing the strongly connected components that constitute the graph of dependences between variables in topological order we not only gain in time, but also in precision. We have implemented our technique in [LLVM](http://llvm.org/), an industrial strength compiler, and have been able to process over 4 million assembly instructions in a few seconds.

# The rest of this page #

  * We have a paper that provides a brief [description](http://homepages.dcc.ufmg.br/~fernando/publications/papers/CGO13_raphael.pdf) of our algorithm.
  * We also have a [video](http://www.youtube.com/watch?v=Vj-TI4Yjt10), in which we describe the range analysis algorithm that we have designed.
  * [Gallery of Examples](gallery.md): this page contains examples of C programs, their CFGs, and the constraint graphs that we produce for them.
  * [How to use Range Analysis in another LLVM pass](HowToUseRangeAnalysisInAnotherPass.md): if you are in need of a range analysis pass for LLVM, this page is where you should go. We explain how to incorporate our project in your LLVM pass.
  * [How to use our dynamic interval profiler](HowToUseRangeAnalysisInstrumentationPass.md): we have a profiler that records, for each variable, the lowest and highest values that it has been assigned during the program execution. This profiler is quite useful to estimate how precise is our analysis.
  * [How To Use Our Custom SPEC Test Script](HowToUseOurCustomSPECTestScript.md): we have been using a customized script to obtain runtime numbers for the SPEC benchmarks. These scripts have been very useful to us, and they are easy to configure.

# What we provide #

Our range analysis algorithm is lightning fast: it can analyze very large programs in a few seconds. And it is not a straw-man: we can find very precise bounds to general C programs. Take a look into our [gallery](gallery.md) to see what we can find. The implementation that we have is also very customizable. A client can trade precision for speed in many different ways:

  * The best way to get more precision out of our implementation is to convert the target program to e-SSA form. The conversion itself is pretty fast: it takes less than one second to convert the entire gcc source code to e-SSA form. The e-SSA form program is about 7% larger than the original program, so our analysis is about 7% slower in this representation. But, the e-SSA form really improves our precision. For the SPEC CPU 2006 programs we get sometimes results 50x more precise!
  * Another way to improve precision is to enable the whole program analysis. The vanilla implementation, which is intra-procedural, only analyzes one function at a time. By using the inter-procedural version, one gets relatively better results. Sometimes the inter-procedural version is twice as precise; that is, it is able to reduce the number of bits necessary to allocate the variables twice as more. The very nice thing is that the inter-procedural version is not much slower than the intra-procedural version. We do range analysis on strongly connected components, and, except for mutually recursive functions, these graphs tend to have the same size in the inter and intra-procedural implementations.
  * Our inter-procedural analysis is not context-sensitive. We can get a limited form of context-sensitiveness by enabling function inlining. This is an LLVM feature. LLVM is able to inline all the non-recursive functions in the code. The program, of course, grows quite a bit. Yet, the growth is not as much as one would, at first, expect: around 80%. The problem is that at least in our context, range analysis, function inlining does not improve the results too much. We measure precision by counting the percentage of bitwidth reduction. If the target function is only called at one site, the version without inlining will gives a more precise result (due to the way we measure it), because we will be counting the pameters twice in the version without inlining.
  * We give the user the option to choose between two different widening strategies. The simple one blows a limit to either minus infinity or plus infinity it it does not converge. We have implemented [jump-set widening](http://lara.epfl.ch/w/sav09:widening_in_variable_range_analysis) too. In this case we use the constants in the program code as the limits for widening. It produces better results in some examples, but in practice we have found that the simple widening strategy is equally as good. The difference in speed between these two approaches is negligible.
  * Another way to trade precision for speed is to do a number of pre-iterations before applying widening. We have experimented with 0, 1, 2 and 16 pre-iterations. We have found that, at least for the very large SPEC CPU 2006 programs, running pre-iterations increases precision in non-trivial ways. Because the strongly connected components tend to be very small, even 16 iterations do not slow down our analysis too much. The gains in precision, for the SPEC programs at least, are around 20% using 16 iterations instead of zero.

# Compatibility #

Range Analysis works on the latest version of LLVM, 3.6.0.

# Want to contribute? #

This is an open-source project. If you want to contribute any feature to our range analysis, do not hesitate to get in touch with us. Our e-mails are available in the [report](http://homepages.dcc.ufmg.br/~fernando/publications/papers/CGO13_raphael.pdf). We also participate in the LLVM-dev mailing list. And you can always leave comments, questions and suggestions in this webpage.

This project is sponsored by the Brazilian Research Council (CNPq).