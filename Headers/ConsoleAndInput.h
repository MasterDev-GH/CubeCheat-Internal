#pragma once
// Updates the console
void printUI();

// responsible for handling input
void handleInput();

// a clean up function
void cleanUpHack(FILE *f);

// Show/hide console
void toggleConsole();

// Create a console
void setupConsole(FILE **f);