// BoostTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/weak_ptr.hpp>
#include <boost/thread.hpp>
#include <CONIO.H>
//#include <windows.h>


// BoostCondVar_Jan13.cpp : Defines the entry point for the console application.
//


#include <iostream>
using namespace std;

#include "boost/smart_ptr/shared_ptr.hpp"
//#include "boost/thread/thread.hpp"

boost::mutex & GetCoutMut()
{
	static boost::mutex smut;
	return smut;
}

#define THREADS_COUNT 2
#define TSYNC_COUT(con_out) \
{\
	boost::lock_guard<boost::mutex> lg(GetCoutMut());\
	con_out;\
}

class A
{
	//Base m_base;
	int m_a;
public:
	A(int a) :m_a(a)
	{
		std::cout << "A constr " << this << ' ' << m_a << std::endl;
	}
	A(const A & Right) :m_a(Right.m_a)
	{
		std::cout << "A Copy constr " << this << " from " << &Right << std::endl;
	}
	~A()
	{
		std::cout << "a destr " << this << ' ' << m_a << std::endl;
	}
	void Work()
	{
		std::cout << "A::Work " << this << ' ' << m_a << std::endl;
	}
	void Add(int a)
	{
		m_a += a;
		std::cout << "A::Add " << this << ' ' << m_a << std::endl;
	}
	friend std::ostream & operator<<(std::ostream & out, const A & right)
	{
		out << right.m_a;
		return out;
	}
};


struct Data
{
	int * m_pCount;
	boost::mutex * m_pOutMut;
	boost::mutex * m_pCountReadyMut;
	boost::condition_variable * m_pCV; // to send that it is ready
	Data(int * pCount, boost::mutex * pOutMut, boost::mutex * pCountReadyMut,
		boost::condition_variable * pCV) : m_pCount(pCount),
		m_pOutMut(pOutMut), m_pCountReadyMut(pCountReadyMut), m_pCV(pCV)
	{
	}
};

// look on/at GetThreadTimes
void ThFunc(Data * pData)
{
	TSYNC_COUT(cout << "from thread " << boost::this_thread::get_id() << " 111" << endl)
	{
		boost::lock_guard<boost::mutex> lg2(*pData->m_pCountReadyMut);
		if (++(*pData->m_pCount) == THREADS_COUNT)
			pData->m_pCV->notify_one();
	}
	{
		boost::unique_lock<boost::mutex> un(*pData->m_pCountReadyMut);
		TSYNC_COUT(cout << " ThFunc before wait " << un.owns_lock() << ' ' << boost::this_thread::get_id() << " 111" << endl)
			pData->m_pCV->wait(un);
		TSYNC_COUT(cout << " ThFunc after wait " << un.owns_lock() << ' ' << boost::this_thread::get_id() << " 111" << endl)
			TSYNC_COUT(cout << "   after sygnal from main  " << boost::this_thread::get_id() << " 111" << endl)
	}
	int nC = 0;
	while (nC < 5)
	{
		boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
		TSYNC_COUT(cout << " ThFunc  ==while== " << boost::this_thread::get_id() << endl)
			++nC;
	}
}

void ThFunc2(Data * pData, int a)
{
	TSYNC_COUT(cout << "from thread ThFunc2 " << boost::this_thread::get_id() << ' ' << a << " 222" << endl)
	{
		boost::lock_guard<boost::mutex> lg2(*pData->m_pCountReadyMut);
		if (++(*pData->m_pCount) == THREADS_COUNT)
			pData->m_pCV->notify_one();
	}
	////////////////////////////
	{
		boost::unique_lock<boost::mutex> un(*pData->m_pCountReadyMut);
		TSYNC_COUT(cout << " ThFunc2 before wait " << un.owns_lock() << ' ' << boost::this_thread::get_id() << " 222" << endl)

		pData->m_pCV->wait(un);
		TSYNC_COUT(cout << " ThFunc2 after wait " << un.owns_lock() << ' ' << boost::this_thread::get_id() << " 222" << endl)
			TSYNC_COUT(cout << "   after sygnal from main  " << boost::this_thread::get_id() << " 222" << endl)
	}
	int nC = 0;
	while (nC < 5)
	{
		boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
		TSYNC_COUT(cout << " ThFunc2  ==while== " << boost::this_thread::get_id() << endl)
			++nC;
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	{
		/*A * pA = new A(2);
		boost::shared_ptr<A> sh(pA);
		sh->Work();*/
		boost::mutex outMut, countReadyMut;
		boost::condition_variable cv;
		int nCountReadyThreads(0);
		Data dt(&nCountReadyThreads, &outMut, &countReadyMut, &cv);

		boost::thread th(ThFunc, &dt);
		boost::thread th2(ThFunc2, &dt, 3);
		int iIterCount(0);

		while (true)
		{
			boost::unique_lock<boost::mutex> un(countReadyMut);				
			cv.wait(un);				
			TSYNC_COUT(cout << "----- inside wait -------- " << ++iIterCount << endl)
			
			if (nCountReadyThreads == THREADS_COUNT)
			{
				TSYNC_COUT(cout << "----- Ready -------- " << ++iIterCount << endl)
					break;
			}			
		}

		TSYNC_COUT(cout << "----- from main after wait --------" << endl << "----- enter number  --------" << endl)
			int a;
		cin >> a;
		cv.notify_all();

		th.join();
		th2.join();
	}
	cout << "==============" << endl;
	return 0;
}


#ifdef Start_THREAD
#define Test123(a) a
//#define Test123(a)
//:test 
void Test123Func();



class A
{
	int m_a;
	//boost::shared_ptr<A> m_sh;
	boost::weak_ptr<A> m_sh;
public:
	A(int a) :m_a(a)
	{
		//// something 
																				Test123(cout << "A(int a) "<<this<<' '<<m_a << endl);
	}
	~A()
	{
	                                       	                                    Test123(cout << "~A() " << this << ' ' << m_a << endl);
	}
	void Show()
	{
		cout << "A::Show() " << this << ' ' << m_a << endl;
	}
	void SetShared(boost::shared_ptr<A> &r_sh)
	{
		m_sh = r_sh;
	}

	void Func(int b)
	{
		//m_sh->m_a += b;
		if (m_sh.use_count() > 0)
		{
			boost::shared_ptr<A> shIn(m_sh);
			if (shIn.get())
				shIn->m_a += b;
		}

	}
};

void ThFunc(int a);


int main()
{
	boost::thread th(ThFunc, 45);
	cout << "before join " << endl;
	th.join();
	cout << "after join " << endl;
	cout << "press any key to exit"<< endl;
	_getch();

#ifdef WEAK_PTR
	{
		A * pA = new A(8);
		boost::shared_ptr<A> sh(pA);
		
		{
			A * pA2 = new A(10);
			boost::shared_ptr<A> sh2(pA2);
			pA->SetShared(sh2);
		}
		pA->Func(5);

		/*boost::shared_ptr<A> sh2(sh);
		boost::shared_ptr<A> sh3;
		sh3 = sh2;
		sh3->Show();
		sh->Show();*/

		pA->SetShared(sh);
		pA->Func(7);
		sh->Func(10);
	}  // not call constructor, 
#endif // WEAK_PTR
    return 0;
}

void Test123Func()
{
	//...
	// variable nCount must have value  1456

}

void ThFunc(int a)
{
	cout << "From thread "<<a <<" th id = "<<boost::this_thread::get_id()<< endl;
	MessageBox(NULL, L"From thread", L"Caption", MB_OK);
}

#endif //Start_THREAD