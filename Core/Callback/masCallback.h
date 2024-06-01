#pragma once

#include "../Common.h"

template<typename SIGNITURE>
class masCallback;

template<typename RET, typename ... ARGS>
class masCallback<RET(ARGS...)>
{
private:
	using TClass    = masCallback;
	using TMethod   = RET(TClass::*)(ARGS...);
	using TFunction = RET(*)(ARGS...);

	union UCallback
	{
		TMethod   Method;
		TFunction Function;
	};

	enum EBindType
	{
		BIND_NONE,
		BIND_METHOD,
		BIND_FUNCTION
	};

private:
	TClass    *Instance;
	UCallback  Callback;
	EBindType  BindType;

	void Internal_Reset()
	{
		Instance          = NULL;
		Callback.Method   = NULL;
		Callback.Function = NULL;
		BindType          = BIND_NONE;
	}

public:
	MAS_CLASS_DISABLE_COPY_AND_MOVE_SEMANTIC(masCallback);

	masCallback()  { Internal_Reset(); }
	~masCallback() { Internal_Reset(); }

	template<typename CLASS>
	void BindMethod(void* in_instance, RET(CLASS::*in_method)(ARGS...))
	{
		Internal_Reset();
		Instance        = (TClass*)in_instance;
		Callback.Method = (TMethod)in_method;
		BindType        = BIND_METHOD;
	}

	void BindFunction(RET(*in_function)(ARGS...))
	{
		Internal_Reset();
		Callback.Function = in_function;
		BindType          = BIND_FUNCTION;
	}

	bool IsBound()
	{
		return (BindType != BIND_NONE);
	}

	RET Exec(ARGS... args)
	{
		switch(BindType)
		{
		case BIND_METHOD:
			if(Instance && Callback.Method)
				return (Instance->*Callback.Method)(std::forward<ARGS>(args)...);
			break;

		case BIND_FUNCTION:
			if(Callback.Function)
				return Callback.Function(std::forward<ARGS>(args)...);
			break;
		}

		return (RET)0;
	}
};

#define MAS_DECLARE_CALLBACK_RET(CALLBACK_NAME, RETURN_TYPE, ...) using CALLBACK_NAME = masCallback<RETURN_TYPE(__VA_ARGS__)>
#define MAS_DECLARE_CALLBACK_NO_RET(CALLBACK_NAME, ...)           using CALLBACK_NAME = masCallback<void(__VA_ARGS__)>