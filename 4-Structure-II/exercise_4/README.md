# {CLEAN* CODE}:  Sample Code 4 [STRUCTURE-II]

```
  _____          __         __   __               _______               __
 |   __ \.-----.|  |--.    |  |_|  |--.-----.    |     __|.-----.---.-.|  |--.-----.
 |   __ <|  _  ||  _  |    |   _|     |  -__|    |__     ||     |  _  ||    <|  -__|
 |______/|_____||_____|    |____|__|__|_____|    |_______||__|__|___._||__|__|_____| ver 0.4
```

**Snake: a multi-platform terminal game**

This version reiterates on the previous exercise to add the new features to the game (while providing a new practice-exercice for the second section of the book). The new features are:

- Implementation of InputLib
- Add 4-buttons controller support
- Implementation of Pause & Run feature
- Improve Makefile organization
- Add submodule OIS

---

### **How To Play**

Run the executable `CleanSnake` or run `make run` to start the game. Uses the keyboard arrows (:arrow_up:, :arrow_down:, :arrow_left:, :arrow_right:) to move the snake. The objective is to eat the *fruits* that appear on screen, without colliding against a wall or against itself.

**Screenshot**

Due to the lack of color and details in MD, you'll not be able to see all the amazing aesthetics we've prepared for this version :P

```
 _____          __         __   __               _______               __
|   __ \.-----.|  |--.    |  |_|  |--.-----.    |     __|.-----.---.-.|  |--.-----.
|   __ <|  _  ||  _  |    |   _|     |  -__|    |__     ||     |  _  ||    <|  -__|
|______/|_____||_____|    |____|__|__|_____|    |_______||__|__|___._||__|__|_____| ver 0.4

┌──────────────────────────────────────────────────────────────────────────────┐
│ Score: 0      Size: 4                                                        │
│──────────────────────────────────────────────────────────────────────────────│
│▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒│
│▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒~~~~~~▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒│
│▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒~~~~~▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒│
│▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒~~~~~▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒│
│▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒^▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒~~~~~~▒◆▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒│
│▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒^^^▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒~~~~~~▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒│
│▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒^^^^^▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒~~~~~▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒│
│▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒^^^^^^^▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒~~~~~▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒│
│▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒^^^^^^^^^▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒~~~~~▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒│
│▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒^^^^^^^^^^▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒~~~~~▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒│
│▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒^^^^^^^^^▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒~~~~~▒▒▒▒▒▒▒▒▒▒▒▒^▒▒▒▒▒▒│
│▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒^^^^^^^▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒~~~~~▒▒▒▒▒▒▒▒▒▒▒^^▒▒▒▒▒▒│
│▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒^^^^^▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒~~~~~▒▒▒▒▒▒▒▒^^^^^▒▒▒▒▒▒│
│▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒^^^▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒~~~~▒▒▒▒▒▒▒▒▒^^^^^▒▒▒▒▒▒│
│▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒^▒▒▒▒▒▒▒▒▒▒▒▒▒▒~~~~▒▒▒▒▒▒▒▒▒^^^^^^▒▒▒▒▒▒│
│▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒~~~~~▒▒▒▒▒▒▒▒▒^^^^^^▒▒▒▒▒▒│
│▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒~~~~~~▒▒▒▒▒▒▒▒^^^^^^▒▒▒▒▒▒▒│
│▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒~~~~~~~~~▒▒▒▒▒▒▒▒^^^^^▒▒▒▒▒▒▒▒│
│▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒~~~~~~~~~~▒▒▒▒▒▒▒▒^^^^^▒▒▒▒▒▒▒▒│
│▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒~~~~~~~~~~▒▒▒▒▒▒▒▒▒^▒▒▒▒▒▒▒▒▒▒▒│
└──────────────────────────────────────────────────────────────────────────────┘
                               *** PAUSED ***

```

---

### **How to Build**

The game has been developed using C++ and has `ncurses` and `OIS` (provided as submodule) as a dependency. Make sure your system has a recent C++ and OjectiveC++ (for macOS) compiler (`clang 8.3.0` or later;  `gcc 9.3.0` or later ) and  `ncurses` (`libncurses / libncurses++` or `libncursesw10 / libncurses++w10` if building on windows). You can use a package management tool for simple and clean installation. `make` is also required to perform the build. 

To build and run:

```bash
make && make run
```

----------

