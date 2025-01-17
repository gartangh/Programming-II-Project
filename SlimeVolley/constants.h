#ifndef CONSTANTS_H
#define CONSTANTS_H

#define FPS 40.0

#define FONT_SIZE 26

#define RADIUS_SLIME 40
#define RADIUS_BALL 12
#define RADIUS_EYES 5
#define RADIUS_COLLISION (46.845)

#define COLLISION_BUFFER (1.2)

#define SLIME_1_INIT_X 150
#define SLIME_2_INIT_X 600
#define BALL_INIT_Y 133.5

#define SLIME_V_X 6
#define SLIME_V_Y 11.625

#define PUPILS_OFFSET_X_1 20
#define PUPILS_OFFSET_X_2 -20
#define PUPILS_OFFSET_Y 20

#define MAX_POINTS 7

#define FREEZE_TIME 1.2

#define REPLAY_MIN 0.5
#define REPLAY_MAX 2.0

#define GRAVITY_BALL (-.375)
#define GRAVITY_SLIME (-.750)
#define NO_GRAVITY 0

#define COY(x) (375-x-75)
#define COY_W_G(x) (x-75)
#define GROUND 0
#define MIDDLE (374)

#define POINTS_HEIGHT COY_W_G(340)

#define GAME_WIDTH 750

#define BOUNCINESS (1.0)

#define DIFFICULTY_AI3 (1) //From 0->1 (float)

#endif
