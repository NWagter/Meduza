#pragma once

#ifdef _DEBUG
#define VA_ARGS(...) , ##__VA_ARGS__

#define ME_ASSERT(assertion)\
{\
	if(!(assertion))\
	{\
		std::string assertmsg = std::string("Assertion `"#assertion"` failed in ") + std::string(__FILE__) + " on line: " + std::to_string(__LINE__) + ": ";\
		printf("%s", assertmsg.c_str());\
		std::terminate();\
	}\
}

#define ME_ASSERT_M(assertion, msg, ...)\
{\
	if(!(assertion))\
	{\
		std::string assertmsg = std::string("Assertion `"#assertion"` failed in ") + std::string(__FILE__) + " on line: " + std::to_string(__LINE__) + ": ";\
		printf("%s", assertmsg.c_str());\
		std::terminate();\
	}\
}

#define ME_CORE_ASSERT(assertion)\
{\
	if(!(assertion))\
	{\
		std::string assertmsg = std::string("Assertion `"#assertion"` failed in ") + std::string(__FILE__) + " on line: " + std::to_string(__LINE__) + ": ";\
		printf("[CORE] %s", assertmsg.c_str());\
		std::terminate();\
	}\
}
#define ME_CORE_ASSERT_M(assertion, msg, ...)\
{\
	if(!(assertion))\
	{\
		std::string assertmsg = std::string("Assertion `"#assertion"` failed in ") + std::string(__FILE__) + " on line: " + std::to_string(__LINE__) + ": ";\
		printf("[CORE] %s \n%s", msg, assertmsg.c_str());\
		std::terminate();\
	}\
}

#define ME_GFX_ASSERT(assertion)\
{\
	if(!(assertion))\
	{\
		std::string assertmsg = std::string("Assertion `"#assertion"` failed in ") + std::string(__FILE__) + " on line: " + std::to_string(__LINE__) + ": ";\
		printf("[GFX] %s", assertmsg.c_str());\
		std::terminate();\
	}\
}

#define ME_GFX_ASSERT_M(assertion, msg, ...)\
{\
	if(!(assertion))\
	{\
		std::string assertmsg = std::string("Assertion `"#assertion"` failed in ") + std::string(__FILE__) + " on line: " + std::to_string(__LINE__) + ": ";\
		printf("[GFX] %s \n%s", msg, assertmsg.c_str());\
		std::terminate();\
	}\
}
#define ME_LOG(...) printf("[Default LOG] " ##__VA_ARGS__)
#define ME_CORE_LOG(...) printf("[CORE LOG] " ##__VA_ARGS__)
#define ME_GFX_LOG(...) printf("[GFX LOG] " ##__VA_ARGS__)

#else
	#define ME_ASSERT(a) {if(!(a)){ }}
	#define ME_ASSERT_M(a, msg, ...) {if(!(a)){}}
	#define ME_CORE_ASSERT(a) {if(!(assertion)){}}
	#define ME_CORE_ASSERT_M(a, msg, ...) {if(!(a)){}}
	#define ME_GFX_ASSERT(a) {if(!(a)){}}}
	#define ME_GFX_ASSERT_M(a, msg, ...) {if(!(a)){}}
	#define ME_LOG(...)
	#define ME_CORE_LOG(...)
	#define ME_GFX_LOG(...)
#endif