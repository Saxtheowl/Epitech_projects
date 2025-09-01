/*
** EPITECH PROJECT, 2025
** Plazza
** File description:
**   Kitchen process interface
*/

#ifndef PLAZZA_KITCHEN_HPP
#define PLAZZA_KITCHEN_HPP

#include <sys/types.h>

struct KitchenProc { pid_t pid; int fd; int cap; int inflight; };

KitchenProc spawn_kitchen(int cooks, int restock_ms, double mult);

#endif

