# Stock Market Simulator

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)

[![clang-format](https://github.com/eric15342335/comp2113-engg1340-group-project/actions/workflows/clang-format.yml/badge.svg?branch=main)](https://github.com/eric15342335/comp2113-engg1340-group-project/actions/workflows/clang-format.yml)
[![Make](https://github.com/eric15342335/comp2113-engg1340-group-project/actions/workflows/make.yml/badge.svg)](https://github.com/eric15342335/comp2113-engg1340-group-project/actions/workflows/make.yml)
[![Pages (doxygen)](https://github.com/eric15342335/comp2113-engg1340-group-project/actions/workflows/static.yml/badge.svg)](https://github.com/eric15342335/comp2113-engg1340-group-project/actions/workflows/static.yml)

## Menu

1. [Team Members](#team-members)
2. [Game Description](#game-description)
3. [How to Play](#how-to-play)
4. [Code Requirements](#code-requirements)
   1. [Generation of random game sets or events](#generation-of-random-game-sets-or-events)
   2. [Data structures for storing game status (e.g., arrays, STL containers)](#data-structures-for-storing-game-status-eg-arrays-stl-containers)
   3. [Dynamic memory management (e.g., dynamic arrays, linked lists, STL containers)](#dynamic-memory-management-eg-dynamic-arrays-linked-lists-stl-containers)
   4. [File input/output (e.g., for loading/saving game status)](#file-inputoutput-eg-for-loadingsaving-game-status)
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

"[Stock](https://eric15342335.github.io/comp2113-engg1340-group-project/classStock.html) Market Simulator" is a game that attempts to introduce a realistic
stock buying experience to players. The game utilizes the random number generation
capability of the operating system to mimic real-life stock unpredictable trends while
giving players breathing room to better think about their [investing](https://en.wikipedia.org/wiki/Investment) strategies.

## How to Play

### Compilation

Prerequisite:

- This repository.
- A working `g++` compiler that supports `C++17`
- `make`
- A terminal that supports [ANSI escape codes](https://en.wikipedia.org/wiki/ANSI_escape_code)

To compile:

```bash
make
```

To run the game:

```bash
./stocksim
```

To ensure an optimal gaming experience, follow these steps before running the game:

### Terminal Size

Maximize your terminal window to its fullest extent.
On Windows, you can achieve this by pressing the Alt+Enter key combination, which will toggle the terminal to fullscreen mode.

### Font Size Adjustment

Reduce your terminal's font size initially.
A larger font size may cause the table displaying stock information and data to be cut off or misaligned within the terminal window.
Start with a smaller font size to ensure the stock table displays correctly, then increase the size if needed.

### Tutorial

After displaying the ASCII game logo, you will be prompted by this screen:

```bash
Please enter.
0 for new save,
1 for loading old save,
2 for deleting save,
3 to quit:
```

Type `0` and press `Enter`. Type your preferred name and press `Enter` again.

Now you should enter the game's main menu.

Some user inputs the game receives (case-insensitive):

- `B`: Buy a stock.
- `S`: Sell a stock.
- `T`: Select a stock (or `0` for [*Happy Stock Index*](https://eric15342335.github.io/comp2113-engg1340-group-project/main_8cpp.html#a2b63ee26099544b05219dff874052fa8)) to display corresponding *price history* graph.
- `E`: Display all on-going events. Enter `E` again to hide the pop-up.
- `N`: Proceed to next round. The game will generate new stock prices and events.
- `X`: Exit the game.

You may wonder why there is no ["Save"](https://en.wikipedia.org/wiki/Saved_game) button. The answer is --- you don't need it!
Each time when you enter `N: Next Round`, the game data is saved *automatically* in the
`saves/` folder. See more information on [File I/O part](#file-inputoutput-eg-for-loadingsaving-game-status).

Table column explaination:

- `#`: The *index* of the stock. You will enter it when you are purchasing/selling a stock.
- `Category`: The respective *categories* a stock is correspond to. Some events are applied to a [specific category](https://eric15342335.github.io/comp2113-engg1340-group-project/events_8h.html#a430b444c74dd3fd1472a31714ec5f1ce) only!
- `Name`: Self-explainatory.
- `$Price`: The current price (per unit) of the stock.
- `Change`: The change of the stock price compared to last round.
- `%Change`: The percentage change of stock price.
- `#Has`: Number of stocks that you can sell.
- `#Max`: Number of stocks that you can buy. This take account of [`trading_fees_percent`](https://eric15342335.github.io/comp2113-engg1340-group-project/main_8cpp.html#a1d043c1c24e1ba3966c9a78f4fcb8316).

Some [additional columns](https://eric15342335.github.io/comp2113-engg1340-group-project/main_8cpp.html#a202ef3d53c7e07383aed69113ccbe680) are hidden, they served for debugging purposes only.

# Code Requirements

## Generation of [random](./random_price.cpp) game sets or [events](https://eric15342335.github.io/comp2113-engg1340-group-project/events_8h.html)

Generation of stock prices [(file)](./random_price.cpp) [(docs)](https://eric15342335.github.io/comp2113-engg1340-group-project/random__price_8cpp.html):

- We used normal distribution to generate the percentage change in the stock price for each new round.
- Instead of generating a new stock price based on the current price, we discovered this is easier for us to code.

Generation of in-game [events](https://eric15342335.github.io/comp2113-engg1340-group-project/events_8h.html):

- In our game, we also included **99** events that will each have a possibility to happen in your gameplay.
  - The (relative) probability of each event is determined by the `Stock_event.probability_permille` member variable. ([Implementation](https://eric15342335.github.io/comp2113-engg1340-group-project/events_8cpp.html#a24cd47ec3d81ef215901b99cbe434829))

## Data structures for storing game status (e.g., arrays, STL containers)

In [`stock.h`](./stock.h), we declared [class `Stock`](https://eric15342335.github.io/comp2113-engg1340-group-project/classStock.html) which utilizes [STL `vector`](https://en.cppreference.com/w/cpp/container/vector), [`list`](https://en.cppreference.com/w/cpp/container/list) and [`map`](https://en.cppreference.com/w/cpp/container/map) to store various game data.

Other than `class Stock`, we have [`struct Stock_event`](https://eric15342335.github.io/comp2113-engg1340-group-project/structStock__event.html) that represents an in-game event.

## Dynamic memory management (e.g., dynamic arrays, linked lists, [STL containers](https://en.cppreference.com/w/cpp/container))

- [`Stock.history`](https://eric15342335.github.io/comp2113-engg1340-group-project/random__price_8cpp.html) is an `std::vector<float>` that stores the history of the stock prices.
- [`Stock.events`](https://eric15342335.github.io/comp2113-engg1340-group-project/random__price_8cpp.html) is an `std::list<Stock_event>` that stores on-going [events]((https://eric15342335.github.io/comp2113-engg1340-group-project/events_8h.html)) that applies to the stock itself.
- [`Stock.attributes`](https://eric15342335.github.io/comp2113-engg1340-group-project/classStock.html#a5f6748d37037cc65608d15cc83b09bf2) is an `std::map<stock_modifiers, float>` that stores the [properties](https://eric15342335.github.io/comp2113-engg1340-group-project/events_8h.html#a185fb61c0dff5e2a9b6c147a261736ee) related to stock price generation.

## [File input/output](./file_io.cpp) (e.g., for loading/saving game status)

This game had options for players to create a new save, load an old save, and delete
a save upon the startup of the game.

The saves are distinguished by the variable
`std::string playerName`. In each
save, every stock has a separate `.save` file, while other basic information is stored
in `playerstatus.save`, and *Happy Stock Index (HSI)* in `hsi.save`.

The saving process is automatic upon the end
of every round to prevent loss of advancements of the game (and also prevent rollback).

Moreover, this game relies heavily on the C++17 library `<filesystem>` to maintain the tidiness
of files. It enables us to obtain the names of available saves, create folders, and delete saves.

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

We take documentation *seriously*. In our code, we use `JavaDoc` as the format to write our comments. This allows us to integrate with third-party documentation auto-generate tools like [`doxygen`](https://www.doxygen.nl/).

If you haven't noticed why we have so many hyperlinks in this [README.md](./README.md) file, click [here](https://eric15342335.github.io/comp2113-engg1340-group-project/) to know what the links are pointing to!

# Credits

## Non-standard libraries used

[![External Libraries](https://img.shields.io/badge/External_Libraries-VariadicTable-darkgreen)](https://github.com/friedmud/variadic_table)

For printing the prettified table, we used [VariadicTable](./nonstdlibs/) in our code. VariadicTable is a third-party header-only library licensed
under [LGPL-2.1](./nonstdlibs/LICENSE.VariadicTable.md).

## Logo

The logo used in-game is generated with [Text to ASCII](https://www.asciiart.eu/text-to-ascii-art).

[Back to top](#stock-market-simulator)
