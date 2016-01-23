/*
 *
 *  Created on: 2016年1月23日
 *      Author: zhangyalei
 */

#ifndef V8PP_CALL_V8_H_
#define V8PP_CALL_V8_H_

#include "include/v8.h"
#include "convert.h"

namespace v8pp {

/// Call a V8 function, converting C++ arguments to v8::Value arguments
/// @param isolate V8 isolate instance
/// @param func  V8 function to call
/// @param recv V8 object used as `this` in the function
/// @param args...  C++ arguments to convert to JS arguments using to_v8
template<typename ...Args>
v8::Handle<v8::Value> call_v8(v8::Isolate* isolate, v8::Handle<v8::Function> func,
	v8::Handle<v8::Value> recv, Args... args)
{
	v8::EscapableHandleScope scope(isolate);

	int const arg_count = sizeof...(Args);
	// +1 to allocate array for arg_count == 0
	v8::Handle<v8::Value> v8_args[arg_count + 1] = { to_v8(isolate, args)... };

	v8::Local<v8::Value> result = func->Call(recv, arg_count, v8_args);

	return scope.Escape(result);
}

} // namespace v8pp

#endif // V8PP_CALL_V8_H_
