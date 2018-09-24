# EGP-410 (AI For Games) 

Template by: Jeff Timanus

Git Link: https://github.com/zap-twiz/EGP-410

Edited by: Josh Grazda

Git Link: https://github.com/Jagman926/EGP-410

## Compile Instructions
 * Download and unzip project folder
 * Open "steering.sln" file
 * Build code
 * Set steering project as startup project
 * Run project

## Input Instructions
 * Mouse Movement

 > Displays mouse coordinates

 * Mouse Click 

 > Moves player (black arrow) to coordinates

 * "Enter" Key 

 > Spawns new unit at random position with a WanderAndChase Steering

 * "D" Key

 > Deletes random unit (excludes player)

 * "Escape" Key

 > Exits game

## Additional Information
 * This repository contains three major directories:

     * DeanLib - Base utility library provided by Dean Lawson. Memory tracking and basic vector mathematics utilities.

     * External Libs - Allegro 5.0.10 support libraries.

     * Game AI - Base source code for EGP 410 Assignments

         * pathfinding

         * state machine

         * steering
