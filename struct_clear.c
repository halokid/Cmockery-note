/*
 结构体剥离清晰代码架构
 下面几个结构体， 逻辑代码 是 cmockery的核心逻辑之一
 
 分析下面的代码逻辑， 顺序如下:
 1,   UnitTest 结构体定义三个属性
      const char* name  
      UnitTestFunction function 
      UnitTestFunctionType function_type 
      
      则
      
      unit_test(null_test_success) 应该返回上述的三个属性
  
  2, 追踪到 unit_test,  我们看此函数的定义为  
     #define unit_test(f) { #f, f, UNIT_TEST_FUNCTION_TYPE_TEST }
     此宏返回上面的三个属性, #f 在这里的用法就是指 参数的名字本身的指针(#f是一个字符串, 就是参数的名字)
     
  3, 这下就齐活了， 组成数组之后，传给  run_tests() 函数，跑正式的单元测试逻辑, 那么我们主要分析 run_tests的逻辑
  
*/

#include <stdio.h>

#define unit_test(f) { #f, f, UNIT_TEST_FUNCTION_TYPE_TEST }

typedef enum UnitTestFunctionType {
  UNIT_TEST_FUNCTION_TYPE_TEST = 0,
  UNIT_TEST_FUNCTION_TYPE_SETUP,
  UNIT_TEST_FUNCTION_TYPE_TEARDOWN,
} UnitTestFunctionType;

typedef void (*UnitTestFunction) (void **state);


typedef struct UnitTest {
  const char* name;
  UnitTestFunction function;
  UnitTestFunctionType function_type;
} UnitTest;


void null_test_success(void **state) {

};


void xx_test(void **state) {

};

int main(int argc, char **argv[])
{

  const UnitTest tests[] = {
    unit_test(null_test_success),
  };

  const UnitTest xx = unit_test(xx_test);
  
  printf("func name point:  %s\n", xx.name);
  printf("func self      :  %p\n", xx.function);
  printf("func type      :  %p\n", xx.function_type);
  
  
  return run_tests(tests);
}

/*
输出:
func name point:  xx_test
func self      :  400516
func type      :  ()

*/





