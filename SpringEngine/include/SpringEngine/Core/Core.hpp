#pragma once

#ifdef SE_PLATEFORM_WINDOWS
	#ifdef SE_BUILD_DLL
		#define SE_API __declspec(dllexport)
	#else
		#define SE_API __declspec(dllimport)
	#endif
#else
	#error SpringEngine should only run on a Windows machine
#endif

#define SE_CLASS(...)
#define SE_PROPERTY(...)

#if defined SE_DEBUG || !defined SE_DBUG
#define VK_VERBOSE
#endif

#ifdef VK_VERBOSE
#define SE_VK_DEBUG(WHAT) WHAT
#else
#define SE_VK_DEBUG(...) do { } while(0)
#endif

#ifdef SE_DEBUG
#define VK_CALL(WHAT) try { WHAT; } catch (const vk::SystemError& err) { SE_CORE_CRITICAL("{}", err.what());	  };
#else
#define VK_CALL(WHAT) WHAT;
#endif
#define SE_ENUMERATE(__array, __member) for (auto component : __array) { SE_CORE_TRACE("{}", component.__member); };


namespace SE
{
	template <typename T>
	using Shared = std::shared_ptr<T>;

	template <typename T, typename ... Args>
	constexpr Shared<T> makeShared(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}