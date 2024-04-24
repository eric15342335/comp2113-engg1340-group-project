# Stock Market Simulator

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

"Stock Market Simulator" is a text-based game that attempts to introduce a realistic
stock buying experience to the players. The game utilizes the random number generation
capability of the operating system to mimic real-life stock unpredictable trends, while
giving players breathing room to better think about their investing strategies.

## Features Implemented

### Generation of random game sets or events

### Data structures for storing game status (e.g., arrays, STL containers)

### Dynamic memory management (e.g., dynamic arrays, linked lists, STL containers)

### File input/output (e.g., for loading/saving game status)
This game had options for players to create a new save, load an old save and delete
save upon the startup of the game. The saves are distinguished by global variable
std::string playerName. The name of the save folders are also in playerName. In each
saves, every stock has a seperate .save file, while other basic information are stored
in playerstatus.save and hsi in hsi.save . The saving process is automatic upon the end 
of everyround to prevent lost of advancements of the game (and also prevent rollback)

Moreover, this game relies heavily on c++17 library <filesystem> to maintain the tidiness
of files. It enable us to obtain the name of avaiable saves, create folders and deleting
saves.

### Program codes in multiple files (recall separate compilation)

### Proper indentation and naming styles

### In-code documentation

## Non-standard libraries used

## Compilation and Execution Instructions

## Credits
### Logo
The logo used here and in-game is generated with [Text to ASCII](https://www.asciiart.eu/text-to-ascii-art)
