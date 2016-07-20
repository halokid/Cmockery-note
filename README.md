# Cmockery-note
Cmockery learn &amp; note 

Cmockery 项目源码学习笔记， 注释流程，架构学习

整个代码看下来，感觉函数的参数反射用得好多， 好多指针的概念。 无论是函数指针， 还是引用类型，初看可能有点晕，但是只要把这些变量当作函数的反射来看，会好一些
--------------------------------------------------------

假如是只有一个单元测试， 则走通逻辑如下：

1, 初始化 UnitTest tests 数组， 然后执行 run_tests(tests)函数
2, run_tests函数跑宏  _run_tests 函数， 该函数逻辑为 
          
            定义各种记录单元测试的变量， 例如测试次数，失败次数等
                                    |
                                    |
                                    |
            按照单元测试数组， 循环执行逻辑进行单元测试核心代码
            A.   定义双链表数据结构, 整个逻辑是把 要测试的函数名都存在双链表中，双链表为全局变量
            B.   执行默认的单元测试函数类型 function_type 为 UNIT_TEST_FUNCTION_TYPE_TEST, run_next_test 为 1
            C.   核心匹配单元测试 输入/输出 的在两个函数， remove_always_return_values, check_for_leftover_values
                 
                 remove_always_return_values 是把要 单元测试的正确的值写入全局变量当中, 一个双链表的节点的属性
                 check_for_leftover_values 是把要 单元测试的正确的值写入全局变量当中, 一个双链表的节点的属性
           