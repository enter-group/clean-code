# {CLEAN* CODE}:  Sample Code 2 [FUNCTIONS]

**Snake: a multi-platform terminal game**

This version reiterates on the previous exercice to add the new features to the game (while providing a new practice-exercice for the second section of the book). The new features are:

- Scrollable Maps with different kinds of terrains and hazards;
- New graphcis and color;
- Restructured Rendering and general game logic;



---

### **How To Play**

Run the executable `CleanSnake` or run `make run` to start the game. Uses the keyboard arrows (:arrow_up:, :arrow_down:, :arrow_left:, :arrow_right:) to move the snake. The objective is to eat the *fruits* that appear on screen, without colliding against a wall or against itself.



**Screenshot**
Due to the lack of color in MD, you'll not be able to see all the amazing aesthetics we've prepared for this version :P

```
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
 Press F1 to exit

```





---

### **How to Build**

The game has been developed using C++ and has `ncurses` as a dependency. Make sure your system has a recent C++ compiler (`clang 8.3.0` or later;  `gcc 9.3.0` or later ) and  `ncurses` (`libncurses / libncurses++` or `libncursesw10 / libncurses++w10` if building on windows). You can use a package management tool for simple and clean installation. `make` is also required to perform the build. 

To build and run:

```bash
make && make run
```

----------

