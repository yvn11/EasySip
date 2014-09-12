#include <thread>
#include <chrono>

//struct f_op
//{
//	void operator()() const {
//		std::cout << __PRETTY_FUNCTION__ << '\n';
//	}
//};

template<typename Dua, typename Func>
//struct timer//(Dua const & d, Func const & f)
//{
void	timer(Dua const & d, Func const & f)
	{
	std::thread([d, f](){
		std::chrono::milliseconds dur(d);
		std::this_thread::sleep_for(dur);
		f();
	}).detach();
	}
//};

