#include "facade.h"
#include <stdlib.h>

struct GameSetting{
	unsigned xres, yres;
	float ratio;
	unsigned target_fps;
	float character_speed;
	unsigned render_depth;
	unsigned flags;
};

static void set_resolution(struct GameSetting *setting, unsigned xres, unsigned yres){
	setting->xres = xres;
	setting->yres = yres;
	setting->ratio = (float)xres / (float)yres;
}

static void set_target_fps(struct GameSetting *setting, unsigned fps){
	setting->target_fps = fps - (setting->xres*setting->yres/100);
	setting->character_speed = 1.5*fps;
}

static void set_render_depth(struct GameSetting *setting, unsigned depth){
	setting->render_depth = depth;
	if(depth <= 10){ setting->flags = 0xff00a032; }
	else if(depth <= 40){ setting->flags = 0x0faaa000; }
	else if(depth <= 100){ setting->flags = 0x4f00a032; }
	else{ setting->flags = 0xffffffff; }
}

struct GameSetting *make_default_setting(){
	struct GameSetting *setting = malloc(sizeof(struct GameSetting));
	set_resolution(setting, 1920, 1080);
	set_target_fps(setting, 60);
	set_render_depth(setting, 35);
	return setting;
}

void low_settings(struct GameSetting *setting){
	set_resolution(setting, 1280, 720);
	set_target_fps(setting, 45);
	set_render_depth(setting, 10);
	}

void medium_settings(struct GameSetting *setting){
	set_resolution(setting, 1920, 1080);
	set_target_fps(setting, 75);
	set_render_depth(setting, 40);
	}

void high_settings(struct GameSetting *setting){
	set_resolution(setting, 3840, 2160);
	set_target_fps(setting, 100);
	set_render_depth(setting, 100);
	}

void ultra_settings(struct GameSetting *setting){
	set_resolution(setting, 3840, 2160);
	set_target_fps(setting, 240);
	set_render_depth(setting, 150);
	}
