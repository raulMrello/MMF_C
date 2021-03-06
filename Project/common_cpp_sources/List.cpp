/*
 * List.cpp
 *
 *  Created on:	09/04/2015
 *  Author: 	raulMrello
 *
 *  List module, manages double-linked lists.
 */

#include "List.h"
#include <stdlib.h>

#if !defined(UINT32_MAX)
#define UINT32_MAX 	0xffffffff  /* 4294967295U */
#endif

//------------------------------------------------------------------------------------
//-- PRIVATE FUNCTIONS ---------------------------------------------------------------
//------------------------------------------------------------------------------------

void List::removeItem(ListItem *listitem){
	// if is first will point to the next
	if(!listitem->prev){
		// if next is null then list is empty
		if(!listitem->next){
			_first = 0;
			_last = 0;
			_count = 0;
			_search = 0;
			free(listitem);
		}
		_first = listitem->next;
		listitem->next->prev = 0;
		_count--;
		 free(listitem);
	}
	// else, adjust pointers
	listitem->prev->next = listitem->next;
	if(listitem->next)
		listitem->next->prev = listitem->prev;
	else
		_last = listitem->prev;
	_count--;
	free(listitem);
}

//------------------------------------------------------------------------------------
//-- PUBLIC FUNCTIONS ----------------------------------------------------------------
//------------------------------------------------------------------------------------

List::List(){
	_count = 0;
	_first = 0;
	_last = 0;
	_search = 0;
	_numItems = UINT32_MAX;
}

//------------------------------------------------------------------------------------
List::~List(){
	// remove all items
	while(_first){
		removeItem(_last);
	}
}

//------------------------------------------------------------------------------------
void List::setLimit(uint32_t numItems) throw (ListException){
	if(!numItems){
		throw NULL_POINTER;
	}
	_numItems = numItems;
}

//------------------------------------------------------------------------------------
template<typename T>
void List::addItem(T* item) throw (ListException){
	if(!item){
		throw NULL_POINTER;
	}
	if(_count >= _numItems){
		throw LIMIT_EXCEEDED;
	}
	ListItem* listitem;
	listitem = (ListItem*)malloc(sizeof(ListItem));
	if(!listitem){
		throw OUT_OF_MEMORY;
	}
	listitem->item = item;
	// if first element, initializes pointers
	if(!_count){
		_first = listitem;
		_last = listitem;
		listitem->prev = 0;
		listitem->next = 0;
	}
	// else at to the end
	else{
		ListItem* last = _last;
		last->next = listitem;
		listitem->prev = last;
		listitem->next = 0;
		_last = listitem;
	}
	_count++;
}

//------------------------------------------------------------------------------------
template<typename T>
void List::removeItem(T* item) throw (ListException){
	if(!item){
		throw NULL_POINTER;
	}
	ListItem* listitem;
	// search the item in all elements
	listitem = _first;
	do{
		if(listitem->item == item){
			removeItem(listitem);
			return;
		}
		listitem = listitem->next;
	}while(listitem);
	throw ITEM_NOT_FOUND;
}

//------------------------------------------------------------------------------------
uint32_t List::getItemCount(){
	return _count;
}

//------------------------------------------------------------------------------------
void* List::getFirstItem(){
	_search = _first;
	if(!_search){
		return 0;
	}
	return _search->item;

}

//------------------------------------------------------------------------------------
void* List::getNextItem(){
	if(!_search){
		return 0;
	}
	_search = _search->next;
	if(!_search){
		return 0;
	}
	return _search->item;
}

//------------------------------------------------------------------------------------
template<typename T>
bool List::searchItem(T* item) throw (ListException){
	if(!item){
		throw NULL_POINTER;
	}
	T* i = (T*)getFirstItem();
	if(!i){
		return 0;
	}
	for(;;){
		if(i == item){
			return i;
		}
		i = (T*)getNextItem();
		if(!i){
			break;
		}
	}
	return 0;
}

