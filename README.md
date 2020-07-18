# DSL
DSL是一种类似XML的通用的描述语言，在形式上更容易手写与阅读。DSL比XML更接近程序语言的构造，基于DSL的描述可以方便的构建解释器，从而可以很容易建造一个领域特定语言（DSL）。这是为什么直接取名叫DSL的原因，意思是它是一个元语言，可以很方便的用来构造DSL。

## 例1：用来描述一个技能（一个2段的技能，第一段80毫秒，第二段100毫秒，在第二段50毫秒时触发伤害逻辑100011）（另外需要在逻辑上基于解析器将技能描述转换成技能实例）

skill(100001)

{

	section(80)
	
	{
	
		animation(cast);
		
		effect(fire);
		
	};
	
	section(100)
	
	{
	
		animation(hit);
		
		impact(50,100011);
		
	};
	
};

## 例2：用于剧情脚本，剧情开始先显示一段对话5，对话完毕创建一堆NPC,每杀死一个NPC更新一次剩余NPC数量，全部杀完显示完成对话6，对话结束后剧情脚本结束。（另外需要在逻辑上基于解析器实现剧情脚本的解释执行[可采取命令队列的形式]）

story(main)

{

	local
	
	{
	
		@ct(0);
		
	};
	
	onmessage("start")
	
	{
	
		showdlg(5);
		
	};
	
	onmessage("dialogfinished",5)
	
	{
	
		loop(10)
		
		{
		
			createnpc(1001+$$);
			
		};
		
	};
	
	onmessage("npckilled")
	
	{
	
		@ct=countnpc();
		
		if(@ct==0){
		
			sendgfxmessage("GameRoot","UpdateNpcCount",0);
			
			showdlg(6);
			
		}else{
		
			sendgfxmessage("GameRoot","UpdateNpcCount",@ct);
			
		};
		
	};
	
	onmessage("dialogfinished",6)
	
	{
	
		terminate();
		
	};
	
};

## 例3：用于描述数据配表结构（另外需要基于解析器实现一个工具根据此描述生成对应的读表器代码）

table(NpcConfig)

{

	field(m_ID,ID,int);
	
	field(m_Type,Type,int,0);
	
	field(m_Model,Model,string);
	
};


## 语言的语法定义见Parse/Dsl.txt文件，语法分析程序采用LL语法分析器生成工具SLK生成。

## 面向语言的开发
DSL即领域特定语言的简写，这个工程提供的是用作DSL的元语言。DSL通常按实现方式分内部DSL与外部DSL两大类，内部DSL一般使用宿主语言的部分语法构造，这样免去了写语法分析的必要，编写DSL的人需要对宿主语言本身有一定的了解，内部DSL的使用在函数式语言里比较常见，C++的模板元编程与操作符重载也常用来实现内部DSL，为java扩充的groove语言有很多对DSL的支持，比如提供命令链的语法糖：a b c d e f <=> a(b).c(d).e(f)。


本工程提供的属于外部DSL，外部DSL因为需要设计语法与编写词法、语法解析等，相比内部DSL在实现上比较麻烦，本工程尝试实现DSL元语言，就是期望简化这一块的工作，基于标准语法来定制DSL，可以与内部DSL在实现上一样简便。其实XML、json就是这种通用DSL语言的例子，本工程的DSL元语言语法借鉴自C系语言，期望在语法上提供与C系语言类似的体验，相比XML与json提供了对高阶表示更易读的支持，更接近于人类语言的核心概念。


面向语言的开发（LOP）最早提出于1994年(http://www.gkc.org.uk/martin/papers/middle-out-t.pdf)["middle-out-t"]，强调基于语言来提供分层间的抽象，这与操作系统分层虚拟机的观点很相似，每一层抽象都定义一种语言，语言定义本质上基于数学，所以是精确的。这篇文章(https://parametri.city/blog/2018-12-23-language-oriented-software-engineering/index.html)["language oriented software engineering"]对LOP的开发过程有一个提炼：
```
The language-oriented methodology proceeds in three steps:

1. Design a domain specific language (DSL) for your core application logic.
2. Write your application in the DSL.
3. Build interpreters to execute your DSL programs, mapping your logical constructs to the actual machinery.
```

## 泛化
维特根斯坦的《逻辑哲学论》从人类语言与世界的类比来理解世界
- 世界是由事实组成的（对应我们语言中的句子）。
- 事实是由事态组成的（对应逻辑里的函项，或陈述句式）。
- 事态是由客体组成的（客体是事物或者说对象，是原子的）。


类似的，程序语言可以这样构成
- 语言是由语句组成的（StatementData）。
- 语句是由函数项组成的(FunctionData)。
- 函数项由符号组成。符号是一个原子的值(ValueData)。


从这个角度看，DSL的这种构造，可以是足够抽象与普遍的语言组织形式，所以，可以想见是足够通用。

## 一些例子
- 几百行代码的脚本解释器：https://github.com/dreamanlan/ScriptInterpreterByDsl
- 基于DSL的unity3d地形生成：https://github.com/dreamanlan/TerrainGenByDsl
- unity3d游戏课程Demo，使用DSL实现一个基于命令队列的脚本，并用于编写游戏逻辑：https://github.com/dreamanlan/GameDemo
- 一个比较完整的基于c#与unity3d的客户端与服务器架构，DSL用于实现游戏高层逻辑与各种编辑器工具以及前面提到的剧情、技能、配表的描述：https://github.com/dreamanlan/CSharpGameFramework
- 一个跨平台批处理脚本解释器：https://github.com/dreamanlan/BatchCommand
- 基于roslyn的C#重写工具（在包含new的函数开头与结尾插入指定的函数调用，可用来profile内存），使用DSL作为配置语言：https://github.com/dreamanlan/CSharpHookRewriter
- 基于roslyn的C#无用类分析工具（可用来清理废弃代码），使用DSL作为配置语言：https://github.com/dreamanlan/UnusedClass
- 一个dotnet exe/dll补丁工具，使用DSL作为脚本：https://github.com/dreamanlan/DotnetPatch
