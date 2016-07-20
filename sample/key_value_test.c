#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <string.h>
#include <cmockery.h>

typedef struct KeyValue {
	unsigned int key;
	const char* value;
} KeyValue;


void set_key_values(KeyValue * const new_key_values,
										const unsigned int new_number_of_key_values);


extern KeyValue* find_item_by_value(const char * const value);
extern void sort_items_by_key(); 

static KeyValue key_values[] = {
	{ 10, "this" },
	{ 52, "test" },
	{ 20, "a" },
	{ 13, "is" },
};

/*
 理解  **state 的用法
 理解双星号 指针的范例程序
 
 -------------------------------------------------------------------------------------
 char c = 'a';
 char *p;
 p = &c;      // 现在 p 里存的就是 c 的地址
 
 char **q;    // q 是 一个二级指针
 q = &p;      //  q 里存的 是 p 的地址， p 就是如前所述是个整数， 所以 p 占有内存的一块空间， 现在 q 就是指向这个空间的开始
 
 -------------------------------------------------------------------------------------
 
*/
void create_key_value(void **state) {
	KeyValue * const items = (KeyValue*)test_malloc(sizeof(key_values));		// give memory to items
	memcpy(items, key_values, sizeof(key_values));						              // set key_values to items
	*state = (void*)items;
	set_key_values(items, sizeof(key_values) / sizeof(key_values[0]) );			// f**k !!!!
}

void destory_key_value(void **state) 
{
	test_free(*state);
	set_key_values(NULL, 0);
}

void test_find_item_by_value(void **state) {
	unsigned int i;
	for (i = 0; i < sizeof(key_values) / sizeof(key_values[0]); i++ ) {
		KeyValue * const found = find_item_by_value(key_values[i].value);
		assert_true(found);
		assert_int_equal(found->key, key_values[i].key);
		assert_string_equal(found->value, key_values[i].value);
	}
}


void test_sort_items_by_keys(void **state) 
{
	unsigned int i;
	KeyValue * const kv = *state;
	sort_items_by_key();
	for (i = 1; i < sizeof(key_values) / sizeof(key_values[0]); i++ ) {
		assert_true(kv[i - 1].key < kv[i].key);
	}
}


int main(int argc, char* argv[]) 
{
	const UnitTest tests[] = {
		unit_test_setup_teardown(test_find_item_by_value, create_key_value, destory_key_value),

		unit_test_setup_teardown(test_sort_items_by_keys, create_key_value, destory_key_value),
	};
	return run_tests(tests);
}






