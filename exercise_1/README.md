# {CLEAN* CODE}:  Sample Code 1 [NAMES]

**Snake: a multi-platform terminal game**

This program implements a classic _Snake_ game to run on a shell window (in text mode). The game has been developed as an exercise for the topic **Names++** the Clean Code book of **Robert C. Martin**. The objective is to use the code found in this repository to exercise the concepts presented during the lesson.



---

### **How To Play**

Run the executable `CleanSnake` or run `make run` to start the game. Uses the keyboard arrows (:arrow_up:, :arrow_down:, :arrow_left:, :arrow_right:) to move the snake. The objective is to eat the *fruits* that appear on screen, without colliding against a wall or against itself.



---

### **How to Build**

The game has been developed using C++ and has `ncurses` as a dependency. Make sure your system has a recent C++ compiler (`clang 8.3.0` or later;  `gcc 9.3.0` or later ) and  `ncurses` (`libncurses / libncurses++` or `libncursesw10 / libncurses++w10` if building on windows). You can use a package management tool for simple and clean installation. `make` is also required to perform the build. 

To build and run:

```bash
make && make run
```

----------

