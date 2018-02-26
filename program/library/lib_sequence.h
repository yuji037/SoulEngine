#pragma once

#include <assert.h>
#include <float.h>

template<class T> class CSequence {
public :
    typedef void (T::*Sequence)(float) ;

    CSequence():
    _time(0),
    _prev(nullptr),
    _now(nullptr),
    _next(nullptr)
    {}
    ~CSequence(){}

    inline void run( T* obj, float delta ){
        if( !_now && !_next ) return ;
        if( _next ){
            _prev = _now ;
            _now = _next ;
            _next = nullptr ;
            _time = 0.0f ;
        }
        (obj->*_now)( delta ) ;
        _time += delta ;
    }

    inline void change( Sequence sequence = nullptr ){
        if( !sequence && !_next ){
            assert(0) ;
        }
        _next = sequence ;
        _time = 0.0f ;
    }

    inline Sequence getSequence(){ return _now ; }
    inline float getTime(){ return _time ; }
    inline bool isInitialize() { return (_time < FLT_EPSILON) ? true : false; }

private :
    float _time ;
    Sequence _prev ;
    Sequence _now ;
    Sequence _next ;

} ;

