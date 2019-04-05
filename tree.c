#include <gmodule.h>
#include <stdio.h>
#include <string.h>

int check7(char* a, char* b)
{
	return strcmp(a,b);
}

int main(int argc, char const *argv[])
{
	GTree* t = g_tree_new((GCompareFunc) check7);

	char* key = "AB";
	char* key2 = "BC";
	char* key3 = "CD";
	char* value = strdup("12345");
	char* value1 = strdup("54321");
	char* value2 = strdup("3");

	g_tree_insert(t, &key, value);
	g_tree_insert(t, &key2, value1);
	g_tree_insert(t, &key3, value2);

	char* foo = g_tree_lookup(t, &key);
	char* foo1 = g_tree_lookup(t, &key3);

	printf("%s\n", foo);
	printf("%s\n", foo1);


	return 0;
	/*
	GTree* t = g_tree_new((GCompareFunc) g_str_equal);

	char* key = strdup("A1234");
	char* value = strdup("1234");

	g_tree_insert(t, key, value);

	char* foo = g_tree_lookup(t, &key);

	printf("%s\n", foo);


	return 0;
	*/
}