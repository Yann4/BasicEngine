#include <vector>

//Doesn't allow duplicates
//O(1) insertion
//O(n) removal
//O(n) access

template <class T>
class Pool
{
	private:

		struct Object
		{
			bool available;
			union
			{
				T data;
				Object* next;
			}state;
		};

		int size = 0;
		int numAlive = 0;

		Object* nextAvailable = nullptr;
		std::vector< Object > objs;

	public:
		Pool();
		Pool(int size);
		
		bool create(T newObj);
		std::vector<T*> getAlive();
		bool removeObj(T toDel);
};

template <class T>
Pool<T>::Pool()
{
}

template <class T>
Pool<T>::Pool(int size):size(size)
{
	objs = std::vector< Object >(size);
	
	//All are available
	for(int i = 0; i < objs.size() - 1; i++)
	{
		 objs[i].state.next = &objs[i+1];
	}
	
	objs[objs.size()-1].state.next = nullptr; //Last one terminates list
	
	nextAvailable = &objs[0];
}

template <class T>
bool Pool<T>::create(T newObj)
{
	if(nextAvailable == nullptr)
	{
		return false;
	}
	
	Object* newO = nextAvailable;
	nextAvailable = nextAvailable->state.next;

	newO->state.data = newObj;
	newO->available = false;
	numAlive++;
	
	return true;
}

template <class T>
std::vector<T*> Pool<T>::getAlive()
{
	std::vector<T*> avl = std::vector<T*>(numAlive);
	int cnt = 0;
	for(auto& o : objs)
	{
		if(!o.available)
		{
			avl.at(cnt++) = &(o.state.data);
		}
	}
	
	return avl;
}

template <class T>
bool Pool<T>::removeObj(T toDel)
{
	for(auto& ob: objs)
	{
		if(!ob.available && ob.state.data == toDel)
		{
			ob.state.next = nextAvailable;
			ob.available = true;
			nextAvailable = &ob;
			numAlive--;
			break;
		}
	}
}
