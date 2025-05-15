#include "observer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct User{
	char name[100];
	size_t pod_count;
	struct Podcast **pods;
};

struct Podcast{
	char title[100];
	size_t sub_count;
	struct User **subs;
};

struct User *make_user(const char *name){
	struct User *user = malloc(sizeof(struct User));
	strcpy(user->name, name);
	user->pod_count = 0;
	return user;
}

void subscribe(struct Podcast *podcast, struct User *user){
	podcast->subs = realloc(podcast->subs, podcast->sub_count+1);
	podcast->subs[podcast->sub_count] = user;
	++podcast->sub_count;

	user->pods = realloc(user->pods, user->pod_count+1);
	user->pods[user->pod_count] = podcast;
	++user->pod_count;
}

void unsubscribe(struct Podcast *podcast, struct User *user){
	for(size_t i=0; i<podcast->sub_count; ++i){
		if(podcast->subs[i] == user){
			podcast->subs[i] = 0;
			break;
		}
	}

	for(size_t i=0; i<user->pod_count; ++i){
		if(user->pods[i] == podcast){
			user->pods[i] = 0;
			break;
		}
	}
}

void user_receive(struct User *user, const char *msg){
	fprintf(stdout, "User: (%s) received a message: [%s]\n", user->name, msg);
}

struct Podcast *make_podcast(const char *title){
	struct Podcast *podcast = malloc(sizeof(struct Podcast));
	strcpy(podcast->title, title);
	podcast->sub_count = 0;
	return podcast;
}

void notify(struct Podcast *podcast, const char *message){
	for(size_t i=0; i<podcast->sub_count; ++i){
		if(podcast->subs[i]) user_receive(podcast->subs[i], message);
	}
}
