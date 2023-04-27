# Arkanoid

[![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=flat&logo=c%2B%2B&logoColor=white)](https://en.cppreference.com/w/c/language)

Action game in C++

## Task

Implement basic **action game** for one or more players against computer.

**Requirements**
1. The game should include destroyable objects.
2. Players should be able to move.
3. Destroyed objects should leave behind bonuses with a certain probability.
4. The game should allow for loading maps from a file and saving scores to a file.
5. The game should utilize polymorphism.

## Description

Arkanoid, also known as Breakout, is a 2D game in which the player uses a paddle to hit a ball towards a wall of bricks. When the ball hits a brick, it is destroyed. The game is won when all bricks are destroyed, but if the ball falls below the paddle level, the player loses. The paddle can only be moved left or right. The speed of the ball gradually increases throughout the game. Bonuses are available, including extending the width of the paddle or slowing down the game temporarily when a brick is destroyed.
<p align="center">
  <img src="arkanoidThumbnail.png" alt="Arkanoid thumbnail" />
</p>

## Controls:

- **Option 1 - number pad:**
  - up: `8` (in menu)
  - down: `2` (in menu)
  - left: `4` (paddle movement)
  - right: `6` (paddle movement)
  - select option (like enter): `5`
- **Option 2 - "aswd":**
  - up: `w` (in menu)
  - down: `s` (in menu)
  - left: `a` (paddle movement)
  - right: `d` (paddle movement)
  - select option: `enter`
- pause: `p`
- quit to main menu: `q`

## How to run

### Software requirements
- **g++ compiler**
  - install on Ubuntu based Linux distributions by this command:
  ```bash
  sudo apt install build-essential
  ```
- **Makefile**
  - Ubuntu installation
  ```bash
  sudo apt install make
  ```
- **Doxygen** (optional for documentation)
  - Ubuntu installation
  ```bash
  sudo apt-get install doxygen - for ubuntu`
  ```

### Installation

To install the game, follow these steps:

- Clone the repository by running this command in your terminal:
  ```bash
  git clone https://github.com/janbabak/Arkanoid.git
  ```
- Navigate to the cloned folder using this command:
  ```bash
  cd Arkanoid
  ```
- To start the game, run this command:
  ```bash
  make run
  ```
- If you want to remove the build target, use this command:
  ```bash
  make clean
  ```
- To generate Doxygen documentation, run this command. The documentation will be located in the `/doc` folder. Simply open `index.html` in your browser to view it.
  ```bash
  make doc
  ```
