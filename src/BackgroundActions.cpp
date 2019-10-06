//
// Created by Denis LEWANDOWSKI on 2019-10-06.
//


#include <random>
#include "../includes/includes.h"
#include "Game.hpp"

static int generatorFuncNumber(int count)
{
    std::random_device  random;
    std::mt19937        generator(random());

    return (int(generator() % count));
}

static t_stars	    *pushStarFront(t_stars *stars, int x, int y)
{
    t_stars *newStar;

    if (stars == nullptr)
    {
        stars = new t_stars;
        stars->x = x;
        stars->y = y;
        stars->next = nullptr;
        return (stars);
    }
    newStar = new t_stars;
    newStar->x = x;
    newStar->y = y;
    newStar->next = stars;
    stars = newStar;
    return (stars);
}

static void    moveStars(t_stars *stars)
{
    t_stars *star;

    star = stars;
    while (star != nullptr)
    {
        star->y++;
        star = star->next;
    }
}

static t_stars     *removeStars(t_stars *stars)
{
    t_stars     *star;
    t_stars     *prevStar = nullptr;

    star = stars;
    while (stars != nullptr)
    {
        if (stars->y >= HEIGHT)
        {
            if (prevStar == nullptr)
            {
                prevStar = stars;
                star = stars->next;
                delete prevStar;
                return (star);
            }
            else
            {
                prevStar->next = stars->next;
                delete stars;
                stars = prevStar->next;
                return (star);
            }
        }
        prevStar = stars;
        stars = stars->next;
    }
    return star;
}

static void    addStarsOnField(Game &game, t_stars *stars)
{
    while (stars != nullptr)
    {
        game.setFieldElem(stars->y, stars->x, '.');
        stars = stars->next;
    }
}

t_stars    *createBackgroud(Game &game, t_stars *stars)
{
    for (int i = 0; i < generatorFuncNumber(2); i++)
        stars = pushStarFront(stars, generatorFuncNumber(WIDTH - 1), 0);
    moveStars(stars);
    stars = removeStars(stars);
    addStarsOnField(game, stars);
    return (stars);
}