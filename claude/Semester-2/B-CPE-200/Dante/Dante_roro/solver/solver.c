/*
** EPITECH PROJECT, 2024
** Dante's Star
** File description:
** Maze solver using BFS algorithm
*/

#define _GNU_SOURCE
#include "../include/dante.h"

queue_t *create_queue(void)
{
    queue_t *queue = malloc(sizeof(queue_t));
    
    if (!queue)
        return NULL;
    
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

void enqueue(queue_t *queue, point_t point)
{
    queue_node_t *new_node = malloc(sizeof(queue_node_t));
    
    if (!new_node)
        return;
    
    new_node->point = point;
    new_node->next = NULL;
    
    if (queue->rear) {
        queue->rear->next = new_node;
    } else {
        queue->front = new_node;
    }
    queue->rear = new_node;
}

point_t dequeue(queue_t *queue)
{
    point_t point = {-1, -1};
    queue_node_t *temp;
    
    if (!queue->front)
        return point;
    
    point = queue->front->point;
    temp = queue->front;
    queue->front = queue->front->next;
    
    if (!queue->front)
        queue->rear = NULL;
    
    free(temp);
    return point;
}

int is_queue_empty(queue_t *queue)
{
    return queue->front == NULL;
}

void free_queue(queue_t *queue)
{
    while (!is_queue_empty(queue)) {
        dequeue(queue);
    }
    free(queue);
}

maze_t *load_maze(const char *filename)
{
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    ssize_t read_len;
    maze_t *maze;
    int height = 0, width = 0;
    int i = 0;

    file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        return NULL;
    }

    while ((read_len = getline(&line, &len, file)) != -1) {
        if (read_len > 0 && line[read_len - 1] == '\n') {
            line[read_len - 1] = '\0';
            read_len--;
        }
        if (width == 0) {
            width = read_len;
        }
        height++;
    }

    if (width == 0 || height == 0) {
        fclose(file);
        free(line);
        return NULL;
    }

    rewind(file);
    
    maze = create_maze(width, height);
    if (!maze) {
        fclose(file);
        free(line);
        return NULL;
    }

    while ((read_len = getline(&line, &len, file)) != -1 && i < height) {
        if (read_len > 0 && line[read_len - 1] == '\n') {
            line[read_len - 1] = '\0';
            read_len--;
        }
        
        if (read_len > 0) {
            strncpy(maze->grid[i], line, width);
            maze->grid[i][width] = '\0';
            i++;
        }
    }

    fclose(file);
    free(line);
    return maze;
}

int is_valid_pos(maze_t *maze, int x, int y)
{
    return x >= 0 && x < maze->width && y >= 0 && y < maze->height;
}

int bfs_solve(maze_t *maze)
{
    queue_t *queue;
    point_t **parent;
    int **visited;
    point_t current, neighbor;
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    int i, found = 0;

    queue = create_queue();
    if (!queue)
        return 0;

    visited = malloc(maze->height * sizeof(int *));
    parent = malloc(maze->height * sizeof(point_t *));
    
    for (i = 0; i < maze->height; i++) {
        visited[i] = calloc(maze->width, sizeof(int));
        parent[i] = malloc(maze->width * sizeof(point_t));
        for (int j = 0; j < maze->width; j++) {
            parent[i][j].x = -1;
            parent[i][j].y = -1;
        }
    }

    if (maze->grid[0][0] == WALL) {
        free_queue(queue);
        for (i = 0; i < maze->height; i++) {
            free(visited[i]);
            free(parent[i]);
        }
        free(visited);
        free(parent);
        return 0;
    }

    point_t start = {0, 0};
    enqueue(queue, start);
    visited[0][0] = 1;

    while (!is_queue_empty(queue) && !found) {
        current = dequeue(queue);

        if (current.x == maze->width - 1 && current.y == maze->height - 1) {
            found = 1;
            break;
        }

        for (i = 0; i < 4; i++) {
            neighbor.x = current.x + dx[i];
            neighbor.y = current.y + dy[i];

            if (is_valid_pos(maze, neighbor.x, neighbor.y) && 
                !visited[neighbor.y][neighbor.x] && 
                maze->grid[neighbor.y][neighbor.x] != WALL) {
                
                visited[neighbor.y][neighbor.x] = 1;
                parent[neighbor.y][neighbor.x] = current;
                enqueue(queue, neighbor);
            }
        }
    }

    if (found) {
        current.x = maze->width - 1;
        current.y = maze->height - 1;
        
        while (!(current.x == 0 && current.y == 0)) {
            if (!(current.x == maze->width - 1 && current.y == maze->height - 1)) {
                maze->grid[current.y][current.x] = SOLUTION;
            }
            current = parent[current.y][current.x];
        }
    }

    free_queue(queue);
    for (i = 0; i < maze->height; i++) {
        free(visited[i]);
        free(parent[i]);
    }
    free(visited);
    free(parent);
    
    return found;
}

int solve_maze(maze_t *maze)
{
    return bfs_solve(maze);
}

void print_solution(maze_t *maze)
{
    print_maze(maze);
}

int main(int argc, char **argv)
{
    maze_t *maze;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s maze_file\n", argv[0]);
        return 84;
    }

    maze = load_maze(argv[1]);
    if (!maze) {
        fprintf(stderr, "Error: Cannot load maze\n");
        return 84;
    }

    if (solve_maze(maze)) {
        print_solution(maze);
    } else {
        printf("no solution found\n");
    }

    free_maze(maze);
    return 0;
}