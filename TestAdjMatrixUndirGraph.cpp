#include "AdjMatrixUndirGraph.h"		// �ڽӾ�������ͼ
#include <iostream>
#include <fstream>
using namespace std;
int main(void)
{
    try									// ��try��װ���ܳ����쳣�Ĵ���
	{
		int N,M;
		ifstream file("C://test1.txt",ios::in);
		if(!file)
        {
            cout<<"���ļ�ʧ��";
            return 0;
        }
		file>>N;
		char *vexs=new char[N];
		for(int i=0;i<N;i++) file>>vexs[i];
		file>>M;
		AdjMatrixUndirGraph<char> g(vexs, N, M);
		char c = '0', e, e1, e2;
		int v, v1, v2, w; //w��ʾȨ�أ�����·����
		for(int i=0;i<M;i++)
        {
            file>>e1;
            file>>e2;
            file>>w;
            v1 = g.GetOrder(e1);
            v2 = g.GetOrder(e2);
            g.InsertArc(v1, v2, w);
        }
        cout<<endl<<"���֮�乫·���ڽӾ���Ϊ��"<<endl;
        if (g.IsEmpty()) cout << "��ͼΪ�ա�" << endl;
        else  g.Display();
	    while (c != '4')	{
            cout << endl << "1. �����ʽ����ͨ·����";
            cout << endl << "2. �������ҽԺ�����";
            cout << endl << "3. ��·ϵͳ";
            cout << endl << "4. �˳�";
		    cout << endl << "ѡ����(0~4):";
		    cin >> c;
		    switch (c) 		{
			    /*case '1':
				    break;
			    case '2':
				    break;*/
			    case '3':
			        cout << endl << "�����ѯ���A��B";
			        cin>> e1 >> e2;
			        v1 = g.GetOrder(e1);
			        v2 = g.GetOrder(e2);
					g.DisplayShortAB(v1, v2);
			        break;
       	      }
         }
	}
	catch (Error err)					// ��׽�������쳣
	{
		err.Show();						// ��ʾ�쳣��Ϣ
	}

	system("PAUSE");					// ���ÿ⺯��system()
	return 0;							// ����ֵ0, ���ز���ϵͳ
}