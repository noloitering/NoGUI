#pragma once

#include <cstring>

#include "raylib.h"

namespace NoMAD
{
	const size_t TAGBUFF = 51;
	const size_t INBUFF = 2001;
	extern size_t OBJCOUNT;
	class GameObj
	{
	protected:
		const size_t id = 0; // unique identifier
		char tag[TAGBUFF] = "Default"; // common identifier
		char inner[INBUFF] = ""; // short description or content
	public:
		GameObj(const size_t& num=OBJCOUNT, const char* type="Default", const char* in="")
			: id(num) {setTag(type); setInner(in); OBJCOUNT++;}
		const size_t getId()
		{
			
			return id;
		}
		
		const char* getTag()
		{
			
			return tag;
		}
		
		const char* getInner()
		{
			
			return inner;
		}
		
		void setTag(const char* type)
		{
			// use strncat so null terminator is added to the end if 'in' is too big
			tag[0] = '\0';
			strncat(tag, type, TAGBUFF - 1);
		}
		
		void setInner(const char* in)
		{
			// use strncat so null terminator is added to the end if 'in' is too big
			inner[0] = '\0';
			strncat(inner, in, INBUFF - 1);
		}
	};
}