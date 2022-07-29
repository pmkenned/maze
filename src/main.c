// TODO:
// * find shortest path
// * interactive mode
// * better maze generation
// * prevent flickering

#include "timer.h"
#include "ansi_esc.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>

#define OUTFILE stdout
#define NELEMS(X) (sizeof(X)/sizeof(X[0]))
#define MS(x) x ## 000000L

#define TT 1
#define LL 2
#define TL 3

#define U 1
#define D 2
#define L 4
#define R 8
#define APPLIED 16

#define NR 20
#define NC 50

#define START_ROW (NR-1)
#define START_COL 0
#define EXIT_ROW 0
#define EXIT_COL (NC-1)

int maze_num;
int maze[NR][NC];

#if 0
int maze[][10] = {
  {TL, TT, TT, TL, TT, TL, TT, TL, TT,  0},
  {TL, LL, LL, TT, LL,  0, LL, TT, TT,  0},
  {LL, LL, TT, LL,  0, TL, TT, TL,  0, TL},
  {LL, TT, LL, TT, TT, LL, TL, TT, TL,  0},
  {LL, TL, TT,  0, TL,  0, LL, LL, TT,  0},
  {LL, LL, TT, TL, LL, TT,  0, LL, LL, TL},
  {LL, TT,  0,  0, TT,  0, TT,  0, LL, LL},
  {TL, TT,  0, LL, TL, LL, TL, TT,  0,  0},
  {LL, TL,  0,  0, LL,  0,  0, LL, TL, TT},
  { 0, TT, TT,  0,  0, TT, LL, TT,  0, LL},
};
#endif

#if 0
const char * maze_str[] = {
    "┌─────┬───┬───┬──────",
    "├─┐ ╷ └─┐ ╵ ╷ └───╴ ╷",
    "│ │ └─┐ ╵ ┌─┴─┬─╴ ┌─┤",
    "│ └─┐ └───┤ ┌─┴─┬─┘ │",
    "│ ┌─┴─╴ ┌─┘ │ ╷ └─╴ │",
    "│ │ ╶─┬─┤ ╶─┘ │ ╷ ┌─┤",
    "│ └─╴ ╵ └─╴ ╶─┘ │ │ │",
    "├───╴ ╷ ┌─┐ ┌───┘ ╵ │",
    "│ ┌─╴ ╵ │ ╵ ╵ ╷ ┌───┤",
    "╵ └───╴ ╵ ╶─┐ └─┘ ╷ │",
    "────────────┴─────┴─┘"
};
#endif

const char * guy_upper = "▀";
const char * guy_lower = "▄";
const char * guy = "▀";

size_t guy_row = START_ROW;
size_t guy_col = START_COL;

typedef struct {
    size_t row;
    size_t col;
} Location;

Location path_to_exit[NR*NC];
size_t num_path;

int past_locations[NR][NC];

int move_stack[NR*NC*3];
size_t move_stack_len;

static void
remember_current_location()
{
    past_locations[guy_row][guy_col] = 1;
}

static int
have_been_here_before(size_t r, size_t c)
{
    return past_locations[r][c];
}

static void
clear_screen(FILE * fp)
{
    fprintf(fp, "%c%c", 27, 99);
}

static int
guy_is_here(size_t r, size_t c)
{
    return guy_row+1 == r && guy_col == c;
}

static int
on_path_to_exit(size_t r, size_t c)
{
    for (size_t i = 0; i < num_path; i++) {
        Location pl = path_to_exit[i];
        if (pl.row == r && pl.col == c)
            return 1;
    }
    return 0;
}

static int have_been_here_before(size_t r, size_t c);

static void
print_guy_or(FILE * fp, size_t r, size_t c, const char * s)
{
    if (on_path_to_exit(r, c)) {
        ansi_set(fp, 1, ANSI_FG_GREEN);
        fprintf(fp, "%s", guy_upper);
        ansi_reset(fp);
#if 1
    } else if (isatty(fileno(fp)) && have_been_here_before(r, c)) {
        ansi_set(fp, 1, ANSI_FG_RED);
        fprintf(fp, "%s", guy_upper);
        ansi_reset(fp);
#endif
    } else {
        fprintf(fp, "%s", s);
    }
}

