# DSL
a simple language just like XML but more readable by people.

��1����������һ�����ܣ�һ��2�εļ��ܣ���һ��80���룬�ڶ���100���룬�ڵڶ���50����ʱ�����˺��߼�100011����������Ҫ���߼��ϻ��ڽ���������������ת���ɼ���ʵ����
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

��2�����ھ���ű������鿪ʼ����ʾһ�ζԻ�5���Ի���ϴ���һ��NPC,ÿɱ��һ��NPC����һ��ʣ��NPC������ȫ��ɱ����ʾ��ɶԻ�6���Ի����������ű���������������Ҫ���߼��ϻ��ڽ�����ʵ�־���ű��Ľ���ִ��[�ɲ�ȡ������е���ʽ]��
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

��3�����������������ṹ��������Ҫ���ڽ�����ʵ��һ�����߸��ݴ��������ɶ�Ӧ�Ķ��������룩
table(NpcConfig)
{
	field(m_ID,ID,int);
	field(m_Type,Type,int,0);
	field(m_Model,Model,string);
};

���Ե��﷨�����Parse/Dsl.txt�ļ����﷨�����������LL�﷨���������ɹ���SLK���ɡ