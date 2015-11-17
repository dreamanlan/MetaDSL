# DSL
a simple language just like XML but more readable by people.

例1：用来描述一个技能（一个2段的技能，第一段80毫秒，第二段100毫秒，在第二段50毫秒时触发伤害逻辑100011）（另外需要在逻辑上基于解析器将技能描述转换成技能实例）
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

例2：用于剧情脚本，剧情开始先显示一段对话5，对话完毕创建一堆NPC,每杀死一个NPC更新一次剩余NPC数量，全部杀完显示完成对话6，对话结束后剧情脚本结束。（另外需要在逻辑上基于解析器实现剧情脚本的解释执行[可采取命令队列的形式]）
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

例3：用于描述数据配表结构（另外需要基于解析器实现一个工具根据此描述生成对应的读表器代码）
table(NpcConfig)
{
	field(m_ID,ID,int);
	field(m_Type,Type,int,0);
	field(m_Model,Model,string);
};

语言的语法定义见Parse/Dsl.txt文件，语法分析程序采用LL语法分析器生成工具SLK生成。