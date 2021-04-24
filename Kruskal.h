#ifndef __KRUSKAL_H__
#define __KRUSKAL_H__
#include "AdjMatrixUndirGraph.h"		// �ڽӱ�������
#include "UFSets.h"		                // ������
#include "MineHeap.h"

// Kruskal����
template <class ElemType, class WeightType>
class KruskalEdge
{
public:
	ElemType vertex1, vertex2;		// �ߵĶ���
	WeightType weight;				// �ߵ�Ȩֵ
	KruskalEdge(ElemType v1, ElemType v2, WeightType w);	// ���캯��
	KruskalEdge(){};	            // ���캯��
	KruskalEdge<ElemType, WeightType> &operator =(const KruskalEdge<ElemType, WeightType> &Ed); // ��ֵ�������
	bool operator <=(const KruskalEdge<ElemType, WeightType> &Ed);		// ����<=��ϵ���� 
	bool operator >(const KruskalEdge<ElemType, WeightType> &Ed);		// ����>��ϵ����
};

template <class ElemType, class WeightType>
KruskalEdge<ElemType, WeightType>::KruskalEdge(ElemType v1, ElemType v2, WeightType w)
// �������: �ɶ���v1��v2��Ȩw����ߡ������캯��
{	// ���캯��
	vertex1 = v1;					// ����vertex1
	vertex2 = v2;					// ����vertex2
	weight = w;						// Ȩweight
}

template <class ElemType, class WeightType>
bool KruskalEdge<ElemType, WeightType>::operator <= (const KruskalEdge<ElemType, WeightType> &Ed)
// �������������<=��ϵ����
{
	return (weight <= Ed.weight);
}

template <class ElemType, class WeightType>
bool KruskalEdge<ElemType, WeightType>::operator > (const KruskalEdge<ElemType, WeightType> &Ed)
// �������������>��ϵ����
{
	return (weight > Ed.weight);
}


template<class ElemType,  class WeightType>
KruskalEdge<ElemType, WeightType> &KruskalEdge<ElemType, WeightType>::operator = (const KruskalEdge<ElemType, WeightType> &Ed)
// �����������ջcopy��ֵ����ǰջ--��ֵ�������
{
	if (&Ed != this)	{
	   vertex1 = Ed.vertex1;					// ����vertex1
	   vertex2 = Ed.vertex2;					// ����vertex2
	   weight = Ed.weight;						// Ȩweight
	}
	return *this;
}


template <class ElemType>
int MiniSpanTreeKruskal(AdjMatrixUndirGraph<ElemType> &g)
// ��ʼ������������g
// �����������Kruskal�㷨������g����С����������
{
	int count, VexNum = g.GetVexNum();
    KruskalEdge<ElemType, int> KEdge;
 	MinHeap<KruskalEdge<ElemType, int> > ha(g.GetEdgeNum());
    ElemType  *kVex, v1, v2;
	kVex = new ElemType[VexNum];	// ���嶥������,�洢������Ϣ 
	for (int i = 0; i < VexNum; i++)
	    g.GetElem(i, kVex[i]);
	UFSets<ElemType> f(kVex,VexNum);// ���ݶ������鹹�첢�鼯 
	for (int v = 0; v < g.GetVexNum(); v++)
		for (int u = g.FirstAdjVex(v); u >= 0; u = g.NextAdjVex(v, u))
			if (v < u)			{	// ��v < u�ı߲��뵽��С�� 
                g.GetElem(v, v1); 
                g.GetElem(u, v2);
                KEdge.vertex1 = v1;
                KEdge.vertex2 = v2;
                KEdge.weight = g.GetWeight(v,u);
				ha.Insert(KEdge);
			}
	count = 0;					    // ��ʾ�Ѿ���ѡ�ı���
	int cost = 0;
	int _weight;
	while (count < VexNum - 1)	{	
        ha.DeleteTop(KEdge);        // �ӶѶ�ȡһ����
		v1 = KEdge.vertex1;
        v2 = KEdge.vertex2;
		_weight = KEdge.weight;
		if (f.Differ(v1, v2))	{	// ���������������㲻��ͬһ������
			cout << "��:( " << v1 << ", " << v2 << " ) Ȩ:" << _weight << endl ; // ����߼�Ȩֵ
			cost += _weight;
			f.Union(v1, v2);		// �������������ڵ����ϲ���һ����
			count++;
		}
		
	}
	cout << "��·�ܳ�:" << cost << endl;
	return cost;
}

template <class ElemType>
void DFSTraverse(const AdjMatrixUndirGraph<ElemType> &g, void (*Visit)(const ElemType &))
// ��ʼ����������ͼg
// ���������������ͼg����������ȱ���
{
	int v;
	for (v = 0; v < g.GetVexNum(); v++)
		g.SetTag(v, UNVISITED);// ��ÿ����������δ���ʱ�־

	for (v = 0; v < g.GetVexNum(); v++)
		
		if (g.GetTag(v) == UNVISITED)
			DFS(g, v , Visit);// ����δ���ʵĶ���v��ʼ��������������� 
}

template <class ElemType>
void DFS(const AdjMatrixUndirGraph<ElemType> &g, int v, void (*Visit)(const ElemType &))
// ��ʼ����������ͼg
// ����������Ӷ���v�������������������
{	
	ElemType e;	
	g.SetTag(v, VISITED);		// ���ö���v�ѷ��ʱ�־
	g.GetElem(v, e);			// ȡ����v������Ԫ��ֵ 
	Visit(e);					// ���ʶ���v
	for (int w = g.FirstAdjVex(v); w != -1; w = g.NextAdjVex(v, w))
		if (g.GetTag(w) == UNVISITED)
			DFS(g, w , Visit);	// ��v����δ���ʹ����ڽӶ���w��ʼ���������������
}

#endif

