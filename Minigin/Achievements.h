#pragma once

#pragma warning (push)
#pragma warning (disable: 4996)
#include <steam_api.h>
#pragma warning (pop)

#include <vector>


#define _ACH_ID( id, name ) { id, #id, name, "", 0, 0 }

enum EAchievements
{
	ACH_WIN_ONE_GAME = 0,
	ACH_WIN_100_GAMES = 1,
	ACH_HEAVY_FIRE = 2,
	ACH_TRAVEL_FAR_ACCUM = 3,
	ACH_TRAVEL_FAR_SINGLE = 4,
};

struct Achievement_t
{
	EAchievements m_eAchievementID;
	const char* m_pchAchievementID;
	char m_rgchName[128];
	char m_rgchDescription[256];
	bool m_bAchieved;
	int m_iIconImage;
};

class CSteamAchievements
{
public:
	CSteamAchievements(const std::vector<Achievement_t>& Achievements_t);

	bool RequestStats();
	bool SetAchievement(const char* ID);
	void HasReceivedAchievement(const char* ID, bool* hasAchieved);

	STEAM_CALLBACK(CSteamAchievements, OnUserStatsReceived, UserStatsReceived_t,
		m_CallbackUserStatsReceived);
	STEAM_CALLBACK(CSteamAchievements, OnUserStatsStored, UserStatsStored_t,
		m_CallbackUserStatsStored);
	STEAM_CALLBACK(CSteamAchievements, OnAchievementStored,
		UserAchievementStored_t, m_CallbackAchievementStored);


private:
	uint64_t m_AppID; // Our current AppID
	std::vector<Achievement_t> m_Achievements; // Achievements data
	int m_NumAchievements; // The number of Achievements
	bool m_bInitialized; // Have we called Request stats and received the callback?
};