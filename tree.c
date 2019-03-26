#include <gmodule.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	GTree* t = g_tree_new((GCompareFunc) g_str_equal);

	char* key = strdup("A1234");
	char* value = strdup("1234");

	g_tree_insert(t, key, value);

	char* foo = g_tree_lookup(t, &key);

	printf("%s\n", foo);


	return 0;
}