
#include "okcoinwebsocketapi.h"


OKCoinWebSocketApiCom *comapi = 0;	//�˴�Ϊȫ�ֱ����������û����ɵ���ģʽ
OKCoinWebSocketApiCn *cnapi = 0;	//�˴�Ϊȫ�ֱ����������û����ɵ���ģʽ

//������webstocket�ص������ڹ���վ�͹���վ�ֱ����������ӣ�
//Ҳ�����������������̷߳����ģ��ʹ���վ�͹���վ�и��ԵĻص�������
//������߳�Ӧ�ò�̫�����Ŀ����ߣ�������Ҫ��һ���ص�����ͬʱ��������վ�����ݣ�������ʹ��ĳ����ø��ӡ�
void cn_callbak_open()
{
	//���������������
	
	std::cout << "����վ���ӳɹ���3���Ӻ�ʼ�������ݣ�����3�Ͽ����ӡ� " << std::endl;
	Sleep(3000);
	//���ӳɹ�����������tick��depth����
	//���⣬�ѽ������������������open�ص�����������:
	//������Ͽ����������Ӻ󴥷����ص����Զ����ͽ�������
	//���Ծ���Ҫ��������Ľ���������ڱ��ص��
	if(cnapi != 0)
	{
		cnapi->ok_btccny_ticker();
		cnapi->ok_btccny_depth();
	}
	
};
void cn_callbak_close()
{
	std::cout << "�����Ѿ��Ͽ��� " << std::endl;
};
void cn_callbak_message(const char *message)
{
	std::cout << "Message: " << message << std::endl;
};

//////////////////////////////////

void com_callbak_open()
{
	//���������������
	
	std::cout << "����վ���ӳɹ���3���Ӻ�ʼ�������ݣ�����3�Ͽ����ӡ� " << std::endl;
	Sleep(3000);
	//���ӳɹ�����������tick��depth����
	//���⣬�ѽ������������������open�ص�����������:
	//������Ͽ����������Ӻ󴥷����ص����Զ����ͽ�������
	//���Ծ���Ҫ��������Ľ���������ڱ��ص��
	if(comapi != 0)
	{
		comapi->ok_btcusd_ticker();
		comapi->ok_btcusd_depth();
	}
	
};
void com_callbak_close()
{
	std::cout << "�����Ѿ��Ͽ��� " << std::endl;
};
void com_callbak_message(const char *message)
{
	std::cout << "Message: " << message << std::endl;
};

int main(int argc, char* argv[]) 
{	
	
	//ʵ����API
	std::string cn_apiKey		= "";									//�뵽www.okcoin.cn���롣
	std::string cn_secretKey		= "";								//�뵽www.okcoin.cn���롣
	cnapi = new OKCoinWebSocketApiCn(cn_apiKey,cn_secretKey);			//����վ
	cnapi->SetCallBackOpen(cn_callbak_open);
	cnapi->SetCallBackClose(cn_callbak_close);
	cnapi->SetCallBackMessage(cn_callbak_message);
	cnapi->Run();//�������ӷ������߳�
	

	std::string com_apiKey		= "";			//�뵽www.okcoin.com���롣
	std::string com_secretKey	= "";			//�뵽www.okcoin.com���롣
	comapi = new OKCoinWebSocketApiCom(com_apiKey,com_secretKey);				//����վ
	comapi->SetCallBackOpen(com_callbak_open);
	comapi->SetCallBackClose(com_callbak_close);
	comapi->SetCallBackMessage(com_callbak_message);
	comapi->Run();//�������ӷ������߳�
	
	Sleep(3000);


	cout << "����1�����µ����ܣ�����2ע�����ݽ�����������3�ر����ӣ������룺";
	string i;
	cin >> i;
	if(i == "1")
	{
		//�ڻ��µ�����
		string symbolcom		=		"ltc_usd";
		string type				=		"buy";//�������ͣ� �޼۵���buy/sell�� �м۵���buy_market/sell_market��
		string price			=		"1";
		string amount			=		"0.1";
		comapi->ok_spotusd_trade(symbolcom,type,price,amount);	//�µ�����

		string order_id	= "33732079";
		comapi->ok_spotusd_cancel_order(symbolcom,order_id);	//ȡ������
		system("pause");
	}

	//�����Ѿ�ע��������ڲ���Ҫʱע���������ٽ��գ�
	//ע������̫����Ǳ�Ҫ���ݣ���ʹ���ĳ�����ȫ�����½����뿪����ע�⴦��
	if(i == "2")
	{
		if(comapi != 0)
		{
			cnapi->remove_ok_btccny_ticker();
			cnapi->remove_ok_btccny_depth();
		}


		if(comapi != 0)
		{
			comapi->remove_ok_btcusd_ticker();
			comapi->remove_ok_btcusd_depth();
		}
		system("pause");
	}

	//�ر�����
	cnapi->Close();	
	comapi->Close();


	system("pause");

	//�ͷ�APIʵ��
	delete cnapi;
	delete comapi;
	cout << "�ͷ�APIʵ����ɡ�";

	system("pause");

}

