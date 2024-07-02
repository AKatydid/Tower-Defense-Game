#include "manager/resource_manager.h"

bool ResourcesManager::load_from_file(SDL_Renderer* renderer)
{
	texture_pool[ResID::Tex_Tileset] = IMG_LoadTexture(renderer, "asset/tileset.png");

	texture_pool[ResID::Tex_Player] = IMG_LoadTexture(renderer, "asset/player.png");
	texture_pool[ResID::Tex_Archer] = IMG_LoadTexture(renderer, "asset/tower_archer.png");
	texture_pool[ResID::Tex_Axeman] = IMG_LoadTexture(renderer, "asset/tower_axeman.png");
	texture_pool[ResID::Tex_Gunner] = IMG_LoadTexture(renderer, "asset/tower_gunner.png");

	texture_pool[ResID::Tex_Slime] = IMG_LoadTexture(renderer, "asset/enemy_slime.png");
	texture_pool[ResID::Tex_KingSlime] = IMG_LoadTexture(renderer, "asset/enemy_king_slime.png");
	texture_pool[ResID::Tex_Skeleton] = IMG_LoadTexture(renderer, "asset/enemy_skeleton.png");
	texture_pool[ResID::Tex_Goblin] = IMG_LoadTexture(renderer, "asset/enemy_goblin.png");
	texture_pool[ResID::Tex_GoblinPriest] = IMG_LoadTexture(renderer, "asset/enemy_goblin_priest.png");
	texture_pool[ResID::Tex_SlimeSketch] = IMG_LoadTexture(renderer, "asset/enemy_slime_sketch.png");
	texture_pool[ResID::Tex_KingSlimeSketch] = IMG_LoadTexture(renderer, "asset/enemy_king_slime_sketch.png");
	texture_pool[ResID::Tex_SkeletonSketch] = IMG_LoadTexture(renderer, "asset/enemy_skeleton_sketch.png");
	texture_pool[ResID::Tex_GoblinSketch] = IMG_LoadTexture(renderer, "asset/enemy_goblin_sketch.png");
	texture_pool[ResID::Tex_GoblinPriestSketch] = IMG_LoadTexture(renderer, "asset/enemy_goblin_priest_sketch.png");

	texture_pool[ResID::Tex_BulletArrow] = IMG_LoadTexture(renderer, "asset/bullet_arrow.png");
	texture_pool[ResID::Tex_BulletAxe] = IMG_LoadTexture(renderer, "asset/bullet_axe.png");
	texture_pool[ResID::Tex_BulletShell] = IMG_LoadTexture(renderer, "asset/bullet_shell.png");

	texture_pool[ResID::Tex_Coin] = IMG_LoadTexture(renderer, "asset/coin.png");
	texture_pool[ResID::Tex_Home] = IMG_LoadTexture(renderer, "asset/home.png");

	texture_pool[ResID::Tex_EffectFlash_Up] = IMG_LoadTexture(renderer, "asset/effect_flash_up.png");
	texture_pool[ResID::Tex_EffectFlash_Down] = IMG_LoadTexture(renderer, "asset/effect_flash_down.png");
	texture_pool[ResID::Tex_EffectFlash_Left] = IMG_LoadTexture(renderer, "asset/effect_flash_left.png");
	texture_pool[ResID::Tex_EffectFlash_Right] = IMG_LoadTexture(renderer, "asset/effect_flash_right.png");
	texture_pool[ResID::Tex_EffectImpact_Up] = IMG_LoadTexture(renderer, "asset/effect_impact_up.png");
	texture_pool[ResID::Tex_EffectImpact_Down] = IMG_LoadTexture(renderer, "asset/effect_impact_down.png");
	texture_pool[ResID::Tex_EffectImpact_Left] = IMG_LoadTexture(renderer, "asset/effect_impact_left.png");
	texture_pool[ResID::Tex_EffectImpact_Right] = IMG_LoadTexture(renderer, "asset/effect_impact_right.png");
	texture_pool[ResID::Tex_EffectExplode] = IMG_LoadTexture(renderer, "asset/effect_explode.png");

	texture_pool[ResID::Tex_UISelectCursor] = IMG_LoadTexture(renderer, "asset/ui_select_cursor.png");
	texture_pool[ResID::Tex_UIPlaceIdle] = IMG_LoadTexture(renderer, "asset/ui_place_idle.png");
	texture_pool[ResID::Tex_UIPlaceHoveredTop] = IMG_LoadTexture(renderer, "asset/ui_place_hovered_top.png");
	texture_pool[ResID::Tex_UIPlaceHoveredLeft] = IMG_LoadTexture(renderer, "asset/ui_place_hovered_left.png");
	texture_pool[ResID::Tex_UIPlaceHoveredRight] = IMG_LoadTexture(renderer, "asset/ui_place_hovered_right.png");
	texture_pool[ResID::Tex_UIUpgradeIdle] = IMG_LoadTexture(renderer, "asset/ui_upgrade_idle.png");
	texture_pool[ResID::Tex_UIUpgradeHoveredTop] = IMG_LoadTexture(renderer, "asset/ui_upgrade_hovered_top.png");
	texture_pool[ResID::Tex_UIUpgradeHoveredLeft] = IMG_LoadTexture(renderer, "asset/ui_upgrade_hovered_left.png");
	texture_pool[ResID::Tex_UIUpgradeHoveredRight] = IMG_LoadTexture(renderer, "asset/ui_upgrade_hovered_right.png");
	texture_pool[ResID::Tex_UIHomeAvatar] = IMG_LoadTexture(renderer, "asset/ui_home_avatar.png");
	texture_pool[ResID::Tex_UIPlayerAvatar] = IMG_LoadTexture(renderer, "asset/ui_player_avatar.png");
	texture_pool[ResID::Tex_UIHeart] = IMG_LoadTexture(renderer, "asset/ui_heart.png");
	texture_pool[ResID::Tex_UICoin] = IMG_LoadTexture(renderer, "asset/ui_coin.png");
	texture_pool[ResID::Tex_UIGameOverBar] = IMG_LoadTexture(renderer, "asset/ui_game_over_bar.png");
	texture_pool[ResID::Tex_UIWinText] = IMG_LoadTexture(renderer, "asset/ui_win_text.png");
	texture_pool[ResID::Tex_UILossText] = IMG_LoadTexture(renderer, "asset/ui_loss_text.png");

	for (const auto& pair : texture_pool)
		if (!pair.second) return false;

	sound_pool[ResID::Sound_ArrowFire_1] = Mix_LoadWAV("asset/sound_arrow_fire_1.mp3");
	sound_pool[ResID::Sound_ArrowFire_2] = Mix_LoadWAV("asset/sound_arrow_fire_2.mp3");
	sound_pool[ResID::Sound_AxeFire] = Mix_LoadWAV("asset/sound_axe_fire.wav");
	sound_pool[ResID::Sound_ShellFire] = Mix_LoadWAV("asset/sound_shell_fire.wav");
	sound_pool[ResID::Sound_ArrowHit_1] = Mix_LoadWAV("asset/sound_arrow_hit_1.mp3");
	sound_pool[ResID::Sound_ArrowHit_2] = Mix_LoadWAV("asset/sound_arrow_hit_2.mp3");
	sound_pool[ResID::Sound_ArrowHit_3] = Mix_LoadWAV("asset/sound_arrow_hit_3.mp3");
	sound_pool[ResID::Sound_AxeHit_1] = Mix_LoadWAV("asset/sound_axe_hit_1.mp3");
	sound_pool[ResID::Sound_AxeHit_2] = Mix_LoadWAV("asset/sound_axe_hit_2.mp3");
	sound_pool[ResID::Sound_AxeHit_3] = Mix_LoadWAV("asset/sound_axe_hit_3.mp3");
	sound_pool[ResID::Sound_ShellHit] = Mix_LoadWAV("asset/sound_shell_hit.mp3");

	sound_pool[ResID::Sound_Flash] = Mix_LoadWAV("asset/sound_flash.wav");
	sound_pool[ResID::Sound_Impact] = Mix_LoadWAV("asset/sound_impact.wav");

	sound_pool[ResID::Sound_Coin] = Mix_LoadWAV("asset/sound_coin.mp3");
	sound_pool[ResID::Sound_HomeHurt] = Mix_LoadWAV("asset/sound_home_hurt.wav");
	sound_pool[ResID::Sound_PlaceTower] = Mix_LoadWAV("asset/sound_place_tower.mp3");
	sound_pool[ResID::Sound_TowerLevelUp] = Mix_LoadWAV("asset/sound_tower_level_up.mp3");

	sound_pool[ResID::Sound_Win] = Mix_LoadWAV("asset/sound_win.wav");
	sound_pool[ResID::Sound_Loss] = Mix_LoadWAV("asset/sound_loss.mp3");

	for (const auto& pair : sound_pool)
		if (!pair.second) return false;

	music_pool[ResID::Music_BGM] = Mix_LoadMUS("asset/music_bgm.mp3");

	for (const auto& pair : music_pool)
		if (!pair.second) return false;

	font_pool[ResID::Font_Main] = TTF_OpenFont("asset/ttf/ipix.ttf", 25);

	for (const auto& pair : font_pool)
		if (!pair.second) return false;

	return true;
}

const FontPool& ResourcesManager::get_font_pool()
{
	return font_pool;
}

const SoundPool& ResourcesManager::get_sound_pool()
{
	return sound_pool;
}

const MusicPool& ResourcesManager::get_music_pool()
{
	return music_pool;
}

const TexturePool& ResourcesManager::get_texture_pool()
{
	return texture_pool;
}