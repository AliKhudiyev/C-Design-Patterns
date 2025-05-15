#include "proxy.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static struct RawLog{
	FILE *file;
	unsigned entry_count;
	float fail_ratio;
} g_rawlog = {0};

static void init_rawlog(struct RawLog *log, const char *filepath){
	log->file = fopen(filepath, "w");
	log->entry_count = 0;
	log->fail_ratio = 0;
}

static void write_rawlog(struct RawLog *log, const char *msg, unsigned char fail){
	fprintf(log->file, "%s\n", msg);
	log->fail_ratio = (log->fail_ratio * log->entry_count + fail) / 
					  (float)log->entry_count;
	++log->entry_count;
}

struct Log *make_log(const char *filepath){
	struct Log *log = malloc(sizeof(struct Log));
	log->time_elapsed = 0;
	strcpy(log->sys_name, "whos-gon-carry-the-logs-v1.2");
	log->rawlog = &g_rawlog;
	if(!g_rawlog.file){ init_rawlog(&g_rawlog, filepath); }
	return log;
}

void log_info(struct Log *log, const char *msg){
	const char *head = "INFO: ";
	char *str = malloc(strlen(head)+strlen(msg)+1);
	sprintf(str, "%s%s", head, msg);
	write_rawlog(log->rawlog, str, 0);
}

void log_alert(struct Log *log, const char *msg){
	const char *head = "ALERT: ";
	char *str = malloc(strlen(head)+strlen(msg)+1);
	sprintf(str, "%s%s", head, msg);
	write_rawlog(log->rawlog, str, 0);
}

void log_warn(struct Log *log, const char *msg){
	const char *head = "WARNING: ";
	char *str = malloc(strlen(head)+strlen(msg)+1);
	sprintf(str, "%s%s", head, msg);
	write_rawlog(log->rawlog, str, 0);
}

void log_abort(struct Log *log, const char *msg){
	const char *head = "ERROR: ";
	char *str = malloc(strlen(head)+strlen(msg)+1);
	sprintf(str, "%s%s", head, msg);
	write_rawlog(log->rawlog, str, 1);
}

void log_syscheck(struct Log *log){
	const char *sysname = "SYSNAME: ";
	const char *elapsed = "ELAPSED: ";
	char *str = malloc(strlen(sysname)+100+strlen(elapsed)+10+4);
	sprintf(str, "%s%s | %s%u", 
			sysname, log->sys_name, elapsed, log->time_elapsed);
	write_rawlog(log->rawlog, str, 0);
}
