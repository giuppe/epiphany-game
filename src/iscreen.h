#ifndef ISCREEN_H_
#define ISCREEN_H_

class IScreen{
public:
	//virtual void init(Uint32 resolution_x, Uint32 resolution_y, Uint32 level_size_x, Uint32 level_size_y, Uint32 cell_size) =0;
		
	//virtual void put(Sprite& sprite, Uint32 pos_x, Uint32 pos_y) =0;

	virtual void put(Sprite& sprite) =0;
		
	//void put(Entity* entity);
	
	virtual Uint32 get_screen_size_x() =0;
	
	virtual Uint32 get_screen_size_y() =0;
	
	virtual void init(Uint32 resolution_x, Uint32 resolution_y, Uint32 level_size_x, Uint32 level_size_y, Uint32 cell_size) =0;
	
	virtual void set_cell_size(Uint32 cell_size) =0;
	
	virtual void set_window_center(int cell_x, int cell_y) =0;
	
	virtual ~IScreen(){}
	
	virtual void clear() = 0;
	
	virtual void flip_display() = 0;
	
};

#endif /*ISCREEN_H_*/
