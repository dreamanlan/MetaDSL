#ifndef STATICCHECK_H
#define STATICCHECK_H

//Template classes for compile-time assertion judgments
template<bool>
class CompileSuccess
{
};
//Compile-time assertion determines successful specialization
template<>
class CompileSuccess<true>
{
public:
    CompileSuccess(...) {}; //A constructor that accepts any argument
};

//The declaration of the tool function that completes the type transfer is just a declaration,
//no function entity, and does not take up memory
int CompileChecker(CompileSuccess<true> const&);

#define STATIC_CHECK(expr, msg)\
{\
	class CompileError_##msg {};\
	sizeof(CompileChecker(CompileSuccess<false!=(expr)>(CompileError_##msg())));\
}
//Below are sample unit test functions and usage formats
//void UnitTest_StaticCheck()
//{
//	STATIC_CHECK(false, CheckFailed_CheckItNow);
//	STATIC_CHECK(true, CheckSuccessfully_Pass);
//}
#endif //STATICCHECK_H
