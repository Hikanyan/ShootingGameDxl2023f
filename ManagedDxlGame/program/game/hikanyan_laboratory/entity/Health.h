#pragma once

class Health
{
public:
    int current_health;
    int max_health;

    Health(int maxHealth) : current_health(maxHealth), max_health(maxHealth)
    {
    }

    void TakeDamage(int amount)
    {
        current_health -= amount;
        if (current_health < 0)
        {
            current_health = 0;
            // プレイヤーの死亡ロジック
        }
    }

    void Heal(int amount)
    {
        current_health += amount;
        if (current_health > max_health)
        {
            current_health = max_health;
        }
    }

    bool IsAlive() const
    {
        return current_health > 0;
    }
};
