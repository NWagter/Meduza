#pragma once

#ifndef NDEBUG
#define VA_ARGS(...) , ##__VA_ARGS__

#define LOG_RED     "\033[31m"      /* Red */
#define LOG_GREEN   "\033[32m"      /* Green */
#define LOG_YELLOW  "\033[33m"      /* Yellow */
#define LOG_BLUE    "\033[34m"      /* Blue */
#define LOG_WHITE   "\033[37m"      /* White */
#define LOG_BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define LOG_BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define LOG_BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define LOG_BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */


#define ME_ASSERT(assertion)\
{\
	if(!(assertion))\
	{\
		std::string assertmsg = std::string("Assertion `"#assertion"` failed in ") + std::string(__FILE__) + " on line: " + std::to_string(__LINE__) + ": ";\
		printf("%s%s \n", LOG_BOLDRED, assertmsg.c_str());\
		std::terminate();\
	}\
}

#define ME_ASSERT_M(assertion, msg, ...)\
{\
	if(!(assertion))\
	{\
		std::string assertmsg = std::string("Assertion `"#assertion"` failed in ") + std::string(__FILE__) + " on line: " + std::to_string(__LINE__) + ": ";\
		printf("%s%s \n", LOG_BOLDRED, assertmsg.c_str());\
		std::terminate();\
	}\
}

#define ME_CORE_ASSERT(assertion)\
{\
	if(!(assertion))\
	{\
		std::string assertmsg = std::string("Assertion `"#assertion"` failed in ") + std::string(__FILE__) + " on line: " + std::to_string(__LINE__) + ": ";\
		printf("%s[CORE] %s \n", LOG_BOLDRED, assertmsg.c_str());\
		std::terminate();\
	}\
}
#define ME_CORE_ASSERT_M(assertion, msg, ...)\
{\
	if(!(assertion))\
	{\
		std::string assertmsg = std::string("Assertion `"#assertion"` failed in ") + std::string(__FILE__) + " on line: " + std::to_string(__LINE__) + ": ";\
		printf("%s[CORE] %s \n%s \n", LOG_BOLDRED, msg, assertmsg.c_str());\
		std::terminate();\
	}\
}

#define ME_GAME_ASSERT(assertion)\
{\
	if(!(assertion))\
	{\
		std::string assertmsg = std::string("Assertion `"#assertion"` failed in ") + std::string(__FILE__) + " on line: " + std::to_string(__LINE__) + ": ";\
		printf("%s[GAME] %s \n", LOG_BOLDRED, assertmsg.c_str());\
		std::terminate();\
	}\
}

#define ME_GAME_ASSERT_M(assertion, msg, ...)\
{\
	if(!(assertion))\
	{\
		std::string assertmsg = std::string("Assertion `"#assertion"` failed in ") + std::string(__FILE__) + " on line: " + std::to_string(__LINE__) + ": ";\
		printf("%s[GAME] %s \n", LOG_BOLDRED, assertmsg.c_str());\
		std::terminate();\
	}\
}

#define ME_GFX_ASSERT(assertion)\
{\
	if(!(assertion))\
	{\
		std::string assertmsg = std::string("Assertion `"#assertion"` failed in ") + std::string(__FILE__) + " on line: " + std::to_string(__LINE__) + ": ";\
		printf("%s[GFX] %s \n", LOG_BOLDRED, assertmsg.c_str());\
		std::terminate();\
	}\
}

#define ME_GFX_ASSERT_M(assertion, msg, ...)\
{\
	if(!(assertion))\
	{\
		std::string assertmsg = std::string("Assertion `"#assertion"` failed in ") + std::string(__FILE__) + " on line: " + std::to_string(__LINE__) + ": ";\
		printf("%s[GFX] %s \n%s", LOG_BOLDRED, msg, assertmsg.c_str());\
		std::terminate();\
	}\
}

#define ME_LUA_ASSERT(assertion)\
{\
	if(!(assertion))\
	{\
		std::string assertmsg = std::string("Assertion `"#assertion"` failed in ") + std::string(__FILE__) + " on line: " + std::to_string(__LINE__) + ": ";\
		printf("%s[LUA] %s \n", LOG_BOLDRED, assertmsg.c_str());\
		std::terminate();\
	}\
}

#define ME_LUA_ASSERT_M(assertion, msg, ...)\
{\
	if(!(assertion))\
	{\
		std::string assertmsg = std::string("Assertion `"#assertion"` failed in ") + std::string(__FILE__) + " on line: " + std::to_string(__LINE__) + ": ";\
		printf("%s[LUA] %s \n%s", LOG_BOLDRED, msg, assertmsg.c_str());\
		std::terminate();\
	}\
}

#define ME_LOG(...) printf("%s[Log] ", LOG_WHITE); printf(__VA_ARGS__)
#define ME_WARNING(...) printf("%s[WARNING] ", LOG_YELLOW);  printf(__VA_ARGS__)
#define ME_ERROR(...) printf("%s[ERROR] ", LOG_RED);  printf(__VA_ARGS__)

#define ME_CORE_LOG(...)printf("%s[CORE Log] ", LOG_WHITE);  printf(__VA_ARGS__)
#define ME_CORE_WARNING(...) printf("%s[WARNING CORE] ", LOG_YELLOW);  printf(__VA_ARGS__)
#define ME_CORE_ERROR(...) printf("%s[ERROR CORE] ", LOG_RED);  printf(__VA_ARGS__)

#define ME_GAME_LOG(...) printf("%s[GAME Log] ", LOG_WHITE);  printf(__VA_ARGS__)
#define ME_GAME_WARNING(...) printf("%s[WARNING GAME] ", LOG_YELLOW);  printf(__VA_ARGS__)
#define ME_GAME_ERROR(...) printf("%s[ERROR GAME] ", LOG_RED);  printf(__VA_ARGS__)

#define ME_GFX_LOG(...) printf("%s[GFX Log] ", LOG_WHITE);  printf(__VA_ARGS__)
#define ME_GFX_WARNING(...) printf("%s[WARNING GFX] ", LOG_YELLOW);  printf(__VA_ARGS__)
#define ME_GFX_ERROR(...) printf("%s[ERROR GFX] ", LOG_RED);  printf(__VA_ARGS__)

#define ME_LUA_LOG(...) printf("%s[LUA Log] ", LOG_WHITE);  printf(__VA_ARGS__)
#define ME_LUA_WARNING(...) printf("%s[WARNING LUA] ", LOG_YELLOW);  printf(__VA_ARGS__)
#define ME_LUA_ERROR(...) printf("%s[ERROR LUA] ", LOG_RED);  printf(__VA_ARGS__)

#else
	#define ME_ASSERT(a) {if(!(a)){ }}
	#define ME_ASSERT_M(a, msg, ...) {if(!(a)){}}
	#define ME_CORE_ASSERT(a) {if(!(assertion)){}}
	#define ME_CORE_ASSERT_M(a, msg, ...) {if(!(a)){}}
	#define ME_GAME_ASSERT(a) {if(!(a)){ }}
	#define ME_GAME_ASSERT_M(a, msg, ...) {if(!(a)){}}
	#define ME_GFX_ASSERT(a) {if(!(a)){}}}
	#define ME_GFX_ASSERT_M(a, msg, ...) {if(!(a)){}}
	#define ME_LUA_ASSERT(a) {if(!(a)){}}}
	#define ME_LUA_ASSERT_M(a, msg, ...) {if(!(a)){}}

	#define ME_LOG(...)
	#define ME_WARNING(...)
	#define ME_ERROR(...)

	#define ME_CORE_LOG(...)
	#define ME_CORE_WARNING(...)
	#define ME_CORE_ERROR(...)

	#define ME_GAME_LOG(...)
	#define ME_GAME_WARNING(...)
	#define ME_GAME_ERROR(...)

	#define ME_GFX_LOG(...)
	#define ME_GFX_WARNING(...)
	#define ME_GFX_ERROR(...)

	#define ME_LUA_LOG(...)
	#define ME_LUA_WARNING(...)
	#define ME_LUA_ERROR(...)
#endif