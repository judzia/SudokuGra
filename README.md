# 🎮 Sudoku in C
## 📖 Project Description
This project is about creating a Sudoku game in C language.
The game allows you to generate Sudoku boards of various sizes (4×4, 9×9, 16×16) with different difficulty levels.
All generated boards are guaranteed to have exactly one valid solution.

**The player's goal is to fill the board so that each row, column, and subgrid contains all numbers exactly once.**

# 🕹 Features
✅ Random Sudoku board generation with a valid solution

✅ Choice of board size: 4×4, 9×9, 16×16

✅ Choice of difficulty level (number of clues shown)

✅ Clear board display in the console

✅ Intuitive menu:

New Game

Save Game

Load Game

Instructions

Exit

✅ Saving and loading game states

✅ Move validation (checking if the move is correct)

✅ User-friendly prompts and messages

# 🧩 Sudoku Rules
Each row must contain all numbers from 1 to n without repetition.

Each column must contain all numbers from 1 to n without repetition.

Each subgrid (of size √n×√n) must also contain all numbers from 1 to n without repetition.

# ⚙️ Board Generation Algorithm
Creation of a full, valid Sudoku board using backtracking algorithm.

Random removal of numbers while ensuring the board has only one solution.


# 🛠 How to Run
= Clone the repository:

```git clone https://github.com/judzia/SudokuGra.git```

- Navigate to the project directory:

```cd SudokuGra```

- Compile the program:

```gcc -w -o sudoku main.c sudoku.c save_load.c```
(iykyk 🤫)

- Run the program:

```./sudoku```

# 📸 Screenshots
Main menu

![image](https://github.com/user-attachments/assets/6e5448c4-1668-48e2-b31b-aa2180734b97)

Gameplay

![image](https://github.com/user-attachments/assets/f99e947a-8120-43e6-8c89-a38c09e29b90)


# 😎 Favorite Meme of the Month

ja po sudoku
![image](https://github.com/user-attachments/assets/1ce9addd-1c78-4598-af46-267989f87fb1)

 ![image](https://github.com/user-attachments/assets/8367b914-366f-4c51-86dd-cd16c9df11c7)


# ⚡️ Known Issues
 No support for very large boards (e.g., 25×25) — performance limitations.

 Generating very difficult boards may take more time.

📚 Technologies Used
Language: C

Compiler: gcc

IDE: any (VS Code, CLion)

# 📋 Completed Requirements
 Clear and well-structured code

 Meaningful variable and function names

 Helpful comments for complex parts

 Modular and reusable code

 No memory leaks (proper memory management)

 Proper handling of pointers and array bounds

 Clear and readable console display

 User-friendly interface and instructions

# 🚀 Summary
Sudoku in C was an exciting challenge combining recursive algorithms, dynamic memory management, and text-based interfaces.
Creating the game required thoughtful code architecture, thorough testing, and a focus on both optimization and clarity.
