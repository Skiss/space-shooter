#include "Data.hpp"

#include "Aircraft.hpp"
#include "Pickup.hpp"
#include "Projectile.hpp"


namespace Data
{
    std::vector<AircraftData> Data::initAircraftData()
    {
        std::vector<AircraftData> data(Aircraft::TypeCount);

        data[Aircraft::Eagle].maxHp = 100;
        data[Aircraft::Eagle].hp = 100;
        data[Aircraft::Eagle].speed = 200.f;
        data[Aircraft::Eagle].fireRate = 2.f;
        data[Aircraft::Eagle].textureID = TextureID::Eagle;

        data[Aircraft::Raptor].maxHp = 20;
        data[Aircraft::Raptor].hp = 20;
        data[Aircraft::Raptor].speed = 80.f;
        data[Aircraft::Raptor].fireRate = 2.f;
        data[Aircraft::Raptor].textureID = TextureID::Raptor;
        data[Aircraft::Raptor].movements.push_back(Movement{ 45, 80 });
        data[Aircraft::Raptor].movements.push_back(Movement{ -45, 160 });
        data[Aircraft::Raptor].movements.push_back(Movement{ 45, 80 });

        data[Aircraft::Avenger].maxHp = 40;
        data[Aircraft::Avenger].hp = 40;
        data[Aircraft::Avenger].speed = 50.f;
        data[Aircraft::Avenger].fireRate = 2.f;
        data[Aircraft::Avenger].textureID = TextureID::Avenger;
        data[Aircraft::Avenger].movements.push_back(Movement{ 45, 50 });
        data[Aircraft::Avenger].movements.push_back(Movement{ 0, 50 });
        data[Aircraft::Avenger].movements.push_back(Movement{ -45, 100 });
        data[Aircraft::Avenger].movements.push_back(Movement{ 0, 50 });
        data[Aircraft::Avenger].movements.push_back(Movement{ 45, 50 });

        return data;
    }

    std::vector<ProjectileData> initProjectileData()
    {
        std::vector<ProjectileData> data(Projectile::TypeCount);

        data[Projectile::EnemyMissile].damage = 200;
        data[Projectile::EnemyMissile].speed = 150.f;
        data[Projectile::EnemyMissile].homingFactor = 12.f;
        data[Projectile::EnemyMissile].textureID = TextureID::Missile;
        data[Projectile::EnemyMissile].target_ = nullptr;

        data[Projectile::AllyMissile] = data[Projectile::EnemyMissile];

        data[Projectile::EnemyBullet].damage = 10;
        data[Projectile::EnemyBullet].speed = 300.f;
        data[Projectile::EnemyBullet].homingFactor = 1.f;
        data[Projectile::EnemyBullet].textureID = TextureID::Bullet;

        data[Projectile::AllyBullet] = data[Projectile::EnemyBullet];

        return data;
    }

    std::vector<PickupData> initPickupData()
    {
        std::vector<PickupData> data(Pickup::TypeCount);

        data[Pickup::FireRate].textureID = TextureID::FireRate;
        data[Pickup::FireRate].action = [](Aircraft& a) { a.increaseFireRate(); };

        data[Pickup::HealthRefill].textureID = TextureID::HealthRefill;
        data[Pickup::HealthRefill].action = [](Aircraft& a) { a.repair(20); };

        return data;
    }
}
