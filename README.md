# DSL
DSL is a scripting language similar to XML/JSON. Compared with XML/JSON, it can be used not only to describe data, but also to describe logic. It is also easier to write and read in form. DSL is closer to the structure of a programming language than XML/JSON. The description based on DSL can easily build an interpreter, making it easy to build a domain-specific language (DSL). This is the reason why it is directly named DSL, which means that it is a meta-language that can be easily used to construct DSL.

PDF Document (Chinese):[《MetaDSL and its application in Unity game development"》](https://github.com/dreamanlan/MetaDSL/blob/master/MetaDSL%20and%20its%20application%20in%20Unity%20game%20development.pdf "MetaDSL及在Unity游戏开发中的应用")

pptx file compression zip (Chinese):[《MetaDSL and its application in Unity game development"》 pptx]( https://github.com/dreamanlan/MetaDSL/blob/master/MetaDSL%E5%8F%8A%E5%9C%A8Unity%E6%B8%B8%E6%88%8F%E5%BC%80%E5%8F%91%E7%9A%84%E5%BA%94%E7%94%A8.zip "MetaDSL及在Unity游戏开发中的应用 pptx")

## Example 1: Used to describe a skill (a 2-stage skill, the first stage is 80 milliseconds, the second stage is 100 milliseconds, and the damage logic 100011 is triggered when the second stage is 50 milliseconds) (in addition, the skill needs to be logically separated based on the parser) Description converted into skill instance)
```
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
```

## Example 2: Used for plot scripts. A dialogue 5 is displayed at the beginning of the plot. After the dialogue is completed, a bunch of NPCs are created. The number of remaining NPCs is updated every time an NPC is killed. When all are killed, the completed dialogue 6 is displayed. After the dialogue is completed, the plot script ends. (In addition, it is necessary to logically implement the interpretation and execution of the plot script based on the parser [which can be in the form of a command queue])

```
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
```

## Example 3: Used to describe the data matching table structure (in addition, a tool based on the parser needs to be implemented to generate the corresponding meter reader code based on this description)

```
table(NpcConfig)
{
	field(m_ID,ID,int);	
	field(m_Type,Type,int,0);	
	field(m_Model,Model,string);	
};
```

## The syntax definition of the language can be found in the Parse/Dsl.txt file, and the syntax analysis program is generated using the LL syntax analyzer generation tool SLK.

## Language-oriented development
DSL is the abbreviation of Domain Specific Language. This project provides the metalanguage used as DSL. DSL is usually divided into two categories: internal DSL and external DSL according to the implementation method. Internal DSL generally uses part of the grammatical structure of the host language, which eliminates the need to write syntax analysis. People who write DSL need to have a certain understanding of the host language itself. The use of internal DSL is relatively common in functional languages. C++ template metaprogramming and operator overloading are also commonly used to implement internal DSL. The groove language extended for Java has a lot of support for DSL, such as providing syntactic sugar for command chains:
```
abcdef < => a(b).c(d).e(f).
```

What this project provides is an external DSL. External DSL requires designing grammar, writing lexicon, grammar analysis, etc., which is more troublesome to implement than internal DSL. This project attempts to implement DSL metalanguage in the hope of simplifying this work, based on standards. syntax to customize the DSL, which can be implemented as easily as the internal DSL. In fact, XML and json are examples of such general DSL languages. The DSL metalanguage syntax of this project is borrowed from C-series languages. It is expected to provide a similar experience to C-series languages ​​in terms of syntax. Compared with XML and json, it provides a higher-order representation. More readable support that is closer to the core concepts of human language.


Language-oriented development (LOP) was first proposed in 1994 by[middle-out-t](http://www.gkc.org.uk/martin/papers/middle-out-t.pdf),It emphasizes providing abstraction between layers based on language. This is very similar to the view of operating system layered virtual machines. Each layer of abstraction defines a Language, language definitions are essentially based on mathematics, so they are precise.  This article [language oriented software engineering](https://parametri.city/blog/2018-12-23-language-oriented-software-engineering/index.html) has a refinement of the LOP development process:
```
The language-oriented methodology proceeds in three steps:

1. Design a domain specific language (DSL) for your core application logic.
2. Write your application in the DSL.
3. Build interpreters to execute your DSL programs, mapping your logical constructs to the actual machinery.
```

## generalize

Wittgenstein's Tractatus Logico-Philosophicus understands the world from the analogy between human language and the world

- The world is made up of facts (corresponding to sentences in our language).
- Facts are composed of states of affairs (corresponding to functions in logic, or declarative sentences).
- The state of affairs is composed of objects (objects are things or objects, which are atomic).

Similarly, a programming language can be structured like this

- Language is composed of statements (StatementData).
- Statements are composed of function items (FunctionData).
- Function terms are composed of symbols. The symbol is an atomic value (ValueData).

From this perspective, the structure of DSL can be a sufficiently abstract and universal language organization form, so it can be imagined that it is general enough.

## some examples
- Script interpreter with several hundred lines of code: https://github.com/dreamanlan/ScriptInterpreterByDsl0 与 https://github.com/dreamanlan/ScriptInterpreterByDsl
- Unity3d terrain generation based on DSL:https://github.com/dreamanlan/TerrainGenByDsl
- Unity3d game course Demo uses DSL to implement a command queue-based script and is used to write game logic:https://github.com/dreamanlan/GameDemo
- A relatively complete client and server architecture based on c# and unity3d. DSL is used to implement high-level game logic and various editor tools as well as the description of the plot, skills, and matching tables mentioned earlier: https://github.com/dreamanlan/CSharpGameFramework
- A cross-platform batch script interpreter: https://github.com/dreamanlan/BatchCommand
- C# rewriting tool based on roslyn (insert specified function calls at the beginning and end of functions containing new, which can be used to profile memory), using DSL as the configuration language:https://github.com/dreamanlan/CSharpHookRewriter
- C# useless class analysis tool based on roslyn (can be used to clean up abandoned code), using DSL as the configuration language: https://github.com/dreamanlan/UnusedClass
- A dotnet exe/dll patch tool that uses DSL as a script: https://github.com/dreamanlan/DotnetPatch
- Cs2Lua, a tool that translates unity c# to lua using slua runtime. The translation intermediate language uses DSL. The translation configuration and customized translation scripts also use DSL and a universal interpreter based on DSL:https://github.com/dreamanlan/Cs2Lua
