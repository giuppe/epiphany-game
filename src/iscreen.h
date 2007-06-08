#ifndef ISCREEN_H_
#define ISCREEN_H_

class IScreen{
public:
	//virtual void init(unsigned int resolution_x, unsigned int resolution_y, unsigned int level_size_x, unsigned int level_size_y, unsigned int cell_size) =0;
		
	//virtual void put(Sprite& sprite, unsigned int pos_x, unsigned int pos_y) =0;

	virtual void put(Sprite& sprite) =0;
		
	//void put(Entity* entity);
	
	virtual unsigned int get_screen_size_x() =0;
	
	virtual unsigned int get_screen_size_y() =0;
	
	virtual void init(unsigned int resolution_x, unsigned int resolution_y, unsigned int level_size_x, unsigned int level_size_y, unsigned int cell_size) =0;
	
	virtual void set_cell_size(unsigned int cell_size) =0;
	
	virtual void set_window_center(int cell_x, int cell_y) =0;
	
	virtual ~IScreen(){}
	
	virtual void clear() = 0;
	
	virtual void flip_display() = 0;
	
};

#endif /*ISCREEN_H_*/
