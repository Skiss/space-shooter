#ifndef CATEGORY_H
#define CATEGORY_H


namespace Category
{ 
    enum Type
    {
        Empty = 0,
        Scene = 1,
        PlayerEntity = 1 << 1,
        AllyEntity = 1 << 2,
        EnemyEntity = 1 << 3
    };
}

#endif