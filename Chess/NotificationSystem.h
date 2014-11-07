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

#include "Position.h"

using namespace std ;

enum class EventType {
	pieceArriving,
	pieceLeaving
	//add any more here
};



template<class Data, class UniqueIdentifier>
struct Notification {
	
protected:
	
	static vector< vector<Notification<Data, UniqueIdentifier>> > registeredMessageRecipients ;
	
	EventType eventType ;
	
	/**
	 * A static member function or global which will be called when notify() is called.
	 * Can also be a non-static member function by using std::bind at the call site.
	 *
	 */
	function<void (Data *)> callBackFunction ;
	
	const UniqueIdentifier match ;
	
	void notify(Data * data) ;

public:
	
	static void notify(EventType eventType, Data * data, const UniqueIdentifier match) ;
	
	Notification(EventType eventType, function<void (Data *)> callBackFunction, const UniqueIdentifier & match) : //
		eventType(eventType), callBackFunction(callBackFunction), match(match) {}
	

	/**
	 * Copy constructor
	 */
	Notification(const Notification & other) :
		eventType(other.eventType), callBackFunction(other.callBackFunction), match(other.match) {}
	
	/**
	 * Move constructor
	 */
	Notification(Notification && other) :
		eventType(std::move(other.eventType)), callBackFunction(std::move(other.callBackFunction)), match(std::move(other.match)) {}
	
	~Notification() {}
	
	void registerForCallback() ;

	
} ;

template<class Data, class UniqueIdentifier>
vector< vector<Notification<Data, UniqueIdentifier>> > Notification<Data, UniqueIdentifier>::registeredMessageRecipients ;

template<class Data, class UniqueIdentifier>
void Notification<Data, UniqueIdentifier>::notify(EventType eventType, Data * data, const UniqueIdentifier match) {
	for (auto i = 0 ; i < registeredMessageRecipients.size() ; i++) {
		if ((registeredMessageRecipients.at(i).size() > 0) && (registeredMessageRecipients.at(i).at(0).eventType == eventType)) {
			for (auto j = 0 ; j < registeredMessageRecipients.at(i).size() ; j++) {
				if (equal(registeredMessageRecipients.at(i).at(j).match, match)) {
					registeredMessageRecipients.at(i).at(j).notify(data) ;
					break ; //may want to comment this out 
				}
			}
			break ;
		}
	}
}

template<class Data, class UniqueIdentifier>
void Notification<Data, UniqueIdentifier>::notify(Data * data) {
	callBackFunction(data) ;
}

template<class Data, class UniqueIdentifier>
void Notification<Data, UniqueIdentifier>::registerForCallback() {
	
	bool firstEventOfType = true ;
	
	for (auto i = 0 ; i < registeredMessageRecipients.size() ; i++) {
		if ((registeredMessageRecipients.at(i).size() > 0) && (registeredMessageRecipients.at(i).at(0).eventType == this->eventType)) {
			firstEventOfType = false ;
			registeredMessageRecipients.at(i).push_back(*this) ;
		}
	}
	
	if (firstEventOfType) {
		registeredMessageRecipients.push_back(vector<Notification<Data, UniqueIdentifier>>()) ;
		auto sz = registeredMessageRecipients.size() ;
		registeredMessageRecipients.at(sz - 1).push_back(*this) ;
	}

}










#endif /* defined(__Chess__NotificationSystem__) */
