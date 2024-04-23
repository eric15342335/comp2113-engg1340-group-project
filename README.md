# Stock Market Simulator

## Menu

1. [Team Members](#team-members)
2. [Game Description](#game-description)
3. [How to Play](#how-to-play)
4. [Code Requirements](#code-requirements)
5. [Non-standard Libraries Used](#non-standard-libraries-used)

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
giving players breathing room to better think about their investing strategies.

## How to Play

```bash
make
./stocksim
```

# Code Requirements

## Generation of random game sets or events

We used normal distribution to generate the percentage change in the stock price for each new round.

See [our documentation on events.h](https://eric15342335.github.io/comp2113-engg1340-group-project/events_8h.html) regarding how such distribution
can be manipulated to suit our needs.

You may want to consult our events.cpp source code, specifically the
`std::vector<Stock_event> pick_events (std::vector<Stock_event>all_events, unsigned int num_events)` for how we implement this feature.

In our game, we also included <num> events that will each have a possibility to happen in your gameplay.

## Data structures for storing game status (e.g., arrays, STL containers)

In [`stock.h`](./stock.h), we declared class [`Stock`](https://eric15342335.github.io/comp2113-engg1340-group-project/classStock.html) which utilizes STL `vector`, `list` and `map` to store various game data:
See [the Stock class documentation](https://eric15342335.github.io/comp2113-engg1340-group-project/classStock.html) for more information.

## Dynamic memory management (e.g., dynamic arrays, linked lists, STL containers)

Placeholder.

## File input/output (e.g., for loading/saving game status)

Related files: [`file_io.cpp`](file_io.cpp) [`file_io.h`](file_io.h)

## Program codes in multiple files (recall separate compilation)

We split our program codes into multiple files according to their functionality and purposes:
- `main.cpp`:
- [`stock.cpp` `stock.h`](https://eric15342335.github.io/comp2113-engg1340-group-project/classStock.html):
- `events.cpp`:
- `graph.cpp`:
- `random_price.cpp`:
- `names.cpp`:
- `file_io.cpp`:
- `draw.cpp`:
- `format.cpp`:

## Proper indentation and naming styles

We enforce our code formatting style via the use of `clang-format` tool. You can see our configuration file [here.](./.clang-format)

## In-code documentation

[Our `doxygen` documentation is available! (Click Me!)](https://eric15342335.github.io/comp2113-engg1340-group-project/)

# Non-standard libraries used

[VariadicTable](./nonstdlibs/README.md)

# Credits

## Logo

The logo used here and in-game is generated with [Text to ASCII](https://www.asciiart.eu/text-to-ascii-art)
