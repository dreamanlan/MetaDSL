#ifndef STATICCHECK_H
#define STATICCHECK_H

//编译期断言判断的模板类
template<bool> 
	class CompileSuccess
{
};
//编译期断言判断成功的偏特化
template<> 
	class CompileSuccess<true>
{
public:
	CompileSuccess(...){}; //可以接受任何参数的构造函数
};

//完成类型中转的工具函数的声明，只是声明，没有函数实体，不会占用内存
int CompileChecker(CompileSuccess<true> const&);

//编译期断言宏，过程中只出现临时变量，不会占用内存空间
//注意：
//	1、expr是bool值；
//	2、msg不是字符串("MyError")形式的，而是变量名(MyError)形式的，必须遵循变量的命名标准；
//	3、和Assert很像，当作一个函数或语句来用；
#define STATIC_CHECK(expr, msg)\
{\
	class CompileError_##msg {};\
	sizeof(CompileChecker(CompileSuccess<false!=(expr)>(CompileError_##msg())));\
}
//下面是单元测试函数 和 使用格式样例
//void UnitTest_StaticCheck(void)
//{
//	STATIC_CHECK(false, CheckFailed_CheckItNow);
//	STATIC_CHECK(true, CheckSuccessfully_Pass);
//}
#endif //STATICCHECK_H
