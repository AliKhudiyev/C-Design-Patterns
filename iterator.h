enum Type{
	TEXT = 0,
	TREE
};

struct Iterator{
	enum Type type;
	void *container;
	void *iter;
};

struct Text;
struct Text *make_text(const char *str);

struct Tree;
struct Tree *make_tree(const char *str);

struct Iterator get_iterator(void *container);
char get_next(struct Iterator *iter);
