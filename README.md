Programing Systems 2 - Assignment 3
-
This repository contains the thrid assignment in the course Programming Systems 2 - a variant of the game "Coup".

The core of this assignment:
-
1. Understand the value and the use of virtual methods, inheritance and polymorphism in C++.
2. Implement a GUI - I chose to use SFML.
3. Throw exceptions if needed.
4. Create Test class to check functionality using doctest.

Makefile commands:
-
- make Main: activates the GUI and runs the game.
- make test: runs the tests cpp file with doctest.
- make valgrind: checks for memory leaks.
- make demo: runs the demo of the game.
- make clean: removes all irrelevant files.

Structur of my project
-
My project files are divided to 3 main directories.
GUI - contains all the implementation regarding to the SFML GUI and fonts.
Roles - contains all the different types of players in the game.
Test - contains the tests of the game. Each class has it's own TEST CASE and a SUB CASE for each function it has.
![Ex3Structure](https://github.com/user-attachments/assets/96080092-f97b-44ed-b59d-09736c3419ca)

Important note about the rules of the game:
-
1. A player is not allowed to perform two arrest in a row (in a bribe) on the same player.
2. A player who can't perfrom any action (peek is not an action) in his turn - his turn will be skipped.
3. If a player must "pay" to other player or to the cash box more coins than he owns - he will pay all he got.
4. A Baron has 50-50 precent chances to either win or lose when he makes an investment.

Important notes:
-
1. Each class has it's own description in the header file. All the functions are explained in the .cpp file in order to keep the header file clean and readable.
2. The GUI is using fonts from the Assets directory - it should not be removed or located in a different place in the project.
3. The demo is a simple run of the game without the use of the GUI.

Information sources:
-
1. Virtual Function in C++ - https://www.geeksforgeeks.org/virtual-function-cpp/
2. Inheritance in C++ - https://www.geeksforgeeks.org/inheritance-in-c/
3. C++ Polymorphism - https://www.geeksforgeeks.org/cpp-polymorphism/
4. C++ How To Generate Random Numbers - https://www.w3schools.com/cpp/cpp_howto_random_number.asp
5. SFML Graphics Library | Quick Tutorial - https://www.geeksforgeeks.org/sfml-graphics-library-quick-tutorial/
6. I also used the presentations that are given in the Moodle.

The game
-
Start page:
![image](https://github.com/user-attachments/assets/ba9aed30-b2d0-4607-bf39-b9eaf25e7c4b)

Register players:
![image](https://github.com/user-attachments/assets/7c319c2c-7e0e-4541-8f19-c4d2cba067cd)

A turn in the game:
![image](https://github.com/user-attachments/assets/45a2265a-650b-451d-8693-1f44fd9afd7d)

Select a player:
![image](https://github.com/user-attachments/assets/fa579dad-629b-4147-87b5-f936692ea99e)

Block a player:
![image](https://github.com/user-attachments/assets/f14330e7-3fed-49ed-af62-9034220576eb)

A win in the game:
![image](https://github.com/user-attachments/assets/b1658be0-6b7b-47f0-b4e2-f610a29d2458)
