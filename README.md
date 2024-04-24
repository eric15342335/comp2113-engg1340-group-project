# [Stock](https://eric15342335.github.io/comp2113-engg1340-group-project/classStock.html) Market Simulator

## Menu

1. [Team Members](#team-members)
2. [Game Description](#game-description)
3. [How to Play](#how-to-play)
4. [Code Requirements](#code-requirements)
   1. [Generation of random game sets or events](#generation-of-random-game-sets-or-events)
   2. [Data structures for storing game status (e.g., arrays, STL containers)](#data-structures-for-storing-game-status-eg-arrays-STL-containers)
   3. [Dynamic memory management (e.g., dynamic arrays, linked lists, STL containers)](#dynamic-memory-management-eg-dynamic-arrays-linked-lists-stl-containers)
   4. [File input/output (e.g., for loading/saving game status)](#file-input-output-eg-for-loading-saving-game-status)
   5. [Program codes in multiple files (recall separate compilation)](#program-codes-in-multiple-files-recall-separate-compilation)
   6. [Proper indentation and naming styles](#proper-indentation-and-naming-styles)
   7. [In-code documentation](#in-code-documentation)
5. [Credits](#credits)
   1. [Logo](#logo)
   2. [Non-standard Libraries Used](#non-standard-libraries-used)

## Team members

<!-- markdownlint-disable MD033 -->

<table>
    <tbody>
        <tr>
            <th>Name</th>
            <th>UID</th>
            <th>Profile</th>
        </tr>
        <tr>
            <td>Cheng Ho Ming</td>
            <td>3036216734</td>
            <td><a href="https://github.com/eric15342335"><img src="https://avatars.githubusercontent.com/u/70310617" alt="Cheng Ho Ming" width=50></a></td>
        </tr>
        <tr>
            <td>Chung Shing Hei</td>
            <td>3036216760</td>
            <td><a href="https://github.com/MaxChungsh"><img src="https://avatars.githubusercontent.com/u/70740754" alt="Chung Shing Hei" width=50></a></td>
        </tr>
        <tr>
            <td>Chow Yui Hei</td>
            <td>3036222446</td>
            <td><a href="https://github.com/Prismatiscence"><img src="https://avatars.githubusercontent.com/u/56928422" alt="Chow Yui Hei" width=50></a></td>
        </tr>
        <tr>
            <td>Chu Chun Yin</td>
            <td>3036270778</td>
            <td><a href="https://github.com/84ds84d8s"><img src="https://avatars.githubusercontent.com/u/129842660" alt="Chu Chun Yin" width=50></a></td>
        </tr>
        <tr>
            <td>Wong Sonny</td>
            <td>3036222458</td>
            <td><a href="https://github.com/comet13579"><img src="https://avatars.githubusercontent.com/u/67854955" alt="Wong Sonny" width=50></a></td>
        </tr>
    </tbody>
</table>

<!-- markdownlint-enable MD033-->

## Game Description

"[Stock]((https://eric15342335.github.io/comp2113-engg1340-group-project/classStock.html)) Market Simulator" is a game that attempts to introduce a realistic
stock buying experience to players. The game utilizes the random number generation
capability of the operating system to mimic real-life stock unpredictable trends while
giving players breathing room to better think about their [investing](https://en.wikipedia.org/wiki/Investment) strategies.

## How to Play

To compile:
```bash
make
```
To run the game:
```bash
./stocksim
```
[Makefile usage](./Makefile)

# Code Requirements

## Generation of [random](./random_price.cpp) game sets or [events](https://eric15342335.github.io/comp2113-engg1340-group-project/events_8h.html)

Generation of stock prices [(file)](./random_price.cpp) [(docs)](https://eric15342335.github.io/comp2113-engg1340-group-project/random__price_8cpp.html):
- We used normal distribution to generate the percentage change in the stock price for each new round.
- Instead of generating new stock price based on current price, we discovered this is easier for us to code.

Generation of in-game [events](https://eric15342335.github.io/comp2113-engg1340-group-project/events_8h.html):
- In our game, we also included *_99_* events that will each have a possibility to happen in your gameplay.
  - The probability of each event is determined by the `probability_permille` member variable. (Despite the name, the value of this variable does not actually represent such meaning in our [implementation](https://eric15342335.github.io/comp2113-engg1340-group-project/events_8cpp.html#a24cd47ec3d81ef215901b99cbe434829))

## Data structures for storing game status (e.g., arrays, STL containers)

In [`stock.h`](./stock.h), we declared [class `Stock`](https://eric15342335.github.io/comp2113-engg1340-group-project/classStock.html) which utilizes [STL `vector`](https://en.cppreference.com/w/cpp/container/vector), [`list`](https://en.cppreference.com/w/cpp/container/list) and [`map`](https://en.cppreference.com/w/cpp/container/map) to store various game data.

Other than `class Stock`, we have [`struct Stock_event`](https://eric15342335.github.io/comp2113-engg1340-group-project/structStock__event.html) that represents an in-game event.

## Dynamic memory management (e.g., dynamic arrays, linked lists, [STL containers](https://en.cppreference.com/w/cpp/container))

- [`Stock.history`](https://eric15342335.github.io/comp2113-engg1340-group-project/random__price_8cpp.html) is an `std::vector<float>` that stores the history of the stock prices.
- [`Stock.events`](https://eric15342335.github.io/comp2113-engg1340-group-project/random__price_8cpp.html) is an `std::list<Stock_event>` that stores on-going [events]((https://eric15342335.github.io/comp2113-engg1340-group-project/events_8h.html)) that applies to the stock itself.
- [`Stock.attributes`](https://eric15342335.github.io/comp2113-engg1340-group-project/classStock.html#a5f6748d37037cc65608d15cc83b09bf2) is an `std::map<stock_modifiers, float>` that stores the [properties](https://eric15342335.github.io/comp2113-engg1340-group-project/events_8h.html#a185fb61c0dff5e2a9b6c147a261736ee) related to stock price generation.

## [File input/output](./file_io.cpp) (e.g., for loading/saving game status)

All game data is stored in `saves/<playername>/*.save`. Such as:
- player's name and balance
- data of all stocks, e.g. price, history, on-going events, modifiers, etc.
- HSI value history

## Program codes in multiple files (recall [separate compilation](./Makefile))

We split our program codes into multiple files according to their functionality and purpose.
[Click me to see the details of each file.](https://eric15342335.github.io/comp2113-engg1340-group-project/files.html)

## Proper indentation and naming styles

We enforce our code formatting style via the use of [`clang-format`](https://clang.llvm.org/docs/ClangFormat.html) tool. You can see our configuration file [here.](./.clang-format)

For naming styles, different [members](#team-members) of our group has different preferences.
Some notable examples (list may not include all styles and files):
- [snake_case](https://en.wikipedia.org/wiki/Snake_case): @eric15342335 [`stock.cpp`](./stock.cpp) [`stock.h`](./stock.h)
- [camelCase](https://en.wikipedia.org/wiki/Camel_case): @Prismatiscence [`format.cpp`](./format.cpp) [`format.h`](./format.h)
 [`draw.cpp`](./draw.cpp) [`draw.h`](./draw.h) [`controls.cpp`](./controls.cpp) [`controls.h`](./controls.h)

## In-code documentation

We take documentation _seriously_. In our code, we use `JavaDoc` as the format to write our comments. This allow us to integrate with third-party documentation auto-generate tools like [`doxygen`](https://www.doxygen.nl/).

If you haven't noticed that why we have so many hyperlinks in this [README.md](./README.md) file, click [here](https://eric15342335.github.io/comp2113-engg1340-group-project/) to know what the links are pointing to!

# Credits

## Non-standard libraries used

For printing the prettified table, we used [VariadicTable](./nonstdlibs/README.md) in our code. VariadicTable is a third-party header-only library licensed
under [LGPL-2.1](./nonstdlibs/LICENSE.VariadicTable.md).

## Logo

The logo used here and in-game is generated with [Text to ASCII](https://www.asciiart.eu/text-to-ascii-art).

