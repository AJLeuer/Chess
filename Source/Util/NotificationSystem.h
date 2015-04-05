//
//  NotificationSystem.h
//  Chess
//
//  Created by Adam James Leuer on 11/3/14.
//  Copyright (c) 2014 Adam James Leuer. All rights reserved.
//

#ifndef __Chess__NotificationSystem__
#define __Chess__NotificationSystem__

#include <iostream>
#include <functional>
#include <vector>

#include <SFML/Window.hpp>
#include "../Util/Position.h"

using namespace std ;

enum class EventType {
	pieceArriving,
	pieceLeaving
	//add any more here
};



template<class Data, typename UniqueNumericIdentifier>
struct Notification {
	
protected:
	
	static vector< vector<Notification<Data, UniqueNumericIdentifier>> > registeredMessageRecipients ;
	
	EventType eventType ;
	
	/**
	 * A static member function or global which will be called when notify() is called.
	 * Can also be a non-static member function by using std::bind at the call site.
	 *
	 */
	function<void (Data *)> callBackFunction ;
	
	UniqueNumericIdentifier hash ;
	
	void notify(Data * data) ;

public:
	
	static void notify(EventType eventType, Data * data, const UniqueNumericIdentifier hash) ;
	
	Notification(EventType eventType, function<void (Data *)> callBackFunction, const UniqueNumericIdentifier hash) : //
		eventType(eventType), callBackFunction(callBackFunction), hash(hash) {}
	

	/**
	 * Copy constructor
	 */
	Notification(const Notification & other) :
		eventType(other.eventType), callBackFunction(other.callBackFunction), hash(other.hash) {}
	
	/**
	 * Move constructor
	 */
	Notification(Notification && other) :
		eventType(std::move(other.eventType)), callBackFunction(std::move(other.callBackFunction)), hash(std::move(other.hash)) {}
	
	~Notification() {}
	
	void registerForCallback() ;

	
} ;

template<class Data, typename UniqueNumericIdentifier>
vector< vector<Notification<Data, UniqueNumericIdentifier>> > Notification<Data, UniqueNumericIdentifier>::registeredMessageRecipients ;

template<class Data, typename UniqueNumericIdentifier>
void Notification<Data, UniqueNumericIdentifier>::notify(EventType eventType, Data * data, const UniqueNumericIdentifier hash) {
	
	for (auto i = 0 ; i < registeredMessageRecipients.size() ; i++) {
		
		if ((registeredMessageRecipients.at(i).size() > 0) && (registeredMessageRecipients.at(i).at(0).eventType == eventType)) {
			
			for (auto j = 0 ; j < registeredMessageRecipients.at(i).size() ; j++) {
				
				if (registeredMessageRecipients.at(i).at(j).hash == hash) {
					registeredMessageRecipients.at(i).at(j).notify(data) ;
					break ; //may want to comment this out 
				}
				
			}
			
			break ;
		}
	}
}

template<class Data, typename UniqueNumericIdentifier>
void Notification<Data, UniqueNumericIdentifier>::notify(Data * data) {
	callBackFunction(data) ;
}

template<class Data, typename UniqueNumericIdentifier>
void Notification<Data, UniqueNumericIdentifier>::registerForCallback() {
	
	bool firstEventOfType = true ;
	
	for (auto i = 0 ; i < registeredMessageRecipients.size() ; i++) {
		if ((registeredMessageRecipients.at(i).size() > 0) && (registeredMessageRecipients.at(i).at(0).eventType == this->eventType)) {
			firstEventOfType = false ;
			registeredMessageRecipients.at(i).push_back(*this) ;
		}
	}
	
	if (firstEventOfType) {
		registeredMessageRecipients.push_back(vector<Notification<Data, UniqueNumericIdentifier>>()) ;
		auto sz = registeredMessageRecipients.size() ;
		registeredMessageRecipients.at(sz - 1).push_back(*this) ;
	}

}










#endif /* defined(__Chess__NotificationSystem__) */
