# Adaptive Replacement Cache (ARC) imitation

## Description & Features
We are proud to present you our implementation of the ARC caching algorithm. Since our goals did not involve using or developing the zero-level "quick" information storage, this project is not a cache itself but just an imitation of it without any actual memory accelerating effects. However, the replacement policy algorithm, all the mechanisms required to implement it and all the overhead costs are presented in full volume. This fact makes our project quite useful for demonstrating the difference between effective and not-so-effective caching algorithms.

ARC was invened as an attempt to create a universal replacement policy capable of balancing between LRU (least recently used) and LFU (least frequently used) policies depending on the memory usage style at every exact moment. To make this equilibrium approachable, one special numeric parameter ***P*** is used. Roughly speaking, ***P*** acts as a ratio of the amounts of LRU and LFU pages cached. The core of the algorithm is the way of manipulating this parameter according to the nature of requests. To apply ***P*** to configuring the set of cached pages, special cache directory is used. This storage (2 linked lists) contains 2**X** identifiers of close-to-being-cached pages (exactly half of which are cached at the moment), where **X** is the actual cache capacity. Finally, new requests variate the ***P*** parameter and, based on ***P*** value, change the state of the cache directory, which leads to the cached pages set being updated and the replacement policy being performed. To find the complete description of the algorithm, see [Nimrod Megiddo, Dharmendra S. Modha, "Outperforming LRU with an Adaptive Replacement Cache Algorithm"](http://theory.stanford.edu/~megiddo/pdf/IEEE_COMPUTER_0404.pdf).

In addition to ARC algorithm itself we created a couple of tools that may be useful for exploring this cache - an automatic testing system, a random test generator and two similar implementations of more trivial caching algorithms - FRC and LRU. While LRU implies one of the most basic replacement policies, FRC (F stands for fixed) is a simplified version of ARC, where ***P*** parameter is set to a constant value.

## Latest version
The latest version of our ARC caching algorithm implementation can be found here: <https://github.com/protobarhatus/arc_cash>.

## Dependencies
To successfully compile, build and launch the imitation you will need to have any C/C++ compiler (gcc should be the most reliable and easy choice) and standard Make and CMake utilities installed. No other special software required.

## How-to-use
### Configuration
Before you get started, it may be useful to take a look at *shared/modes.h* header file. At the top of it you can find a couple of definitions, including **DEMONSTRATION_MODE**, **FRC_CP_RATIO** and **FLAW_CONTROL**. The last one is just a debugging launch mode. It disables all the output and enables automatic diagnostics of cache state after each request, printing an error message if something went wrong or staying silent if no flaws occured. There is no actual point in using it if you haven't changed the code - we've already checked everything, so just keep it commented out. **FRC_CP_RATIO** is a constant definition, describing the ratio of **fixed** ***P*** parameter (talking about FRC) to the cache capacity, that can be useful for experimenting with FRC effectiveness. Finally, **DEMONSTRATION MODE** allows you to collect a set of statistical values (hit ratio, actually), that will be put to a file, mentioned as a launch argument.

### Building and compiling
To build the project, use first `cmake CMakeLists.txt` to create a Makefile and some subfiles, and then just `make` or `make all`. When you finished working with the program, to clean out all object and executable files use `make clean`.

### Creating tests
First of all, to use the automatic test generator, you can just launch `./testgen`. It will automatically generate a bunch of 1000000-requests tests with different request patterns and put them into the *testpool* foulder. To create your own test, you can write it down in a file, formatted as "*cache-capacity **(space)** amount of requests **(space)** requests, separated by spaces*". *Request* in this context means just an identifier (an integer decimal number from 0 to 2e9) of a page requested at each round. After you hev created this *.tst* text file, put it in the *testpool* directory, so the testing program is able to see it.

Actually we've already placed some handmade and generated tests into the *testpool* foulder. *arcperfpattern* show the ARC supremacy in the brightest way (if you use these files in demonstration mode), and *handytests* are just a couple of primitive handmade tests to make this project look more human.

### Running tests
If the demonstration mode is off, you can just launch any of the 3 imitations presented by just using `./arc`, `./frc` or `./lru`. After launching type the test, formatted as it was described above and after that you will receive one number - a number of cache hits, actually. If the demonstration mode is on, you can make the same thing, but don't forget to insert the name of the output file as the launch argument - the result will be dropped there. But it should be much more interesting and productive to use our testing system. Launch `./test` and type the name of the test file, placed to *testpool* directory, as a launch argument. The automatic tester will run ARC, FRC and LRU on this test and place the resulting statistics to the *testres.log* file in the main project directory. At the same time, if you have already autogenerated the tests, you can insert the name of the test pattern as a launch argument (e.g. `./test noise`) and the tester will run all the caches on every generated test, related to the pattern mentioned, dropping the statistics to the *testres.log* file. Finally, you can just type `./test all`, open the *testres.log* and enjoy the system collecting statistics about caches' efficiency on all the automatically generated patterns.

## Documentation
As it was mentioned before, an accurate and comprehensive description of ARC and FRC algorithms plus various statistics and a bunch of other useful information can be found in Nimrod Megiddo's and Dharmendra S. Modha's article [here](http://theory.stanford.edu/~megiddo/pdf/IEEE_COMPUTER_0404.pdf). More particular in-code documentation (compatible with Doxygen) can be added upon request.

## License
This is an open-source educational project. You can freely use, edit and distribute any versions of this code in personal and commercial purposes.

## Contacts
#### Oleg Sukhodolov, co-author of the project
email: <suhodolov.o@yandex.ru>,
GitHub: [protobarhatus](https://github.com/protobarhatus)

#### Korney Ivanishin, co-author of the project
email: <korney059@gmail.com>,
GitHub: [quaiion](https://github.com/quaiion)