const char * box_chars[] = {
    " ", "╴", "╵", "┘",
    "╶", "─", "└", "┴",
    "╷", "┐", "│", "┤",
    "┌", "┬", "├", "┼" 
};

static void
print_maze(FILE * fp)
{
    if (isatty(fileno(fp)))
        clear_screen(fp);
    const char * tmp;
#if 0
    for (size_t r = 0; r < NR; r++) {
        fprintf(fp, "%s\n", maze_str[r]);
    }
    fprintf(fp, "\n");
#endif
    fprintf(fp, "maze %d:\n", maze_num);
    for (size_t r = 0; r < NR; r++) {
        for (size_t c = 0; c < NC; c++) {
            int x = 0;
            if (maze[r][c] & TT)
                x |= 4; // RIGHT
            if (maze[r][c] & LL)
                x |= 8; // BOTTOM
            if ((r > 0) && maze[r-1][c] & LL)
                x |= 2; // TOP
            if ((c > 0) && maze[r][c-1] & TT)
                x |= 1; // LEFT
            fprintf(fp, "%s", box_chars[x]);
            tmp = (x & 4) ? "─" : " ";
            if (r == 0)
                fprintf(fp, "%s", tmp);
            else
                print_guy_or(fp, r-1, c, tmp);
        }
        // print right wall
        if (r == 0)
            tmp = "╷";
        else
            tmp = (maze[r][NC-1] & TT) ? "┤" : "│";
        fprintf(fp, "%s\n", tmp);
    }
    // print bottom wall
    tmp = (maze[NR-1][0] & LL) ? "└" : "╶";
    fprintf(fp, "%s", tmp);
    print_guy_or(fp, START_ROW, START_COL, "─");
    for (size_t c = 1; c < NC; c++) {
        size_t r = NR;
        tmp = (maze[r-1][c] & LL) ? "┴" : "─";
        fprintf(fp, "%s", tmp);
        print_guy_or(fp, r-1, c, "─");
    }
    fprintf(fp, "┘\n");
    //fflush(fp);
}

static int
get_moves(size_t r, size_t c)
{
    int moves = 0;
    if ((r > 0) && !(maze[r][c] & TT))
        moves |= U;
    if ((c > 0) && !(maze[r][c] & LL))
        moves |= L;
    if ((r < NR-1) && !(maze[r+1][c] & TT))
        moves |= D;
    if ((c < NC-1) && !(maze[r][c+1] & LL))
        moves |= R;
    return moves;
}

static int
count_moves(int moves)
{
    int nmoves = 0;
    nmoves += (moves >> 0) & 1;
    nmoves += (moves >> 1) & 1;
    nmoves += (moves >> 2) & 1;
    nmoves += (moves >> 3) & 1;
    return nmoves;
}

static int
pick_random_move(int moves)
{
    int move = 0;
    while (1) {
        int s = rand() % 4;
        if (moves & (1 << s)) {
            move = moves & (1 << s);
            break;
        }
    }
    return move;
}

static void
push_moves_to_stack(int moves)
{
    if (moves & U)
        move_stack[move_stack_len++] = U;
    if (moves & D)
        move_stack[move_stack_len++] = D;
    if (moves & L)
        move_stack[move_stack_len++] = L;
    if (moves & R)
        move_stack[move_stack_len++] = R;
}

static void
push_moves_to_stack_shuffled(int moves)
{
    int x[4] = {0, 1, 2, 3};
    for (int i = 0; i < 4; i++) {
        int r = rand() % (4-i);
        int t = x[3-i];
        x[3-i] = x[r];
        x[r] = t;
    }

    for (int i = 0; i < 4; i++) {
        if ((x[i]==0) && (moves & U))
            move_stack[move_stack_len++] = U;
        if ((x[i]==1) && (moves & D))
            move_stack[move_stack_len++] = D;
        if ((x[i]==2) && (moves & L))
            move_stack[move_stack_len++] = L;
        if ((x[i]==3) && (moves & R))
            move_stack[move_stack_len++] = R;
    }
}

static void
apply_move(int move)
{
    move &= ~APPLIED;
    switch (move) {
        case U: guy_row--; break;
        case D: guy_row++; break;
        case L: guy_col--; break;
        case R: guy_col++; break;
        default: assert(0);
    }
}

