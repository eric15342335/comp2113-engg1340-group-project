# Stock Market Simulator

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)

[![CI](https://github.com/eric15342335/comp2113-engg1340-group-project/actions/workflows/make.yml/badge.svg)](https://github.com/eric15342335/comp2113-engg1340-group-project/actions/workflows/make.yml)
[![CodeFactor](https://www.codefactor.io/repository/github/eric15342335/comp2113-engg1340-group-project/badge/main)](https://www.codefactor.io/repository/github/eric15342335/comp2113-engg1340-group-project/overview/main)
[![Coverage Status](https://coveralls.io/repos/github/eric15342335/comp2113-engg1340-group-project/badge.svg?branch=main)](https://coveralls.io/github/eric15342335/comp2113-engg1340-group-project?branch=main)

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

"Stock Market Simulator" is a game that attempts to introduce a realistic
stock buying experience to players. The game utilizes the random number generation
capability of the operating system to mimic real-life stock unpredictable trends while
giving players breathing room to better think about their [investing](https://en.wikipedia.org/wiki/Investment) strategies.

## How to Play

[![Demo gameplay video](https://github.com/eric15342335/comp2113-engg1340-group-project/assets/70310617/c8971d2d-8289-45f9-9dfc-71ed74345e98)](https://connecthkuhk-my.sharepoint.com/:v:/g/personal/maxcsh_connect_hku_hk/EUUeLr39qLJHh7RePm4zwA8BMFvg9WQOopkL9vd-6KSMgg)

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

Or if you prefer one step:

```bash
make all
```

<!--
If you use CMake:
```bash
cmake -B build -S . --fresh
cmake --build build --clean-first
cmake --install build --prefix .
./stocksim
```
-->

To ensure an optimal gaming experience, please adopt the following recommendations before running the game:

### Terminal Size

Maximize your terminal window to its fullest extent.

On Windows, you can achieve this by pressing the `Alt+Enter` key combination, which will toggle the terminal to fullscreen mode.

### Font Size Adjustment

Reduce your terminal's font size initially.

Unsuitably large font sizes may cause the table displaying stock information and data to be cut off or misaligned within the terminal window.

Start with a smaller font size, such as `10`, to ensure the stock table displays correctly, and then increase the size if needed.

### Tutorial

After displaying the ASCII game logo, you will be prompted by this screen:

```bash
Please enter.
0 for new save,
1 for loading old save(s),
2 for deleting save,
3 to quit:
```

Type `0` and press `Enter`. Type your preferred name and press `Enter` again.

Now you should enter the game's main menu.

Some user inputs the game receives (case-insensitive):

- `B`: Buy a stock.
- `S`: Sell a stock.
- `T`: Select a stock (or `0` for [*Happy Stock Index*](https://eric15342335.github.io/comp2113-engg1340-group-project/main_8cpp.html#a2b63ee26099544b05219dff874052fa8)) to display a corresponding *price history* graph, which shows the historical performance of a stock and the fluctuations in stock price. Enter `T` again to hide the pop-up.
- `E`: Display all ongoing events that affect the performance of stocks. Enter `E` again to hide the pop-up.
- `N`: Proceed to the next round. The game will generate new stock prices and events.
- `X`: Exit the game.

You may wonder why there is no [save](https://en.wikipedia.org/wiki/Saved_game) button. The answer is --- you don't need it!

Each time when you enter `N: Next Round`, the game data is saved *automatically* in the
`saves/` folder. See more information on [File I/O part](#file-inputoutput-eg-for-loadingsaving-game-status).

Table column explanation:

- `#`: The *index* of the stock. You will enter it when you are purchasing/selling a stock.
- `Category`: The respective *categories* a stock corresponds to. Some events are applied to a [specific category](https://eric15342335.github.io/comp2113-engg1340-group-project/events_8h.html#a430b444c74dd3fd1472a31714ec5f1ce) only!
- `Name`: Self-explainatory.
- `$Price`: The current price (per unit) of the stock.
- `Change`: The change in the stock price compared to the last round.
- `%Change`: The percentage change of stock price.
- `#Has`: Number of stocks that you can sell.
- `#Max`: Number of stocks that you can buy. This takes account of [`trading_fees_percent`](https://eric15342335.github.io/comp2113-engg1340-group-project/main_8cpp.html#a1d043c1c24e1ba3966c9a78f4fcb8316).

Some [additional columns](https://eric15342335.github.io/comp2113-engg1340-group-project/main_8cpp.html#ab13096bec8ac73e79de04d721ce4f863) are hidden, they served for debugging purposes only.

# Code Requirements

## Generation of [random](./src/random_price.cpp) game sets or [events](https://eric15342335.github.io/comp2113-engg1340-group-project/events_8h.html)

Generation of stock prices:

- We used normal distribution to generate the percentage change in the stock price for each new round.

<https://github.com/eric15342335/comp2113-engg1340-group-project/blob/1cd66bfd883a18577a4b8d5d246b4aff21e000f6/src/random_price.cpp#L114-L128>

Generation of in-game events:

- In our game, we also included [**99**](https://github.com/eric15342335/comp2113-engg1340-group-project/blob/1cd66bfd883a18577a4b8d5d246b4aff21e000f6/src/events.cpp#L1255-L1263) events that will each have a possibility to happen in your gameplay.
  - The (relative) probability of each event is determined by the `Stock_event.probability_permille` member variable.

<https://github.com/eric15342335/comp2113-engg1340-group-project/blob/1cd66bfd883a18577a4b8d5d246b4aff21e000f6/src/events.cpp#L48-L60>

## Data structures for storing game status (e.g., arrays, STL containers)

In [stock.h](./stock.h), we declared class [Stock](https://eric15342335.github.io/comp2113-engg1340-group-project/classStock.html) which utilizes STL `vector`, `list` and `map` to store various game data.

<https://github.com/eric15342335/comp2113-engg1340-group-project/blob/1cd66bfd883a18577a4b8d5d246b4aff21e000f6/include/stock.h#L266-L295>

The class `Stock` itself represents an Stock object, which you can purchase, sell, generate a new price for it, etc.

<https://github.com/eric15342335/comp2113-engg1340-group-project/blob/1cd66bfd883a18577a4b8d5d246b4aff21e000f6/include/stock.h#L36-L58>

Other than `class Stock`, we have struct [Stock_event](https://eric15342335.github.io/comp2113-engg1340-group-project/structStock__event.html) that represents an in-game event.

<https://github.com/eric15342335/comp2113-engg1340-group-project/blob/1cd66bfd883a18577a4b8d5d246b4aff21e000f6/include/events.h#L104-L176>

## Dynamic memory management (e.g., dynamic arrays, linked lists, [STL containers](https://en.cppreference.com/w/cpp/container))

- [Stock.history](https://eric15342335.github.io/comp2113-engg1340-group-project/class_stock.html#a3e2f9db4597032d002af9a31eba6e35c) is an `std::vector<float>` that stores the history of the stock prices.
- [Stock.events](https://eric15342335.github.io/comp2113-engg1340-group-project/class_stock.html#ab7a85d9f901420579b21cc4e78ea6827) is an `std::list<Stock_event>` that stores on-going [events](https://eric15342335.github.io/comp2113-engg1340-group-project/struct_stock__event.html) that applies to the stock itself.
- [Stock.attributes](https://eric15342335.github.io/comp2113-engg1340-group-project/class_stock.html#a5f6748d37037cc65608d15cc83b09bf2) is an `std::map<stock_modifiers, float>` that stores the [properties](https://eric15342335.github.io/comp2113-engg1340-group-project/events_8h.html#a185fb61c0dff5e2a9b6c147a261736ee) related to stock price generation.

<https://github.com/eric15342335/comp2113-engg1340-group-project/blob/1cd66bfd883a18577a4b8d5d246b4aff21e000f6/include/stock.h#L282-L291>

## [File input/output](./src/file_io.cpp) (e.g., for loading/saving game status)

This game provides players with the ability to create a new save file, load an existing save, or delete a save upon starting the game.
The save files are distinguished by the `std::string playerName` variable.

### Save File Structure

- Each stock in the game has a separate `.save` file.
- Basic player information is stored in the `playerstatus.save` file.
- The *Happy Stock Index (HSI)* is stored in the `hsi.save` file.

### Automatic Saving

To prevent loss of progress and prevent rollbacks, the game automatically saves the current state at the end of every round.

### File Management

The game heavily relies on the `<filesystem>` library introduced in `C++17` to maintain file organization. This library enables the game to:

- Obtain a list of available save files.
- Create new folders for save files.
- Delete existing save files.

### Note for macOS and Linux Users

If you are running the game on `macOS` or `Linux` and not from the terminal, the `saves` folder will be located in the root directory.

## Program codes in multiple files (recall [separate compilation](./Makefile))

We split our program codes into multiple files according to their functionality and purpose.
[Click me to see the details of each file.](https://eric15342335.github.io/comp2113-engg1340-group-project/files.html)

## Proper indentation and naming styles

We enforce our code formatting style via the use of [clang-format](https://clang.llvm.org/docs/ClangFormat.html) tool. You can see our configuration file [here.](./.clang-format)

For naming styles, different [members](#team-members) of our group has different preferences.
Some notable examples (list may not include all styles and files):

- [snake_case](https://en.wikipedia.org/wiki/Snake_case): @eric15342335 [stock.cpp](./src/stock.cpp) [stock.h](./include/stock.h) [events.h](./include/events.h)

- [camelCase](https://en.wikipedia.org/wiki/Camel_case): @Prismatiscence [format.cpp](./src/format.cpp) [format.h](./include/format.h)
 [draw.cpp](./src/draw.cpp) [draw.h](./include/draw.h) [controls.cpp](./src/controls.cpp) [controls.h](./include/controls.h)

## In-code documentation

We place a strong emphasis on code documentation in our project. We utilize the `JavaDoc` format to write our comments, which enables seamless integration with third-party documentation auto-generation tools like [Doxygen](https://www.doxygen.nl/).

If you've noticed the numerous hyperlinks throughout this `README.md` file, they are pointing to the automatically generated documentation hosted on our GitHub Pages site. You can access this documentation by clicking [here](https://eric15342335.github.io/comp2113-engg1340-group-project/).

# Credits

## Non-standard libraries used

[![External Libraries](https://img.shields.io/badge/External_Libraries-VariadicTable-darkgreen)](https://github.com/friedmud/variadic_table)

For printing prettified tables in our code, we used the [VariadicTable](./include/nonstdlibs/) library.
VariadicTable is a third-party header-only library licensed under [LGPL-2.1](./include/nonstdlibs/LICENSE).

## Logo

The logo used in this game is generated with [Text to ASCII](https://www.asciiart.eu/text-to-ascii-art).

[Back to top](#stock-market-simulator)
