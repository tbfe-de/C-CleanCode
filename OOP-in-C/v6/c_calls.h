#ifndef C_CALLS_H
#define C_CALLS_H

#define SCALL_(object, method)\
	object##_##method()
#define SCALL_1(object, method, _1)\
	object##_##method(_1)
#define SCALL_2(object, method, _1, _2)\
	object##_##method(_1, _2)
#define SCALL_3(object, method, _1, _2, _3)\
	object##_##method(_1, _2, _3)
#define SCALL_4(object, method, _1, _2, _3, _4)\
	object##_##method(_1, _2, _3, _4)
#define SCALL_5(object, method, _1, _2, _3, _4, _5)\
	object##_##method(_1, _2, _3, _4, _5)
#define SCALL_6(object, method, _1, _2, _3, _4, _5, _6)\
	object##_##method(_1, _2, _3, _4, _5, _6)

#define DCALL_(class, object, method)\
	class##_##method(&(object))
#define DCALL_1(class, object, method, _1)\
	class##_##method(&(object), _1)
#define DCALL_2(class, object, method, _1, _2)\
	class##_##method(&(object), _1, _2)
#define DCALL_3(class, object, method, _1, _2, _3)\
	class##_##method(&(object), _1, _2, _3)
#define DCALL_4(class, object, method, _1, _2, _3, _4)\
	class##_##method(&(object), _1, _2, _3, _4)
#define DCALL_5(class, object, method, _1, _2, _3, _4, _5)\
	class##_##method(&(object), _1, _2, _3, _4, _5)
#define DCALL_6(class, object, method, _1, _2, _3, _4, _5, _6)\
	class##_##method(&(object), _1, _2, _3, _4, _5, _6)

#define VCALL_(class, object, method)\
	((class##_virtual_##method##_call)\
	 (*(void (***)(void))&object)[class##_virtual_##method])(&(object))
#define VCALL_1(class, object, method, _1)\
	((class##_virtual_##method##_call)\
	 (*(void (***)(void))&object)[class##_virtual_##method])(&(object), _1)
#define VCALL_2(class, object, method, _1, _2)\
	((class##_virtual_##method##_call)\
	 (*(void (***)(void))&object)[class##_virtual_##method])(&(object), _1, _2)
#define VCALL_3(class, object, method, _1, _2, _3)\
	((class##_virtual_##method##_call)\
	 (*(void (***)(void))&object)[class##_virtual_##method])(&(object), _1, _2, _3)
#define VCALL_4(class, object, method, _1, _2, _3, _4)\
	((class##_virtual_##method##_call)\
	 (*(void (***)(void))&object)[class##_virtual_##method])(&(object), _1, _2, _3, _4)
#define VCALL_5(class, object, method, _1, _2, _3, _4, _5)\
	((class##_virtual_##method##_call)\
	 (*(void (***)(void))&object)[class##_virtual_##method])(&(object), _1, _2, _3, _4, _5)
#define VCALL_6(class, object, method, _1, _2, _3, _4, _5, _6)\
	((class##_virtual_##method##_call)\
	 (*(void (***)(void))&object)[class##_virtual_##method])(&(object), _1, _2, _3, _4, _5, _6)

#endif // include guard
