#ifndef		__CHAIN_H__
#define		__CHAIN_H__

#include "BaseType.h"
#include "Queue.h"

/**	Լ��CChainNode<DataT,RecyclerT>�����ݳط���,Recycle�������ڷ����������ݳأ�
*	Ҳ����˵Recycle��������֮�󣬽��Ӧ�ò����κ������ϣ����ݳ������Խ��ý��
*	��Ϊ�½����䡣
*	@Remarks
*	RecyclerT��Ҫ���ϣ�
*	1�����޲��������Ĭ�Ϲ��졣
*	2���ṩ���з���VOID Recycle(CChainNode<DataT,RecyclerT>* pNode)��
*/
template<typename DataT,typename RecyclerT>
class CChain;

template<typename DataT,typename RecyclerT>
class CChainNode
{
public:
	typedef CChain<DataT,RecyclerT>		ChainType;
	typedef CChainNode<DataT,RecyclerT>	ItemType;
	friend class CChain<DataT,RecyclerT>;
	friend class Iterator;
	/**	һ������STL�е������Ķ��������Ǹ����ϲ��ϸ�һ����
	*/
	class Iterator
	{
	public:
		inline ChainType*				GetChain(VOID) const
		{
			if(NULL==m_pItem)
				return NULL;
			return m_pItem->m_pChain;
		}
		inline const Iterator			GetNext(VOID) const
		{
			if(NULL==m_pItem)
				return Iterator();
			return Iterator(m_pItem->m_pNext);
		}
		inline const Iterator			GetPrevious(VOID) const
		{
			if(NULL==m_pItem)
				return Iterator();
			return Iterator(m_pItem->m_pPrevious);
		}
		inline BOOL						IsNull(VOID) const
		{
			return m_pItem==NULL;
		}
	public:
		inline ItemType* GetPtr(VOID) const {return m_pItem;}
		inline VOID Recycle(VOID)
		{
			if(NULL==m_pItem)
				return;
			m_pItem->Recycle();
		}
		inline BOOL						IsAllocated(VOID) const
		{
			if(NULL==m_pItem)
				return FALSE;
			return m_pItem->IsAllocated();
		}
	public:
		inline DataT& operator * (VOID) const {CrashAssert(m_pItem);return m_pItem->m_Data;}
		inline DataT* operator -> (VOID) const {CrashAssert(m_pItem);return &(m_pItem->m_Data);}	
	public:
		inline Iterator& operator++(VOID)
		{
			CrashAssert(m_pItem);
			m_pItem=m_pItem->m_pNext;
			return *this;
		}
		inline const Iterator operator++(INT)
		{
			CrashAssert(m_pItem);
			Iterator tmp = *this;
			++(*this);
			return tmp;
		}
		inline Iterator& operator--(VOID)
		{
			CrashAssert(m_pItem);
			m_pItem=m_pItem->m_pPrevious;
			return *this;
		}
		inline const Iterator operator--(INT)
		{
			CrashAssert(m_pItem);
			Iterator tmp = *this;
			--(*this);
			return tmp;
		}
		inline BOOL operator == (const Iterator& other) const
		{
			return m_pItem==other.m_pItem;
		}
		inline BOOL operator != (const Iterator& other) const
		{
			return !(operator ==(other));
		}
	public:
		Iterator(VOID)
		{
			m_pItem=NULL;
		}
		explicit Iterator(ItemType* ptr)
		{
			m_pItem=ptr;
		}
		Iterator(const Iterator& other)
		{
			m_pItem=other.m_pItem;
		}
		inline Iterator& operator = (const Iterator& other)
		{
			if(this==&other)
				return *this;
			m_pItem=other.m_pItem;
			return *this;
		}
		inline Iterator& operator = (ItemType* pItem)
		{
			m_pItem=pItem;
			return *this;
		}
	private:
		ItemType* m_pItem;
	};
protected:
	ChainType*					m_pChain;
	ItemType*					m_pNext;
	ItemType*					m_pPrevious;
protected:
	DataT						m_Data;
	RecyclerT					m_Recycler;
public:
	CChainNode(VOID)
	{
		m_pChain    = NULL;
		m_pNext     = NULL;
		m_pPrevious = NULL;
		m_Recycler.m_pNode = this;
	}
	virtual ~CChainNode(VOID){}
public:
	DataT& GetData(VOID){return m_Data;}
	const DataT& GetData(VOID) const {return m_Data;}
public:
	inline VOID Recycle(VOID);
	inline BOOL IsAllocated(VOID)const;
public:
	RecyclerT& GetRecycler(VOID){return m_Recycler;}
	const RecyclerT& GetRecycler(VOID)const{return m_Recycler;}
private:
	//ʹ��ǰ�������������벢��������������ǰ�����Ϊ�ڽӣ��������ϵĽ��������һ��
	inline VOID DisConnect(VOID);
};

