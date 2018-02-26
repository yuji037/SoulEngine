#ifndef T2k_SOUND_H
#define T2k_SOUND_H

#include <time.h>
#include "DXUT.h"
#include "SDKsound.h"
#include "t2k_support.h"

namespace t2k {

	class Se {
	public :
		static constexpr int max = 20 ;
		Se(){
			for( int i = 0 ; i < max ; ++i ) p_sound[ i ] = nullptr ;
		}
		~Se() {
			for( int i = 0 ; i < max ; ++i ) SAFE_DELETE(p_sound[i]) ;
		}
		clock_t not_play_time ;
		CSound* p_sound[max] ;

		inline void play() {
			not_play_time = clock() ;
			for( int i = 0 ; i < max ; ++i ) {
				if( p_sound[ i ]->IsSoundPlaying() ) continue ;
				p_sound[ i ]->Play() ;
				return ;
			}
		}
	};

}

#endif

