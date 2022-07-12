// I WANT TO PLAY WITH YOU
//        YOUR FRIEND, AI

#include <stdio.h>

int i = 0;
int j = 0;
int SCREEN_WIDTH = 82;
int SCREEN_HEIGHT = 27;
int SCORE_HEIGHT = 5;
int ROCKET_START_Y1 = 13;
int ROCKET_START_Y2 = 13;
int BALL_X = 41;
int BALL_Y = 13;
int SCORE1 = 0;
int SCORE2 = 0;
int vector_X = -1;
int vector_Y = 1;
char hor = '-';
char ver = '|';
char ball = 'o';
char c;
char player_key;
char space = ' ';

void screen_rendering(int y, int x, int t_y, int r1_y, int r2_y, char h, char v,
                      char b, int s1, int s2, int b_x, int b_y) {
  while (i < t_y) {
    j = 0;
    while (j < x) {
      if (i == 0 || i == t_y - 1) {
        printf("%c", hor);
      } else if (i == t_y / 2 && j == x / 3) {
        printf("Player one: %d | Player two: %d", s1, s2);
      } else {
        printf(" ");
      }
      j++;
    }
    printf("\n");
    i++;
  }
  i = 0;
  while (i < y) {
    j = 0;
    while (j < x) {
      if (i == 0 || i == y - 1) {
        printf("%c", h);
      } else if (j == 0 || j == x - 1) {
        printf("%c", v);
      } else if (j == 2 && (i == r1_y || i == r1_y - 1 || i == r1_y + 1)) {
        printf("]");
      } else if (j == 79 && (i == r2_y || i == r2_y - 1 || i == r2_y + 1)) {
        printf("[");
      } else if (j == b_x && i == b_y) {
        printf("%c", b);
      } else if (j == x / 2) {
        printf("%c", v);
      } else {
        printf(" ");
      }
      ++j;
    }
    printf("\n");
    ++i;
  }
}

void moveRocket(int r1, int r2, char p1) {
  if ((p1 == 'z' || p1 == 'Z') && (r1 < 24)) {
    ROCKET_START_Y1++;
  } else if ((p1 == 'a' || p1 == 'A') && (r1 > 2)) {
    ROCKET_START_Y1--;
  } else if ((p1 == 'm' || p1 == 'M') && (r2 < 24)) {
    ROCKET_START_Y2++;
  } else if ((p1 == 'k' || p1 == 'K') && (r2 > 2)) {
    ROCKET_START_Y2--;
  }
}

int moveBall_x(int b_x, int b_y, int v_x, int r1_y, int r2_y) {
  if (b_x == 3 && (b_y == r1_y || b_y == r1_y - 1 || b_y == r1_y + 1)) {
    v_x = (-1) * v_x;
  }
  if (b_x == 78 && (b_y == r2_y || b_y == r2_y - 1 || b_y == r2_y + 1)) {
    v_x = (-1) * v_x;
  }
  return v_x;
}
int moveBall_y(int b_y, int v_y) {
  if (b_y == 1 || b_y == 26) {
    v_y = (-1) * v_y;
  }
  return v_y;
}

int main(void) {
  while (SCORE1 < 21 && SCORE2 < 21) {
    screen_rendering(SCREEN_HEIGHT, SCREEN_WIDTH, SCORE_HEIGHT, ROCKET_START_Y1,
                     ROCKET_START_Y2, hor, ver, ball, SCORE1, SCORE2, BALL_X,
                     BALL_Y);
    scanf("%c", &player_key);
    if (player_key != space) {
      moveRocket(ROCKET_START_Y1, ROCKET_START_Y2, player_key);
      vector_X = moveBall_x(BALL_X, BALL_Y, vector_X, ROCKET_START_Y1,
                            ROCKET_START_Y2);
      vector_Y = moveBall_y(BALL_Y, vector_Y);
      BALL_X = BALL_X + vector_X;
      BALL_Y = BALL_Y + vector_Y;
      if (BALL_X == 1) {
        SCORE2++;
        BALL_X = 41;
        BALL_Y = 13;
        ROCKET_START_Y1 = 13;
        ROCKET_START_Y2 = 13;
      } else if (BALL_X == 80) {
        SCORE1++;
        BALL_X = 41;
        BALL_Y = 13;
        vector_X = 1;
        vector_Y = -1;
        ROCKET_START_Y1 = 13;
        ROCKET_START_Y2 = 13;
      }
    }
  }
  if (SCORE1 == 21) {
    printf("Congratulations, Player one wins!");
  } else {
    printf("Congratulations, Player two wins!");
  }
}
