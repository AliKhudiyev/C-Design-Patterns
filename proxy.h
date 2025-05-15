struct RawLog;
struct Log{
	unsigned time_elapsed;
	char sys_name[100];
	struct RawLog *rawlog;
};

struct Log *make_log(const char *filepath);
void log_info(struct Log *log, const char *msg);
void log_alert(struct Log *log, const char *msg);
void log_warn(struct Log *log, const char *msg);
void log_abort(struct Log *log, const char *msg);
void log_syscheck(struct Log *log);
