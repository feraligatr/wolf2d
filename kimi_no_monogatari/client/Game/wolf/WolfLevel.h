#ifndef _WOLF_LEVEL_H_
#define _WOLF_LEVEL_H_

// TODO: for now, we create a data struct for wolf level, and then later we will use 
// the data to create anything. or get data from here.
// we use a static function to got LevelData from a file, and save to it in another function.

// TODO: future we may chnage the file data format and import the version concept, then can add new feature.
// and support all version's readwrite.

// all the data will be public, use class descriptor just a custom.

#include "trStream.h"

enum PowType
{
//please provide description
	pow_none,			// not pow
	pow_gibs,			//  1% if <=10%; SLURPIESND
	pow_gibs2,			//  1% if <=10%; SLURPIESND
	pow_alpo,			//  4% if <100%; HEALTH1SND
	pow_firstaid,		// 25% if <100%; HEALTH2SND
	pow_key1,			// gold key;		GETKEYSND
	pow_key2,			// silver key;	GETKEYSND
	pow_key3,			// not used
	pow_key4,			// not used
	pow_cross,			//  100pts; BONUS1SND
	pow_chalice,		//  500pts; BONUS2SND
	pow_bible,			// 1000pts; BONUS3SND
	pow_crown,			// 5000pts; BONUS4SND
	pow_clip,			// 8bul if <99bul; GETAMMOSND
	pow_clip2,			// 4bul if <99bul; GETAMMOSND
	pow_machinegun,		// machine gun; GETMACHINESND
	pow_chaingun,		// gatling gun; GETGATLINGSND
	pow_food,			// 10% if <100%; HEALTH1SND
	pow_fullheal,		// 99%, 25bul; BONUS1UPSND
	pow_25clip,			// 25bul if <99bul; GETAMMOBOXSND
	pow_spear,			// spear of destiny!

	pow_last,
	pow_num = pow_last
// add new types <!only!> here (after last)

};

class WolfLevelConfig
{
public:
	static WolfLevelConfig* getDefaultConfig();

	// various Config class defines.
	// use class but not pair is for later extend.

	class StaticInfo
	{
	public:
		bool visible;
		PowType powType;
	};

	std::vector<StaticInfo> staticInfos;

private:
	WolfLevelConfig();
};

class WolfLevel
{
public:

	WolfLevel* createLevelFromStream(tree::Stream& s);

	// TODO: output later.

	std::string m_mapName;
	std::string m_musicName;
	// tileData
	u16* m_tileWalls;
	u16* m_tileObjects;
	u16* m_tileOthers;

};




#endif /* _WOLF_LEVEL_H_ */