static int
apply_top_move()
{
    int top_move = move_stack[move_stack_len-1];
    apply_move(top_move);
    move_stack[move_stack_len-1] |= APPLIED;
    path_to_exit[num_path++] = (Location){.row=guy_row, .col=guy_col};
    return top_move;
}

static void
undo_move(int move)
{
    move &= ~APPLIED;
    switch (move) {
        case U: guy_row++; break;
        case D: guy_row--; break;
        case L: guy_col++; break;
        case R: guy_col--; break;
        default: assert(0);
    }
}

static int
undo_and_pop_top_move()
{
    assert(num_path > 0);
    num_path--;
    undo_move(move_stack[--move_stack_len]);
    if (move_stack_len == 0)
        return 0;
    return move_stack[move_stack_len-1];
}

static int
top_move_is_applied()
{
    return move_stack[move_stack_len-1] & APPLIED;
}

static int
at_exit()
{
    return (guy_row == EXIT_ROW) && (guy_col == EXIT_COL);
}

static const char *
move_str(int move)
{
    if (move & U) return "U";
    if (move & D) return "D";
    if (move & L) return "L";
    if (move & R) return "R";
    return NULL;
}

static void
print_moves(FILE * fp)
{
    int n = 0;
    for (size_t i = 0; i < move_stack_len; i++) {
        int move = move_stack[i];
        if (move & APPLIED) {
            fprintf(fp, "%s ", move_str(move));
            if (++n % NC == 0)
                fprintf(fp, "\n");
        }
    }
    fprintf(fp, "\n");
}

static int
inverse_move(int move)
{
    move &= ~APPLIED;
    switch (move) {
        case U: return D;
        case D: return U;
        case L: return R;
        case R: return L;
        case 0: return 0;
        default: assert(0);
    }
}

static void
delay(int ms)
{
    if (isatty(fileno(OUTFILE)))
        nanosleep(&(struct timespec){.tv_sec = 0, .tv_nsec=ms*1000000L}, NULL);
}

static int
solve_no_goto()
{
    int prev_move = 0;
    while (1) {
        remember_current_location();
        int moves = get_moves(guy_row, guy_col) & ~inverse_move(prev_move);
        push_moves_to_stack(moves);
        do {
            if (count_moves(moves) == 0) {
                do {
                    if (move_stack_len <= 1)
                        return 0;
                    prev_move = undo_and_pop_top_move();
                } while (top_move_is_applied());
            }
            prev_move = apply_top_move();
        } while ((moves=0, have_been_here_before(guy_row, guy_col)));
        if (at_exit())
            break;
    }
    return 1;
}

static int
solve()
{
    int prev_move = 0;
    //print_maze(OUTFILE);
    while (1) {
        remember_current_location();
        int moves = get_moves(guy_row, guy_col) & ~inverse_move(prev_move);
        push_moves_to_stack(moves);
        if (count_moves(moves) == 0) {
undo_another:
            if (move_stack_len <= 1)
                return 0;
            prev_move = undo_and_pop_top_move();
            if (top_move_is_applied())
                goto undo_another;
        }
        prev_move = apply_top_move();
#if 0
        if (move_stack_len % 5 == 0) {
            print_maze(OUTFILE);
            delay(80);
        }
#endif
        if (have_been_here_before(guy_row, guy_col))
            goto undo_another;
        if (at_exit())
            break;
    }
    return 1;
}

static void
put_walls_around_perimeter()
{
    maze[0][0] = TL;
    for (size_t c = 1; c < NC; c++) {
        maze[0][c] = TT;
    }
    for (size_t r = 1; r < NR; r++) {
        maze[r][0] = LL;
    }
}

static void
put_walls_everywhere()
{
    for (size_t r = 0; r < NR; r++) {
        for (size_t c = 0; c < NC; c++) {
            maze[r][c] = TL;
        }
    }
}

static int
moves_inside_maze(size_t r, size_t c)
{
    int moves = 0;
    if (r > 0)
        moves |= U;
    if (c > 0)
        moves |= L;
    if (r < NR-1)
        moves |= D;
    if (c < NC-1)
        moves |= R;
    return moves;
}

