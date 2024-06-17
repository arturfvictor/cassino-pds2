#ifndef GENERICDAO
#define GENERICDAO

#include <string>
#include <vector>

using std::string;
using std::vector;

template <typename T>
class GenericDao {
    public:
        virtual vector<T*> list() = 0;
        virtual T* find(int id) = 0;
        virtual T* save(T* object) = 0;
        virtual T* remove(int id) = 0;
    protected:
        virtual int generateUniqueId() = 0;
};

#endif