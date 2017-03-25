#define LOAD_ASSETS()  GD.safeload("myassets.gd2");
#define WALK_HANDLE 0
#define WALK_WIDTH 60
#define WALK_HEIGHT 50
#define WALK_CELLS 2
#define Idle_HANDLE 1
#define Idle_WIDTH 160
#define Idle_HEIGHT 140
#define Idle_CELLS 2
#define Golpe_HANDLE 2
#define Golpe_WIDTH 185
#define Golpe_HEIGHT 130
#define Golpe_CELLS 2
#define Muerte_HANDLE 3
#define Muerte_WIDTH 195
#define Muerte_HEIGHT 90
#define Muerte_CELLS 1
#define ASSETS_END 232900UL
static const shape_t WALK_SHAPE = {0, 60, 50, 0};
static const shape_t Idle_SHAPE = {1, 160, 140, 0};
static const shape_t Golpe_SHAPE = {2, 185, 130, 0};
static const shape_t Muerte_SHAPE = {3, 195, 90, 0};