static void
create_path_to_exit()
{
    int prev_move = 0;
    while (1) {
        remember_current_location();
        int moves = moves_inside_maze(guy_row, guy_col) & ~inverse_move(prev_move);
        push_moves_to_stack_shuffled(moves);
        if (count_moves(moves) == 0) {
undo_another:
            prev_move = undo_and_pop_top_move();
            if (top_move_is_applied())
                goto undo_another;
        }

        prev_move = apply_top_move();
        if (have_been_here_before(guy_row, guy_col))
            goto undo_another;
        if (prev_move & U) {
            maze[guy_row+1][guy_col] &= ~TT;
        } else if (prev_move & D) {
            maze[guy_row][guy_col] &= ~TT;
        } else if (prev_move & L) {
            maze[guy_row][guy_col+1] &= ~LL;
        } else {
            maze[guy_row][guy_col] &= ~LL;
        }
        if (at_exit())
            break;
#if 0
        print_maze(OUTFILE);
        delay(100);
#endif
    }
    guy_row = START_ROW;
    guy_col = START_COL;
    memset(past_locations, 0, sizeof(past_locations));
    move_stack_len = 0;
    num_path = 0;
    path_to_exit[num_path++] = (Location){.row=START_ROW, .col=START_COL};
}

static void
init_maze()
{
    guy_row = START_ROW;
    guy_col = START_COL;
    memset(past_locations, 0, sizeof(past_locations));
    num_path = 0;
    path_to_exit[num_path++] = (Location){.row=START_ROW, .col=START_COL};
    move_stack_len = 0;

    put_walls_around_perimeter();
    put_walls_everywhere();
    create_path_to_exit();

#if 0
    // randomize

    // top row
    for (size_t c = 1; c < NC; c++) {
        if (rand() % 2)
            maze[0][c] |= LL;
    }
    for (size_t r = 1; r < NR; r++) {
        // left side
        if (rand() % 2)
            maze[r][0] |= TT;
        for (size_t c = 1; c < NC; c++) {
            maze[r][c] = rand() % 4;
        }
    }
#endif

    maze[NR-1][0] &= ~LL; // start
    maze[0][NC-1] &= ~TT; // exit
}

#define NMAZES 10000
int main()
{
    DECLARE_TIMER(1);
    START_TIMER(1);
    int mazes_found = 0;
    for (maze_num = 0; maze_num < NMAZES; maze_num++) {
        init_maze();
        //print_maze(OUTFILE);
        //delay(900);
        //return 0;
        if (solve()) {
            print_maze(OUTFILE);
            print_moves(OUTFILE);
            mazes_found++;
            delay(900);
            //break;
#if 0
        } else {
            print_maze(OUTFILE);
            fprintf(OUTFILE, "no solution exists\n");
            delay(100);
#endif
        }
    }
    STOP_TIMER(1);
    printf("mazes found: %d/%d\n", mazes_found, NMAZES);
    printf("time: %ldms\n", GET_ELAPSED_MS(1));

#if 0
    for (guy_row = 0; guy_row < NR; guy_row++) {
        for (guy_col = 0; guy_col < NC; guy_col++) {
            print_maze();
            fprintf(OUTFILE, "\n");
        }
    }
#endif

#if 0
    for (int i = 0; i < 500; i++) {
        if (isatty(fileno(OUTFILE)))
            clear_screen(OUTFILE);
        print_maze(OUTFILE);
        int moves = get_moves(guy_row, guy_col);
        int move = pick_random_move(moves);
        apply_move(move);
        if (isatty(fileno(OUTFILE)))
            nanosleep(&(struct timespec){.tv_sec = 0, .tv_nsec=MS(20)}, NULL);
    }
#endif

#if 0
    for (size_t r = 0; r < NR; r++) {
        for (size_t c = 0; c < NC; c++) {
            int m = get_moves(r, c);
            if (m & L)
                fprintf(OUTFILE, "L");
            if (m & R)
                fprintf(OUTFILE, "R");
            if (m & U)
                fprintf(OUTFILE, "U");
            if (m & D)
                fprintf(OUTFILE, "D");
            fprintf(OUTFILE, "\t");
        }
        fprintf(OUTFILE, "\n");
    }
#endif
    return 0;
}
