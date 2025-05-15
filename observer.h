struct User;
struct Podcast;

struct User *make_user(const char *name);
void subscribe(struct Podcast *podcast, struct User *user);
void unsubscribe(struct Podcast *podcast, struct User *user);
void user_receive(struct User *user, const char *msg);

struct Podcast *make_podcast(const char *title);
void notify(struct Podcast *podcast, const char *message);
