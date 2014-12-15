#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N_MINE 10
#define BOARD_WIDTH  9
#define BOARD_HEIGHT 9

#define BUF_SIZE  256
#define TRUE  1
#define FALSE 0

#define UNCHECKED_MASK  ((unsigned char) 0x80)
#define BOMB            ((unsigned char) 0x7f)

static void
init_board(void);

static void
print_board(void);

static void
open_panel(int y, int x);

static char
check_sweeped(void);

static unsigned char board[BOARD_HEIGHT + 2][BOARD_WIDTH + 2] = {{0}};


/*!
 * @brief Entry point of this program
 * @return Exit-status
 */
int
main(void)
{
  static char buf[BUF_SIZE];
  int x, y;
  char sweeped;

  srand((unsigned int) time(NULL));
  printf("Start Minesweeper\n\n");
  for (;;) {
    init_board();
    sweeped = FALSE;
    while (!sweeped) {
      print_board();
      for (;;) {
        printf("where? [a-i][1-9] > ");
        fgets(buf, sizeof(buf), stdin);
        if (!strcmp(buf, "quit\n")) return EXIT_SUCCESS;
        if (strlen(buf) < 2) continue;
        if (buf[0] >= 'a' && buf[0] <= 'i') {
          x = buf[0] - 'a' + 1;
        } else if (buf[0] >= 'A' && buf[0] <= 'I') {
          x = buf[0] - 'A' + 1;
        } else {
          continue;
        }
        if (buf[1] >= '1' && buf[1] <= '9') {
          y = buf[1] - '0';
        } else {
          continue;
        }
        break;
      }
      open_panel(y, x);
      if (board[y][x] == BOMB) break;
      sweeped = check_sweeped();
    }
    print_board();
    if (sweeped) {
      printf("Good-Job!!!  You've sweeped all Mines in success.\n");
    } else {
      printf("Oops!!! You've hit a Mine...\n\n");
    }
    printf("\ntry again? [Y/N]");
    fgets(buf, sizeof(buf), stdin);
    if (!strcmp(buf, "n\n") || !strcmp(buf, "N\n")) {
      break;
    }
  }
  return EXIT_SUCCESS;
}


/*!
 * @brief Initialize board
 */
static void
init_board(void)
{
  int i, x, y;
  memset(board, 0, sizeof(board)); 
  for (i = 0; i < N_MINE; i++) {
    do {
      x = rand() % BOARD_WIDTH + 1;
      y = rand() % BOARD_HEIGHT + 1;
    } while (board[y][x] == BOMB);
    board[y][x] = BOMB;
    if (board[y - 1][x - 1] != BOMB) board[y - 1][x - 1] += 1;
    if (board[y - 1][x] != BOMB)     board[y - 1][x]     += 1;
    if (board[y - 1][x + 1] != BOMB) board[y - 1][x + 1] += 1;
    if (board[y][x - 1] != BOMB)     board[y][x - 1]     += 1;
    if (board[y][x + 1] != BOMB)     board[y][x + 1]     += 1;
    if (board[y + 1][x - 1] != BOMB) board[y + 1][x - 1] += 1;
    if (board[y + 1][x] != BOMB)     board[y + 1][x]     += 1;
    if (board[y + 1][x + 1] != BOMB) board[y + 1][x + 1] += 1;
  }
  for (y = 0; y < BOARD_HEIGHT + 2; y++) {
    for (x = 0; x < BOARD_WIDTH + 2; x++) {
      board[y][x] |= UNCHECKED_MASK;
    }
  }
}


/*!
 * @brief Print board
 */
static void
print_board(void)
{
  int x, y;
  printf("\n  |abcdefghi\n");
  printf("--+---------\n");
  for (y = 1; y <= BOARD_HEIGHT; y++) {
    printf("%2d|", y);
    for (x = 1; x <= BOARD_WIDTH; x++) {
      if (board[y][x] & UNCHECKED_MASK) {
        putchar('o');
      } else {
        switch (board[y][x]) {
          case 0:
            putchar('.');
            break;
          case 1:
          case 2:
          case 3:
          case 4:
          case 5:
          case 6:
          case 7:
          case 8:
            printf("%d", (int) board[y][x]);
            break;
          case BOMB:
            putchar('@');
            break;
        }
      }
    }
    puts("");
  }
  puts("");
}


/*!
 * @brief Open specified panel
 *
 * If there is no bombs around specified panel, open eight neighborhood panels
 * @param [in] y  Y-coordinate
 * @param [in] x  X-coordinate
 */
static void
open_panel(int y, int x)
{
  if (y < 1 || y > BOARD_HEIGHT || x < 1 || x > BOARD_WIDTH) {
    return;
  }
  /* Already opened */
  if (!(board[y][x] & UNCHECKED_MASK)) {
    return;
  }
  board[y][x] &= ~UNCHECKED_MASK;
  if (board[y][x] == 0) {
    open_panel(y - 1, x - 1);
    open_panel(y - 1, x);
    open_panel(y - 1, x + 1);
    open_panel(y, x - 1);
    open_panel(y, x + 1);
    open_panel(y + 1, x - 1);
    open_panel(y + 1, x);
    open_panel(y + 1, x + 1);
  }
}


/*!
 * @brief Check whether all non-bomb panel is opened or not.
 * @return If all non-bomb panel is opened, return 1, otherwise return 0.
 */
static char
check_sweeped(void)
{
  int x, y;
  for (y = 1; y <= BOARD_HEIGHT; y++) {
    for (x = 1; x <= BOARD_WIDTH; x++) {
      /* Specified panel is not opened though the panel is not bomb */
      if ((board[y][x] & ~UNCHECKED_MASK) != BOMB && (board[y][x] & UNCHECKED_MASK)) {
        return FALSE;
      }
    }
  }
  return TRUE;
}
