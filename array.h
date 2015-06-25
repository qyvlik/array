#ifndef ARRAY
#define ARRAY

#include <list>
#include <vector>

using std::list;
using std::vector;

template<typename T>
class Array
{
public:
    Array(){}

    explicit Array(const Array& other):
        m_data(other.m_data)
    {
        this->fetch();
    }

    Array& operator =(const Array& other){
        this->data() = other.data();
        this->fetch();
        return *this;
    }

    virtual ~Array(){}

    class Iterator{
        Array& data;
        size_t index;
    public:
        Iterator(Array& d, size_t i):
            data(d), index(i)
        {
        }

        bool operator == (const Iterator& rhs) const{
            return (rhs.index == this->index && (&this->data == &rhs.data));
        }

        bool operator != (const Iterator& rhs) const{
            return !(rhs.index == this->index && (&this->data == &rhs.data));
        }

        T& operator * () {
            return this->data.at( (this->data.length() <= index ? data.length()-1: index) );
        }

        Iterator& operator[](size_t pos){
            this->index = (pos > data.size()) ? data.size() : pos;
            return *this;
        }

        Iterator& operator ++(int) {
            if(this->data.length()-1 >=  index )
                this->index++;
            return *this;
        }

        Iterator& operator ++() {
            if(this->data.length()-1 >= index )
                ++this->index;
            return *this;
        }

        Iterator& operator --(int) {
            if(index > 1)
                this->index--;
            return *this;
        }

        Iterator& operator --() {
            if(index > 1)
                --this->index;
            return *this;
        }

    };

    Iterator begin() { return Iterator(*this, 0); }

    Iterator end() { return Iterator(*this, this->length()); }

    void append(const T& value){
        this->data().push_back(value);
        this->index().push_back(&(this->last()));
    }

    void prepend(const T& value){
        this->data().push_front(value);
        this->index().push_front(&(this->first()));
    }

    void insert(size_t index, const T & value){
        auto i = this->data().insert(index, value);
        this->index().insert(index,&(*i));
    }

    T& first() { return this->data().front(); }

    const T& first() const{ return this->data().front(); }

    T& last() { return this->data().back(); }
    const T& last()const{ return this->data().back(); }

    T& at(size_t index) {return *(this->index().at(index)); }
    const T& at(size_t index) const {return *(this->index().at(index)); }

    T& operator[](size_t index){ return *(this->index().operator [](index));}
    const T& operator[](size_t index) const {return *(this->index().operator [](index)); }

    size_t length() const {return this->data().size();}
    size_t size() const { return this->data().size(); }

    bool isEmpty() const { return this->data().empty(); }

    bool operator == (const Array& rhs) const {
        return this->data() == rhs.data();
    }

    void clear(){
        this->data().clear();
        this->index().clear();
    }

    void remove(const T& value){
        auto begin =  this->index().begin();
        auto end = this->index().end();
        while(begin != end){

            /* operator == function */
            if(*(*begin) == value){
                this->index().erase(begin);
                break;
            }
            begin++;
        }
        this->data().remove(value);
    }

protected:
    std::list<T>& data(){ return this->m_data; }

    const std::list<T>& data()const{ return this->m_data; }

    std::vector<T*>& index(){ return this->m_index; }

    const std::vector<T*>& index() const { return this->m_index; }

    void fetch(){
        auto iter = this->data().begin();
        auto end = this->data().end();
        this->index().clear();
        this->index().resize(this->data().size());
        auto Iiter = this->index().begin();
        while(iter != end){
            (*Iiter) = &(*iter);
            Iiter++;
            iter++;
        }
    }

private:
    std::list<T> m_data;
    std::vector<T*> m_index;
};

#endif // ARRAY

