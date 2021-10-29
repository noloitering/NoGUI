//#pragma once

namespace NoMVC
{
	class Model
	{
	public:
		virtual void update() = 0;
		virtual void render() = 0;
	};
}