template<typename DataT,typename RecyclerT>
class CChain
{
public:
	typedef CChain<DataT,RecyclerT>			ChainType;
	typedef CChainNode<DataT,RecyclerT>		ItemType;
	typedef typename ItemType::Iterator		Iterator;
	friend class CChainNode<DataT,RecyclerT>;
private:
	UINT				m_uNum;
	ItemType*			m_pHead;
	ItemType*			m_pTail;
public:
	CChain(VOID)
	{
		m_uNum		= 0;
		m_pHead		= NULL;
		m_pTail     = NULL;
	}
	virtual ~CChain(VOID)
	{
		RemoveAll();
	}
	//��ȡ�����һ�����
	inline const Iterator	First(VOID) const
	{
		return Iterator(m_pHead);
	}
	//��ȡ�������һ�����
	inline const Iterator	Last(VOID) const
	{
		return Iterator(m_pTail);
	}
	//��ȡ�����Ͻ������
	inline UINT				GetNum(VOID) const
	{
		return m_uNum;
	}
	//��ȡ��i�����(��0��ʼ����)
	inline Iterator			GetIterator(INT i) const;
	//�������ϲ���ָ����㣬���ؽ���������е�λ��
	inline INT				IndexOf(const Iterator& it) const;
	//������ͷ���һ����㣬�˽�㽫��Ϊ�µ�����ͷ
	inline BOOL				AddFirst(const Iterator& it);
	//������β���һ����㣬�˽�㽫��Ϊ�µ�����β
	inline BOOL				AddLast(const Iterator& it);
	//��ָ�����ǰ����һ�����,ָ����㲻��Ϊ��
	inline BOOL				InsertBefore(const Iterator& pos,const Iterator& it);
	//��ָ���������һ����㣬ָ����㲻��Ϊ��
	inline BOOL				InsertAfter(const Iterator& pos,const Iterator& it);
	//ɾ����һ����㣬��㷵�������ݳأ�����ɾ��������ĵ�һ�����
	inline const Iterator	RemoveFirst(VOID);
	//ɾ�����һ����㣬��㷵�������ݳأ�����ɾ������������һ�����
	inline const Iterator	RemoveLast(VOID);
	//��������ɾ��һ����㣬��㷵�������ݳأ����ر�ɾ��������Ľ��
	inline const Iterator	Remove(const Iterator& it);
	//��������ɾ�����н�㣬ȫ����㷵�������ݳ�
	inline BOOL				RemoveAll(VOID);
	//�ƶ�ָ�����Ϊ�����׽��
	inline const Iterator	MoveAsFirst(const Iterator& it);
	//�ƶ�ָ�����Ϊ����β���
	inline const Iterator	MoveAsLast(const Iterator& it);
};

template<typename DataT>
class NodeRecyclerForDataT
{
public:
	typedef NodeRecyclerForDataT<DataT> Recycler;
	typedef CChainNode<DataT,Recycler> DataNode;
	friend class CChainNode<DataT,Recycler>;
public:
	VOID Recycle(VOID)
	{
		if(NULL==m_pNode)
			return;
		m_pNode->GetData().Recycle();
	}
	BOOL IsAllocated(VOID) const
	{
		return m_pNode->GetData().IsAllocated();
	}
private:
	NodeRecyclerForDataT(VOID):m_pNode(NULL)
	{}
private:
	DataNode* m_pNode;
};

#include "Chain.inl"

#endif