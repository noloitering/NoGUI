#ifndef MODEL_H
#define MODEL_H

namespace NoMVC
{
	class Model
	{
	public:
		virtual void update() = 0;
		virtual void render() = 0;
	};
}

#endif