# Tetris
### SetUp on Linux (Ubuntu) system
1. Open the terminal
2. Update the Ubuntu package lists 
```
$sudo apt update && sudo apt dist-upgrade
```
3. Install the GNU compiler tools (gcc/g++) and the GDB debugger
```
$ sudo apt install build-essential gdb
```
4. Install git
```
$ sudo apt install git
```
5. Install SFML libraries
```
$ sudo install libsfml-dev
```
6. Clone the repository
```
$ git clone https://github.com/maidenlessCS/PA5 Tetris
```
7. Go to the Tetris directory
```
$ cd Tetris
```
8. Compile the project
```
$ g++ -std=C++11 *.cpp -o Tetris -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```
9. Run the game
```
$ ./Tetris
```
## Game description
The Game should boot up to a main menu where the player is greeted with a musical them and can choose to play or exit the game.