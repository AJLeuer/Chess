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

#include "../Util/UniqueNumericID.h"
#include "../Util/Position.h"


using namespace std ;


enum class EventType {
	pieceArrivingAtPositionSpecifiedByID,
	pieceLeavingPositionSpecifiedByID,
	pieceSpecifiedByIDWasCaptured,
	pawnSpecifiedByIDWasPromoted
	//add any more here
};



template<typename Data>
struct Notification {
	
protected:
	
	static vector< vector<Notification<Data>> > registeredMessageRecipients ;
	
	EventType eventType ;
	
	/**
	 * A static member function or global which will be called when notify() is called.
	 * Can also be a non-static member function by using std::bind at the call site.
	 *
	 */
	function<void (Data *)> callBackFunction ;
	
	const UniqueNumericIdentifier uniqueID ;
	
	void notify(Data * data) ;

public:
	
	static void notify(EventType eventType, Data * data, const UniqueNumericIdentifier uniqueID) ;
	
	Notification(EventType eventType, function<void (Data *)> callBackFunction, const UniqueNumericIdentifier uniqueID) : //
		eventType(eventType), callBackFunction(callBackFunction), uniqueID(uniqueID) {}
	

	/**
	 * Copy constructor
	 */
	Notification(const Notification & other) :
		eventType(other.eventType), callBackFunction(other.callBackFunction), uniqueID(other.uniqueID) {}
	
	/**
	 * Move constructor
	 */
	Notification(Notification && other) :
		eventType(std::move(other.eventType)), callBackFunction(std::move(other.callBackFunction)), uniqueID(std::move(other.uniqueID)) {}
	
	~Notification() {}
	
	void registerForCallback() ;

	
} ;

template<typename Data>
vector< vector<Notification<Data>> > Notification<Data>::registeredMessageRecipients ;

template<typename Data>
void Notification<Data>::notify(EventType eventType, Data * data, const UniqueNumericIdentifier uniqueID) {
	
	for (auto i = 0 ; i < registeredMessageRecipients.size() ; i++) {
		
		if ((registeredMessageRecipients.at(i).size() > 0) && (registeredMessageRecipients.at(i).at(0).eventType == eventType)) {
			
			for (auto j = 0 ; j < registeredMessageRecipients.at(i).size() ; j++) {
				if (registeredMessageRecipients.at(i).at(j).uniqueID == uniqueID) {
					registeredMessageRecipients.at(i).at(j).notify(data) ;
				}
			}
			break ; //we only need to iterate through the sub-vector of registeredMsgRecipients that matches our EventType
		}
	}
}

template<typename Data>
void Notification<Data>::notify(Data * data) {
	callBackFunction(data) ;
}

template<typename Data>
void Notification<Data>::registerForCallback() {
	
	bool firstEventOfType = true ;
	
	for (auto i = 0 ; i < registeredMessageRecipients.size() ; i++) {
		if ((registeredMessageRecipients.at(i).size() > 0) && (registeredMessageRecipients.at(i).at(0).eventType == this->eventType)) {
			firstEventOfType = false ;
			registeredMessageRecipients.at(i).push_back(*this) ;
		}
	}
	
	if (firstEventOfType) {
		registeredMessageRecipients.push_back(vector<Notification<Data>>()) ;
		auto sz = registeredMessageRecipients.size() ;
		registeredMessageRecipients.at(sz - 1).push_back(*this) ;
	}

}





#endif /* defined(__Chess__NotificationSystem__) */
