#include "singleton.h"

struct DBSesh{
	int status;
} *g_dbsesh = 0;

struct DBSesh *make_dbsesh(){
	if(!g_dbsesh){
		g_dbsesh = malloc(sizeof(struct DBSesh));
		// proper initialization
	}
	return g_dbsesh;
}
