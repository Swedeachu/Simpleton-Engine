#pragma once
int RUNNING; // value for telling if engine is running or not, when FALSE the program closes
int FULLSCREEN; // value for telling if game window is in full screen mode or not

void startEngine(void);
void stopEngine(void);
void startFrame(void);
void completeFrame(void);
void setGameState(void (*initFunction)(), void (*loopFunction)(), void (*closeFunction)());
void handleFullScreen(void);
