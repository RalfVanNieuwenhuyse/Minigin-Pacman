#ifndef ACHIEVEMENTCHECKER_H
#define ACHIEVEMENTCHECKER_H

#pragma once
#include "Component.h"
#include "Event.h"
#include "Achievements.h"

namespace dae
{
    class AchievementChecker : public Component
    {
    public:
        AchievementChecker(GameObject* owner);

        ~AchievementChecker() = default;
        AchievementChecker(const AchievementChecker& other) = delete;
        AchievementChecker(AchievementChecker&& other) = delete;
        AchievementChecker& operator=(const AchievementChecker& other) = delete;
        AchievementChecker& operator=(AchievementChecker&& other) = delete;


    private:
        void CheckForWin(const dae::Event* e);

        unsigned const int m_MINScore{ 500 };

    };
}

#endif // ACHIEVEMENTCHECKER_H
