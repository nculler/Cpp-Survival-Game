# Survival Game Project

## Basic Information
- **Project:** Survival Game
- **Language:** C++

## Project Description
This project is a survival game where the player navigates a procedurally generated world, searching for food and water while avoiding hazards. The world is represented by a polymorphic 2D array of pointers to a `Land` base class, which is extended by various terrain types such as forests, deserts, and lakes. The player class tracks the player's position, hunger, thirst, and health, which influence the game’s outcome.

## Materials Used
- **Laptop with Internet Connection**
- **AWS Account with Cloud9 instance configured**

## Skills Showcased
- Object-oriented programming with polymorphism and inheritance
- Virtual functions and pure abstract classes
- 2D array manipulation
- Game state management and player interactions
- Handling user input and boundary conditions

## How to Run
1. Implement the base and derived classes:
   - `Land` (abstract base class with virtual functions `getDescription()` and `visit(Player &p)`).
   - Derived classes such as `Forest`, `Desert`, `Lake` (each affecting the player differently).
   - `Player` class to track position and stats (hunger, thirst, health).
2. Randomly generate a 10x10 map with different terrain types.
3. Implement player movement with the following rules:
   - Players can move north, south, east, or west.
   - If a player moves beyond the boundary, implement a **wrap-around** (e.g., moving west from (0,5) places the player at (9,5)).
   - Each move decreases hunger and thirst; if either reaches zero, health decreases.
4. Extend the base gameplay by adding at least **three new land types** with unique random events (e.g., encountering wildlife, finding a town, meeting a traveler who provides items).
5. Ensure robust user input handling to prevent crashes or invalid inputs.
6. Compile and run the game using a C++ compiler:
   ```sh
   g++ -o survival_game main.cpp
   ./survival_game
   ```

## Additional Information
Ensure that the code properly handles boundary conditions, user input validation, and unique terrain interactions to enhance the gameplay experience.

## Author
Nathan Culler
