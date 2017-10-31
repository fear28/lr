#ifndef _LEARNING_HPP_
#define _LEARNING_HPP_
#include <condition_variable>


namespace ml{
class Barrier
{
private:
    std::mutex _mutex;
    std::condition_variable _cv;
    std::size_t _count;
    std::size_t _count2;
    std::size_t _count_org;
    bool tryb;
public:
    explicit Barrier(std::size_t count) : _count{count}, _count_org{count} {tryb=false; }
    void Wait()
    {
		if(!tryb){
			std::unique_lock<std::mutex> lock{_mutex};
			if (--_count == 0) {
				_cv.notify_all();
				_count2=_count_org;
				tryb=true;
			} else {
				_cv.wait(lock, [this] { return _count == 0; });
			}
		}else{
			std::unique_lock<std::mutex> lock{_mutex};
			if (--_count2 == 0) {
				_cv.notify_all();
				_count=_count_org;
				tryb=false;
			} else {
				_cv.wait(lock, [this] { return _count2 == 0; });
			}
			
		}
    }
};

double multi_uczenie(int it, double** x,int* l,int lp, int ww, double alfa,double* w, double eps, int thread, bool dbg);
void multi_thread_uczenie(int it, double** x,int* l,int lp, int ww, double alfa,double* w, double eps,int pocz1,int kon1,int pocz2,int kon2,Barrier* bar,double* b,double* osg,int id,std::mutex* mutex,bool dbg);
double uczenie(int it, double** x,int* l,int lp, int ww, double alfa,double* w, double eps,bool dbg);
}
#endif //_LEARNING_HPP_
