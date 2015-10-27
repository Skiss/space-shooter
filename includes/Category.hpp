#ifndef CATEGORY_H
#define CATEGORY_H


namespace Category
{ 
    enum Type
    {
        Empty = 0,
        Scene = 1,
        PlayerEntity = 1 << 1,
        AllyAircraft = 1 << 2,
        AllyProjectile = 1 << 3,
        EnemyAircraft = 1 << 4,
        EnemyProjectile = 1 << 5
    };
}

#endif