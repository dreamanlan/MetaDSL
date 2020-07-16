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
- 一个比较完整的基于c#与unity3d的客户端与服务器架构，DSL用于实现游戏高层逻辑与各种编辑器工具：https://github.com/dreamanlan/CSharpGameFramework
- 一个跨平台批处理脚本解释器：https://github.com/dreamanlan/BatchCommand
- 基于roslyn的C#重写工具（在包含new的函数开头与结尾插入指定的函数调用，可用来profile内存），使用DSL作为配置语言：https://github.com/dreamanlan/CSharpHookRewriter
- 基于roslyn的C#无用类分析工具（可用来清理废弃代码），使用DSL作为配置语言：https://github.com/dreamanlan/UnusedClass
