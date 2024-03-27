#include <SDL.h>
#include <iostream>
#include <deque>
#include <random>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int BLOCK_SIZE = 20;
const int INITIAL_SNAKE_LENGTH = 3;

struct Point {
    int x, y;
};

enum Direction { UP, DOWN, LEFT, RIGHT };

class SnakeGame {
public:
    SnakeGame();
    ~SnakeGame();
    void run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::deque<Point> snake;
    Point food;
    Direction direction;
    bool running;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> dis;

    void handleEvents();
    void update();
    void render();
    void spawnFood();
    bool checkCollision();
};

SnakeGame::SnakeGame() : gen(rd()), dis(0, (WINDOW_WIDTH / BLOCK_SIZE) - 1) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Point initialPos;
    initialPos.x = WINDOW_WIDTH / 2;
    initialPos.y = WINDOW_HEIGHT / 2;
    snake.push_front(initialPos);
    for (int i = 1; i < INITIAL_SNAKE_LENGTH; ++i) {
        Point newPos;
        newPos.x = snake.front().x - BLOCK_SIZE;
        newPos.y = snake.front().y;
        snake.push_back(newPos);
    }
    spawnFood();
    direction = RIGHT;
    running = true;
}

SnakeGame::~SnakeGame() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SnakeGame::run() {
    while (running) {
        handleEvents();
        update();
        render();
        SDL_Delay(100);
    }
}

void SnakeGame::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
            break;
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                case SDLK_w:
                    if (direction != DOWN)
                        direction = UP;
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    if (direction != UP)
                        direction = DOWN;
                    break;
                case SDLK_LEFT:
                case SDLK_a:
                    if (direction != RIGHT)
                        direction = LEFT;
                    break;
                case SDLK_RIGHT:
                case SDLK_d:
                    if (direction != LEFT)
                        direction = RIGHT;
                    break;
            }
        }
    }
}

void SnakeGame::update() {
    Point new_head = snake.front();
    switch (direction) {
        case UP:
            new_head.y -= BLOCK_SIZE;
            break;
        case DOWN:
            new_head.y += BLOCK_SIZE;
            break;
        case LEFT:
            new_head.x -= BLOCK_SIZE;
            break;
        case RIGHT:
            new_head.x += BLOCK_SIZE;
            break;
    }
    snake.push_front(new_head);
    if (snake.front().x == food.x && snake.front().y == food.y) {
        spawnFood();
    } else {
        snake.pop_back();
    }
    if (checkCollision()) {
        running = false;
    }
}

void SnakeGame::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (std::deque<Point>::const_iterator it = snake.begin(); it != snake.end(); ++it) {
        SDL_Rect rect = {it->x, it->y, BLOCK_SIZE, BLOCK_SIZE};
        SDL_RenderFillRect(renderer, &rect);
    }
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect = {food.x, food.y, BLOCK_SIZE, BLOCK_SIZE};
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}

void SnakeGame::spawnFood() {
    food.x = dis(gen) * BLOCK_SIZE;
    food.y = dis(gen) * BLOCK_SIZE;
}

bool SnakeGame::checkCollision() {
    if (snake.front().x < 0 || snake.front().x >= WINDOW_WIDTH || snake.front().y < 0 || snake.front().y >= WINDOW_HEIGHT) {
        return true;
    }
    for (std::deque<Point>::iterator it = snake.begin() + 1; it != snake.end(); ++it) {
        if (it->x == snake.front().x && it->y == snake.front().y) {
            return true;
        }
    }
    return false;
}

int main() {
    SnakeGame game;
    game.run();
    return 0;
}
