#pragma once
#include <memory>
#include <string>
#include <map>
#include <list>
#include "AnyValue.h"
using std::string;
using std::map;
using std::list;
namespace Utils
{
	typedef map<string, AnyValue> event_value_map_type;
	class Event
	{
	public:
		typedef std::shared_ptr<Event> ptr;
		Event() {}

		 ~Event() {}

		void setName(const char* name);
		const char* getName();
		AnyValue getValue(const char* key);
		void setValue(const char* key, AnyValue value);
	private:
		string _name;
		event_value_map_type _event_value_map;
	};

	//================================================================
	class EventReceiver
	{
	public:
		typedef std::shared_ptr<EventReceiver> ptr;

		virtual ~EventReceiver() {};

		virtual void receive(Event::ptr event) = 0;
	};

	//=================================================================
	/**
	���ʹ�ã��������������ע�ᵽEventManager��ע��ʱ�¼����ƺͽ��ն����Ӧ��ͬһ���¼������ж��receiver���¼�����ʱsend���¼�
	�Ϳ���ִ������receiver��Ӧ��receive�¼���
	*/
	typedef std::list<EventReceiver::ptr> event_list_type;
	typedef std::map<std::string, event_list_type> event_receiver_map_type;
	class EventManager
	{
	public:
		EventManager(){}
		~EventManager() {}
		static EventManager* Inst();

		Event::ptr createEvent();
		void sendEvent(Event::ptr event);
		void postEvent(Event::ptr event);
		void registerReceiver(const char* event_name, EventReceiver::ptr event_receiver);
		void unRegisterReceiver(const char* event_name, EventReceiver::ptr event_receiver);
	private:
		static EventManager* m_Inst;
		event_receiver_map_type _event_receiver_map;
	};
}


