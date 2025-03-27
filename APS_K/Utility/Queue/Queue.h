#pragma once

#include <afxmt.h>

template<class T>
class CQueue
{
private:
	struct NODE
	{
		T pPacket;
		NODE* pNext;
	};

	NODE* m_pHeadNode;	// 머리 노드 포인터
	NODE* m_pTailNode;	// 꼬리 노드 포인터

	int m_nNodeCount;	// 큐에 있는 엔트리 갯수
	CCriticalSection m_clCritSect;

public:
	CQueue()
	{
		m_pHeadNode = NULL;
		m_pTailNode = NULL;

		m_nNodeCount = 0;
	};

	~CQueue()
	{
		this->RemoveAll();
	};

	bool Push(T pPacket)
	{
		m_clCritSect.Lock();

		// 노드를 만든다.
		NODE* pNode = new NODE;
		if (pNode == NULL)
		{
			m_clCritSect.Unlock();
			return false;
		}

		// 새 노드를 구성한다.
		pNode->pPacket = pPacket;
		pNode->pNext = NULL;

		// 텅빈 큐인지 확인한다.
		if (m_pHeadNode == NULL)
		{
			// 머리노드와 꼬리노드가 모두 새 노드를 가리킨다.
			m_pHeadNode = pNode;
			m_pTailNode = pNode;
		}
		else
		{
			// 꼬리노드와 새 노드를 연결한다.
			m_pTailNode->pNext = pNode;
			// 새 노드가 꼬리노드가 된다.
			m_pTailNode = pNode;
		}

		// 큐의 노드 개수를 증가한다.
		m_nNodeCount++;

		m_clCritSect.Unlock();

		return true;
	};

	T Pop(void)
	{
		m_clCritSect.Lock();

		// 텅빈 큐인지 확인한다.
		if (m_pHeadNode == NULL)
		{
			m_clCritSect.Unlock();
			return NULL;
		}

		T pPacket;

		// 머리노드 포인터를 따로 저장한다.
		NODE* pTempHead = m_pHeadNode;

		// 머리노드의 패킷 포인터를 넘겨준다.
		pPacket = m_pHeadNode->pPacket;

		// 머리노드가 가리키는 노드가 새 머리노드가 된다.
		m_pHeadNode = m_pHeadNode->pNext;
		// 새 머리노드가 NULL이면 꼬리노드도 NULL이다.
		if (m_pHeadNode == NULL)
		{
			m_pTailNode = NULL;
		}

		// 이전 머리노드를 해제한다.
		delete pTempHead;

		// 큐의 노드 개수를 감소한다.
		m_nNodeCount--;

		m_clCritSect.Unlock();

		return pPacket;
	};

	void RemoveAll(void)
	{
		T pPacket;

		// 모든 노드를 POP하고 패킷 메모리도 해제한다.
		while (true)
		{
			pPacket = this->Pop();

			if (pPacket == NULL)
			{
				break;
			}
			else
			{
				delete pPacket;
			}
		}
	};

	int GetCount(void)
	{
		int nRetVal;

		m_clCritSect.Lock();
		nRetVal = m_nNodeCount;
		m_clCritSect.Unlock();

		return nRetVal;
	};
};