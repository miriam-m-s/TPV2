
 #pragma once
 #include "../ecs/Component.h"
 #include "../sdlutils/SDLUtils.h"

class Transform;
class Texture;

 struct FramedImage : ecs::Component {
 public:

 	__CMPID_DECL__(ecs::_FRAMEDIMAGE)


    FramedImage(Texture* tex, int row, int column): frametime(50), tex_(tex), row_(row), column_(column) {
        m_clip.w = tex_->width() / column;
        m_clip.h = tex_->height() / row;
        initime = sdlutils().currRealTime();
    }

    virtual ~FramedImage() {};

 	void setTexture(Texture* tex) {
 		tex_ = tex;
 	}

 	void select_sprite(int x, int y){
        m_clip.x = x * m_clip.w;
        m_clip.y = y * m_clip.h;
     }

    void draw() {

        select_sprite(i, j);

        if (sdlutils().currRealTime() - initime >= 50) {
         	if (i < column_-1)i++;
         	else {
         		i = 0;
         		j++;
         	}
         	if (j >= row_)j = 0;
         	initime = sdlutils().currRealTime();
        }
    }


 	Texture* tex_;

    float frametime;
 	int row_;
 	int column_;
 	SDL_Rect m_clip;
 	int i=0;
 	int j=0;
 	float initime = 0;
	
 };
 
