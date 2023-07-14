#include "wx/wx.h"
#include "Main.hpp"

class App : public wxApp{

public:
	App();
	~App();
	virtual bool OnInit();
private:
	Main* frame1 = nullptr;
};
